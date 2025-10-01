#include "libs/math/stats.h"
#include <gtest/gtest.h>

TEST(StatsTest, Mean) {
    Stats stats;

    vector<vector<pair<string,string>>> data = { { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} } };
    EXPECT_DOUBLE_EQ(stats.calcMean(data), 88.0);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "82"} }
    };
    EXPECT_DOUBLE_EQ(stats.calcMean(data), 84.25);

    data = { {} };
    EXPECT_DOUBLE_EQ(stats.calcMean(data), -1.0);
}

TEST(StatsTest, Median) {
    Stats stats;

    vector<vector<pair<string,string>>> data = { { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} } };
    EXPECT_DOUBLE_EQ(stats.calcMedian(data), 88.0);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "82"} }
    };
    EXPECT_DOUBLE_EQ(stats.calcMedian(data), 85.0);

    data = { {} };
    EXPECT_DOUBLE_EQ(stats.calcMedian(data), -1.0);
}

TEST(StatsTest, Mode) {
    Stats stats;

    vector<vector<pair<string,string>>> data = { { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} } };
    vector<int> result = stats.calcMode(data);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 88);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "82"} }
    };
    result = stats.calcMode(data);
    EXPECT_EQ(result.size(), 4);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "77"} }
    };
    result = stats.calcMode(data);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 77);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "88"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "77"} }
    };
    result = stats.calcMode(data);
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 77);
    EXPECT_EQ(result[1], 88);

    data = { {} };
    result = stats.calcMode(data);
    ASSERT_TRUE(result.empty());
}

TEST(StatsTest, Variance) {
    Stats stats;

    vector<vector<pair<string,string>>> data = { { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} } };
    EXPECT_DOUBLE_EQ(stats.calcVariance(data), 0.0);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "77"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "82"} }
    };
    EXPECT_DOUBLE_EQ(stats.calcVariance(data), 26.1875);

    data = { {} };
    EXPECT_DOUBLE_EQ(stats.calcVariance(data), -1.0);
}

TEST(StatsTest, StandardDeviation) {
    Stats stats;

    vector<vector<pair<string,string>>> data = { { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "88"} } };
    EXPECT_DOUBLE_EQ(stats.calcStandardDeviation(data), 0.0);

    data = 
    {
        { {"id", "1"}, {"name", "Alice"}, {"age", "23"}, {"score", "70"} },
        { {"id", "2"}, {"name", "Bob"}, {"age", "45"}, {"score", "70"} },
        { {"id", "3"}, {"name", "Henry"}, {"age", "32"}, {"score", "90"} },
        { {"id", "4"}, {"name", "Susan"}, {"age", "61"}, {"score", "90"} }
    };
    EXPECT_DOUBLE_EQ(stats.calcStandardDeviation(data), 10);

    data = { {} };
    EXPECT_DOUBLE_EQ(stats.calcStandardDeviation(data), -1.0);
}