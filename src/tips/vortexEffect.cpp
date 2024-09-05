#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
// 文心一言给的代码，错误，不是漩涡，更类似旋转
cv::Mat createVortexEffect(const cv::Mat& src, double strength) {
	cv::Mat dst = cv::Mat::zeros(src.size(), src.type());

	int centerX = src.cols / 2;
	int centerY = src.rows / 2;

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			double dx = x - centerX;
			double dy = y - centerY;
			double distance = sqrt(dx * dx + dy * dy);
			if (distance == 0) continue;

			// 计算漩涡角度，根据距离调整
			double angle = atan2(dy, dx) + strength * distance / std::max(src.cols, src.rows);

			// 计算新的x，y位置
			int newX = centerX + static_cast<int>(cos(angle) * distance);
			int newY = centerY + static_cast<int>(sin(angle) * distance);

			// 边界检查
			if (newX >= 0 && newX < src.cols && newY >= 0 && newY < src.rows) {
				dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(newY, newX);
			}
		}
	}

	return dst;
}

// 通义千问给的代码, 差不多是对的，但是不够扭曲,在这个上面做了点扩展
cv::Mat tongyiVortexEffect(const cv::Mat& src, double strength, std::vector<std::pair<float,float>> centerOffset) {

	cv::Mat dst = src.clone();

	for (auto offset : centerOffset) {

		int cx = src.cols * offset.first;//src.cols / 2;
		int cy = src.rows * offset.second;//src.rows / 2;

		float radius = 50;// std::min(cx, cy) - 10;
		cv::Mat map_x, map_y;
		map_x.create(src.size(), CV_32FC1);
		map_y.create(src.size(), CV_32FC1);
		//float strength = 1.0f;
		int sy = std::max(cy - 50, 0);
		int ey = std::min(cy + 50, src.rows);
		int sx = std::max(cx - 50, 0);
		int ex = std::min(cx + 50, src.cols);

		for (int y = 0; y < src.rows; y++) {
			for (int x = 0; x < src.cols; x++) {
				map_x.at<float>(y, x) = x;
				map_y.at<float>(y, x) = y;
			}
		}

		for (int y = sy; y < ey; y++) {
			for (int x = sx; x < ex; x++) {
				float dx = x - cx;
				float dy = y - cy;
				float dist = sqrt(dx * dx + dy * dy);
				if (dist < radius) {
					float theta = atan2(dy, dx);
					float newX = cx + cos(theta + strength * (radius - dist)) * dist;
					float newY = cy + sin(theta + strength * (radius - dist)) * dist;
					map_x.at<float>(y, x) = newX;
					map_y.at<float>(y, x) = newY;
				}
				else {
					map_x.at<float>(y, x) = x;
					map_y.at<float>(y, x) = y;
				}
			}
		}
		cv::remap(dst, dst, map_x, map_y, cv::INTER_LINEAR);
	}

	return dst;
}

#include <random>
int getRandomInRange(int a, int b) {
	// 确保a <= b
	if (a > b) {
		std::swap(a, b);
	}

	// 使用随机数引擎和分布来生成随机数
	std::random_device rd; // 用于获取随机数种子
	std::mt19937 gen(rd()); // 以随机数种子初始化Mersenne Twister生成器
	std::uniform_int_distribution<> dis(a, b); // 定义均匀分布范围

	// 生成并返回随机数
	return dis(gen);
}

int main() {

	cv::Mat src = cv::imread("1.bmp");
	cv::resize(src, src, cv::Size(320,256));
	double strength = 0.03;// 0.03 是比较适合的强度 ， + 是逆时针 - 是顺时针
	//cv::Mat vortex = createVortexEffect(src, strength);

	std::vector<std::pair<float, float>> centerOffset;

	for (int index = 0; index < 10; index++) {
		centerOffset.emplace_back(getRandomInRange(0,100) /100.0f, getRandomInRange(0, 100) /100.0f);
	}

	//centerOffset.emplace_back(0.5, 0.5);

	while (true) {
		//strength += 0.1;
		cv::Mat vortex = tongyiVortexEffect(src, strength,centerOffset);
		cv::imshow("vortex", vortex);
		cv::waitKey(100);
	}
	return 0;
}