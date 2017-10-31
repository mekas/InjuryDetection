//
// Created by eka on 20/09/17.
//
#include "IoUtil.h"

vector<Mat> IoUtil::read_images(string path) {
    vector <Mat> images;

    if(!exists(path) || !is_directory(path)){
        cout << path  << " is not a directory!\n";
        throw "IO Exception";
    }

    cout << "path: " << path << '\n';
    int i=0;
    for(directory_iterator itr(path);itr!=directory_iterator();++itr){
        if(Util::has(PERMITTED_EXTENSION,itr->path().extension().string()))
        {
            string filename = itr->path().string();
            Mat image = imread(filename, IMREAD_GRAYSCALE);
            images.push_back(image);
            cout << filename << '\n';
            //cout << "size: " << image.size() << ", depth: " << image.channels() << "\n";
            //namedWindow(to_string(i), WINDOW_AUTOSIZE);
            //imshow(to_string(i), image);
            i++;
        }
    }
    return images;
}

Mat IoUtil::read_image(string path) {
    vector <Mat> images;

    if(!exists(path) || !is_regular_file(path)){
        cout <<path << " is not a file!\n";
        throw "IO Exception";
    }

    Mat image = imread(path, IMREAD_COLOR);
    return image;
}

const vector <string> IoUtil::PERMITTED_EXTENSION= {".tif",".jpg",".jpeg",".png"};
