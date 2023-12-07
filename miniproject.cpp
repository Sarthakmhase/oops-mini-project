#include<iostream>
#include <fstream>

using namespace std;

class student
{
    int rollno;
    char name[50];
    int ADS_marks, CS_marks, COA_marks, OOPS_marks, FLAT_marks;
    double average;
    char grade;

public:
    void getdata();
    void showdata() const;
    void calculate();
    int retrollno() const;
}; 

void student::calculate()
{
    average = (ADS_marks + CS_marks + COA_marks + OOPS_marks + FLAT_marks) / 5.0;
    if (average >= 90)
        grade = 'A';
    else if (average >= 75)
        grade = 'B';
    else if (average >= 50)
        grade = 'C';
    else
        grade = 'F';
}

void student::getdata()
{
    cout << "\nEnter student's roll number: ";
    cin >> rollno;
    cout << "\n\nEnter student name: ";
    cin.ignore();  //ignore fuction is used to clear input buffer to take new inputs.
    cin.getline(name, 50);  //getline() function used to get multiple characters from a user's input. 
    cout << "\nAll marks should be out of 100";
    cout << "\nEnter marks OF ADS: ";
    cin >> ADS_marks;
    cout << "Enter marks OF CS: ";
    cin >> CS_marks;
    cout << "Enter marks OF COA: ";
    cin >> COA_marks;
    cout << "Enter marks OF OOPS: ";
    cin >> OOPS_marks;
    cout << "Enter marks OF FLAT: ";
    cin >> FLAT_marks;
    calculate();
}

void student::showdata() const
{
    cout << "\nRoll number of student: " << rollno;
    cout << "\nName of student: " << name;
    cout << "\nADS: " << ADS_marks;
    cout << "\nCS: " << CS_marks;
    cout << "\nCOA: " << COA_marks;
    cout << "\nOOPS: " << OOPS_marks;
    cout << "\nFLAT: " << FLAT_marks;
    cout << "\nAverage Marks: " << average;
    cout << "\nGrade of student is: "<< grade;
}

int student::retrollno() const
{
    return rollno;
}

// Function declarations
void create_student();
void display_sp(int); // Display particular record
void display_all();   // Display all records
void write_all_to_file();
// MAIN
int main()
{
    char ch;
   do
    {
        int num;
        system("cls"); //used to clear the screen.
        cout << "\n\n\n\tMENU";
        cout << "\n\n\t1. Create student record";
        cout << "\n\n\t2. Search student record";
        cout << "\n\n\t3. Display all students records";
        cout << "\n\n\t4. Write in the file";
        cout << "\n\n\t5. Exit";
        cout << "\n\n\tWhat is your Choice (1/2/3/4/5): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            create_student();
            break;
        case '2':
            cout << "\n\n\tEnter The roll number: ";
            cin >> num;
            display_sp(num);
            break;
        case '3':
            display_all();
            break;
        
        case '5':
            cout << "Exiting, Thank you!";
            exit(0);
        case '4':
            write_all_to_file();
             break;
    
        default:
            cout << "Invalid choice. Please enter a valid option (1/2/3/4/5).";
        }
    } while (ch != '5');
    return 0;
}

// Write student details to file
void create_student()
{
    student stud;
    ofstream oFile;
    oFile.open("student.dat", ios::binary | ios::app); //ios::binary =>Open in binary mode    ios::app=> used to add the data at end of the file
    stud.getdata();
    oFile.write(reinterpret_cast<char *>(&stud), sizeof(student));  //reading the file
    oFile.close();
    cout << "\n\nStudent record has been created.";
    cin.ignore();
    
}

void display_all()
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened! Press any key to exit.";
        cin.ignore();
        cin.get();  //used to access the character array.
        return;
    }
    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(student))) //used to read all file data
    {
        stud.showdata();
        cout << "\n\n====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void display_sp(int n)
{
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "File could not be opened... Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(student)))
    {
        if (stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if (!flag)
        cout << "\n\nRecord does not exist.";
    cin.ignore();
    cin.get();
}

void write_all_to_file() {
    student stud;
    ifstream inFile;
    ofstream outFile;
    
    inFile.open("student.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened! Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    
    outFile.open("output.txt"); // Create or overwrite output.txt
    
    if (!outFile) {
        cout << "Output file could not be created! Press any key to exit.";
        cin.ignore();
        cin.get();
        return;
    }
    
    outFile << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(student))) {
        // Redirect output to the file
        streambuf *coutbuf = cout.rdbuf(); // Save the current cout buffer
        cout.rdbuf(outFile.rdbuf()); 
        
        stud.showdata();
        cout << "\n\n====================================\n";
    
        cout.rdbuf(coutbuf);
    }
    
    inFile.close();
    outFile.close();
    
    cout << "\n\nAll records have been written to the file 'output.txt'.";
    cin.ignore();
    cin.get();
}
