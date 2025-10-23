#include <iostream>
#include <vector>
#include <windows.h>
#include "header.h"
using namespace std;



void initializeZero(int* arr, int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = 0;
	}
}

vector<HANDLE> createThreads(int markerNum)
{
	hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	vector<HANDLE> threadHandles;
	// INDEXATION FROM 1!!!!!!!
	hMutex = CreateMutex(NULL, FALSE, NULL);
	for (int i = 1; i <= markerNum; i++)
	{
		HANDLE hThread;
		DWORD IDThread;
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Marker, (LPVOID)i, 0, &IDThread);
		threadHandles.push_back(hThread);
		impToCont.push_back(CreateEvent(NULL, TRUE, FALSE, NULL));
		shutDown.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
	}
	return threadHandles;
}

bool* createBoolArray(int markerNum)
{
	bool* ifAct = new bool[markerNum];
	for (int i = 0; i < markerNum; i++)
	{
		ifAct[i] = true;
	}
	return ifAct;
}




void askCapasity(paramstr* param)
{
	cout << "Enter the array capasity: ";
	cin >> param->n;
	param->arr = new int[param->n];
}


int askMarkerNum()
{
	cout << "Enter the number of threads \'Marker\': ";
	int markerNum;
	cin >> markerNum;
	return markerNum;
}

void printArr()
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << ' ';
	}
}



void Marker(LPVOID x)
{
	int numberOfMarker = (int)x;
	//1
	WaitForSingleObject(hStartEvent, INFINITE);

	//2
	srand(numberOfMarker);

	//3
	int numberOfMarkedElements = 0;
	bool running = true;
	vector<int> indexes;
	while (running)
	{
		//3.1
		int rn = rand();

		//3.2
		rn %= n;

		//3.3
		WaitForSingleObject(hMutex, INFINITE);
		if (arr[rn] == 0)
		{
			//3.3.1
			Sleep(5);

			//3.3.2
			arr[rn] = numberOfMarker;
			numberOfMarkedElements++;
			indexes.push_back(rn);

			//3.3.3
			Sleep(5);

			//3.3.4
			ReleaseMutex(hMutex);
		}
		//3.4
		else
		{
			ReleaseMutex(hMutex);
			//3.4.1
			WaitForSingleObject(hConsoleMutex, INFINITE);
			cout << numberOfMarker << " - " << numberOfMarkedElements << " - " << rn << '\n';
			ReleaseMutex(hConsoleMutex);

			//3.4.2
			SetEvent(impToCont[numberOfMarker - 1]);

			//3.4.3
			HANDLE ifStop[2] = { hStartEvent, shutDown[numberOfMarker - 1] };
			DWORD result = WaitForMultipleObjects(2, ifStop, FALSE, INFINITE);                         /////////////////////
			if (result == WAIT_OBJECT_0 + 1)
			{
				running = false;
			}
			ResetEvent(impToCont[numberOfMarker - 1]);

			if (result == WAIT_OBJECT_0)
			{
				ResetEvent(hStartEvent);
			}
		}
	}

	//4
	WaitForSingleObject(hMutex, INFINITE);
	for (int i = 0; i < indexes.size(); i++)
	{
		arr[indexes[i]] = 0;
	}
	ReleaseMutex(hMutex);
}