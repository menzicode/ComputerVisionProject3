
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

int thresholding(Mat& src, Mat& dst) {
	Mat src2, dst2, mask;
	src.copyTo(dst);
	int T = 90;
	for (int i = 0; i < dst.rows; i++) {
		for (int j = 0; j < dst.cols; j++) {
			Vec3b pixels = dst.at<Vec3b>(i, j);
			int b = pixels.val[0];
			int g = pixels.val[1];
			int r = pixels.val[2];
			int intensity = (b + g + r) / 3;

			for (int c = 0; c < 3; c++) {
				if (intensity < T) {
					dst.at<Vec3b>(i, j)[c] = 255;
				}
				else
					dst.at<Vec3b>(i, j)[c] = 0;
			}

		}
	}
	cvtColor(dst, dst, COLOR_BGR2GRAY);
	return(0);
}
/*int x = stats.at<int>(Point(0, 1));
	int y = stats.at<int>(Point(1, 1));
	int w = stats.at<int>(Point(2, 1));
	int h = stats.at<int>(Point(3, 1));*/

int segment(Mat& src, Mat& dst) {
	Mat labels, stats, centroids, thresholdimg, res;
	//src.copyTo(dst);
	int labelc = connectedComponentsWithStats(src, labels, stats, centroids, 8, CV_32S);
	normalize(labels, dst, 0, 255, NORM_MINMAX, CV_8U);

	//cout << dst.size() << endl;
	for (int i = 0; i < labels.rows; i++) {
		for (int j = 0; j < labels.cols; j++) {
			int x = labels.at<int>(i,j);
			if (x > 5) {
				dst.at<uchar>(i, j) = 0 ;
			}
		}
		
	}
	applyColorMap(dst, dst, COLORMAP_TURBO);
	
	

	return(0);
}
/*class labels {
private:
	string objectName;
	vector<int> features;
public:
	labels(string x) {
		objectName = x;

	}
	string getName() { return objectName; }
	
};*/

int collectData(vector<int> feature) {
	// training mode, take feacture vectors of known object (task 4) feature vectors need to be stored
	// implement feature function, when pressing N this function is applied
	// pass feature vector ->>
	string objectName;

	cout << "Please enter object name" << endl;
	getline(cin, objectName =+".txt");

	ofstream out_file(objectName.c_str());
	ostream_iterator<string> out_iterator(out_file, "/n");
	copy(feature.begin(), feature.end(), out_iterator);
	cout << "Feature Vector of " << objectName << " saved.";


}










enum mode { threholding, regular, con_comp };
int main() {
	VideoCapture cap(0);
	Mat dst, dst1, dst2, temp1, src, labels1, stats, centroids;
	Mat frame;
	int task = 0;

	for (;;) {
		cap >> frame;
		char key = waitKey(10);

		if (key == 'r') {
			task = regular;
			printf("regular");
		}

		if (key == 'o') {
			task = threholding;
			printf("thresholding");
		}
		if (key == 'c') {
			task = con_comp;
			printf("regions");
		}

		if (task == threholding) {
			thresholding(frame, dst);
			imshow("Video", dst);
		}
		if (task == con_comp) {
			thresholding(frame, dst);
			segment(dst, labels1);
			imshow("Video", labels1);
		}

		if (task == regular) {
			imshow("Video", frame);
		}

		if (key == 'q') {
			destroyAllWindows;
			cout << "Closing Program " << endl;
			break;
		}
	}
	return(0);
}
