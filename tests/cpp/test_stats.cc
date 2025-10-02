#include "libs/math/stats.h"
#include <gtest/gtest.h>

using namespace std;

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
    ASSERT_TRUE(statsPtr->readData(dataOneLine));
    EXPECT_DOUBLE_EQ(statsPtr->calcMean(), 88.0);

    ASSERT_TRUE(statsPtr->readData(dataFull1));
    EXPECT_DOUBLE_EQ(statsPtr->calcMean(), 84.25);

    ASSERT_TRUE(statsPtr->readData(dataEmpty));
    EXPECT_DOUBLE_EQ(statsPtr->calcMean(), -1.0);
}

TEST_F(StatsTest, Median) {
    ASSERT_TRUE(statsPtr->readData(dataOneLine));
    EXPECT_DOUBLE_EQ(statsPtr->calcMedian(), 88.0);

    ASSERT_TRUE(statsPtr->readData(dataFull1));
    EXPECT_DOUBLE_EQ(statsPtr->calcMedian(), 85.0);

    ASSERT_TRUE(statsPtr->readData(dataEmpty));
    EXPECT_DOUBLE_EQ(statsPtr->calcMedian(), -1.0);
}

TEST_F(StatsTest, Mode) {
    ASSERT_TRUE(statsPtr->readData(dataOneLine));
    vector<int> result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 88);

    ASSERT_TRUE(statsPtr->readData(dataFull1));
    result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 4);

    ASSERT_TRUE(statsPtr->readData(dataFull2));
    result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 77);

    ASSERT_TRUE(statsPtr->readData(dataFull3));
    result = statsPtr->calcMode();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 70);
    EXPECT_EQ(result[1], 90);

    ASSERT_TRUE(statsPtr->readData(dataEmpty));
    result = statsPtr->calcMode();
    ASSERT_TRUE(result.empty());
}

TEST_F(StatsTest, Variance) {
    ASSERT_TRUE(statsPtr->readData(dataOneLine));
    EXPECT_DOUBLE_EQ(statsPtr->calcVariance(), 0.0);

    ASSERT_TRUE(statsPtr->readData(dataFull1));
    EXPECT_DOUBLE_EQ(statsPtr->calcVariance(), 26.1875);

    ASSERT_TRUE(statsPtr->readData(dataEmpty));
    EXPECT_DOUBLE_EQ(statsPtr->calcVariance(), -1.0);
}

TEST_F(StatsTest, StandardDeviation) {
    ASSERT_TRUE(statsPtr->readData(dataOneLine));
    EXPECT_DOUBLE_EQ(statsPtr->calcStandardDeviation(), 0.0);

    ASSERT_TRUE(statsPtr->readData(dataFull3));
    EXPECT_DOUBLE_EQ(statsPtr->calcStandardDeviation(), 10);

    ASSERT_TRUE(statsPtr->readData(dataEmpty));
    EXPECT_DOUBLE_EQ(statsPtr->calcStandardDeviation(), -1.0);
}