#include <gtest/gtest.h>
#include "task1m.h"

TEST(fact_mod, simpleTest)
{
	vector<int> arr = { 1, 1, 2, 6, 24, 120, 720 };
	EXPECT_EQ(fact_mod(6), arr);
}

TEST(fact_mod, overflowTest)
{
	ASSERT_LT(fact_mod(1000)[1000], 1000000007);
	ASSERT_LT(fact_mod(10000)[10000], 1000000007);
	ASSERT_LT(fact_mod(100000)[100000], 1000000007);
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

TEST(welcomeMessage, contentTest)
{
	streambuf* origCin = cin.rdbuf();
	streambuf* origCout = cout.rdbuf();
	string inputData = "\n";
	istringstream inputStream(inputData);
	ostringstream outputStream;
	cin.rdbuf(inputStream.rdbuf());
	cout.rdbuf(outputStream.rdbuf());
	welcomeMessage();
	cin.rdbuf(origCin);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "This program calculates the factorial of the entered number in the range from 0 to " + to_string(INT_MAX) + ".\nIf the result is bigger than 1000000006, program displays the result modulo 1000000007.\nPress ENTER to continue..." + "\033[2J\033[H");
}

TEST(askInt, simpleTest)
{
	streambuf* origCin = cin.rdbuf();

	string inputData1("31");
	istringstream inputStream1(inputData1);
	cin.rdbuf(inputStream1.rdbuf());
	EXPECT_EQ(askInt(), 31);

	string inputData2("2100000000");
	istringstream inputStream2(inputData2);
	cin.rdbuf(inputStream2.rdbuf());
	EXPECT_EQ(askInt(), 2100000000);

	string inputData3("12345");
	istringstream inputStream3(inputData3);
	cin.rdbuf(inputStream3.rdbuf());
	EXPECT_EQ(askInt(), 12345);

	string inputData4("7438436");
	istringstream inputStream4(inputData4);
	cin.rdbuf(inputStream4.rdbuf());
	EXPECT_EQ(askInt(), 7438436);

	cin.rdbuf(origCin);
}

TEST(displayAll, simpleTest)
{
	vector<int> arr = { 1, 1, 2, 6, 24, 120, 720 };
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	displayAll(arr);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	string check = "0! - 1\n"
		"1! - 1\n"
		"2! - 2\n"
		"3! - 6\n"
		"4! - 24\n"
		"5! - 120\n"
		"6! - 720\n";
	EXPECT_EQ(output, check);
}

TEST(displayAll, emptyArrayTest)
{
	vector<int> arr;
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	displayAll(arr);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "ARRAY IS EMPTY!\n");
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

TEST(displayFactorial, simpleTest)
{
	vector<int> arr = { 1, 1, 2, 6, 24, 120, 720 };

	streambuf* origCin = cin.rdbuf();
	string inputData("4");
	istringstream inputStream(inputData);
	cin.rdbuf(inputStream.rdbuf());

	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());

	displayFactorial(arr);

	cout.rdbuf(origCout);
	cin.rdbuf(origCin);

	string output = outputStream.str();
	string check = "Enter the number, which factorial you want to see: 4! - 24\n";

	EXPECT_EQ(output, check);
}

TEST(displayFactorial, emptyArrayTest)
{
	vector<int> arr;
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	displayAll(arr);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "ARRAY IS EMPTY!\n");
}

TEST(fileOutAll, simpleTest)
{
	vector<int> arr = { 1, 1, 2, 6, 24, 120, 720 };

	streambuf* origCin = cin.rdbuf();
	string inputData("testFileOutAllTask1.txt");
	istringstream inputStream(inputData);
	cin.rdbuf(inputStream.rdbuf());

	fileOutAll(arr);

	cin.rdbuf(origCin);

	string check = "0! - 1\n"
		"1! - 1\n"
		"2! - 2\n"
		"3! - 6\n"
		"4! - 24\n"
		"5! - 120\n"
		"6! - 720\n";
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

TEST(fileOutAll, emptyArrayTest)
{
	vector<int> arr;
	streambuf* origCout = cout.rdbuf();
	ostringstream outputStream;
	cout.rdbuf(outputStream.rdbuf());
	displayAll(arr);
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "ARRAY IS EMPTY!\n");
}