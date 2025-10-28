#include <task1m.h>

int main()
{
	welcomeMessage();
	vector<int> arr;
	int choise = 0;
	int n;
	while (choise != 6)
	{
		choise = askInt(menuStr() + "Choise: ", 6, 1);
		clearConsole();
		switch (choise)
		{
		case 1:
			n = askInt("Enter the number: ");
			arr = fact_mod(n);
			break;
		case 2:
			displayAll(arr);
			break;
		case 3:
			displayFactorial(arr);
			break;
		case 4:
			fileOutAll(arr);
			break;
		case 5:
			fileOutFactorial(arr);
			break;
		}
		waitEnter("Press ENTER to continue...");
		clearConsole();
	}
}