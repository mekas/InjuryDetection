#include <string>
#include <iostream>
#include <opencv/cv.hpp>
#include "IoUtil.h"
#include "ImgUtil.h"

using namespace std;
using namespace cv;

int main() {
    //string path = "../warna_dasar_luka/Foto_luka_hitam_fix";
    string photo_hitam = "../warna_dasar_luka/Foto_luka_hitam_fix/15.jpg";
    string photo_kuning = "../warna_dasar_luka/Foto_luka_kuning_fix/4.jpg";
    string photo_merah = "../warna_dasar_luka/Foto_luka_merah_fix/6.JPG";
    string photo_campur = "../foto_luka_gimp/luka_campur/1.JPG";
    string photo_hitam_reg = "../warna_dasar_luka/Foto_luka_hitam_fix/15_region.png";
    string photo_kuning_reg = "../warna_dasar_luka/Foto_luka_kuning_fix/4_region.png";
    string photo_merah_reg = "../warna_dasar_luka/Foto_luka_merah_fix/6_region.png";
    string photo_campur_reg = "../foto_luka_gimp/luka_campur/1_region.png";
    string photo_out = "campur1_detect.png";
    cout << "Hello, World!" << std::endl;
    Mat img = IoUtil::readImage(photo_campur);
    ImgUtil img_util;
    Mat img_reg = IoUtil::readImage(photo_campur_reg);
    Mat imtest = img_util.boundedThresholding(img, img_reg);
    Mat im_percentage =img_util.displayPercentage(imtest);

    imshow("input", img);
    //imshow("boundary", img_reg);
    imshow("test", imtest);
    imshow("region", im_percentage);
    imwrite(photo_out,im_percentage);
    waitKey(0);
    return 0;
}