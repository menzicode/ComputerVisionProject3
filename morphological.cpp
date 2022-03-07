#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

enum TYPE { EROSION, DILATION };


int morph(cv::Mat &src, cv::Mat &dst, cv::Mat &str, TYPE tp) {
    Mat comp;
    str.convertTo(comp, CV_8U, 255);
    int osCol = (str.cols - 1) / 2;
    int osRow = (str.rows - 1) / 2;
    double s = sum(comp)[0];

    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (i >= osRow && i < src.rows - osRow) {
                if( j >= osCol && j < src.cols - osCol) {
                    Mat ar = src.rowRange(i - osRow, i + osRow + 1);
                    Mat ac = ar.colRange(j - osCol, j + osCol + 1);
                    std::vector<Mat> planes(3);
                    split(ac, planes);
                    Mat pix;
                    Mat ad = planes[0];
                    ad.convertTo(pix, CV_8U);
                    Mat scal = str.mul(pix);
                    Mat sub; 
                    subtract(comp, scal, sub);
                    double subsum = sum(sub)[0];
                    if (tp == DILATION ) {
                        if (subsum < s) {
                            dst.ptr<uchar>(i)[j] = 255;
                        }
                        else {
                            dst.ptr<uchar>(i)[j] = 0;
                        }
                    }
                    else if (tp == EROSION ) {
                        if (subsum == 0) {
                            dst.ptr<uchar>(i)[j] = 255;
                        }
                        else {
                            dst.ptr<uchar>(i)[j] = 0;
                        }
                    }
                } 
                else {
                    int dif;
                    Mat ar = src.rowRange(i - osRow, i + osRow + 1);
                    Mat ac;
                    Mat m_comp; 
                    Mat m_str;
                    Mat m_scal;
                    if (j < osCol) {
                        dif = osCol - j;
                        ac = ar.colRange(0, j + osCol + 1);
                        m_comp = comp.colRange(dif, comp.cols);
                        m_str = str.colRange(dif, comp.cols);
                    }
                    else {
                        dif = j - (src.cols - osCol) + 1;
                        ac = ar.colRange(j - osCol, src.cols);
                        m_comp = comp.colRange(0, comp.cols - dif);
                        m_str = str.colRange(0, comp.cols - dif);
                    }
                    std::vector<Mat> planes(3);
                    split(ac, planes);
                    Mat pix;
                    Mat ad = planes[0];
                    ad.convertTo(pix, CV_8U);
                    //std::cout << i << " " << j << " " << dif << " " << m_str << " \n" << pix << "\n";
                    m_scal = m_str.mul(pix);
                    Mat sub;
                    subtract(m_comp, m_scal, sub);
                    double m_s = sum(m_comp)[0];
                    double m_subsum = sum(sub)[0];
                    if (tp == DILATION) {
                        if (m_subsum < m_s) {
                            dst.ptr<uchar>(i)[j] = 255;
                        }
                        else {
                            dst.ptr<uchar>(i)[j] = 0;
                        }
                    }
                    else if (tp == EROSION) {
                        if (m_subsum == 0) {
                            dst.ptr<uchar>(i)[j] = 255;
                        }
                        else {
                            dst.ptr<uchar>(i)[j] = 0;
                        }
                    }
                }
            }
            else if (j >= osCol && j < src.cols - osCol) {
                int dif;
                Mat ar; 
                Mat ac;
                Mat m_comp; 
                Mat m_str;
                Mat m_scal;
                if (i < osRow) {
                    dif = osRow - i;
                    ar = src.rowRange(0, i + osRow + 1);
                    ac = ar.colRange(j - osCol, j + osCol + 1);
                    m_comp = comp.rowRange(dif, comp.rows);
                    m_str = str.rowRange(dif, comp.rows);
                }
                else {
                    dif = i - (src.rows - osRow) + 1;
                    ar = src.rowRange(i - osRow, src.rows);
                    ac = ar.colRange(j - osCol, j + osCol + 1);
                    m_comp = comp.rowRange(0, comp.rows - dif);
                    m_str = str.rowRange(0, comp.rows - dif);
                }
                std::vector<Mat> planes(3);
                split(ac, planes);
                Mat pix;
                Mat ad = planes[0];
                ad.convertTo(pix, CV_8U);
                m_scal = m_str.mul(pix);
                Mat sub;
                subtract(m_comp, m_scal, sub);
                double m_s = sum(m_comp)[0];
                double m_subsum = sum(sub)[0];
                if (tp == DILATION) {
                    if (m_subsum < m_s) {
                        dst.ptr<uchar>(i)[j] = 255;
                    }
                    else {
                        dst.ptr<uchar>(i)[j] = 0;
                    }
                }
                else if (tp == EROSION) {
                    if (m_subsum == 0) {
                        dst.ptr<uchar>(i)[j] = 255;
                    }
                    else {
                        dst.ptr<uchar>(i)[j] = 0;
                    }
                }
            }
        }
    }

    return 0;
}

int erosion(Mat &src, Mat &dst, Mat &str) {
    morph(src, dst, str, EROSION);
    return 0;
}

int dilation(Mat &src, Mat &dst, Mat &str) {
    morph(src, dst, str, DILATION);
    return 0;
}

int open(Mat &src, Mat &dst, Mat &str) {
    Mat i_mat = Mat::zeros(src.rows, src.cols, CV_8U);
    morph(src, i_mat, str, EROSION);
    morph(i_mat, dst, str, DILATION);
    return 0;
}

int close(Mat &src, Mat &dst, Mat &str) {
    Mat i_mat = Mat::ones(src.rows, src.cols, CV_8U);
    morph(src, i_mat, str, DILATION);
    morph(i_mat, dst, str, EROSION);
    return 0;
}

int grassfire_shrink(Mat &src, Mat &dst, int distance_threshold) {
    Mat distances = Mat::ones(src.rows, src.cols, CV_8U);
    for (int i = 1; i < src.rows; i++) {
        for (int j = 1; j < src.cols; j++) {
            int up_img = src.ptr<uchar>(i-1)[j];
            int left_img = src.ptr<uchar>(i)[j-1];
            int up_dist = distances.ptr<uchar>(i-1)[j];
            int left_dist = distances.ptr<uchar>(i)[j-1];
            if (up_img == 0 || left_img == 0) {
                distances.ptr<uchar>(i)[j] = 1;
            }
            else {
                if (up_dist < left_dist) {
                    distances.ptr<uchar>(i)[j] = up_dist + 1;  
                }
                else {
                    distances.ptr<uchar>(i)[j] = left_dist + 1;
                }
            }
        }
    }
    for (int i = src.rows - 1; i >= 0; i--) {
        for (int j = src.cols - 1; j >= 0; j--) {
            int down_img = src.ptr<uchar>(i+1)[j];
            int right_img = src.ptr<uchar>(i)[j+1];
            int down_dist = distances.ptr<uchar>(i+1)[j];
            int right_dist = distances.ptr<uchar>(i)[j+1];
            int pix = distances.ptr<uchar>(i)[j];
            if (down_img == 0 || right_img == 0) {
                distances.ptr<uchar>(i)[j] = 1;
            }
            else {
                if (down_dist < right_dist && down_dist < pix) {
                    distances.ptr<uchar>(i)[j] = down_dist + 1;  
                }
                else if (right_dist < down_dist && right_dist < pix) {
                    distances.ptr<uchar>(i)[j] = right_dist + 1;
                }
                else {
                    distances.ptr<uchar>(i)[j] = pix;
                }
            }
        }
    }
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (distances.ptr<uchar>(i)[j] < distance_threshold) {
                dst.ptr<uchar>(i)[j] = 0;
            }
            else {
                dst.ptr<uchar>(i)[j] = 255;
            }
        }
    }
    //std::cout<<distances;
    return 0;
}

int grassfire_grow(Mat &src, Mat &dst, int distance_threshold) {
    Mat distances = Mat::ones(src.rows, src.cols, CV_8U);
    for (int i = 1; i < src.rows; i++) {
        for (int j = 1; j < src.cols; j++) {
            int up_img = src.ptr<uchar>(i-1)[j];
            int left_img = src.ptr<uchar>(i)[j-1];
            int up_dist = distances.ptr<uchar>(i-1)[j];
            int left_dist = distances.ptr<uchar>(i)[j-1];
            if (up_img == 255 || left_img == 255) {
                distances.ptr<uchar>(i)[j] = 1;
            }
            else {
                if (up_dist < left_dist) {
                    distances.ptr<uchar>(i)[j] = up_dist + 1;  
                }
                else {
                    distances.ptr<uchar>(i)[j] = left_dist + 1;
                }
            }
        }
    }
    for (int i = src.rows - 1; i >= 0; i--) {
        for (int j = src.cols - 1; j >= 0; j--) {
            int down_img = src.ptr<uchar>(i+1)[j];
            int right_img = src.ptr<uchar>(i)[j+1];
            int down_dist = distances.ptr<uchar>(i+1)[j];
            int right_dist = distances.ptr<uchar>(i)[j+1];
            int pix = distances.ptr<uchar>(i)[j];
            if (down_img == 255 || right_img == 255) {
                distances.ptr<uchar>(i)[j] = 1;
            }
            else {
                if (down_dist < right_dist && down_dist < pix) {
                    distances.ptr<uchar>(i)[j] = down_dist + 1;  
                }
                else if (right_dist < down_dist && right_dist < pix) {
                    distances.ptr<uchar>(i)[j] = right_dist + 1;
                }
                else {
                    distances.ptr<uchar>(i)[j] = pix;
                }
            }
        }
    }
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (distances.ptr<uchar>(i)[j] < distance_threshold) {
                dst.ptr<uchar>(i)[j] = 255;
            }
            else {
                dst.ptr<uchar>(i)[j] = 0;
            }
        }
    }
    //std::cout<<distances;
    return 0;
}