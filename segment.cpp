
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int segment(Mat& src, Mat& dst, int n_regions) {
	Mat labels, stats, centroids, thresholdimg, res;

	int n_labels = connectedComponentsWithStats(src, labels, stats, centroids, 8, CV_32S);
    std::vector<std::pair<int, int>> label_area;
    for (int i = 1; i < n_labels; i++) {
        int area = stats.at<int>(Point(4, i));
        std::pair<int, int> l_a = {area, i};
        label_area.push_back(l_a);
    }
    sort(label_area.begin(), label_area.end());
    std::vector<int> valid_labels;
    for (int i = 0; i < n_labels - 1; i++) {
        int min_index = n_labels - 1 - n_regions;
        if (i >= min_index) {
            valid_labels.push_back(label_area[i].second);
        }
    }

	for (int i = 0; i < labels.rows; i++) {
		for (int j = 0; j < labels.cols; j++) {
            if (std::find(valid_labels.begin(), valid_labels.end(), labels.ptr<int>(i)[j]) == valid_labels.end()) {
                labels.ptr<int>(i)[j] = 0; 
            }
		}
	}

    //normalize(labels, dst, 0, 255, NORM_MINMAX, CV_8U);

	applyColorMap(dst, dst, COLORMAP_TURBO);

	return(0);
}