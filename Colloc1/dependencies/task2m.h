#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <sstream>
#include <regex>
using namespace std;

int inputFromConsole(vector<int>& arr)
{
	arr.clear();
	cout << "Enter the numbers separated by a whitespace:\n";
	string line;
	getline(cin, line);
	istringstream iss(line);
	string token;
	int counterOfFaults = 0;
	while (iss >> token)
	{
		try
		{
			arr.push_back(stoi(token));
		}
		catch (...)
		{
			counterOfFaults++;
		}
	}
	return counterOfFaults;
}

void clearConsole()
{
	cout << "\033[2J\033[H";
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

int inputFromFile(vector<int>& arr)
{

	arr.clear();
	string filename = askFileName("Enter the input filename: ");
	ifstream in;
	in.open(filename);
	if (!in.is_open())
	{
		cout << "FILE DID NOT OPEN PROPERLY!";
		return -1;
	}
	string token;
	int counterOfFaults = 0;
	while (in >> token)
	{
		try
		{
			arr.push_back(stoi(token));
		}
		catch (...)
		{
			counterOfFaults++;
		}
	}
	in.close();
	return counterOfFaults;
}

void printArr(vector<int> arr)
{
	if (arr.empty())
	{
		cout << "ARRAY IS EMPTY!\n";
		return;
	}
	cout << "[ " << arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		cout << ", " << arr[i];
	}
	cout << " ]";
}

void fileOutArr(vector<int>arr)
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
	out << "[ " << arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		out << ", " << arr[i];
	}
	out << " ]";
	out.close();
}

void unifyArr(vector<int>& arr)
{
	set s(arr.begin(), arr.end());
	arr.clear();
	arr.assign(s.begin(), s.end());
}

int askInt(string msg = "", int max = INT_MAX, int min = 0)
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

