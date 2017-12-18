//
// Created by eka on 09/12/17.
//

#ifndef TISSUE_CELL_CLUSTER_H
#define TISSUE_CELL_CLUSTER_H

#include "ImgUtil.h"

/**
 * Static k-means of 3 cluster
 * This version of k-means is unable to create cluster anything but three
 * Specifically tune to solve color segmentation for skin injury detection
 */
class Cluster {
public:
    Cluster(const Mat &im, uint black, uint red, uint yellow);
    vector<Vec3b> getComputedCentroid();

private:
    //class variables
    Mat im; //local data structure to store image reference
    Size mSize;
    uint centroidRaw[3];
    vector<Vec3b> centroid;
    vector<uint> clusterMember;
    vector<Point> blackCluster;
    vector<Point> redCluster;
    vector<Point> yellowCluster;

    //methods
    uint getClosestCentroid(int, int);
    void run();
    void iteration();
    void updateCentroid();
    Vec3b updateCentroid(vector<Point> &);

    //constant
    static const uint BLACK_CLUSTER_ID = 0;
    static const uint RED_CLUSTER_ID = 1;
    static const uint YELLOW_CLUSTER_ID = 2;
};


#endif //TISSUE_CELL_CLUSTER_H
