#include "stats.h"

/**
 * Gets the scores from the data and converts them to integers.
 * @param data the data
 * @return if data is not empty, returns a vector of the scores, otherwise returns an empty vector
 * @author Tilde
 */
vector<int> getScores(vector<vector<pair<string, string>>> data) 
{
    if (data.empty() || data[0].empty())                        // checks if data is empty
    {
        return vector<int>{};
    }

    vector<int> scores;

    for (const auto& row : data)
    {
        string scoreString = row.back().second;                 // gets the second string of the last pair in the row, i.e. the score
        int scoreInt;

        try {                                               
            scoreInt = stoi(scoreString);                       // tries to convert to int
            scores.push_back(scoreInt);
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
 * @author Tilde
 */
double Stats::calcMean(vector<vector<pair<string, string>>> data) 
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
 * @author Tilde
 */
double Stats::calcMedian(vector<vector<pair<string, string>>> data)
{
    auto scores = getScores(data);
    
    if (scores.empty()) {
        return -1;
    }

    sort(scores.begin(), scores.end());                         // sorts the scores in ascending order

    int middleIndex = scores.size()/2;

    if (scores.size() % 2 == 0)                                 // checks if there is an even number of scores
    {
        double sumOfMiddleScores = scores[middleIndex-1] + scores[middleIndex];
        return sumOfMiddleScores/2;                             // calculates average of middle scores
    }

    return scores[middleIndex];
}

/**
 * Calculates the mode of the scores.
 * @param data the data
 * @return if data is not empty, returns a vector with the modes of the scores, otherwise returns an empty vector
 * @author Tilde
 */
vector<int> Stats::calcMode(vector<vector<pair<string, string>>> data)
{
    auto scores = getScores(data);
    
    if (scores.empty()) {
        return vector<int>{};
    }

    map<int, int> frequencies;                                  // creates map with key score and value frequency

    for (const auto& score : scores) 
    {
        frequencies[score] += 1;                                // adds 1 to the current value of the key. If the key score doesn't exist in the map, creates a key with default value 0 
    }

    vector<int> modes;
    int maxFreq = 0;

    for (const auto& freq : frequencies) 
    {
        if (maxFreq < freq.second)
        {
            modes.clear();                                      // clear vector of previously stored modes
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
 * @return if data is not empty, returns the variance of the scores, otherwise returns -1
 * @author Tilde
 */
double Stats::calcVariance(vector<vector<pair<string, string>>> data) 
{
    auto scores = getScores(data);
    
    if (scores.empty()) {
        return -1.0;
    }

    double sum = 0.0;

    for (const auto& score : scores) 
    {
        sum += score;
    }

    double mean = sum/scores.size();
    sum = 0.0;

    for (const auto& score : scores) 
    {
        double squaredDiff = (score-mean)*(score-mean);
        sum += squaredDiff;
    }

    return sum/scores.size();
}

/**
 * Calculates the standard deviation of the scores.
 * @param data the data
 * @return if data is not empty, returns the standard deviation of the scores, otherwise returns -1
 * @author Tilde
 */
double Stats::calcStandardDeviation(vector<vector<pair<string, string>>> data) 
{
    double variance = calcVariance(data);

    if (variance == -1.0) 
    {
        return variance;
    }

    return sqrt(variance);
}