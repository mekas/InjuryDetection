//
// Created by eka on 20/09/17.
//

#ifndef TISSUE_CELL_UTIL_H
#define TISSUE_CELL_UTIL_H
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Util {
public:
    static bool has(const vector <string> &vec, string p);

private:
    struct IsMatch;
};


#endif //TISSUE_CELL_UTIL_H
