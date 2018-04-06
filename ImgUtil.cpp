//
// Created by eka on 05/10/17.
//


#include "ImgUtil.h"


vector<Mat> ImgUtil::boundedThresholding(vector<string> files, vector<string> &files_out) {
    Mat img, img_reg;
    vector<Mat> result;
    for(string file: files){
        img = IoUtil::readImage(file);
        string file_reg = Util::getRegionFilename(file);
        try{
            img_reg = IoUtil::readImage(file_reg);
            cout << "Processing " << file << '\n';
            //check size of im and img_reg
            Size size_im = img.size();
            Size size_imreg = img_reg.size();
            if(size_im != size_imreg)
                throw string("size of image and label is different!");

            Mat img_cluster = boundedThresholding(img, img_reg);
            Mat img_result = displayPercentage(img_cluster);
            result.emplace_back(img_result);

            //next record file out path
            string file_out = Util::getOutputFilename(file);
            files_out.emplace_back(file_out);
        } catch (string &e){
            cout << e << '\n';
        }
        cout << '\n';
    }
    return result;
}

Mat ImgUtil::boundedThresholding(Mat &img, Mat &img_bound) {
    this->img=img;
    this->img_bound=img_bound;

    this->freqYellow=0;
    this->freqRed=0;
    this->freqBlack=0;

    Mat imtest(img.size(), CV_8UC3);
    imtest=cv::Scalar(255,255,255);

    //check size of im and img_reg
    Size size_im = img.size();
    Size size_imreg = img_bound.size();
    assert(size_im == size_imreg);

    vector<Point> region = scanRegion();
    for(Point location: region){
        //compare current pixel value with centroid
        Vec3b pixel = img.at<Vec3b>(location.y, location.x);
        uint cluster=this->shortestCentroid(pixel);
        switch (cluster){
            case 0:
                //black case
                imtest.at<Vec3b>(location) = this->centroid[0];
                this->freqBlack++;
                break;
            case 1:
                //red case
                imtest.at<Vec3b>(location) = this->centroid[1];
                this->freqRed++;
                break;
            case 2:
                //yellow case
                imtest.at<Vec3b>(location) = this->centroid[2];
                this->freqYellow++;
                break;
        }
    }

    npixel = freqRed + freqYellow + freqBlack;
    this->ratioBlack = (float) freqBlack *100 / npixel;
    this->ratioYellow = (float) freqYellow *100/ npixel;
    this->ratioRed = (float) freqRed *100/ npixel;
    cout << "red ratio: " << this->ratioRed << ", yellow ratio: " << this->ratioYellow << ", red ratio: " << this->ratioBlack << "\n";
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

    this->freqBlack = 0;
    this->freqRed = 0;
    this->freqYellow = 0;
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
            //cout << j << '\n';
            Vec3b color = img_bound.at<Vec3b>(j,i);
            if(compareBlack(color)){
                Point p;
                p.x = i;
                p.y = j;
                region.emplace_back(p);
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
    //int width = imres.size().width;
    float baseScale = (float) height / 500;
    int margin = 15*baseScale;
    int marginText = 5*baseScale;
    float textLength = 50*baseScale;
    //define rect height as 1/20 of screen height
    int rectWide = height/15;
    float scale = (float) height/500;

    //assume we define region at bottom left corner
    Scalar_<double> yellowColor = Scalar(YELLOW_B, YELLOW_G, YELLOW_R);
    Scalar_<double> redColor = Scalar(RED_B, RED_G, RED_R);
    Scalar_<double> blackColor = Scalar(BLACK_B, BLACK_G, BLACK_R);

    stringstream stream;

    //draw red text at left
    Point vRed1(margin, margin+rectWide);
    Point vRed2(vRed1.x + rectWide, margin);
    Point vRedText(vRed2.x + marginText, vRed1.y - marginText);
    rectangle(imres, vRed1, vRed2, redColor, FILLED, LINE_8);
    stream << fixed << setprecision(2) << ratioRed;
    putText(imres, stream.str() + "%", vRedText, CV_FONT_HERSHEY_PLAIN, scale, redColor,1 , LINE_AA);
    stream.str("");

    //draw yellow box + text at middle
    Point vYellow1(vRedText.x + textLength + margin, margin+rectWide);
    Point vYellow2(vYellow1.x+ rectWide, margin);
    Point vYellowText(vYellow2.x + marginText, vYellow1.y - marginText);
    rectangle(imres, vYellow1, vYellow2, yellowColor, FILLED, LINE_8);
    stream << fixed << setprecision(2) << ratioYellow;
    putText(imres, stream.str() + "%", vYellowText, CV_FONT_HERSHEY_PLAIN, scale, yellowColor,1 , LINE_AA);
    stream.str("");

    //draw black text at right
    Point vBlack1(vYellowText.x + textLength + margin, margin + rectWide);
    Point vBlack2(vBlack1.x + rectWide, margin);
    Point vBlackText(vBlack2.x + marginText, vBlack1.y - marginText);
    rectangle(imres, vBlack1, vBlack2, blackColor, FILLED, LINE_8);
    stream << fixed << setprecision(2) << ratioBlack;
    putText(imres, stream.str() + "%", vBlackText, CV_FONT_HERSHEY_PLAIN, scale, blackColor, 1, LINE_AA);

    return imres;
}

void ImgUtil::Vec3iToVec3b(Vec3i &vi, Vec3b &vb) {
    //both vector must have the same size
    for (int i = 0; i < 3; ++i) {
        vb.val[i]=(uchar) vi.val[i];
    }
}

Vec3b ImgUtil::uintToVec3b(uint &color) {
    Vec3b colorVec3b;
    colorVec3b[0] = static_cast<uchar>(color >> 16);
    colorVec3b[1] = static_cast<uchar>((color >> 8) &0xff);
    colorVec3b[2] = static_cast<uchar>(color & 0xff);
    return colorVec3b;
}

uint ImgUtil::Vec3bToUint(Vec3b &colorVec) {
    uint color = (colorVec.val[0] << 16) | (colorVec.val[1] << 8) | colorVec.val[2];
    return 0;
}
