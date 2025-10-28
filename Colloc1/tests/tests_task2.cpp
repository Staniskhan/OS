#include <gtest/gtest.h>
#include "task2m.h"

TEST(inputFromConsole, simpleTest)
{
	vector<int> arr1 = { 1, 2, 3, 4, 5, 5, 4, 3, 2, 1 };
	vector<int> arr;
	streambuf* origCin = cin.rdbuf();
	string inputData("1 2 3 4 5 h h hh j k 5 4 3 2 1");
	istringstream inputStream(inputData);
	cin.rdbuf(inputStream.rdbuf());
	int n = inputFromConsole(arr);
	EXPECT_EQ(n, 5);
	for (int i = 0; i < arr.size(); i++)
	{
		EXPECT_EQ(arr[i], arr1[i]);
	}
}

TEST(clearConsole, workTest)
{
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	clearConsole();
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "\033[2J\033[H");
}

TEST(checkFileName, simpleTest)
{
	EXPECT_EQ(checkFileName("name"), true);
	EXPECT_EQ(checkFileName("name.txt"), true);
	EXPECT_EQ(checkFileName("name.asd"), true);
	EXPECT_EQ(checkFileName("name.asd.txt"), true);
	EXPECT_EQ(checkFileName("name.asd."), false);
	EXPECT_EQ(checkFileName("name."), false);
	EXPECT_EQ(checkFileName("nam>e.txt"), false);
	EXPECT_EQ(checkFileName("nam<e.txt"), false);
	EXPECT_EQ(checkFileName("nam:e.txt"), false);
	EXPECT_EQ(checkFileName("nam\"e.txt"), false);
	EXPECT_EQ(checkFileName("nam/e.txt"), false);
	EXPECT_EQ(checkFileName("nam\\e.txt"), false);
	EXPECT_EQ(checkFileName("nam|e.txt"), false);
	EXPECT_EQ(checkFileName("nam*e.txt"), false);
	EXPECT_EQ(checkFileName("nam?e.txt"), false);
	EXPECT_EQ(checkFileName("nam>e"), false);
	EXPECT_EQ(checkFileName("nam<e"), false);
	EXPECT_EQ(checkFileName("nam:e"), false);
	EXPECT_EQ(checkFileName("nam\"e"), false);
	EXPECT_EQ(checkFileName("nam/e"), false);
	EXPECT_EQ(checkFileName("nam\\e"), false);
	EXPECT_EQ(checkFileName("nam|e"), false);
	EXPECT_EQ(checkFileName("nam*e"), false);
	EXPECT_EQ(checkFileName("nam?e"), false);
	EXPECT_EQ(checkFileName("CON.txt"), false);
	EXPECT_EQ(checkFileName("AUX.txt"), false);
	EXPECT_EQ(checkFileName("PRN.txt"), false);
	EXPECT_EQ(checkFileName("NUL.txt"), false);
	EXPECT_EQ(checkFileName("COM4.txt"), false);
	EXPECT_EQ(checkFileName("LPT5.txt"), false);
	EXPECT_EQ(checkFileName("CON"), false);
	EXPECT_EQ(checkFileName("AUX"), false);
	EXPECT_EQ(checkFileName("PRN"), false);
	EXPECT_EQ(checkFileName("NUL"), false);
	EXPECT_EQ(checkFileName("COM1"), false);
	EXPECT_EQ(checkFileName("LPT9"), false);
}

TEST(addExtension, simpleTest)
{
	EXPECT_EQ(addExtension("name"), "name.txt");
	EXPECT_EQ(addExtension("name.txt"), "name.txt");
	EXPECT_EQ(addExtension("name.asd"), "name.asd.txt");
}

TEST(inputFromFile, simpleTest)
{
	vector<int> fromFile;
	vector<int> manual = { 1, 14, 15, 4234, 23425 };
	int n;
	ofstream out;
	out.open("testInputFromFileTask2.txt");
	out << "1 14   a as asd !@#   d2 15 4234 23425 f";
	out.close();

	streambuf* origCin = cin.rdbuf();
	string inputData("testInputFromFileTask2.txt");
	istringstream inputStream(inputData);
	cin.rdbuf(inputStream.rdbuf());

	n = inputFromFile(fromFile);

	cin.rdbuf(origCin);
	EXPECT_EQ(n, 6);
	EXPECT_EQ(fromFile, manual);
}

TEST(printArr, simpleTest)
{
	vector<int> arr = { 1, 2, 2, 3, 4, 5 };
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	printArr(arr);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "[ 1, 2, 2, 3, 4, 5 ]");
}

TEST(printArr, emptyArrayTest)
{
	vector<int> arr;
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	printArr(arr);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "ARRAY IS EMPTY!\n");
}

TEST(fileOutArr, simpleTest)
{
	vector<int> arr = { 1, 14, 15, 4234, 23425 };

	streambuf* origCin = cin.rdbuf();
	string inputData("testFileOutAllTask1.txt");
	istringstream inputStream(inputData);
	cin.rdbuf(inputStream.rdbuf());

	fileOutArr(arr);

	cin.rdbuf(origCin);

	string check = "[ 1, 14, 15, 4234, 23425 ]\n";
	string output = "";
	string token;
	ifstream in;
	in.open("testFileOutAllTask1.txt");
	while (getline(in, token))
	{
		output += token + "\n";
	}
	EXPECT_EQ(output, check);
}

TEST(unifyArr, simpleTest)
{
	vector<int> arr = { 1,1,2,2,3,3,4,4,5,5,5,4,3,2,1,3,2,1,4,5,8,1234567,643,345,543,643 };
	vector<int>check = { 1,2,3,4,5,8,345,543,643,1234567 };
	unifyArr(arr);
	EXPECT_EQ(arr, check);
}