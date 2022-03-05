#include <stdio.h>
#include <opencv2/opencv.hpp>

#ifndef MORPHOLOGICAL_H
#define MORPHOLOGICAL_H

cv::Mat square5x5 = cv::Mat::ones(5,5, CV_8U);
uchar diamond5[25] = {0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0};
cv::Mat diamond5x5(5, 5, CV_8U, diamond5);
uchar cross5[25] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0};
cv::Mat cross5x5(5, 5, CV_8U, cross5);
cv::Mat square3x3 = cv::Mat::ones(3, 3, CV_8U);
uchar cross3[9] = {0, 1, 0, 1, 1, 1, 0, 1, 0};
cv::Mat cross3x3(3, 3, CV_8U, cross3);
int erosion(cv::Mat &src, cv::Mat &dst, cv::Mat &str);
int dilation(cv::Mat &src, cv::Mat &dst, cv::Mat &str);
int open(cv::Mat &src, cv::Mat &dst, cv::Mat &str);
int close(cv::Mat &src, cv::Mat &dst, cv::Mat &str);

#endif