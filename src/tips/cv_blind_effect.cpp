#include <iostream>
#include <opencv2/opencv.hpp>

enum Direction :uint8_t {
    left2right = 0x00,
    right2left = 0x01,
    top2bottom = 0x02,
    bottom2top = 0x03
};

void applyBlindEffect(const cv::Mat &srcImg, int numStrips, Direction direction) {

    int width = srcImg.cols;
    int height = srcImg.rows;

    int stripheight = height / numStrips;
    int stripwidth = width / numStrips;
    cv::Mat canvas = cv::Mat::zeros(cv::Size(width, height), srcImg.type());

    switch(direction) {
        case Direction::top2bottom: {
            for (int curline = 1; curline < stripheight; curline++) {
                for (int index = 0; index < numStrips; index++) {
                    int startRow = index * stripheight;
                    int endRow = std::min(startRow + curline, height);
                    srcImg(cv::Rect(0, startRow, width, endRow - startRow)).copyTo(canvas(cv::Rect(0, startRow, width, endRow - startRow)));
                }
                cv::imshow("blindEffect", canvas);
                cv::waitKey(50);
            }
        }break;
        case Direction::bottom2top: {
            for (int curline = 1; curline < stripheight; curline++) {
                for (int index = 0; index < numStrips; index++) {
                    int startRow = std::min(index * stripheight + stripheight, height);
                    int endRow = std::max(startRow - curline, 0);
                    srcImg(cv::Rect(0, endRow, width, startRow - endRow)).copyTo(canvas(cv::Rect(0, endRow, width, startRow - endRow)));
                }
                cv::imshow("blindEffect", canvas);
                cv::waitKey(50);
            }
        }break;
        case Direction::left2right: {
            for (int curcol = 1; curcol < stripwidth; curcol++) {
                for (int index = 0; index < numStrips; index++) {
                    int startCol = index * stripwidth;
                    int endCol = std::min(startCol + curcol, width);
                    srcImg(cv::Rect(startCol, 0, endCol - startCol, height)).copyTo(canvas(cv::Rect(startCol, 0, endCol - startCol, height)));
                }
                cv::imshow("blindEffect", canvas);
                cv::waitKey(50);
            }
        }break;
        case Direction::right2left: {
            for (int curcol = 1; curcol < stripwidth; curcol++) {
                for (int index = 0; index < numStrips; index++) {
                    int startCol = std::min(index * stripwidth + stripwidth, width);
                    int endCol = std::max(startCol - curcol, 0);
                    srcImg(cv::Rect(endCol, 0, startCol - endCol, height)).copyTo(canvas(cv::Rect(endCol, 0, startCol - endCol, height)));
                }
                cv::imshow("blindEffect", canvas);
                cv::waitKey(50);
            }
        }break;
        default: {

        }break;
    }
}

int main() {

    cv::Mat srcImg = cv::imread("2.bmp");
    cv::resize(srcImg, srcImg, cv::Size(320, 256));

    applyBlindEffect(srcImg,10,Direction::right2left);

    return 0;
}

