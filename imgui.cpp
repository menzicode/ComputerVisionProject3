#include <stdio.h>
#include <opencv2/opencv.hpp>
#define CVUI_IMPLEMENTATION
#include "cvui.h"
#include "threshold.h"
#include "morphological.h"
#include "segment.h"
#include "features.h"
#define WINDOW_NAME "Control"

int main(int argc, char** argv )
{
    cv::Mat frame = cv::Mat(200, 500, CV_8UC3);
    cv::Mat image;
    image = cv::imread("C:/Users/mhmen/Pictures/CS/ComputerVision/corkscrew2.jpg");
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    cv::namedWindow(WINDOW_NAME);
    cvui::init(WINDOW_NAME);

    int thresh = 0;
    int n_regions = 1;
    int grass_thresh = 2; 
    bool thresholded=false;
    bool ero=false;
    bool dil=false;
    bool op=false;
    bool cl=false;
    bool seg=false;
    bool gras_g=false;
    bool gras_s=false;

    cv::Mat tframe = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);
    cv::Mat eframe = cv::Mat::ones(image.rows, image.cols, CV_8U);
    cv::Mat gframe = cv::Mat::ones(image.rows, image.cols, CV_8U);
    imshow("Display Image", image);
    while(true) {
        cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE );
        frame = cv::Scalar(49, 52, 49);
        if(cvui::checkbox(frame, 25, 40, "Erosion", &ero)){
            dil=false;
            op=false;
            cl=false;
        }
        if(cvui::checkbox(frame, 25, 60, "Dilation", &dil)){
            ero=false;
            op=false;
            cl=false;
        }
        if(cvui::checkbox(frame, 25, 80, "Open", &op)){
            ero=false;
            dil=false;
            cl=false;
        }
        if(cvui::checkbox(frame, 25, 100, "Close", &cl)){
            ero=false;
            op=false;
            dil=false; 
        }
        if(cvui::checkbox(frame, 25, 120, "Grassfire grow", &gras_g)) {

        }
        if(cvui::checkbox(frame, 25, 140, "Grassfire shrink", &gras_s)) {

        }
        if(cvui::checkbox(frame, 25, 169, "Segment",  &seg)) {

        }
        if(cvui::trackbar(frame, 150, 10, 200, &thresh, 0, 255)){
            ero=false;
            op=false;
            dil=false; 
            cl=false;
            gras_g=false;
            gras_s=false;
            cv::Mat fframe = cv::Mat::zeros(image.rows, image.cols, CV_8UC3);     
            threshold(image, fframe, thresh);
            fframe.convertTo(tframe, CV_8U, -1, 255);
            cv::imshow("Display Image", tframe);
        }
        if(cvui::trackbar(frame, 150, 140, 200, &grass_thresh, 2, 100)) {
            
        }
        if(cvui::trackbar(frame, 150, 60, 100, &n_regions, 0, 6)) {
            
        }
        if (ero) {
            erosion(tframe, eframe, square5x5);
            if (seg) {
                cv::Mat sframe = cv::Mat::ones(image.rows, image.cols, CV_8U);
                segment(eframe, sframe, n_regions);
                cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe);
            }
            else {
                cv::imshow("Display Image", eframe);
            }
        }
        if (dil) {
            dilation(tframe, eframe, square5x5);
            if (seg) {
                cv::Mat sframe = cv::Mat::zeros(image.rows, image.cols, CV_8U);
                segment(eframe, sframe, n_regions);
                cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe);
            }
            else {
                cv::imshow("Display Image", eframe);
            }
        }
        if (op) {
            open(tframe, eframe, square5x5);
            if (seg) {
                cv::Mat sframe = cv::Mat::zeros(image.rows, image.cols, CV_8U);
                segment(eframe, sframe, n_regions);
                cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe);
            }
            else {
                cv::imshow("Display Image", eframe);
            }
        }
        if (cl) {
            close(tframe, eframe, square5x5);
            if (seg) {
                cv::Mat sframe = cv::Mat::zeros(image.rows, image.cols, CV_8U);
                segment(eframe, sframe, n_regions);
                //cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe); 
            }
            else {
                cv::imshow("Display Image", eframe);
            }
        }
        if (gras_g) {
            if (!op && !cl && !ero && !dil && !gras_s) {
                grassfire_grow(tframe, gframe, grass_thresh);
            }
            else if (!gras_s) {
                grassfire_grow(eframe, gframe, grass_thresh);
            }
            if (seg) {
                cv::Mat sframe = cv::Mat::zeros(image.rows, image.cols, CV_8U);
                segment(eframe, sframe, n_regions);
                //cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe); 
            }
            else {
                cv::imshow("Display Image", gframe);
            }
        }
        if (gras_s) {
            if (!op && !cl && !ero && !dil && !gras_g) {
                grassfire_shrink(tframe, gframe, grass_thresh);
            }
            else if (!gras_g) {
                grassfire_shrink(eframe, gframe, grass_thresh);
            }
            else if (gras_g) {
                grassfire_shrink(gframe, eframe, grass_thresh);
            }
            if (seg && gras_g) {
                cv::Mat sframe = cv::Mat::zeros(image.rows, image.cols, CV_8U);
                segment(eframe, sframe, n_regions);
                //cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe); 
            }
            else if (seg && !gras_g) {
                cv::Mat sframe = cv::Mat::zeros(image.rows, image.cols, CV_8U);
                segment(gframe, sframe, n_regions);
                //cvtColor(sframe, sframe, COLOR_BGR2GRAY);
                getMoments(sframe);
                cv::imshow("Display Image", sframe);             }
            else if (!gras_g) {
                cv::imshow("Display Image", gframe);
            }
            else {
                cv::imshow("Display Image", eframe);
            }
        }
        cvui::update();
        cv::imshow(WINDOW_NAME, frame);
    if (cv::waitKey(30) == 27) {
      break;
    }

    }
    return 0;
}


