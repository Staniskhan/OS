#include <iostream>
#include <windows.h>

struct min_max_struct
{
	int* arr;
	int size;
	int min;
	int max;
};

struct avg_struct
{
	int* arr;
	int size;
	int avg;
};

void min_max(min_max_struct *ret_struct)
{
	ret_struct->min = ret_struct->arr[0];
	ret_struct->max = ret_struct->arr[0];
	for (int i = 0; i < ret_struct->size; i++)
	{
		if (ret_struct->min > ret_struct->arr[i])
		{
			ret_struct->min = ret_struct->arr[i];
			Sleep(7);
		}
		else if (ret_struct->max < ret_struct->arr[i])
		{
			ret_struct->max = ret_struct->arr[i];
			Sleep(7);
		}
	}

	ExitThread(0);
}

void average(avg_struct* ret_struct)
{
	ret_struct->avg = 0;
	for (int i = 0; i < ret_struct->size; i++)
	{
		ret_struct->avg += ret_struct->arr[i];
		Sleep(12);
	}
	if (((10*ret_struct->avg) / ret_struct->size) % 10 >= 5)
	{
		ret_struct->avg /= ret_struct->size;
		ret_struct->avg++;
	}
	else
	{
		ret_struct->avg /= ret_struct->size;
	}

	ExitThread(0);
}

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

	//displaying results of threads
	std::cout 
		<< "min: " << mms.min 
		<< "\nmax: " << mms.max
		<< "\navg: " << as.avg;

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
