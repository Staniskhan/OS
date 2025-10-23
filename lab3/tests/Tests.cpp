#include <catch2/catch_test_macros.hpp>
#include <memory>

#include <windows.h>
#include "header.h"


    //int n;
    //int* arr;
    //std::vector<HANDLE> impToCont;
    //std::vector<HANDLE> shutDown;

//
//// Тестируемые функции (вынесены в отдельный модуль)
//void initializeZero(int* arr, int n) {
//    for (int i = 0; i < n; i++) arr[i] = 0;
//}
//
//std::vector<HANDLE> createThreads(int markerNum) {
//    std::vector<HANDLE> handles;
//    for (int i = 0; i < markerNum; i++) {
//        handles.push_back(CreateEvent(NULL, TRUE, FALSE, NULL));
//    }
//    return handles;
//}

//bool* createBoolArray(int markerNum) {
//    bool* arr = new bool[markerNum];
//    for (int i = 0; i < markerNum; i++) arr[i] = true;
//    return arr;
//}

TEST_CASE("initializeZero инициализирует массив нулями") {
    //const int size = 5;
    //int* testArr = new int[size] {1, 2, 3, 4, 5};

    initializeZero();

    for (int i = 0; i < n; i++) {
        REQUIRE(arr[i] == 0);
    }
    delete[] arr;
}

TEST_CASE("createBoolArray создает массив правильного размера") {
    const int num = 3;
    bool* boolArr = createBoolArray(num);

    REQUIRE(boolArr != nullptr);
    for (int i = 0; i < num; i++) {
        REQUIRE(boolArr[i] == true);
    }
    delete[] boolArr;
}

TEST_CASE("createBoolArray корректно обрабатывает нулевой размер") {
    bool* boolArr = createBoolArray(0);
    REQUIRE(boolArr != nullptr); // Допустимо, но массив пуст
    delete[] boolArr;
}

TEST_CASE("createThreads создает корректное количество потоков") {
    const int threadCount = 4;
    auto handles = createThreads(threadCount);

    REQUIRE(handles.size() == threadCount);
    for (auto handle : handles) {
        REQUIRE(handle != NULL);
        CloseHandle(handle);
    }
}

TEST_CASE("createThreads обрабатывает нулевое количество потоков") {
    auto handles = createThreads(0);
    REQUIRE(handles.empty());
}