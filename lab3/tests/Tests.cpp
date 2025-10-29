#include <sstream>
#include "functions.h"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>

TEST_CASE("initializeZero() simple test")
{
    params p;
    p.n = 10;
    p.arr = new int[10];
    initializeZero(p);
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(p.arr[i] == 0);
    }
    delete[] p.arr;
}

TEST_CASE("createBoolArray() simple test")
{
    bool* arr = createBoolArray(150);
    for (int i = 0; i < 150; i++)
    {
        REQUIRE(arr[i] == true);
    }
    delete[] arr;
}

//TEST_CASE("createBoolArray() throwing exception test")
//{
//    bool* arr;
//    REQUIRE_THROWS(arr = createBoolArray(-1));
//}

TEST_CASE("askCapacity() simple test")
{
    streambuf* origCin = cin.rdbuf();
    string inputData("31");
    istringstream inputStream(inputData);
    cin.rdbuf(inputStream.rdbuf());

    params p;
    askCapasity(p);

    REQUIRE(p.n == 31);
    REQUIRE_NOTHROW(p.arr[30]);

    cin.rdbuf(origCin);
}

TEST_CASE("askMarkerNum() simple test")
{
    streambuf* origCin = cin.rdbuf();
    string inputData("123");
    istringstream inputStream(inputData);
    cin.rdbuf(inputStream.rdbuf());

    params p;
    askMarkerNum(p);

    REQUIRE(p.markerNum == 123);

    cin.rdbuf(origCin);
}

TEST_CASE("printArr() simple test")
{
    streambuf* origCout = cout.rdbuf();
    ostringstream outputStream;
    cout.rdbuf(outputStream.rdbuf());
    params p;
    p.n = 7;
    p.arr = new int[7];
    for (int i = 0; i < 7; i++)
    {
        p.arr[i] = 2 * i + 3;
    }
    printArr(p);
    cout.rdbuf(origCout);
    string output = outputStream.str();
    REQUIRE(output == "3 5 7 9 11 13 15 ");
}

TEST_CASE("askNumberOfThreadToClose() simple test")
{
    SECTION("writing number of the thread to close with the 1-st try")
    {
        streambuf* origCin = cin.rdbuf();
        string inputData("1");
        istringstream inputStream(inputData);
        cin.rdbuf(inputStream.rdbuf());

        params p;
        p.markerNum = 3;
        bool* ifAct = new bool[3];
        ifAct[0] = true;
        ifAct[1] = true;
        ifAct[2] = true;

        REQUIRE(askNumberOfThreadToClose(p, ifAct) == 1);

        cin.rdbuf(origCin);
        delete[] ifAct;
    }

    SECTION("writing number of the thread to close with the 1-st try")
    {
        streambuf* origCin = cin.rdbuf();
        string inputData("1 1 3 3 1 3 1 1 1 3 1 3 3 1 2 3 1 2 2 1 3 2 1 3 1 2 1 3 1");
        istringstream inputStream(inputData);
        cin.rdbuf(inputStream.rdbuf());

        params p;
        p.markerNum = 3;
        bool* ifAct = new bool[3];
        ifAct[0] = false;
        ifAct[1] = true;
        ifAct[2] = false;

        REQUIRE(askNumberOfThreadToClose(p, ifAct) == 2);

        cin.rdbuf(origCin);
        delete[] ifAct;
    }
}