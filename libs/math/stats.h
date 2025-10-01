#ifndef STATS_H
#define STATS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

class Stats {
    public: 
        double calcMean(vector<vector<pair<string, string>>> data);
        double calcMedian(vector<vector<pair<string, string>>> data);
        vector<int> calcMode(vector<vector<pair<string, string>>> data);
        double calcVariance(vector<vector<pair<string, string>>> data);
        double calcStandardDeviation(vector<vector<pair<string, string>>> data);
};

#endif