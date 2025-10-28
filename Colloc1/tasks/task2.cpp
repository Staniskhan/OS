#include "task2m.h"

int main()
{
	vector<int> arr;
	int n = askInt("Do you want to input the array manually(1) or from the file(2)?\n>", 2, 1);
	cin.ignore();
	switch (n)
	{
	case 1:
		n = inputFromConsole(arr);
		break;
	case 2:
		n = inputFromFile(arr);
		break;
	}
	cout << endl << "The number of rejected elements: " << n << endl << "Original array:\n";
	printArr(arr);
	unifyArr(arr);
	cout << endl << "There are only unique elements left in the array." << endl;
	n = askInt("Do you want to display the unified array to the console(1) or to the file(2)?\n>", 2, 1);
	switch (n)
	{
	case 1:
		cout << "Unified array:\n";
		printArr(arr);
		break;
	case 2:
		fileOutArr(arr);
		break;
	}
	cout << "\nPress ENTER to finish the program...\n";
	cin.ignore();
	cin.get();
}