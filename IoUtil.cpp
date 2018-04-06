//
// Created by eka on 20/09/17.
//
#include "IoUtil.h"

vector<string> IoUtil::readImagesAsString(string path) {
    vector <string> files;

    if(!exists(path) || !is_directory(path)){
        cout << path  << " is not a directory!\n";
        throw "IO Exception";
    }

    //cout << "path: " << path << '\n';
    int i=0;
    string filename;
    directory_iterator end_itr;
    boost::filesystem::path fpath(path);
    try{
        for(directory_iterator itr{fpath};itr!=end_itr;++itr){
            filename = itr->path().string();
            //filter by extension and not passing region filename
            if(Util::has(PERMITTED_EXTENSION,itr->path().extension().string()) &&
               !(Util::hasString("region", filename) ||
                 Util::hasString("result", filename )))
            {
                //cout << filename << '\n';
                files.emplace_back(filename);

                //cout << "size: " << image.size() << ", depth: " << image.channels() << "\n";
                //namedWindow(to_string(i), WINDOW_AUTOSIZE);
                //imshow(to_string(i), image);
                //cout << i << '\n';
                i++;
            }
        }
    } catch (...){
        cout << "exception" << '\n';
    }

    return files;
}

vector<Mat> IoUtil::readImages(string path) {
    vector <Mat> images;

    if(!exists(path) || !is_directory(path)){
        cout << path  << " is not a directory!\n";
        throw "IO Exception";
    }

    cout << "path: " << path << '\n';
    int i=0;
    for(directory_iterator itr(path);itr!=directory_iterator();++itr){
        //filter by extension and not passing region filename
        if(Util::has(PERMITTED_EXTENSION,itr->path().extension().string()) &&
                !Util::hasString("_region", itr->path().filename().string()))
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

Mat IoUtil::readImage(string path) {
    vector <Mat> images;

    if(!exists(path) || !is_regular_file(path)){
        //cout <<path << " is not a file!\n";
        throw string("IO Exception for " + path + " skipping.");
    }

    Mat image = imread(path, IMREAD_COLOR);
    return image;
}

const vector <string> IoUtil::PERMITTED_EXTENSION= {".tif",".jpg",".jpeg",".png"};

void IoUtil::storeMatFiles(vector<string> paths, vector<Mat> images) {
    for(int i =0; i<paths.size();i++){
        imwrite(paths[i], images[i]);
    }
}
