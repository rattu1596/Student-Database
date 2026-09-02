#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

class Student
{
    int roll;
    char name[50];
    char course[50];
    float marks;

public:

    void input()
{
    cout << "Enter Roll Number : ";
    cin >> roll;
    
    cin.ignore(1000, '\n');

    cout << "Enter Name        : ";
    cin.getline(name,50);

    cout << "Enter Course      : ";
    cin.getline(course,50);

    cout << "Enter Marks       : ";
    cin >> marks;
}

  void display()
{
    cout << "\nRoll No : " << roll;
    cout << "\nName    : " << name;
    cout << "\nCourse  : " << course;
    cout << "\nMarks   : " << marks << endl;
}
int getRoll()
    {
        return roll;
    }

    float getMarks()
    {
        return marks;
    }
};

void addStudent()
{
    Student s;

    ofstream file("student.dat", ios::binary | ios::app);

    if(!file)
    {
        cout << "\nError opening file\n";
        return;
    }

    s.input();
    file.write((char*)&s, sizeof(s));

    cout << "\nStudent added successfully\n";

    file.close();
}

void displayStudents()
{
    Student s;
    int count = 0;

    ifstream file("student.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo records found\n";
        return;
    }

    cout << "\n------ STUDENT RECORDS ------\n";

    while(file.read((char*)&s,sizeof(s)))
    {
        s.display();
        cout << "-----------------------------\n";
        count++;
    }

    if(count == 0)
    {
        cout << "\nNo student records available\n";
    }
    else
    {
        cout << "\nTotal Students : " << count << endl;
    }

    file.close();
}

void searchStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number : ";
    cin >> roll;
    cin.ignore(1000, '\n');
    ifstream file("student.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo records found\n";
        return;
    }

    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.getRoll() == roll)
        {
            cout << "\nStudent Found\n";
            s.display();
            found = true;
            break;
        }
    }

    if(!found)
        cout << "\nRecord not found\n";

    file.close();
}

void updateStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to Update : ";
    cin >> roll;
    cin.ignore(1000, '\n');
    fstream file("student.dat", ios::binary | ios::in | ios::out);

    // ✅ FIX: Check file exists
    if(!file)
    {
        cout << "\nNo records found\n";
        return;
    }

    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.getRoll() == roll)
        {
            cout << "\nEnter New Details\n";
            s.input();

            file.seekp(-1 * sizeof(s), ios::cur); // move pointer back
            file.write((char*)&s,sizeof(s));

            cout << "\nRecord Updated Successfully\n";

            found = true;
            break;
        }
    }

    if(!found)
        cout << "\nRecord not found\n";

    file.close();
}

void deleteStudent()
{
    Student s;
    int roll;
    bool found = false;

    cout << "Enter Roll Number to Delete : ";
    cin >> roll;
    cin.ignore(1000, '\n');
    ifstream file("student.dat", ios::binary);

    // ✅ FIX: Check file exists
    if(!file)
    {
        cout << "\nNo records found\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);

    while(file.read((char*)&s,sizeof(s)))
    {
        if(s.getRoll() != roll)
            temp.write((char*)&s,sizeof(s));
        else
            found = true;
    }

    file.close();
    temp.close();

    remove("student.dat");
    rename("temp.dat","student.dat");

    if(found)
        cout << "\nRecord Deleted Successfully\n";
    else
        cout << "\nRecord not found\n";
}
void showTopper()
{
    Student s, top;
    bool first = true;

    ifstream file("student.dat", ios::binary);

    if(!file)
    {
        cout << "\nNo records found\n";
        return;
    }

    while(file.read((char*)&s,sizeof(s)))
    {
        if(first || s.getMarks() > top.getMarks())
        {
            top = s;
            first = false;
        }
    }

    file.close();

    if(!first)
    {
        cout << "\n------ CLASS TOPPER ------\n";
        top.display();
    }
    else
        cout << "\nNo records found\n";
}
int main()
{
    int choice;

    do
    {
        cout << "\n=================================\n";
        cout << "     STUDENT MANAGEMENT SYSTEM\n";
        cout << "=================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Show Topper\n";
        cout << "7. Exit\n";
        cout << "=================================\n";

        cout << "Enter choice : ";
        cin >> choice;
        cin.ignore(1000, '\n');

        switch(choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: showTopper(); break;
            case 7: cout << "Exiting program\n"; break;
            default: cout << "Invalid choice\n";
        }

    }while(choice != 7);

    return 0;
}
