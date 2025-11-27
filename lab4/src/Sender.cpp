#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            cout << "Usage: " << argv[0] << " <filename>\n";
            system("pause");
            return 1;
        }

        string filename = argv[1];

        ofstream in(filename, ios::binary | ios::app);
        if (!in) {
            cout << "Error in opening the file " << filename << '\n';
            system("pause");
            return 1;
        }

        HANDLE hStart = OpenSemaphoreW(SEMAPHORE_MODIFY_STATE, FALSE, L"Global\\StartSemaphore");
        if (!hStart) {
            cout << "Error in opening the start semaphore: " << GetLastError() << '\n';
            system("pause");
            return 1;
        }
        if (!ReleaseSemaphore(hStart, 1, NULL)) {
            cout << "ReleaseSemaphore(Start) failed: " << GetLastError() << '\n';
            CloseHandle(hStart);
            system("pause");
            return 1;
        }
        CloseHandle(hStart);

        HANDLE hMutex = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS, FALSE, L"Global\\mutexSemaphore");
        if (hMutex == NULL) {
            cout << "Error in opening the mutex-semaphore: " << GetLastError() << '\n';
            system("pause");
            return 1;
        }

        HANDLE hEmpty = OpenSemaphoreW(SEMAPHORE_ALL_ACCESS, FALSE, L"Global\\emptySemaphore");
        if (hEmpty == NULL) {
            cout << "Error in opening free space semaphore: " << GetLastError() << '\n';
            CloseHandle(hMutex);
            system("pause");
            return 1;
        }
        const char* fullName = "Global\\fullSemaphore";
        HANDLE hFull = OpenSemaphoreA(SEMAPHORE_ALL_ACCESS, FALSE, fullName);
        if (hFull == NULL) {
            cout << "Error in opening the ocupied space semaphore: " << GetLastError() << '\n';
            CloseHandle(hMutex);
            CloseHandle(hEmpty);
            system("pause");
            return 1;
        }


        while (true) {
            cout << "Choose an action:\n";
            cout << "> s - send a message to file\n";
            cout << "> e - exit\n";

            string cmd;
            if (!getline(cin, cmd)) {
                cout << "Input error.\n";
                system("pause");
                break;
            }

            while (!cmd.empty() && isspace((unsigned char)cmd.back())) cmd.pop_back();
            size_t pos = 0;
            while (pos < cmd.size() && isspace((unsigned char)cmd[pos])) ++pos;
            if (pos > 0) cmd.erase(0, pos);

            if (cmd == "s") {

                string line;
                while (true) {
                    cout << "Enter the message (each < 20 characters). Empty line is an input: ";
                    if (!getline(cin, line)) {
                        cout << "Input error.\n";
                        break;
                    }

                    if (line.empty()) {
                        cout << "Message required.";
                        system("pause");
                        return 1;
                    }

                    if (line.size() > 19) {
                        cout << "The message must be less than 20 characters long. Try again.\n";
                        continue;
                    }


                    DWORD wt = WaitForSingleObject(hEmpty, INFINITE);
                    if (wt != WAIT_OBJECT_0) {
                        cout << "WaitForSingleObject(empty) failed: " << GetLastError() << '\n';
                        break;
                    }

                    wt = WaitForSingleObject(hMutex, INFINITE);
                    if (wt != WAIT_OBJECT_0) {
                        cout << "WaitForSingleObject(mutex) failed: " << GetLastError() << '\n';
                        ReleaseSemaphore(hEmpty, 1, NULL);
                        break;
                    }

                    in.write(line.data(), static_cast<streamsize>(line.size()));
                    in.put('\n');
                    in.flush();


                    if (!ReleaseSemaphore(hMutex, 1, NULL)) {
                        cout << "ReleaseSemaphore(mutex) failed: " << GetLastError() << '\n';
                    }
                    if (!ReleaseSemaphore(hFull, 1, NULL)) {
                        cout << "ReleaseSemaphore(full) failed: " << GetLastError() << '\n';
                    }

                    if (!in) {
                        cout << "File write error\n";
                    }

                    break;
                }
            }
            else if (cmd == "e") {
                break;
            }
            else {
                cout << "Unknown command. Please enter s or e.\n";
                continue;
            }
        }


        CloseHandle(hMutex);
        CloseHandle(hEmpty);
        CloseHandle(hFull);
        in.close();
    }
    catch (const exception& ex) {
        cout << "Exception: " << ex.what() << '\n';
        system("pause");
        return 1;
    }
    return 0;
}