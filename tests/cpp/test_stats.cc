#include "libs/math/stats.h"
#include <gtest/gtest.h>
#include <sstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class StatsTest : public ::testing::Test
{
    protected:
        const vector<vector<pair<string,string>>> dataOneLine = { { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} } };
        const vector<vector<pair<string,string>>> dataFull1 = 
        {
            { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
            { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
            { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
            { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "82"} }
        };
        const vector<vector<pair<string,string>>> dataFull2 = 
        {
            { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
            { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
            { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
            { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "77"} }
        };
        const vector<vector<pair<string,string>>> dataFull3 = 
        {
            { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "70"} },
            { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "70"} },
            { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
            { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "90"} }
        };
        const vector<vector<pair<string,string>>> dataEmpty = { {} };

        static shared_ptr<Stats> statsPtr;

    static void SetUpTestSuite()
    {
        statsPtr = make_shared<Stats>();
    }

    static void TearDownTestSuite()
    {
        statsPtr.reset();
    }
};

shared_ptr<Stats> StatsTest::statsPtr = nullptr;

TEST_F(StatsTest, Mean) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcMean(), 88.0);

    statsPtr->readData(dataFull1);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcMean(), 84.25);

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcMean(), -1.0);
}

TEST_F(StatsTest, Median) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcMedian(), 88.0);

    statsPtr->readData(dataFull1);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcMedian(), 85.0);

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcMedian(), -1.0);
}

TEST_F(StatsTest, Mode) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    vector<int> result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 88);

    statsPtr->readData(dataFull1);
    ASSERT_TRUE(statsPtr->loadScores());
    result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 4);

    statsPtr->readData(dataFull2);
    ASSERT_TRUE(statsPtr->loadScores());
    result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 77);

    statsPtr->readData(dataFull3);
    ASSERT_TRUE(statsPtr->loadScores());                
    result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 2);
    EXPECT_TRUE(find(result.begin(), result.end(), 70) != result.end());
    EXPECT_TRUE(find(result.begin(), result.end(), 90) != result.end());

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    result = statsPtr->calcMode();
    ASSERT_TRUE(result.empty());
}

TEST_F(StatsTest, Variance) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcVariance(), 0.0);

    statsPtr->readData(dataFull1);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcVariance(), 26.1875);

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcVariance(), -1.0);
}

TEST_F(StatsTest, StandardDeviation) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcStandardDeviation(), 0.0);

    statsPtr->readData(dataFull3);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcStandardDeviation(), 10);

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_DOUBLE_EQ(statsPtr->calcStandardDeviation(), -1.0);
}

TEST_F(StatsTest, Frequencies) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    auto result = statsPtr->calcFrequencies(); 
    EXPECT_EQ(result[88], 1);

    statsPtr->readData(dataFull2);
    ASSERT_TRUE(statsPtr->loadScores());
    result = statsPtr->calcFrequencies();
    EXPECT_EQ(result[88], 1);
    EXPECT_EQ(result[77], 2);
    EXPECT_EQ(result[90], 1);

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    result = statsPtr->calcFrequencies();
    ASSERT_TRUE(result.empty());
}

TEST_F(StatsTest, Frequency) {
    statsPtr->readData(dataOneLine);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_EQ(statsPtr->calcFrequency(88), 1);

    statsPtr->readData(dataFull2);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_EQ(statsPtr->calcFrequency(88), 1);
    EXPECT_EQ(statsPtr->calcFrequency(77), 2);
    EXPECT_EQ(statsPtr->calcFrequency(90), 1);

    statsPtr->readData(dataEmpty);
    ASSERT_TRUE(statsPtr->loadScores());
    EXPECT_EQ(statsPtr->calcFrequency(88), -1);
}

TEST_F(StatsTest, JSON) {
    statsPtr->readData(dataFull3);
    ASSERT_TRUE(statsPtr->loadScores());

    json jsonObj;
    statsPtr->fillJSONObject(jsonObj);

    EXPECT_DOUBLE_EQ(jsonObj["mean"], 80);
    EXPECT_DOUBLE_EQ(jsonObj["median"], 80);
    auto result = jsonObj["mode"];
    EXPECT_TRUE(find(result.begin(), result.end(), 70) != result.end());
    EXPECT_DOUBLE_EQ(jsonObj["variance"], 100);
    EXPECT_DOUBLE_EQ(jsonObj["SD"], 10);
    EXPECT_EQ(jsonObj["frequencies"]["70"], 2);
}