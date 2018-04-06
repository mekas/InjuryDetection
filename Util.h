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
    static bool has(const vector <string> &vec, const string &p);
    static bool hasString(const string &part, const string &input);
    static string getRegionFilename(string &input);
    static string getOutputFilename(string &input);

private:
    struct IsMatch;
};


#endif //TISSUE_CELL_UTIL_H
