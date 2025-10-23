#include <windows.h>
#include <vector>
#include <iostream>
using namespace std;



struct paramstr
{
	int n;
	int* arr;
	HANDLE hStartEvent;
	vector<HANDLE> impToCont;
	vector<HANDLE> shutDown;
	HANDLE hMutex;
	HANDLE hConsoleMutex;
};

void initializeZero(int* arr, int n);
vector<HANDLE> createThreads(int markerNum);
bool* createBoolArray(int markerNum);
void askCapasity();
int askMarkerNum();
void printArr();
void Marker(LPVOID x);