#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;

struct params
{

	int n;
	int* arr;
	int markerNum;
	HANDLE hStartEvent;
	vector<HANDLE> impToCont;
	vector<HANDLE> shutDown;
	HANDLE hMutex;
	HANDLE hConsoleMutex;
};

struct markerCreateParams
{
	params& p;
	int i;
};

DWORD WINAPI Marker(LPVOID x)
{
	markerCreateParams* mcp = (markerCreateParams*)x;
	int numberOfMarker = mcp->i;
	//1
	WaitForSingleObject(mcp->p.hStartEvent, INFINITE);

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
		rn %= mcp->p.n;

		//3.3
		WaitForSingleObject(mcp->p.hMutex, INFINITE);
		if (mcp->p.arr[rn] == 0)
		{
			//3.3.1
			Sleep(5);

			//3.3.2
			mcp->p.arr[rn] = numberOfMarker;
			numberOfMarkedElements++;
			indexes.push_back(rn);

			//3.3.3
			Sleep(5);

			//3.3.4
			ReleaseMutex(mcp->p.hMutex);
		}
		//3.4
		else
		{
			ReleaseMutex(mcp->p.hMutex);
			//3.4.1
			WaitForSingleObject(mcp->p.hConsoleMutex, INFINITE);
			cout << numberOfMarker << " - " << numberOfMarkedElements << " - " << rn << '\n';
			ReleaseMutex(mcp->p.hConsoleMutex);

			//3.4.2
			SetEvent(mcp->p.impToCont[numberOfMarker - 1]);

			//3.4.3
			HANDLE ifStop[2] = { mcp->p.hStartEvent, mcp->p.shutDown[numberOfMarker - 1] };
			DWORD result = WaitForMultipleObjects(2, ifStop, FALSE, INFINITE);                         /////////////////////
			if (result == WAIT_OBJECT_0 + 1)
			{
				running = false;
				ResetEvent(mcp->p.impToCont[numberOfMarker - 1]);
			}
			else if (result == WAIT_OBJECT_0)
			{
				ResetEvent(mcp->p.hStartEvent);
			}
		}
	}

	//4
	WaitForSingleObject(mcp->p.hMutex, INFINITE);
	for (int i = 0; i < indexes.size(); i++)
	{
		mcp->p.arr[indexes[i]] = 0;
	}
	ReleaseMutex(mcp->p.hMutex);

	return 0;
}


void initializeZero(params& p)
{
	for (int i = 0; i < p.n; i++)
	{
		p.arr[i] = 0;
	}
}

vector<HANDLE> createThreads(params& p)
{
	p.hStartEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	vector<HANDLE> threadHandles;
	// INDEXATION FROM 1!!!!!!!
	p.hMutex = CreateMutex(NULL, FALSE, NULL);

	for (int i = 1; i <= p.markerNum; i++)
	{
		markerCreateParams* mcp = new markerCreateParams{ p, i };
		HANDLE hThread;
		DWORD IDThread;
		hThread = CreateThread(NULL, 0, Marker, mcp, 0, &IDThread);
		threadHandles.push_back(hThread);
		p.impToCont.push_back(CreateEvent(NULL, TRUE, FALSE, NULL));
		p.shutDown.push_back(CreateEvent(NULL, FALSE, FALSE, NULL));
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




void askCapasity(params& p)
{
	cout << "Enter the array capasity: ";
	cin >> p.n;
	p.arr = new int[p.n];
}


void askMarkerNum(params& p)
{
	cout << "Enter the number of threads \'Marker\': ";
	cin >> p.markerNum;
}

void printArr(params& p)
{
	for (int i = 0; i < p.n; i++)
	{
		cout << p.arr[i] << ' ';
	}
}

int askNumberOfThreadToClose(params& p, bool* ifAct)
{
	int numOfClosingThread = -1;
	while (numOfClosingThread < 1 || numOfClosingThread > p.markerNum || !ifAct[numOfClosingThread - 1])
	{
		cout << "\nEnter the number of thread you would like to close (from 1 to " << p.markerNum << "): ";
		cin >> numOfClosingThread;
	}
	return numOfClosingThread;
}

#endif