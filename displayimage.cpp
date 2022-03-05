#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "threshold.h"
#include "morphological.h"

using namespace cv;

int main(int argc, char** argv )
{
    cv::namedWindow("Morphological S5", 1); 
    cv::namedWindow("Morphological D5", 1);
    cv::namedWindow("Morphological C5", 1);
    cv::namedWindow("Morphological S5", 1);
    cv::namedWindow("Morphological C3", 1);
    Mat image;
    image = imread("C:/Users/mhmen/Pictures/CS/ComputerVision/corkscrew2.jpg");
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    for(;;) {
        namedWindow("Display Image", WINDOW_AUTOSIZE );
        imshow("Display Image", image);
        int thresh = 110;
        cv::Mat tframe = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
        threshold(image, tframe, thresh);
        cv::imshow("Threshold", tframe);
        char key = cv::waitKey(0);
        if( key == 'q') {
                break; 
        }
        if( key == 's') {
                cv::imwrite("threshold.jpg", tframe);
        }
        if ( key == 'e') {
            bool exact = false;
            cv::Mat s5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat d5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat s3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            erosion(tframe, s5frame, square5x5);
            erosion(tframe, d5frame, diamond5x5);
            erosion(tframe, c5frame, cross5x5);
            erosion(tframe, c3frame, cross3x3);
            erosion(tframe, s3frame, square3x3);
            cv::imshow("Morphological S5", s5frame);
            cv::imshow("Morphological D5", d5frame);
            cv::imshow("Morphological C5", c5frame);
            cv::imshow("Morphological S3", s3frame);
            cv::imshow("Morphological C3", c3frame);
        }
        if ( key == 'd') {
            bool exact = false;
            cv::Mat s5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat d5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat s3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            dilation(tframe, s5frame, square5x5);
            dilation(tframe, d5frame, diamond5x5);
            dilation(tframe, c5frame, cross5x5);
            dilation(tframe, c3frame, cross3x3);
            dilation(tframe, s3frame, square3x3);
            cv::imshow("Morphological S5", s5frame);
            cv::imshow("Morphological D5", d5frame);
            cv::imshow("Morphological C5", c5frame);
            cv::imshow("Morphological S3", s3frame);
            cv::imshow("Morphological C3", c3frame);
            cv::namedWindow("Threshold", 1);
            cv::imshow("Threshold", tframe);
        }
        if ( key == 'o') {
            bool e_exact = false;
            bool d_exact = false;
            cv::Mat s5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat d5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat s3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            open(tframe, s5frame, square5x5);
            open(tframe, d5frame, diamond5x5);
            open(tframe, c5frame, cross5x5);
            open(tframe, c3frame, cross3x3);
            open(tframe, s3frame, square3x3);
            cv::imshow("Morphological S5", s5frame);
            cv::imshow("Morphological D5", d5frame);
            cv::imshow("Morphological C5", c5frame);
            cv::imshow("Morphological S3", s3frame);
            cv::imshow("Morphological C3", c3frame);
        }
        if ( key == 'c') {
            bool e_exact = false;
            bool d_exact = false;
            cv::Mat s5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat d5frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat c3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            cv::Mat s3frame = cv::Mat::zeros(image.rows, image.cols, CV_8U);
            close(tframe, s5frame, square5x5);
            close(tframe, d5frame, diamond5x5);
            close(tframe, c5frame, cross5x5);
            close(tframe, c3frame, cross3x3);
            close(tframe, s3frame, square3x3);
            cv::imshow("Morphological S5", s5frame);
            cv::imshow("Morphological D5", d5frame);
            cv::imshow("Morphological C5", c5frame);
            cv::imshow("Morphological S3", s3frame);
            cv::imshow("Morphological C3", c3frame);
        }
    }
    return 0;
}