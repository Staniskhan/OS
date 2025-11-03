#include "task3m.h"

int main()
{
	myList<int> list{ 1, 2, 3, 4, 5, 6 };
	list.showList();
	list.reverse();
	list.showList();
}