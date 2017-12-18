//
// Created by eka on 09/12/17.
//

#include "Cluster.h"

Cluster::Cluster(const Mat &im, uint black, uint red, uint yellow) {
    this->im=im;
    centroidRaw[0]=black;
    centroidRaw[1]=red;
    centroidRaw[2]=yellow;
    mSize=im.size();
    clusterMember.resize(static_cast<unsigned long>(mSize.width * mSize.height), 0);

    //cast centroidRaw (uint) to centroid (in Vec3b)
    for (int i = 0; i < ImgUtil::CENTROID_SIZE; ++i) {
        centroid.at(i)=ImgUtil::uintToVec3b(centroidRaw[i]);
    }
    this->run();
}

/**
 * The method lookup current pixel value and compare with all centroids to get closest centroid position
 * @param i, x coordinate
 * @param j, y coordinate
 * @return closes centroid index
 */
uint Cluster::getClosestCentroid(int i, int j) {
    //first get current pixel
    Vec3b pixel = im.at<Vec3b>(j,i);
    //second compute distance between current pixel with centroids
    vector<double> dist;
    for(Vec3b center: this->centroid){
        double d=0;
        for (int i = 0; i < 3; ++i) {
            d+=pow(pixel.val[i] - center.val[i],2);
        }
        d = sqrt(d);
        dist.push_back(d);
    }
    //finally return closest centroid
    auto minIt = min_element(dist.begin(), dist.end());
    long minpos = distance(dist.begin(),minIt);
    return static_cast<uint>(minpos);
}

void Cluster::iteration() {
    //reinit all three clusters
    blackCluster.clear();
    redCluster.clear();
    yellowCluster.clear();

    //initially must set centroid membership for all pixels
    int ix = 0;
    Size size = im.size();
    for (int i = 0; i < size.width; ++i) {
        for (int j = 0; j < size.height; ++j) {
            //set cluster membership based on closest centroid index
            uint centroidId = getClosestCentroid(i,j);
            clusterMember[i]=centroidId;
            switch(centroidId){
                case Cluster::BLACK_CLUSTER_ID:
                    blackCluster.emplace_back(Point(i,j));
                    break;
                case Cluster::RED_CLUSTER_ID:
                    redCluster.emplace_back(Point(i,j));
                    break;
                case Cluster::YELLOW_CLUSTER_ID:
                    blackCluster.emplace_back(Point(i,j));
                    break;
            }
            //store each cluster id into its own separate cluster vector
            ix++;
        }
    }

    //next we need to update the centroid for each cluster
    updateCentroid();
}

void Cluster::updateCentroid(){
    this->centroid.at(0)=this->updateCentroid(blackCluster);
    this->centroid.at(1)=this->updateCentroid(redCluster);
    this->centroid.at(2)=this->updateCentroid(yellowCluster);
}

Vec3b Cluster::updateCentroid(vector<Point> &cluster) {
    Vec3i average; //for storing average of each color
    for (int k = 0; k < cluster.size(); ++k) {
        Point p=cluster.at(k);
        Vec3b pixel = im.at<Vec3b>(p);
        average.val[0]+=pixel.val[0];
        average.val[1]+=pixel.val[1];
        average.val[2]+=pixel.val[2];
    }
    for (int l = 0; l < 3; ++l) {
        average.val[l]/=cluster.size();
    }
    Vec3b mean;
    ImgUtil::Vec3iToVec3b(average, mean);
    return mean;
}

/**
 * Core running method for k-means training
 */
void Cluster::run() {
    //run until convergence
    //backup old centroid
    vector<Vec3b> oldCentroid;
    double distance=norm(centroid, oldCentroid);
    while(distance >= numeric_limits<double>::epsilon()){
        iteration();
    }
}

vector<Vec3b> Cluster::getComputedCentroid() {
    return this->centroid;
}
