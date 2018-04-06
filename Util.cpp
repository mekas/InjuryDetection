//
// Created by eka on 20/09/17.
//

#include "Util.h"

struct Util::IsMatch{
    const string t;
    IsMatch(const string init): t(init){}
    bool operator()(const string p) const {return p==t;}
};

bool Util::has(const vector <string> &vec, const string &p){
    bool res = any_of(vec.begin(), vec.end(), IsMatch(p));
    return res;
}

bool Util::hasString(const string &part, const string &input) {
    size_t found = input.find(part);
    return found != string::npos;
}

/**
 * generate region filename given input filename
 * @param input
 * @return region filename
 */
string Util::getRegionFilename(string &input) {
    unsigned long slash_index = input.find_last_of("/\\");
    unsigned long dot_index = input.find_last_of('.');
    string path = input.substr(0, slash_index+1);
    string name = input.substr(slash_index + 1, dot_index - slash_index - 1);
    string extra_label = "_region";
    string extension = ".png";
    return path+name+extra_label+extension;
}

string Util::getOutputFilename(string &input) {
    unsigned long slash_index = input.find_last_of("/\\");
    unsigned long dot_index = input.find_last_of('.');
    string path = input.substr(0, slash_index+1);
    string name = input.substr(slash_index + 1, dot_index - slash_index - 1);
    string extra_label = "_result";
    string extension = ".png";
    return path+name+extra_label+extension;
}


