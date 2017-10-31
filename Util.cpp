//
// Created by eka on 20/09/17.
//

#include "Util.h"

struct Util::IsMatch{
    const string t;
    IsMatch(const string init): t(init){}
    bool operator()(const string p) const {return p==t;}
};

bool Util::has(const vector <string> &vec, string p){
    bool res = any_of(vec.begin(), vec.end(), IsMatch(p));
    return res;
}
