//
// Created by eka on 20/09/17.
//

#ifndef TISSUE_CELL_IOUTIL_H
#define TISSUE_CELL_IOUTIL_H

#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Util.h"
//#include <filesystem> //not supported at gcc installed at August 2, 2017

using namespace std;
using namespace boost::filesystem;
using namespace cv;

class IoUtil {
public:
    static vector<Mat> readImages(string path);
    static vector<string> readImagesAsString(string path);
    static Mat readImage(string filepath);
    static void storeMatFiles(vector<string> paths, vector<Mat> images);
private:
    static const vector <string> PERMITTED_EXTENSION;
};

#endif //TISSUE_CELL_IOUTIL_H
