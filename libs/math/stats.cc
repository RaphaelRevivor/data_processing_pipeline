#include "stats.h"

/**
 * Gets the scores from the data.
 * @param data the data
 * @return if data is not empty, returns a vector of the scores, otherwise returns an empty vector
 */
vector<int> getScores(vector<vector<pair<string, string>>> data) 
{
    if (data.empty()) 
    {
        return vector<int>{};
    }

    vector<int> scores;                                         // creates a vector to fill with scores

    for (const auto& row : data)
    {
        string scoreString = row.back().second;                 // gets the second string of the last pair, i.e. the score
        int scoreInt;

        try {                                               
            scoreInt = stoi(scoreString);                       // tries to convert to int
            scores.push_back(scoreInt);                         // pushes the converted score to the vector
        } catch (const invalid_argument& e) {
            cout << "Error: Not a valid number: " << scoreString << endl;
        } catch (const out_of_range& e) {
            cout << "Error: Number out of range: " << scoreString << endl;
        }
    }

    return scores;
}

/**
 * Calculates the mean of the scores.
 * @param data the data
 * @return if data is not empty, returns the mean of the scores, otherwise -1
 */
double Stats::mean(vector<vector<pair<string, string>>> data) 
{
    auto scores = getScores(data);
    
    if (scores.empty()) {
        return -1;
    }

    double sum = 0.0;

    for (const auto& score : scores) 
    {
        sum += score;
    }

    return sum/scores.size();
}

/**
 * Calculates the median of the scores.
 * @param data the data
 * @return if data is not empty, returns the median of the scores, otherwise -1
 */
double Stats::median(vector<vector<pair<string, string>>> data)
{
    auto scores = getScores(data);
    
    if (scores.empty()) {
        return -1;
    }

    sort(scores.begin(), scores.end());

    int middleIndex = scores.size()/2;

    if (scores.size() % 2 == 0) 
    {
        double sumOfMiddleScores = scores[middleIndex-1] + scores[middleIndex];
        return sumOfMiddleScores/2;
    }

    return scores[middleIndex];
}

/**
 * Calculates the mode of the scores.
 * @param data the data
 * @return if data is not empty, returns a vector with the modes of the scores, otherwise returns an empty vector
 */
vector<int> Stats::mode(vector<vector<pair<string, string>>> data)
{
    auto scores = getScores(data);
    
    if (scores.empty()) {
        return vector<int>{};
    }

    map<int, int> frequencies;

    for (const auto& score : scores) 
    {
        frequencies[score] += 1;
    }

    vector<int> modes;
    int maxFreq = 0;

    for (const auto& freq : frequencies) 
    {
        if (maxFreq < freq.second) 
        {
            modes.clear();
            modes.push_back(freq.first);
            maxFreq = freq.second;
        } 
        else if (maxFreq == freq.second)
        {
            modes.push_back(freq.first);
        }
    }

    return modes;
}

/**
 * Calculates the variance of the scores.
 * @param data the data
 * @return if data is not empty, returns the variance of the scores, otherwise returns an empty vector
 */
double Stats::variance(vector<vector<pair<string, string>>> data) 
{

}

/**
 * Calculates the standard deviation of the scores.
 * @param data the data
 * @return if data is not empty, returns the standard deviation of the scores, otherwise returns an empty vector
 */
double Stats::variance(vector<vector<pair<string, string>>> data) 
{

}