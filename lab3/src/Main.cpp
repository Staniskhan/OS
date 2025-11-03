#include <iostream>
#include <windows.h>
#include <vector>
#include "functions.h"
using namespace std;

int main()
{
	params p;
	//1
	p.hConsoleMutex = CreateMutex(NULL, FALSE, NULL);
	askCapasity(p);

	//2
	initializeZero(p);

	//3
	askMarkerNum(p);

	//4
	vector<HANDLE> threadHandles = createThreads(p);

	//5
	SetEvent(p.hStartEvent);                  //////////////////////////////////

	//6
	bool* ifAct = createBoolArray(p.markerNum);
	int numOfLeftMarkers = p.markerNum;
	while (numOfLeftMarkers > 0)
	{
		//6.1
		//WaitForMultipleObjects(leftMarkers, impToCont.data(), TRUE, INFINITE);
		vector<HANDLE> leftMarkers;
		for (int i = 0; i < p.markerNum; i++)
		{
			if (ifAct[i])
			{
				leftMarkers.push_back(p.impToCont[i]);
			}
		}
		WaitForMultipleObjects(numOfLeftMarkers, leftMarkers.data(), TRUE, INFINITE);

		//6.2                                                                                            // mutex
		WaitForSingleObject(p.hMutex, INFINITE);
		printArr(p);
		cout << endl;
		ReleaseMutex(p.hMutex);

		//6.3
		int numOfClosingThread = askNumberOfThreadToClose(p, ifAct);

		//6.4
		SetEvent(p.shutDown[numOfClosingThread - 1]);

		//6.5
		WaitForSingleObject(threadHandles[numOfClosingThread - 1], INFINITE);
		numOfLeftMarkers--;
		ifAct[numOfClosingThread - 1] = false;

		//6.6
		WaitForSingleObject(p.hMutex, INFINITE);
		printArr(p);
		cout << endl;
		ReleaseMutex(p.hMutex);

		for (int i = 0; i < p.markerNum; i++)
		{
			if (ifAct[i])
			{
				ResetEvent(p.impToCont[i]);
			}
		}

		//6.7
		SetEvent(p.hStartEvent);                                                   /////////////////////////
	}

	delete[] p.arr;
	delete[] ifAct;
	CloseHandle(p.hStartEvent);
	CloseHandle(p.hMutex);
	CloseHandle(p.hConsoleMutex);
	for (int i = 0; i < p.markerNum; i++)
	{
		CloseHandle(p.impToCont[i]);
		CloseHandle(p.shutDown[i]);
		CloseHandle(threadHandles[i]);
	}

	system("pause");
}