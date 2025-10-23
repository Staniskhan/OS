#include <gtest/gtest.h>
#include "ThreadsWinAPI.h"


TEST(MinMaxCalculations, simpleTest) {
    int *arr = new int[5]{ 3, 1, 4, 1, 5 };
    min_max_struct mms;
    mms.arr = arr;
    mms.size = 5;
    min_max(&mms);
    EXPECT_EQ(mms.min, 1);
    EXPECT_EQ(mms.max, 5);
}

TEST(MinMaxCalculations, overflowTest) {
    int* arr = new int[6] {2147483647, -7651, -2147483646, 147, 57472 };
    min_max_struct mms;
    mms.arr = arr;
    mms.size = 5;
    min_max(&mms);
    EXPECT_EQ(mms.min, -2147483646);
    EXPECT_EQ(mms.max, 2147483647);
}

TEST(AverageCalculations, simpleTest) {
    int* arr = new int[5] { 3, 1, 4, 1, 5 };
    avg_struct as;
    as.arr = arr;
    as.size = 5;
    average(&as);
    EXPECT_EQ(as.avg, 3);
}

TEST(AverageCalculations, overflowTest) {
    int* arr = new int[5] {2147483647, 57, -2147483646, 11556, -6545 };
    avg_struct as;
    as.arr = arr;
    as.size = 5;
    average(&as);
    EXPECT_EQ(as.avg, 1014);
}
