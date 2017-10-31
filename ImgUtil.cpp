//
// Created by eka on 05/10/17.
//


#include "ImgUtil.h"

Mat ImgUtil::boundedThresholding(Mat &img, Mat &img_bound) {
    this->img=img;
    this->img_bound=img_bound;

    Mat imtest(img.size(), CV_8UC3);
    imtest=cv::Scalar(255,255,255);

    vector<Point> region = scanRegion();
    for(Point location: region){
        //compare current pixel value with centroid
        Vec3b pixel = img.at<Vec3b>(location.y, location.x);
        uint cluster=this->shortestCentroid(pixel);
        switch (cluster){
            case 0:
                imtest.at<Vec3b>(location) = this->centroid[0];
                break;
            case 1:
                imtest.at<Vec3b>(location) = this->centroid[1];
                break;
            case 2:
                imtest.at<Vec3b>(location) = this->centroid[2];
                break;
        }
    }

    //imshow("test", imtest);
    return imtest;
}

ImgUtil::ImgUtil(){
    Vec3b black_vec, red_vec, yellow_vec;
    black_vec.val[0] = BLACK_B;
    black_vec.val[1] = BLACK_G;
    black_vec.val[2] = BLACK_R;

    red_vec.val[0] = RED_B;
    red_vec.val[1] = RED_G;
    red_vec.val[2] = RED_R;

    yellow_vec.val[0] = YELLOW_B;
    yellow_vec.val[1] = YELLOW_G;
    yellow_vec.val[2] = YELLOW_R;

    this->centroid.push_back(black_vec);
    this->centroid.push_back(red_vec);
    this->centroid.push_back(yellow_vec);
}

bool ImgUtil::compareBlack(Vec3b vec) {
    uchar b = vec.val[0];
    uchar g = vec.val[1];
    uchar r = vec.val[2];
    return b == 0 && g == 0 && r == 0;

}

vector<Point> ImgUtil::scanRegion() {
    vector<Point> region;
    //both img & img_bound have same size
    Size size = this->img.size();

    for (int i = 0; i < size.width; ++i) {
        for (int j = 0; j < size.height; ++j) {
            Vec3b color = img_bound.at<Vec3b>(j,i);
            if(compareBlack(color)){
                Point p;
                p.x = i;
                p.y = j;
                region.push_back(p);
            }
        }
    }

    return region;
}

vector<double> ImgUtil::centroidDistance(Vec3b pixel) {
    vector<double> dist;
    for(Vec3b center: this->centroid){
        double d=0;
        for (int i = 0; i < 3; ++i) {
            d+=pow(pixel.val[i] - center.val[i],2);
        }
        d = sqrt(d);
        dist.push_back(d);
    }
    return dist;
}

uint ImgUtil::shortestCentroid(Vec3b pixel) {
    vector<double> dist = this->centroidDistance(pixel);
    auto minIt = min_element(dist.begin(), dist.end());
    long minpos = distance(dist.begin(),minIt);
    return static_cast<uint>(minpos);
}

Mat ImgUtil::displayPercentage(Mat &img){
    Mat imres=img.clone();
    int height = imres.size().height;
    int width = imres.size().width;
    int margin = 20;
    int marginText = 5;
    //define rect height as 1/20 of screen height
    int rectWide = height/15;

    //assume we define region at bottom left corner
    Scalar_<double> regionColor;
    regionColor = Scalar(0, 0, 0);
    Point v1(margin, margin+rectWide);
    Point v2(width - margin, margin);
    Point vText(v1.x + marginText, v1.y - marginText);
    rectangle(imres, v1, v2, regionColor, FILLED, LINE_8);

    String redText, yellowText, blackText;
    putText(imres, "percent", vText, CV_FONT_HERSHEY_PLAIN, 1.0f, Scalar(YELLOW_B, YELLOW_G, YELLOW_R));
    return imres;
}
