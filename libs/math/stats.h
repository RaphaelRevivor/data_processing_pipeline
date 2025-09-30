#ifndef STATS_H
#define STATS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "map"

using namespace std;

class Stats {
    public: 
        double mean(vector<vector<pair<string, string>>> data);
        double median(vector<vector<pair<string, string>>> data);
        vector<int> mode(vector<vector<pair<string, string>>> data);
        double variance(vector<vector<pair<string, string>>> data);
};

#endif