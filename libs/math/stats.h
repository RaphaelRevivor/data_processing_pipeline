#ifndef STATS_H
#define STATS_H

#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class Stats {
    private:
        vector<vector<pair<string, string>>> data;
        vector<int> scores;
        double sumScores;
    public: 
        void readData(const vector<vector<pair<string, string>>>& data);
        bool loadScores();
        double calcMean();
        double calcMedian();
        vector<int> calcMode();
        double calcVariance();
        double calcStandardDeviation();
        unordered_map<int, int> calcFrequencies();
        int calcFrequency(const int& value);
        bool generateStatsFile();
};

#endif