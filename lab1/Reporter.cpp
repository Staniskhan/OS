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
    if (argc != 4)
    {
        cout << "Usage: Reporter *name_of_binary_file* *name_of_the_report_file* *hour_work_payment*" << endl;
        return 1;
    }

    int numberOfEntries = atoi(argv[2]);


    ifstream in(argv[1], ios::binary | ios::in);
    if (!in.is_open())
    {
        cout << "Error in opening the file " << argv[1] << endl;
        return 1;
    }

    ofstream out(argv[2]);
    if (!out.is_open())
    {
        cout << "Error in opening the file " << argv[2] << endl;
        return 1;
    }

    out << "File report <<" << argv[1] << ">>\nID\tName\tHours\tSalary\n";

    employee emp;
    while (in.read((char*)(&emp), sizeof(emp)))
    {
        out << emp.num << '\t' << emp.name << '\t' << emp.hours << '\t' << emp.hours * atoi(argv[3]) << '\n';
    }
    in.close();
    out.close();
    return 0;
}