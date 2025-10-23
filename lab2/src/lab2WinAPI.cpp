#include <iostream>
#include <windows.h>
#include <ThreadsWinAPI.h>





int main()
{
	//creating an array
	int n;
	std::cout << "Enter the size of array: ";
	std::cin >> n;
	int* arr = new int[n];
	std::cout << "Enter the elements of array separating them with whitespace or each on a new line:\n";
	for (int i = 0; i < n; i++)
	{
		std::cin >> arr[i];
	}

	//filling structures
	min_max_struct mms;
	mms.arr = arr;
	mms.size = n;

	avg_struct as;
	as.arr = arr;
	as.size = n;

	//launching threads
	HANDLE hMinMaxThread;
	DWORD IDMinMaxThread;
	HANDLE hAvgThread;
	DWORD IDAvgThread;

	hMinMaxThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)min_max, &mms, 0, &IDMinMaxThread);
	if (hMinMaxThread == NULL)
	{
		return GetLastError();
	}
	hAvgThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)average, &as, 0, &IDAvgThread);
	if (hAvgThread == NULL)
	{
		return GetLastError();
	}
	WaitForSingleObject(hMinMaxThread, INFINITE);
	CloseHandle(hMinMaxThread);
	WaitForSingleObject(hAvgThread, INFINITE);
	CloseHandle(hAvgThread);



	//processing the array
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == mms.min || arr[i] == mms.max)
		{
			arr[i] = as.avg;
		}
	}

	//displaying the processed array
	std::cout << "\n\nThe processed array:\n";
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << "\n\n";

	system("pause");
	ExitThread(0);
}
