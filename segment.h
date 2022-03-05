
#include <stdio.h>
#include <opencv2/opencv.hpp>

#ifndef SEGMENT_H
#define SEGMENT_H

using namespace cv;

int segment(Mat &src, Mat &dst, int n_regions);

#endif