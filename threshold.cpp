#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int threshold(Mat &src, Mat &dst, int thresh) {
    int adjThreshold;
    if (thresh < 0) {
        adjThreshold = 0;
    }
    else if (thresh >= 256) {
        adjThreshold = 255;
    }
    else {
        adjThreshold = thresh;
    }
    Mat src_f;
    src.convertTo(src_f, CV_32FC3);
    std::vector<Mat> planes(3);
    split(src_f, planes);
    Mat intensity((planes[0] + planes[1] + planes[2]) / 3);
    Mat intensity3c;
    intensity.convertTo(intensity3c, CV_8UC3);
    uchar table[256];
    for (int i = 0; i < adjThreshold; i++) {
        table[i] = 0;
    }
    for (int i = adjThreshold; i < 256; i++) {
        table[i] = 255;
    }
    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.ptr();
    for (int i = 0; i < 256; i++){
        p[i] = table[i];
    }
    std::cout<< lookUpTable.size() << "\n" << table;
    LUT(intensity3c, lookUpTable, dst);

    return 0;
}