#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<HANDLE> processes;

wstring CreateCmdLine(const wstring& execPath, const wstring& params) {
    return L"\"" + execPath + L"\" " + params;
}

bool DoProcess(const wstring& execPath, const wstring& params) {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    wstring cmdLine = CreateCmdLine(execPath, params);

    if (!CreateProcessW(
        NULL,
        &cmdLine[0],
        NULL, NULL, FALSE,
        CREATE_NEW_CONSOLE,
        NULL, NULL,
        &si, &pi))
    {
        cout << "Fail in creating process Sender\nLast error: " << GetLastError() << '\n';
        system("pause");
        return 1;
    }

    processes.push_back(pi.hProcess);
    CloseHandle(pi.hThread);

    return true;
}

#endif