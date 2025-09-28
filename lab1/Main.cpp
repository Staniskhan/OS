#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
using namespace std;



struct employee {
    int num;
    char name[10];
    double hours;
};



int main()
{
    string binFileName, numberOfEntries;

    cout << "Enter the name of the binary file: ";
    cin >> binFileName;
    cout << "Enter the number of entries in the binary file: ";
    cin >> numberOfEntries;


    string startCommand = "Creator.exe " + binFileName + ' ' + numberOfEntries;

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(STARTUPINFOA));
	si.cb = sizeof(STARTUPINFOA);

	if (!CreateProcessA(NULL, const_cast<LPSTR>(startCommand.c_str()), NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "Fail in creating process Creator\nExtended info: " << GetLastError();
		system("pause");
		return 1;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
    
	


	ifstream binToConsole(binFileName, ios::binary|ios::in);
	if (!binToConsole.is_open())
	{
		cout << "Error in opening the binary file " << binFileName;
		system("pause");
		return 1;
	}

	cout << "Information from binary file <<" << binFileName << ">>\n";

	employee emp;
	while (binToConsole.read((char*)(&emp), sizeof(emp)))
	{
		cout << emp.num << '\t' << emp.name << '\t' << emp.hours << '\n';
	}
	
	binToConsole.close();

	string reportFileName, hourWorkPayment;
	cout << "Enter name of report file: ";
	cin >> reportFileName;
	cout << "Enter hour work payment: ";
	cin >> hourWorkPayment;

	startCommand = "Reporter.exe " + binFileName + ' ' + reportFileName + ' ' + hourWorkPayment;

	ZeroMemory(&si, sizeof(STARTUPINFOA));
	si.cb = sizeof(STARTUPINFOA);

	if (!CreateProcessA(NULL, const_cast<LPSTR>(startCommand.c_str()), NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "Fail in creating process Reporter\nExtended info: " << GetLastError();
		system("pause");
		return 1;
	}

	WaitForSingleObject(pi.hProcess, INFINITE);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	
	


	ifstream reportToConsole(reportFileName, ios::in);
	if (!reportToConsole.is_open())
	{

		cout << "Error in opening the report file " << reportFileName;
		system("pause");
		return 1;
	}
	

	cout << "Information from report file <<" << reportFileName << ">>\n";
	char curr;
	while (reportToConsole >> noskipws >> curr)
	{
		cout << curr;
	}
	
	
	system("pause");
	return 0;

}