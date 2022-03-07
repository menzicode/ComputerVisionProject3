#include <stdio.h>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace cv;

std::vector<std::vector<double>> getMoments(Mat &src, int n_labels) {
    // Mat greysrc;
    // cvtColor(src, greysrc, COLOR_BGR2GRAY);
    std::vector<std::vector<Point>> contours;
    findContours(src, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
    std::vector<Moments> all_moments(contours.size());
    for (int i = 0; i < contours.size(); i++) {
        all_moments[i] = moments(contours[i]);
    }
    std::vector<std::vector<double>> features;
    for (int i = 0; i < all_moments.size(); i++) {
        Moments mom = all_moments[i];
        double centroidX = mom.m10 / mom.m00; 
        double centroidY = mom.m01 / mom.m00;
        double muA = mom.mu20 / mom.m00;
        double muB = mom.mu02 / mom.m00;
        double muC = mom.mu11 / mom.m00;
        //Mat cov(2, 2, CV_16F, covv);
        double orient = atan((2 * muC) / (muA - muB));
        std::vector<double> objectfeatures;
        objectfeatures.push_back(mom.m00);
        objectfeatures.push_back(centroidX);
        objectfeatures.push_back(centroidY);
        objectfeatures.push_back(orient);
        features.push_back(objectfeatures);
        //printf("%i %i %f %f %f\n", i, all_moments.size(), orient, centroidX, centroidY);
    }
    sort(features.begin(), features.end());
    return features;
}

