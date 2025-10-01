#include <gtest/gtest.h>
#include "../src/lab2WinAPI.cpp"


TEST(ArrayCalculations, MinMaxCalculation) {
    int *arr = new int[5]{ 3, 1, 4, 1, 5 };
    min_max_struct mms;
    mms.arr = arr;
    mms.size = 5;
    min_max(&mms);
    EXPECT_EQ(mms.min, 1);
    EXPECT_EQ(mms.max, 5);
}

//TEST(ArrayCalculations, AverageCalculation) {
//    int arr[] = { 1, 2, 3, 4, 5 };
//    EXPECT_EQ(calculate_average(arr, 5), 3);
//}
//
//TEST(ArrayCalculations, EmptyArray) {
//    int* arr = nullptr;
//    // Здесь нужно добавить обработку пустого массива в функциях
//}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}