#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

    cv::Mat img1 = cv::imread("1.bmp");
    cv::Mat img2 = cv::imread("2.bmp");

    cv::resize(img1, img1, cv::Size(320, 256));
    cv::resize(img2, img2, cv::Size(320, 256));

    double alpha = 0.0;
    double beta = 1.0;
    double gamma = 0;
    bool inOrder{ true };
    while (true) {
        inOrder ? alpha += 0.01 : alpha -= 0.01;
        beta = abs(1.0 - alpha);
        if (alpha > 1.0 || alpha < 0.0) {
            inOrder = !inOrder;
        }

        cv::Mat imgBlend;
        cv::addWeighted(img1, alpha, img2, beta, gamma, imgBlend);

        cv::imshow("blend", imgBlend);
        cv::waitKey(1);
    }
    return 0;
}