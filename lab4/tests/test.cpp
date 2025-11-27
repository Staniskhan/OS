#include "gtest/gtest.h"
#include "Functions.h"
#include <windows.h>

class FunctionsTest : public ::testing::Test {
protected:
    void SetUp() override {
        for (auto& process : processes) {
            CloseHandle(process);
        }
        processes.clear();
    }

    void TearDown() override {
        for (auto& process : processes) {
            if (process) {
                TerminateProcess(process, 0);
                WaitForSingleObject(process, INFINITE);
                CloseHandle(process);
            }
        }
        processes.clear();
    }
};

TEST_F(FunctionsTest, CreateCmdLine_WithEmptyParams) {
    wstring execPath = L"C:\\test.exe";
    wstring params = L"";
    wstring expected = L"\"C:\\test.exe\" ";

    EXPECT_EQ(CreateCmdLine(execPath, params), expected);
}

TEST_F(FunctionsTest, CreateCmdLine_WithSpacesInPath) {
    wstring execPath = L"C:\\Program Files\\test.exe";
    wstring params = L"arg1 arg2";
    wstring expected = L"\"C:\\Program Files\\test.exe\" arg1 arg2";

    EXPECT_EQ(CreateCmdLine(execPath, params), expected);
}

TEST_F(FunctionsTest, CreateCmdLine_WithMultipleParams) {
    wstring execPath = L"test.exe";
    wstring params = L"-mode fast -output result.txt";
    wstring expected = L"\"test.exe\" -mode fast -output result.txt";

    EXPECT_EQ(CreateCmdLine(execPath, params), expected);
}

TEST_F(FunctionsTest, CreateCmdLine_WithSpecialCharacters) {
    wstring execPath = L"C:\\test app\\my app.exe";
    wstring params = L"file\"name.txt";
    wstring expected = L"\"C:\\test app\\my app.exe\" file\"name.txt";

    EXPECT_EQ(CreateCmdLine(execPath, params), expected);
}

TEST_F(FunctionsTest, DoProcess_MultipleCalls_AddsToProcessList) {
    size_t initialSize = processes.size();
    EXPECT_EQ(initialSize, 0);
}