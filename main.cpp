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
    string photo_campur = "../warna_dasar_luka/Foto_luka_campur_fix/49.jpg";
    string photo_reg = "../warna_dasar_luka/Foto_luka_hitam_fix/15_region.png";
    string photo_kuning_reg = "../warna_dasar_luka/Foto_luka_kuning_fix/4_region.png";
    string photo_merah_reg = "../warna_dasar_luka/Foto_luka_merah_fix/6_region.png";
    string photo_campur_reg = "../warna_dasar_luka/Foto_luka_campur_fix/49_region.png";
    string photo_out = "49_detect.png";
    cout << "Hello, World!" << std::endl;
    Mat img = IoUtil::read_image(photo_campur);
    ImgUtil img_util;
    Mat img_reg = IoUtil::read_image(photo_campur_reg);
    Mat imtest = img_util.boundedThresholding(img, img_reg);
    Mat im_percentage =ImgUtil::displayPercentage(imtest);

    imshow("input", img);
    //imshow("boundary", img_reg);
    imshow("test", imtest);
    imshow("region", im_percentage);
    imwrite(photo_out,imtest);
    waitKey(0);
    return 0;
}