#include <windows.h>
#include <iostream>

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

void min_max(min_max_struct* ret_struct)
{
	ret_struct->min = ret_struct->arr[0];
	ret_struct->max = ret_struct->arr[0];
	for (int i = 0; i < ret_struct->size; i++)
	{
		if (ret_struct->min > ret_struct->arr[i])
		{
			ret_struct->min = ret_struct->arr[i];
		}
		Sleep(7);
		if (ret_struct->max < ret_struct->arr[i])
		{
			ret_struct->max = ret_struct->arr[i];
		}
		Sleep(7);
	}
	std::cout << "min: " << ret_struct->min << "\nmax: " << ret_struct->max << '\n';

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
	if (((10 * ret_struct->avg) / ret_struct->size) % 10 >= 5)
	{
		ret_struct->avg /= ret_struct->size;
		ret_struct->avg++;
	}
	else
	{
		ret_struct->avg /= ret_struct->size;
	}
	std::cout << "avg: " << ret_struct->avg << '\n';

	ExitThread(0);
}