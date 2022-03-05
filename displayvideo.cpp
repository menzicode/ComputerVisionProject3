#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "threshold.h"
#include "morphological.h"

int main(int argc, char *argv[]) {
        cv::VideoCapture *capdev;

        // open the video device
        capdev = new cv::VideoCapture(0);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }   

        // get some properties of the image
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                       (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);

        cv::namedWindow("Video", 1); // identifies a window


        cv::Mat frame;
        
        for(;;) {
                *capdev >> frame; // get a new frame from the camera, treat as a stream
                if( frame.empty() ) {
                  printf("frame is empty\n");
                  break;
                }                
                cv::imshow("Video", frame);

                // see if there is a waiting keystroke
                char key = cv::waitKey(10);
                if (key == 't') {
                    int thresh = 110;
                    // std::cout << "\nEnter threshold: ";
                    // std::cin >> thresh;
                    for (;;) {
                        *capdev >> frame;
                        cv::Mat tframe = cv::Mat::zeros(frame.rows, frame.cols, CV_8UC3);
                        threshold(frame, tframe, thresh);
                        cv::imshow("Video", tframe);
                        char key = cv::waitKey(10);
                        if( key == 's') {
                            cv::imwrite("threshold.jpg", tframe);
                            cv::imwrite("thresholdOG.jpg", frame);
                        }
                        if( key == 'q') {
                            break;
                        }
                        if ( key == 'e') {
                            cv::Mat s5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat d5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat s3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            erosion(tframe, s5frame, square5x5);
                            erosion(tframe, d5frame, diamond5x5);
                            erosion(tframe, c5frame, cross5x5);
                            erosion(tframe, c3frame, cross3x3);
                            erosion(tframe, s3frame, square3x3);
                            cv::namedWindow("Erosion S5", 1); 
                            cv::namedWindow("Erosion D5", 1);
                            cv::namedWindow("Erosion C5", 1);
                            cv::namedWindow("Erosion S5", 1);
                            cv::namedWindow("Erosion C3", 1);
                            cv::imshow("Erosion S5", s5frame);
                            cv::imshow("Erosion D5", d5frame);
                            cv::imshow("Erosion C5", c5frame);
                            cv::imshow("Erosion S3", s3frame);
                            cv::imshow("Erosion C3", c3frame);
                            cv::namedWindow("Threshold", 1);
                            cv::imshow("Threshold", tframe);
                        }
                        if ( key == 'd') {
                            cv::Mat s5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat d5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat s3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            dilation(tframe, s5frame, square5x5);
                            dilation(tframe, d5frame, diamond5x5);
                            dilation(tframe, c5frame, cross5x5);
                            dilation(tframe, c3frame, cross3x3);
                            dilation(tframe, s3frame, square3x3);
                            cv::namedWindow("Dilation S5", 1); 
                            cv::namedWindow("Dilation D5", 1);
                            cv::namedWindow("Dilation C5", 1);
                            cv::namedWindow("Dilation S5", 1);
                            cv::namedWindow("Dilation C3", 1);
                            cv::imshow("Dilation S5", s5frame);
                            cv::imshow("Dilation D5", d5frame);
                            cv::imshow("Dilation C5", c5frame);
                            cv::imshow("Dilation S3", s3frame);
                            cv::imshow("Dilation C3", c3frame);
                            cv::namedWindow("Threshold", 1);
                            cv::imshow("Threshold", tframe);
                        }
                        if ( key == 'o') {
                            cv::Mat s5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat d5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat s3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            open(tframe, s5frame, square5x5);
                            open(tframe, d5frame, diamond5x5);
                            open(tframe, c5frame, cross5x5);
                            open(tframe, c3frame, cross3x3);
                            open(tframe, s3frame, square3x3);
                            cv::namedWindow("Open S5", 1); 
                            cv::namedWindow("Open D5", 1);
                            cv::namedWindow("Open C5", 1);
                            cv::namedWindow("Open S5", 1);
                            cv::namedWindow("Open C3", 1);
                            cv::imshow("Open S5", s5frame);
                            cv::imshow("Open D5", d5frame);
                            cv::imshow("Open C5", c5frame);
                            cv::imshow("Open S3", s3frame);
                            cv::imshow("Open C3", c3frame);
                            cv::namedWindow("Threshold", 1);
                            cv::imshow("Threshold", tframe);
                        }
                        if ( key == 'c') {
                            cv::Mat s5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat d5frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat c3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            cv::Mat s3frame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
                            close(tframe, s5frame, square5x5);
                            close(tframe, d5frame, diamond5x5);
                            close(tframe, c5frame, cross5x5);
                            close(tframe, c3frame, cross3x3);
                            close(tframe, s3frame, square3x3);
                            cv::namedWindow("Close S5", 1); 
                            cv::namedWindow("Close D5", 1);
                            cv::namedWindow("Close C5", 1);
                            cv::namedWindow("Close S5", 1);
                            cv::namedWindow("Close C3", 1);
                            cv::imshow("Close S5", s5frame);
                            cv::imshow("Close D5", d5frame);
                            cv::imshow("Close C5", c5frame);
                            cv::imshow("Close S3", s3frame);
                            cv::imshow("Close C3", c3frame);
                            cv::namedWindow("Threshold", 1);
                            cv::imshow("Threshold", tframe);
                        }                        
                    }
                }
                if( key == 'q') {
                    break;
                }
        }
        
}