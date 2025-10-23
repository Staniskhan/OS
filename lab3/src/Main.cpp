#include "header.h"
#include <iostream>
#include <windows.h>
#include <vector>
using namespace std;









int main()
{
	paramstr param;
	//1
	hConsoleMutex = CreateMutex(NULL, FALSE, NULL);
	askCapasity();

	//2
	initializeZero(param.arr, param.n);

	//3
	int markerNum = askMarkerNum();

	//4
	vector<HANDLE> threadHandles = createThreads(markerNum);

	//5
	SetEvent(hStartEvent);                  //////////////////////////////////

	//6
	bool* ifAct = createBoolArray(markerNum);
	int numOfLeftMarkers = markerNum;
	while (numOfLeftMarkers > 0)
	{
		//6.1
		//WaitForMultipleObjects(leftMarkers, impToCont.data(), TRUE, INFINITE);
		vector<HANDLE> leftMarkers;
		for (int i = 0; i < markerNum; i++)
		{
			if (ifAct[i])
			{
				leftMarkers.push_back(impToCont[i]);
			}
		}
		WaitForMultipleObjects(numOfLeftMarkers, leftMarkers.data(), TRUE, INFINITE);

		//6.2                                                                                            // mutex
		WaitForSingleObject(hMutex, INFINITE);
		printArr();
		cout << endl;
		ReleaseMutex(hMutex);

		//6.3
		int numOfClosingThread = -1;
		while (numOfClosingThread < 1 || numOfClosingThread > markerNum || !ifAct[numOfClosingThread - 1])
		{
			cout << "\nEnter the number of thread you would like to close (from 1 to " << markerNum << "): ";
			cin >> numOfClosingThread;
		}

		//6.4
		SetEvent(shutDown[numOfClosingThread - 1]);

		//6.5
		WaitForSingleObject(threadHandles[numOfClosingThread - 1], INFINITE);
		numOfLeftMarkers--;
		ifAct[numOfClosingThread - 1] = false;

		//6.6
		WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < n; i++)
		{
			cout << arr[i] << ' ';
		}
		cout << endl;
		ReleaseMutex(hMutex);

		for (int i = 0; i < markerNum; i++)
		{
			if (ifAct[i])
			{
				ResetEvent(impToCont[i]);
			}
		}

		//6.7
		SetEvent(hStartEvent);                                                   /////////////////////////
	}

	delete[] arr;
	delete[] ifAct;
	CloseHandle(hStartEvent);
	CloseHandle(hMutex);
	CloseHandle(hConsoleMutex);
	for (int i = 0; i < markerNum; i++)
	{
		CloseHandle(impToCont[i]);
		CloseHandle(shutDown[i]);
		CloseHandle(threadHandles[i]);
	}

	system("pause");
}