//
// Created by eka on 05/10/17.
//

#ifndef TISSUE_CELL_IMGUTIL_H
#define TISSUE_CELL_IMGUTIL_H


#include <opencv/cv.hpp>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <boost/format.hpp>

using namespace std;
using namespace cv;

class ImgUtil {
private:
    //constants
    static const uint YELLOW = 0x91663c;
    static const uint YELLOW_R = YELLOW >> 16;
    static const uint YELLOW_G = YELLOW >> 8 & 0x0000ff;
    static const uint YELLOW_B = YELLOW & 0x0000ff;
    static const uint YELLOW_BGR = (YELLOW_B) << 16 | (YELLOW_G) << 8 | (YELLOW_R);
    static const uint RED = 0x9a3932;
    static const uint RED_R = RED >> 16;
    static const uint RED_G = RED >> 8 & 0x0000ff;
    static const uint RED_B = RED & 0x0000ff;
    static const uint RED_BGR = (RED_B) << 16 | (RED_G) << 8 | (RED_R);
    static const uint BLACK_C = 0x282f1f;
    static const uint BLACK_R = BLACK_C >> 16;
    static const uint BLACK_G = BLACK_C >> 8 & 0x0000ff;
    static const uint BLACK_B = BLACK_C & 0x0000ff;
    static const uint BLACK_BGR = (BLACK_B) << 16 | (BLACK_G) << 8 | (BLACK_R);

    //variables
    vector<Vec3b> centroid;
    int freqRed, freqYellow, freqBlack, npixel;
    float ratioRed, ratioYellow, ratioBlack;
    Mat img, img_bound;

    //methods
    bool compareBlack(Vec3b vec);
    vector<Point> scanRegion();
    vector<double> centroidDistance(Vec3b pixel);
    uint shortestCentroid(Vec3b pixel);

public:
    static const uint BLACK = 0;
    static const uint WHITE = 0xFFFFFF;
    Mat boundedThresholding(Mat &img, Mat &img_bound);
    ImgUtil();
    Mat displayPercentage(Mat &img);
    static const uint CENTROID_SIZE = 3;
    static void Vec3iToVec3b(Vec3i &, Vec3b &);
    static Vec3b uintToVec3b(uint &color);
    static uint Vec3bToUint(Vec3b &color);
};


#endif //TISSUE_CELL_IMGUTIL_H
