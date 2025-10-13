#include "stats.h"

/**
 * Reads data and stores it.
 * @param newData the data
 * @author Tilde
 */
void Stats::readData(const vector<vector<pair<string, string>>>& newData)
{
    data.clear();

    vector<pair<string, string>> tempRow;

    if (!(newData.empty() || newData[0].empty()))               // only enters if the new data is not empty
    {
        for (const auto& row : newData)
        {
            for (const auto& pair : row) 
            {
                tempRow.emplace_back(make_pair(pair.first, pair.second));
            }
            data.push_back(tempRow);
            tempRow.clear();
        }
    }
}

/**
 * Loads the scores from the data.
 * @return true if scores are loaded correctly, otherwise false
 * @note this function must be called after new data has been read in order to use the score functions
 * @author Tilde
 */
bool Stats::loadScores()
{
    scores.clear();
    sumScores = 0;

    if (data.empty() || data[0].empty())                        // checks if data is empty
    {
        return true;
    }

    for (const auto& row : data)
    {
        string scoreString = row.back().second;                 // gets the second string of the last pair in the row, i.e. the score
        int scoreInt;

        try {                                               
            scoreInt = stoi(scoreString);                       // tries to convert to int
            scores.push_back(scoreInt);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << ". Score not valid: " << scoreString << endl;
            return false;
        } 
    }

    sumScores = accumulate(scores.begin(), scores.end(), 0);

    return true;
}

/**
 * Calculates the mean of the scores.
 * @return if data is not empty, returns the mean of the scores, otherwise -1
 * @author Tilde
 */
double Stats::calcMean() 
{
    if (scores.empty()) {
        return -1;
    }

    return sumScores/scores.size();
}

/**
 * Calculates the median of the scores.
 * @return if data is not empty, returns the median of the scores, otherwise -1
 * @author Tilde
 */
double Stats::calcMedian()
{
    if (scores.empty()) {
        return -1;
    }

    sort(scores.begin(), scores.end());                         // sorts the scores in ascending order

    int middleIndex = static_cast<int>(scores.size())/2;

    if (scores.size() % 2 == 0)                                 // checks if there is an even number of scores
    {
        double sumOfMiddleScores = scores[middleIndex-1] + scores[middleIndex];
        return sumOfMiddleScores/2;                             // calculates average of middle scores
    }

    return scores[middleIndex];
}

/**
 * Calculates the mode of the scores.
 * @return if data is not empty, returns a vector with the modes of the scores, otherwise returns an empty vector
 * @author Tilde
 */
vector<int> Stats::calcMode()
{
    if (scores.empty()) {
        return vector<int>{};
    }

    auto freqScores = calcFrequencies();

    vector<int> modes;
    int maxFreq = 0;

    for (const auto& freq : freqScores) 
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
 * @return if data is not empty, returns the variance of the scores, otherwise returns -1
 * @author Tilde
 */
double Stats::calcVariance() 
{
    if (scores.empty()) {
        return -1.0;
    }

    double mean = sumScores/scores.size();
    double squaredDiffSum = 0.0;

    for (const auto& score : scores) 
    {
        double squaredDiff = (score-mean)*(score-mean);
        squaredDiffSum += squaredDiff;
    }

    return squaredDiffSum/scores.size();
}

/**
 * Calculates the standard deviation of the scores.
 * @return if data is not empty, returns the standard deviation of the scores, otherwise returns -1
 * @author Tilde
 */
double Stats::calcStandardDeviation() 
{
    double variance = calcVariance();

    if (variance == -1.0) 
    {
        return variance;
    }

    return sqrt(variance);
}

/**
 * Calculates the frequency of each score.
 * @return if data is not empty, returns an unordered map of the frequency of the scores, otherwise returns an empty unordered_map
 * @author Tilde
 */
unordered_map<int, int> Stats::calcFrequencies() 
{
    unordered_map<int, int> freqScores;

    for (const auto& score : scores) 
    {
        freqScores[score] += 1;                                 // adds 1 to the current value of the key. If the key score doesn't exist in the map, creates a key with default value 0 
    }

    return freqScores;
}

/**
 * Calculates the frequency of one score.
 * @param value the score
 * @return if data is not empty, returns the frequency of the score, otherwise returns -1
 * @author Tilde
 */
int Stats::calcFrequency(const int& value)
{
    if (scores.empty()) {
        return -1;
    }

    int freq = 0;

    for (const auto& score : scores) 
    {
        if (value == score)
        {
            freq++;
        }
    }

    return freq;
}

bool Stats::generateStatsFile(json& jsonObj)
{
    jsonObj["mean"] = calcMean();
    jsonObj["median"] = calcMedian();
    jsonObj["mode"] = calcMode();
    jsonObj["variance"] = calcVariance();
    jsonObj["SD"] = calcStandardDeviation();

    auto intFreqs = calcFrequencies();
    unordered_map<string, int> stringFreqs;

    for (const auto& freq : intFreqs)
    {
        stringFreqs[to_string(freq.first)] = freq.second;       // translate all int keys into string keys and add to new map
    }

    jsonObj["frequencies"] = stringFreqs;

    cout << setw(4) << jsonObj << endl;

    return true;
}