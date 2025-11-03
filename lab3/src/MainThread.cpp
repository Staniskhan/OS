#include <iostream>
#include <windows.h>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

struct params
{

	int n;
	int* arr;
	int markerNum;
	mutex mStartEvent;
	condition_variable hStartEvent;
	bool bStartEvent;
	vector<mutex> mimpToCont;
	vector<condition_variable> impToCont;
	vector<bool> bimpToCont;
	vector<mutex> mshutDown;
	vector<condition_variable> shutDown;
	vector < bool> bshutDown;
	mutex hMutex;
	mutex hConsoleMutex;
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
	unique_lock<mutex> lock(mcp->p.mStartEvent);
	mcp->p.hStartEvent.wait(lock, mcp->p.bStartEvent);

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
		mcp->p.hMutex.lock();
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
			mcp->p.hMutex.unlock();
		}
		//3.4
		else
		{
			mcp->p.hMutex.unlock();
			//3.4.1
			mcp->p.hConsoleMutex.lock();
			cout << numberOfMarker << " - " << numberOfMarkedElements << " - " << rn << '\n';
			mcp->p.hConsoleMutex.unlock();

			//3.4.2
			lock_guard<mutex> lock(mcp->p.mimpToCont[numberOfMarker - 1]);
			mcp->p.bimpToCont[numberOfMarker - 1] = true;
			mcp->p.impToCont[numberOfMarker - 1].notify_one();                                    ///////////////////////////////////////

			//3.4.3
			unique_lock<mutex> lock(mcp->p.mStartEvent);
			mcp->p.hStartEvent.wait(lock, mcp->p.bStartEvent || mcp->p.bshutDown[numberOfMarker - 1]);
			//HANDLE ifStop[2] = { mcp->p.hStartEvent, mcp->p.shutDown[numberOfMarker - 1] };
			//DWORD result = WaitForMultipleObjects(2, ifStop, FALSE, INFINITE);                         /////////////////////
			if (result == WAIT_OBJECT_0 + 1)
			{
				running = false;
				lock_guard<mutex> lock(mcp->p.mimpToCont[numberOfMarker - 1]);
				mcp->p.bimpToCont[numberOfMarker - 1] = false;
				mcp->p.impToCont[numberOfMarker - 1].notify_one();
			}																				     ///////////////////////////////////////
			else if (result == WAIT_OBJECT_0)
			{
				lock_guard<mutex> lock(mcp->p.mStartEvent);
				mcp->p.bStartEvent = false;
				mcp->p.hStartEvent.notify_one();
			}
		}
	}

	//4
	mcp->p.hMutex.lock();
	for (int i = 0; i < indexes.size(); i++)
	{
		mcp->p.arr[indexes[i]] = 0;
	}
	mcp->p.hMutex.unlock();

	return 0;
}


void initializeZero(params& p)
{
	for (int i = 0; i < p.n; i++)
	{
		p.arr[i] = 0;
	}
}

vector<thread> createThreads(params& p)
{
	vector<thread> threadHandles;
	// INDEXATION FROM 1!!!!!!!
	// p.hMutex = new mutex;	

	for (int i = 1; i <= p.markerNum; i++)
	{
		markerCreateParams* mcp = new markerCreateParams{ p, i };
		thread t(Marker, mcp);
		threadHandles.push_back(t);
		p.bimpToCont.push_back(false);
		p.bshutDown.push_back(false);
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


int main()
{
	params p;
	//1
	//p.hConsoleMutex = CreateMutex(NULL, FALSE, NULL);
	askCapasity(p);

	//2
	initializeZero(p);

	//3
	askMarkerNum(p);

	//4
	vector<thread> threadHandles = createThreads(p);

	//5             //////////////////////////////////
	lock_guard<mutex> lock(p.mStartEvent);
	p.bStartEvent = true;
	p.hStartEvent.notify_all();

	//6
	bool* ifAct = createBoolArray(p.markerNum);
	int numOfLeftMarkers = p.markerNum;
	while (numOfLeftMarkers > 0)
	{
		//6.1
		//WaitForMultipleObjects(leftMarkers, impToCont.data(), TRUE, INFINITE);
		vector<condition_variable> leftMarkers;
		for (int i = 0; i < p.markerNum; i++)
		{
			if (ifAct[i])
			{
				leftMarkers.push_back(p.impToCont[i]);
			}
		}
		WaitForMultipleObjects(numOfLeftMarkers, leftMarkers.data(), TRUE, INFINITE);

		//6.2                                                                                            // mutex
		p.hMutex.lock();
		printArr(p);
		cout << endl;
		p.hMutex.unlock();

		//6.3
		int numOfClosingThread = askNumberOfThreadToClose(p, ifAct);

		//6.4
		SetEvent(p.shutDown[numOfClosingThread - 1]);

		//6.5
		threadHandles[numOfClosingThread - 1].join();
		numOfLeftMarkers--;
		ifAct[numOfClosingThread - 1] = false;

		//6.6
		p.hMutex.lock();
		printArr(p);
		cout << endl;
		p.hMutex.unlock();

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
	for (int i = 0; i < p.markerNum; i++)
	{
		CloseHandle(p.impToCont[i]);
		CloseHandle(p.shutDown[i]);
	}

	system("pause");
}