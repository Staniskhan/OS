#include <windows.h>
#undef max
#include <conio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <limits>
#include <vector>
#include <mutex>
#include <map>

using namespace std;


struct employee {
    int num;
    char name[10];
    double hours;
};

vector<HANDLE> processes;



struct RecordLock {
    SRWLOCK lock;
    RecordLock() {
        InitializeSRWLock(&lock);
    }
};

map<int, RecordLock> recordLocks;
mutex recordMapMutex; 


bool createProcesses(const wstring& path, const wstring& params)
{
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));


    wstring cmdLine = L"\"" + path + L"\" " + params;


    if (!CreateProcessW(
        NULL,
        &cmdLine[0],
        NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE,
        NULL, NULL,
        &si, &pi))
    {
        throw runtime_error("Cannot start process: " +
            string(path.begin(), path.end()));
    }

    processes.push_back(pi.hProcess);

    return true;
}

void PrintFile(const string& fileName)
{
    employee emp;
    ifstream file(fileName, ios::binary);
    if (!file)
    {
        cerr << "Couldn't open the file: " << fileName << endl;
        return;
    }

    int index = 1;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        std::cout << "\nEmployee " << index++ << endl;
        std::cout << "ID: " << emp.num << endl;
        std::cout << "Name: " << emp.name << endl;
        std::cout << "Hours: " << emp.hours << endl;
    }
    file.close();

    std::cout << endl;
}

employee FindEmployeeInFile(int employeeNum, const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file) {
        return employee{ 0, "", 0.0 };
    }

    employee emp;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        if (emp.num == employeeNum) {
            return emp;
        }
    }

    return employee{ 0, "", 0.0 };
}

bool ModifyEmployeeInFile(int employeeNum, const employee& newEmp, const string& filename) {
    fstream file(filename, ios::binary | ios::in | ios::out);
    if (!file) {
        return false;
    }

    employee emp;
    streampos pos = 0;
    while (file.read(reinterpret_cast<char*>(&emp), sizeof(employee))) {
        if (emp.num == employeeNum) {
            file.seekp(pos);
            file.write(reinterpret_cast<const char*>(&newEmp), sizeof(employee));
            return true;
        }
        pos = file.tellg();
    }

    return false;
}


RecordLock& GetRecordLock(int employeeNum) {
    lock_guard<mutex> lock(recordMapMutex);
    return recordLocks[employeeNum];
}

struct SRWExclusiveGuard {
    SRWLOCK* lock;
    SRWExclusiveGuard(SRWLOCK* l) : lock(l) { AcquireSRWLockExclusive(lock); }
    ~SRWExclusiveGuard() { ReleaseSRWLockExclusive(lock); }
};

struct SRWSharedGuard {
    SRWLOCK* lock;
    SRWSharedGuard(SRWLOCK* l) : lock(l) { AcquireSRWLockShared(lock); }
    ~SRWSharedGuard() { ReleaseSRWLockShared(lock); }
};

void HandleClient(HANDLE hPipe, const string& filename) {
    char buffer[512];
    DWORD bytesRead;

    while (true) {
        
        BOOL success = ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL);
        if (!success || bytesRead == 0) {
            std::cout << "Client disconnected" << endl;
            break;
        }

        buffer[bytesRead] = '\0';
        string request(buffer);
       

        
        size_t colonPos = request.find(":");
        if (colonPos == string::npos) {
            std::cout << "Invalid request format" << endl;
            continue;
        }

        string operationStr = request.substr(0, colonPos);
        string employeeNumStr = request.substr(colonPos + 1);

        string req;

        if (operationStr == "1") {
            req = "Modification";
        }
        else req = "Reading";

        std::cout << "Request from client: " << req <<" for employee number "<< employeeNumStr<< endl;



        int employeeNum;
        try {
            employeeNum = stoi(employeeNumStr);
        }
        catch (...) {
            std::cout << "Error parsing employee number" << endl;
            continue;
        }

        char buffer[1024];

        if (operationStr == "1") { // modification
            RecordLock& recordLock = GetRecordLock(employeeNum);
            try {
                SRWExclusiveGuard guard(&recordLock.lock); 

                employee emp = FindEmployeeInFile(employeeNum, filename);
                DWORD bytesWritten = 0;
                WriteFile(hPipe, &emp, sizeof(employee), &bytesWritten, NULL);

                while (true) {
                    DWORD bytesRead = 0;
                    if (!ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL) || bytesRead == 0) {
                        break; 
                    }

                    
                    if (bytesRead == sizeof(employee)) {
                        employee newEmp;
                        memcpy(&newEmp, buffer, sizeof(employee));
                        bool result = ModifyEmployeeInFile(employeeNum, newEmp, filename);

                        string resultStr = result ? "SUCCESS" : "FAILED";
                        WriteFile(hPipe, resultStr.c_str(), (DWORD)resultStr.length() + 1, &bytesWritten, NULL);

                        
                        std::cout << "Record " << employeeNum << " saved. Releasing lock." << endl;
                        break;
                    }
                    
                    else {
                        buffer[bytesRead] = '\0';
                        string resp(buffer);
                        if (resp.find("COMPLETE") != string::npos) {
                            std::cout << "Client cancelled modification for " << employeeNum << ". Releasing lock." << endl;
                            break;
                        }
                    }
                }
            }
            catch (...) { throw; }
        }
        else if (operationStr == "2") { // reading
            RecordLock& recordLock = GetRecordLock(employeeNum);

            try {
               
                SRWSharedGuard guard(&recordLock.lock);

                employee emp = FindEmployeeInFile(employeeNum, filename);
                DWORD bytesWritten = 0;
                if (!WriteFile(hPipe, &emp, sizeof(employee), &bytesWritten, NULL)) {
                    cerr << "WriteFile failed: " << GetLastError() << endl;
                }
                else {
                    
                    while (true) {
                        DWORD bytesRead = 0;
                        char textBuf[256];
                        
                        if (!ReadFile(hPipe, textBuf, sizeof(textBuf) - 1, &bytesRead, NULL) || bytesRead == 0) {
                            std::cout << "Client disconnected during read" << endl;
                            break; 
                        }

                        textBuf[bytesRead] = '\0';
                        string response(textBuf);
                        if (response.find("COMPLETE_READ") == 0) {
                            std::cout << "Client completed read access to record " << employeeNum << endl;
                            break; 
                        }
                    }
                }
            }
            catch (...) {
                throw;
            }
        }
        else if (operationStr == "COMPLETE" || operationStr == "COMPLETE_READ") {
            std::cout << "Received completion command for record " << employeeNum << endl;
        }
        else {
            std::cout << "Unknown operation: " << operationStr << endl;
        }
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
}

int askEmpNumber()
{
    int a;
    while (true) {
        std::cout << "Enter the number of employees: ";
        std::cin >> a;
        if (!std::cin) throw runtime_error("EOF or bad input");
        if (a < 0)
        {
            std::cout << "Error: Number of employees can't be negative.\n";
        }
        else
        {
            break;
        }
    }
    return a;
}

int askID()
{
    int ret;
    while (true) {
        std::cout << "Employee's id number: ";
        if (!(std::cin >> ret)) {
            std::cout << "Error: please enter a valid integer for employee id.\n";
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (ret < 0) {
            std::cout << "Error: id can't be negative.\n";
            continue;
        }
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
    }
    return ret;
}

string askName()
{
    string tmp;
    while (true) {
        std::cout << "Employee's name: ";
        if (!std::getline(std::cin, tmp)) {
            std::cout << "Input error. Please try again.\n";
            continue;
        }

        size_t start = tmp.find_first_not_of(" \t");
        size_t end = tmp.find_last_not_of(" \t");

        if (start == string::npos) {
            std::cout << "Name can't be empty. Please try again.\n";
            continue;
        }

        tmp = tmp.substr(start, end - start + 1);


        if (tmp.length() > 9) {
            std::cout << "Error: Name is too long. Maximum length is 9 characters.\n";
            continue;
        }


        return tmp;
    }
}

int askHours()
{
    int a;
    while (true) {
        std::cout << "Number of working hours: ";
        if (!(std::cin >> a)) {
            std::cout << "Error: please enter a valid count of hours.\n";
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (a < 0) {
            std::cout << "Error: Working hours can't be negative.\n";
            continue;
        }
        return a;
    }
}


int main()
{
    try 
    {
        //1.1
        string filename;
        cout << "Enter filename: ";
        if (!getline(cin, filename) || filename.empty()) 
        {
            throw runtime_error("Filename required");
        }
        ofstream out(filename, ios::binary);
        out.exceptions(ofstream::failbit | ofstream::badbit);

        int empNumber;
        empNumber = askEmpNumber();
        
        for (int i = 0; i < empNumber; ++i) 
        {
            employee emp;

            std::cout << "Enter information about employee number " << (i + 1) << "\n";

            emp.num = askID();
            strcpy_s(emp.name, sizeof(emp.name), askName().c_str());
            emp.hours = askHours();

            out.write(reinterpret_cast<const char*>(&emp), sizeof(emp));
        }

        out.close();
        std::cout << empNumber << " records were written into \"" << filename << "\"\n";
        std::cout << "File content: " << endl;
        //1.2
        PrintFile(filename);

        //1.3
        int num_prosses;
        cout << "Enter number of processes:";
        cin >> num_prosses;
        if (cin.fail() || num_prosses <= 0) {
            throw runtime_error("Incorrect array size.");
        }

        wstring senderPath = L"Client.exe";
        wstring senderParams = wstring(filename.begin(), filename.end()) + L" " + to_wstring(empNumber);

        for (int i = 0; i < num_prosses; ++i) {
            createProcesses(senderPath, senderParams);
        }

        vector<HANDLE> pipes (num_prosses);
        vector<thread> clientThreads;

        for (int i = 0; i < num_prosses; ++i) {
            pipes[i] = CreateNamedPipe(
                "\\\\.\\pipe\\NamedPipe",                
                PIPE_ACCESS_DUPLEX,     
                PIPE_TYPE_MESSAGE |    
                PIPE_READMODE_MESSAGE | 
                PIPE_WAIT,              
                PIPE_UNLIMITED_INSTANCES,
                512,                   
                512,                    
                0,                     
                NULL);                  

            if (pipes[i] == INVALID_HANDLE_VALUE) {
                cout << "Pipe's creating error: " << GetLastError() << endl;
                system("pause");
                return 1;
            }

            BOOL connected = ConnectNamedPipe(pipes[i], NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

            clientThreads.emplace_back(HandleClient, pipes[i], filename);

        }

        WaitForMultipleObjects(processes.size(), processes.data(), TRUE, INFINITE);

        cout << "All client processes completed. Server stops requests processing." << endl;
        for (auto& thread : clientThreads) {
            if (thread.joinable()) {
                thread.join();
            }
        }

        for (auto& hProcess : processes) {
            CloseHandle(hProcess);
        }
        processes.clear();

        for (auto& hPipe : pipes) {
            CloseHandle(hPipe);
        }

        cout << "\nFile content: " << endl;
        PrintFile(filename);

        cout << "Enter 1 to shutdown server: " << endl;

        string command;
        while (true) {
            getline(cin, command);
            if (command == "1") {
                break;
            }
            cout << "Unknown command. Enter 1 to shutdown server: " << endl;
        }

        cout << "Server shutdown complete." << endl;
        return 0;
      
    }

    catch (const exception& e) 
    {
        cout << "Exception: " << e.what() << '\n';
                for (auto& h : processes) {
            CloseHandle(h);
        }
        return 1;
    }
    return 0;
}