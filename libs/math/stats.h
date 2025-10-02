#ifndef STATS_H
#define STATS_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric>

using namespace std;

class Stats {
    private:
        vector<int> scores;
    public: 
        bool readData(const vector<vector<pair<string, string>>>& data);
        double calcMean();
        double calcMedian();
        vector<int> calcMode();
        double calcVariance();
        double calcStandardDeviation();
};

#endif