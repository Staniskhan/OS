#include <iostream>
#include <fstream>
using namespace std;



struct employee {
    int num;
    char name[10];
    double hours;
};




int main(int argc, char* argv[]) 
{
    if (argc != 3) 
    {
        cout << "Usage: Creator *name_of_binary_file* *number_of_entries*" << endl;
        return 1;
    }

    int numberOfEntries = atoi(argv[2]);

    ofstream out(argv[1], ios::binary|ios::out);

    if (!out.is_open())
    {
        cout << "Error in opening the file " << argv[1] << endl;
        return 1;
    }

    employee emp;
    for (int i = 0; i < numberOfEntries; i++)
    {
        cout << "Enter employee ID: ";
        cin >> emp.num;
        cout << "Enter employee name: ";
        cin >> emp.name;
        cout << "Enter the number of hours worked: ";
        cin >> emp.hours;

        out.write((char*)(&emp), sizeof(emp));
    }

    out.close();
    return 0;
}