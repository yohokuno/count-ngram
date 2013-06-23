#include <gtest/gtest.h>
#include "lossyCounter.hpp"

typedef LossyCounter<int> Counter;
typedef LossyCounter<int>::Iterator Iterator;

TEST(LossyCounterTestCase, LossyCounterTest) {
    Counter counter(3);

    for (int i : {100,100,100,101,102}) {
        counter.count(i);
    }

    set<pair<int,size_t> > actual(counter.begin(), counter.end()),
        expected = {{100,3},{101,2},{102,2}};

    EXPECT_EQ(expected, actual);
}

TEST(LossyCounterTestCase, TakeFrequentTest) {
    Counter counter(10);

    for (int i : {100,100,100,101,102,102,103}) {
        counter.count(i);
    }

    deque<Iterator> actual;
    counter.takeFrequent(actual, 2);

    EXPECT_EQ(2, actual.size());
    EXPECT_EQ(100, actual[0]->first);
    EXPECT_EQ(3, actual[0]->second);
    EXPECT_EQ(102, actual[1]->first);
    EXPECT_EQ(2, actual[1]->second);
}

TEST(LossyCounterTestCase, ExtractNgramTest) {
    vector<string> actual = extractNgram("a b c", 2, "^", "");
    vector<string> expected = {"^","a","^ a","b","a b","c","b c"};

    EXPECT_EQ(expected, actual);
}
