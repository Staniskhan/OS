#include <gtest/gtest.h>
#include "task3m.h"

TEST(isEmpty, simpleTest)
{
	myList<int> list{ 1, 2, 3, 4, 5, 6, 100000, INT_MAX, INT_MIN };
	EXPECT_EQ(list.isEmpty(), false);
	myList<int> list1;
	EXPECT_EQ(list1.isEmpty(), true);
}

TEST(getFirst, simpleTest)
{
	myList<int> list{ 1, 2, 3, 4, 5, 6, 100000, INT_MAX, INT_MIN };
	EXPECT_EQ(list.getFirst(), 1);
	myList<int> list1{ INT_MAX, 2, 3, 4, 5, 6, 100000, 1, INT_MIN };
	EXPECT_EQ(list1.getFirst(), INT_MAX);
	myList<char> list2{ 'q', 'f', '3', '$', '3'};
	EXPECT_EQ(list2.getFirst(), 'q');
	myList<double> list3{ 8645645.1234332, 2.2, 3.543 };
	EXPECT_EQ(list3.getFirst(), 8645645.1234332);
	myList<float> list4{ 645.123, 2.2, 3.543 };
	EXPECT_EQ(list4.getFirst(), (float)645.123);
}

TEST(getLast, simpleTest)
{
	myList<int> list{ 1, 2, 3, 4, 5, 6, 100000, INT_MAX, INT_MIN };
	EXPECT_EQ(list.getLast(), INT_MIN);
	myList<int> list1{ INT_MAX, 2, 3, 4, 5, 6, 100000, 1 };
	EXPECT_EQ(list1.getLast(), 1);
	myList<char> list2{ 'q', 'f', '3', '$', '3' };
	EXPECT_EQ(list2.getLast(), '3');
	myList<double> list3{ 2.2, 3.543, 8645645.1234332 };
	EXPECT_EQ(list3.getLast(), 8645645.1234332);
	myList<float> list4{ 645.123, 2.2, 3.543 };
	EXPECT_EQ(list4.getLast(), (float)3.543);
}

TEST(pushHead, simpleTest)
{
	myList<int> list{ 1, 2, 3 };
	list.pushHead(8);
	EXPECT_EQ(list.getFirst(), 8);
}

TEST(pushTail, simpleTest)
{
	myList<int> list{ 1, 2, 3 };
	list.pushTail(8);
	EXPECT_EQ(list.getLast(), 8);
}

TEST(showList, simpleTestInt)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<int> list{ 1, 2, 3,4,23,423,3124123,3 };
	list.showList();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "{1, 2, 3, 4, 23, 423, 3124123, 3}");
}

TEST(showList, simpleTestChar)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<char> list{ 's', 'g', '$','@','a','t','1','a'};
	list.showList();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "{s, g, $, @, a, t, 1, a}");
}

TEST(showList, simpleTestString)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<string> list{ "asd", "asd", "23d","2@2"};
	list.showList();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "{asd, asd, 23d, 2@2}");
}

TEST(showList, simpleTestDouble)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<double> list{ 2.3, 2345.54, 2.12453,-15.294 };
	list.showList();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "{2.3, 2345.54, 2.12453, -15.294}");
}

TEST(showList, emptyListTest)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<double> list;
	list.showList();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "THE LIST IS EMPTY!");
}

TEST(showLikeString, simpleTestInt)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<int> list{ 1, 2, 3,4,23,423,3124123,3 };
	list.showLikeString();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "12342342331241233");
}

TEST(showLikeString, simpleTestChar)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<char> list{ 's', 'g', '$','@','a','t','1','a' };
	list.showLikeString();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "sg$@at1a");
}

TEST(showLikeString, simpleTestString)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<string> list{ "asd", "asd", "23d","2@2" };
	list.showLikeString();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "asdasd23d2@2");
}

TEST(showLikeString, simpleTestDouble)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<double> list{ 2.3, 2345.54, 2.12453,-15.294 };
	list.showLikeString();
	cout.rdbuf(origCout);
	string output = outputStream.str();;
	EXPECT_EQ(output, "2.32345.542.12453-15.294");
}

TEST(showLikeString, emptyListTest)
{
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());
	myList<double> list;
	list.showList();
	cout.rdbuf(origCout);
	string output = outputStream.str();
	EXPECT_EQ(output, "THE LIST IS EMPTY!");
}

TEST(clear, simpleTest)
{
	myList<int> list{ 1,2,3,4,5 };

	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "12345");

	list.clear();

	ostringstream outputStream1;
	cout.rdbuf(outputStream1.rdbuf());

	cout.rdbuf(outputStream1.rdbuf());
	list.showLikeString();
	cout.rdbuf(origCout);
	output = outputStream1.str();
	EXPECT_EQ(output, "THE LIST IS EMPTY!");
}

TEST(deleteElement, simpleTest)
{
	myList<int> list{ 1,2,3,4,5,1,2,3,4,5,5,4,3,2,1 };

	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.deleteElement(2);
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "134513455431");
}

TEST(changeElement, simpleTest)
{
	myList<int> list{ 1,2,3,4,5,1,2,3,4,5,5,4,3,2,1 };

	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.changeElement(2, 1000);
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "110003451100034554310001");
}

TEST(reverse, simpleTestInt)
{
	myList<int> list{ 1,2,3,4,5,1,2,3,4,5,5,4,3,2,1 };

	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.reverse();
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "123455432154321");
}

TEST(reverse, simpleTestChar)
{
	myList<char> list{ 'a','s','d','f','g','h','g'};

	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.reverse();
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "ghgfdsa");
}

TEST(reverse, simpleTestString)
{
	myList<string> list{ "asd", "fh", "3d@"};

	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.reverse();
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "3d@fhasd");
}

TEST(reverse, oneElementTest)
{
	myList<int> list = { 123 };
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.reverse();
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "123");
}

TEST(reverse, emptyListTest)
{
	myList<int> list;
	ostringstream outputStream;
	streambuf* origCout = cout.rdbuf(outputStream.rdbuf());

	list.reverse();
	list.showLikeString();

	cout.rdbuf(origCout);
	string output = outputStream.str();

	EXPECT_EQ(output, "THE LIST IS EMPTY!");
}