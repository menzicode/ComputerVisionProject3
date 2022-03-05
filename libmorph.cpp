#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "morphological.h"
using namespace cv;
using namespace std;
Mat src, erosion_dst, dilation_dst;
int erosion_elem = 0;
int erosion_size = 2;
int dilation_elem = 0;
int dilation_size = 2;
int const max_elem = 2;
int const max_kernel_size = 21;
void Erosion( int, Mat &src, Mat &erosion_dst);
void Dilation( int, Mat &src, Mat &dilation_dst);
int main( int argc, char** argv )
{
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
                    double thresh = 110;
                    // std::cout << "\nEnter threshold: ";
                    // std::cin >> thresh;
                    for (;;) {
                      Mat framein;
                        *capdev >> framein;
                        Mat frame;
                        Mat tframe;
                        cvtColor(framein, frame, COLOR_RGB2GRAY);
                        //threshold(frame, tframe, thresh);]
                        threshold(frame, tframe, thresh, 255, THRESH_BINARY);
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
                          Mat eframe;
                          Mat dframe;
                          Mat eframe2 = cv::Mat::zeros(framein.rows, framein.cols, CV_8U);
                          Mat dframe2 = cv::Mat::zeros(framein.rows, framein.cols, CV_8U);
                          Erosion( 0, tframe, eframe );
                          Dilation( 0, tframe, dframe );
                          erosion(tframe, eframe2, square5x5);
                          namedWindow("Erosion custom", 1);
                          imshow("Erosion custom", eframe2);
                          waitKey(0);
                          return 0;
                        }
                    }
                }
                if( key == 'q') {
                    break;
                }
        }
}
void Erosion( int, Mat &src, Mat &erosion_dst )
{
  int erosion_type = 0;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }
  Mat element = getStructuringElement( erosion_type,
                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                       Point( erosion_size, erosion_size ) );
  cout << element;
  erode( src, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
}
void Dilation( int, Mat &src, Mat &erosion_dst )
{
  int dilation_type = 0;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }
  Mat element = getStructuringElement( dilation_type,
                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                       Point( dilation_size, dilation_size ) );
  cout << element;
  dilate( src, dilation_dst, element );
  imshow( "Dilation Demo", dilation_dst );
}