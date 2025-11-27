#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <Functions.h>
using namespace std;

int main() {
    try {
        string filename;
        cout << "Enter filename: ";
        if (!getline(cin, filename) || filename.empty()) {
            cout << "Filename is empty!\n";
            system("pause");
            return 1;
        }

        if (std::filesystem::exists(filename))
        {
            std::filesystem::remove(filename);
        }

        int buff;
        cout << "Enter number of messages:";
        cin >> buff;
        if (cin.fail() || buff <= 0) {
            cout << "Incorrect number of messages!";
            system("pause");
            return 1;
        }
        int processesNum;
        cout << "Enter number of processes:";
        cin >> processesNum;
        if (cin.fail() || processesNum <= 0) {
            cout << "Incorrect number of processes!";
            system("pause");
            return 1;
        }

        HANDLE m = CreateSemaphoreA(NULL, 1, 1, "Global\\mutexSemaphore");
        if (m == NULL) {
            cout << "Failed to create mutex-semaphore. Error: " << to_string(GetLastError()) << '\n';
            system("pause");
            return 1;
        }
        HANDLE e = CreateSemaphoreA(NULL, buff, buff, "Global\\emptySemaphore");
        if (e == NULL) {
            cout << "Failed to create free space semaphore. Error: " << to_string(GetLastError()) << '\n';
            system("pause");
            return 1;
        }
        HANDLE f = CreateSemaphoreA(NULL, 0, buff, "Global\\fullSemaphore");
        if (f == NULL) {
            cout << "Failed to create the ocupied space semaphore. Error: " << to_string(GetLastError()) << '\n';
            system("pause");
            return 1;
        }

        HANDLE ss = CreateSemaphoreA(NULL, 0, processesNum, "Global\\StartSemaphore");

        for (int i = 0; i < processesNum; ++i) {
            DoProcess(L"Sender.exe", wstring(filename.begin(), filename.end()));
        }

        if (ss == NULL) {
            cout << "Failed creating start semaphore: " << to_string(GetLastError()) << '\n';
            system("pause");
            return 1;
        }
        for (int i = 0; i < processesNum; i++) {
            DWORD r = WaitForSingleObject(ss, INFINITE);
            if (r != WAIT_OBJECT_0) {
                cout << "WaitForSingleObject failed: " << to_string(GetLastError()) << '\n';
                system("pause");
                return 1;
            }

        }
        cout << "Ready.\n";
        CloseHandle(ss);

        ifstream out(filename, ios::binary);
        if (!out) {
            cout << "Cannot open file for reading: " << filename;
            system("pause");
            return 1;
        }
        string line;
        while (true) {
            char choise = 0;
            cout << "Enter c to continue, e to exit:";
            if (!(cin >> choise)) {
                cout << "Input error.\n";
                break;
            }

            if (choise == 'c') {
                while (true) {
                    WaitForSingleObject(f, INFINITE);
                    WaitForSingleObject(m, INFINITE);
                    if (!getline(out, line)) {
                        if (out.eof()) {
                            ReleaseSemaphore(m, 1, NULL);
                            ReleaseSemaphore(e, 1, NULL);
                            continue;
                        }
                        else {
                            ReleaseSemaphore(m, 1, NULL);
                            ReleaseSemaphore(e, 1, NULL);
                            cout << "Error reading from file\n";
                            system("pause");
                            return 1;
                        }
                    }
                    cout << "Received line: " << line << '\n';

                    if (!ReleaseSemaphore(m, 1, NULL)) {
                        cout << "ReleaseSemaphore(mutex) failed: " << to_string(GetLastError()) << '\n';
                        system("pause");
                        return 1;
                    }
                    if (!ReleaseSemaphore(e, 1, NULL)) {
                        cout << "ReleaseSemaphore(empty) failed: " << to_string(GetLastError()) << '\n';
                        system("pause");
                        return 1;
                    }
                    break;
                }
            }


            else if (choise == 'e') {
                break;
            }
            else {
                cout << "Unknown command. Please enter c or e.\n";
                continue;
            }
        }

    }
    catch (const exception& ex) {
        cout << "Exception: " << ex.what() << '\n';

        for (HANDLE h : processes) {
            CloseHandle(h);
        }
        return 1;
    }
    return 0;
}