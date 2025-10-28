#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
typedef unsigned long long ull;
using namespace std;

vector<int> fact_mod(int n)
{
	ull MAX = 1000000007;
	ull result = 1;
	vector<int> arr;
	arr.push_back(1);
	for (ull i = 1; i <= n; i++)
	{
		result *= i;
		result %= MAX;
		arr.push_back((int)result);
	}
	return arr;
}

void clearConsole()
{
	cout << "\033[2J\033[H";
}

void welcomeMessage()
{
	cout << "This program calculates the factorial of the entered number in the range from 0 to " << INT_MAX << ".\nIf the result is bigger than 1000000006, program displays the result modulo 1000000007.\nPress ENTER to continue...";
	cin.get();
	clearConsole();
}

int askInt(string msg, int max = INT_MAX, int min = 0)
{
	bool ind = true;
	int res;
	while (ind)
	{
		try
		{
			cout << msg;
			string str;
			cin >> str;
			if (str.length() > 10)
			{
				clearConsole();
				cout << "TRY AGAIN!\n";
			}
			else
			{
				if (stoll(str) > (long long)max || stoll(str) < min)
				{
					clearConsole();
					cout << "TRY AGAIN!\n";
				}
				else
				{
					ind = false;
					res = stoi(str);
				}
			}
		}
		catch (invalid_argument)
		{
			clearConsole();
			cout << "TRY AGAIN!\n";
		}
	}
	return res;
}

void displayAll(vector<int> arr)
{
	if (arr.empty())
	{
		cout << "ARRAY IS EMPTY!\n";
		return;
	}
	for (int i = 0; i < arr.size(); i++)
	{
		cout << i << "! - " << arr[i] << endl;
	}
}

bool checkFileName(string filename)
{
	if (regex_match(filename, (regex)".*[><:\"/\\\\|*?].*")
		|| regex_match(filename, (regex)"^CON\\.*[^.]*")
		|| regex_match(filename, (regex)"^AUX\\.*[^.]*")
		|| regex_match(filename, (regex)"^PRN\\.*[^.]*")
		|| regex_match(filename, (regex)"^NUL\\.*[^.]*")
		|| regex_match(filename, (regex)"^COM[1-9]\\.*[^.]*")
		|| regex_match(filename, (regex)"^LPT[1-9]\\.*[^.]*")
		|| regex_match(filename, (regex)"^.*\\.$"))
	{
		return false;
	}
	return true;
}


string addExtension(string filename)
{
	if (!regex_match(filename, (regex)".*[.]txt")) filename += ".txt";
	return filename;
}


string askFileName(string msg)
{
	cout << msg;
	string filename;
	cin >> filename;
	while (!checkFileName(filename))
	{
		cin.get();
		clearConsole();
		cout << "TRY AGAIN!\n" << msg;
		cin >> filename;
	}
	filename = addExtension(filename);
	return filename;
}

void fileOutAll(vector<int> arr)
{
	if (arr.empty())
	{
		cout << "ARRAY IS EMPTY!\n";
		return;
	}
	ofstream out;
	string filename = askFileName("Enter the name of the output file: ");
	out.open(filename);
	if (!out.is_open())
	{
		cout << "FILE DID NOT OPEN PROPERLY!";
		return;
	}
	for (int i = 0; i < arr.size(); i++)
	{
		out << i << "! - " << arr[i] << endl;
	}
	out.close();
}

void fileOutFactorial(vector<int> arr)
{
	if (arr.empty())
	{
		cout << "ARRAY IS EMPTY!\n";
		return;
	}
	ofstream out;
	string filename = askFileName("Enter the name of the output file: ");
	out.open(filename);
	if (!out.is_open())
	{
		cout << "FILE DID NOT OPEN PROPERLY!";
		return;
	}
	int n = askInt("Enter the number, which factorial you want to see: ", arr.size() - 1);
	out << n << "! - " << arr[n] << endl;
	out.close();
}

void displayFactorial(vector<int> arr)
{
	if (arr.empty())
	{
		cout << "ARRAY IS EMPTY!\n";
		return;
	}
	int n = askInt("Enter the number, which factorial you want to see: ", arr.size() - 1);
	cout << n << "! - " << arr[n] << endl;
}

void waitEnter(string msg = "")
{
	cout << msg;
	cin.ignore();
	cin.get();
}

string menuStr()
{
	return "Choose action:\n"
		"1. Set new array.\n"
		"2. Display all factorials in console.\n"
		"3. Display certain factorial in console.\n"
		"4. File out all factorials.\n"
		"5. File out factorial.\n"
		"6. Exit program.\n";
}

void printMenu()
{
	cout << menuStr();
}

int main()
{
	welcomeMessage();
	vector<int> arr;
	int choise = 0;
	int n;
	while (choise != 6)
	{
		choise = askInt(menuStr() + "Choise: ", 6, 1);
		clearConsole();
		switch (choise)
		{
		case 1:
			n = askInt("Enter the number: ");
			arr = fact_mod(n);
			break;
		case 2:
			displayAll(arr);
			break;
		case 3:
			displayFactorial(arr);
			break;
		case 4:
			fileOutAll(arr);
			break;
		case 5:
			fileOutFactorial(arr);
			break;
		}
		waitEnter("Press ENTER to continue...");
		clearConsole();
	}
}