#include <cstdlib>
using namespace std;
#include <iostream>
#include <string>
#include <cmath> // you can include algorithm #include <algorithm>
#include <algorithm>
#include <fstream>

// Qn 2a.  strusture student
struct students
{
    string stud_name;
    int stud_num, test1, test2, test3, assignment1, assignment2, assignment3, DP;

} student; /* this is an instant object
student of the structure student this object can also be an array
like student[100]*/

// a function that calulate average
double average(int marks, int n);
// a function that calculates the dp
int dpCalculator(int avg_ass, int avg_test);
// the function that displays the average test marks;
int main(void)
{
    // Qn2 b, creating an array of students records from a structure i like it!!
    students student_record[100];

    /*
    Im going to read the contents of a file using
     store them in a array of datatpye student
     which is a structure
    */
    string path("students.txt");
    ifstream filereadObject(path);
    string stud_name;
    int index = 0;
    int stud_num, test1, test2, test3, assignment1,
        assignment2, assignment3, average_test, average_ass, DP;
    if (filereadObject.is_open())
    {
        /*Read the file data and store them in an array
        for the first question im not reading the dp because
        it doesn't exist

        */
        while (filereadObject >> stud_name >>
               stud_num >> test1 >> test2 >> test3 >>
               assignment1 >> assignment2 >> assignment3)
        {
            student_record[index].stud_name = stud_name;
            student_record[index].stud_num = stud_num;
            student_record[index].test1 = test1;
            student_record[index].test2 = test2;
            student_record[index].test3 = test3;
            student_record[index].assignment1 = assignment1;
            student_record[index].assignment2 = assignment2;
            student_record[index].assignment3 = assignment3;
            index++;
        }
    }
    else
    {
        cout << "CAN NOT READ TO A CLOSED FILE" << endl;
    }
    //  Qn c. Displeying the data on the screen using our array

    //  loop throug the array and display the output

    cout << "c) STUDENTS MARKS" << endl;
    cout << "stud_name\t stud#\t test1\t test2\t test3\t ass1\t ass2\t ass3\t DP" << endl;
    for (int i = 0; i < index; i++)
    {

        cout << student_record[i].stud_name << "\t" << student_record[i].stud_num << "\t"
             << student_record[i].test1 << "\t" << student_record[i].test2 << "\t"
             << student_record[i].test3 << "\t" << student_record[i].assignment1 << "\t"
             << student_record[i].assignment2 << "\t"
             << student_record[i].assignment3 << "\t"
             << " "
             << "\n";
    }
    // save memory!!!
    filereadObject.close();
    //  Qn d. THE AVERAGE TEST MARK FOR EACH STUDENT
    /*
    by calling a fuction called displayAverageTest() IM going to use my array structure to perform this task!!
    */
    cout << "\nd) AVERAGE OF TEST MARKS OF STUDENTS" << endl;
    cout << "stud_name\t stud#\t test1\t test2\t test3\t average test mark" << endl;
    for (int i = 0; i < index; i++)
    {
        int marks = student_record[i].test1 + student_record[i].test2 + student_record[i].test3;
        cout << student_record[i].stud_name << "\t" << student_record[i].stud_num << "\t"
             << student_record[i].test1 << "\t" << student_record[i].test2 << "\t"
             << student_record[i].test3 << "\t" << average(marks, 3) << "\n";
    }

    //  Qn e. THE AVERAGE ASSIGNMENT MARK FOR EACH STUDENT
    /*
    by calling a fuction called displayAveragAss() IM going to
     use my array structure to perform this task!!
    */
    cout << "\ne) AVERAGE OF ASSIGNMENT MARKS OF STUDENTS" << endl;
    cout << "stud_name\t stud#\t assgn1\t assgn2\t assgn3\t averageassigment mark" << endl;
    for (int i = 0; i < index; i++)
    {
        int marks = student_record[i].assignment1 + student_record[i].assignment2 + student_record[i].assignment3;
        cout << student_record[i].stud_name << "\t" << student_record[i].stud_num << "\t"
             << student_record[i].assignment1 << "\t" << student_record[i].assignment2 << "\t"
             << student_record[i].assignment3 << "\t" << average(marks, 3) << "\n";
    }

    /*
    displaying average marks of all students and average and DPs

    */
    string path1("average.txt");
    ofstream fileWriteObject(path1);

    if (fileWriteObject.is_open())
    {
        for (int i = 0; i < index; i++)
        {
            int test_marks = student_record[i].test1 + student_record[i].test2 + student_record[i].test3;
            int assign_marks = student_record[i].assignment1 + student_record[i].assignment2 + student_record[i].assignment3;

            /*
        'IM GOING TO CREATE A DP CALCULATOR WHICH TAKES TWO PARAMS AND USE THE
        FORMULAR 0.55 * TEST + 0.45 * ASSIGNMENTS = DP'
        */

            int DP = dpCalculator(average(assign_marks, 3), average(test_marks, 3));
            fileWriteObject << student_record[i].stud_name
                            << "\t" << student_record[i].stud_num << "\t"
                            << student_record[i].test1 << "\t"
                            << student_record[i].test2 << "\t"
                            << student_record[i].test3 << "\t"
                            << student_record[i].assignment1 << "\t"
                            << student_record[i].assignment2 << "\t"
                            << student_record[i].assignment3 << "\t"
                            << average(test_marks, 3) << "\t"
                            << average(assign_marks, 3) << "\t"
                            << DP
                            << "\n";
        }
        // fileWriteObject << "stud_name\t stud#\t test1\t test2\t test3\t A1\t A2\t A3\t avg_T\t avg_A\t DP \n ";
        cout << "\nf) A FILE HAS BEEN CREATED WITH AVERAGE AND IT'S NAME IS: "
             << path1 << endl;
    }
    else
    {
        cout << "CAN NOT READ TO A CLOSED FILE!! \a" << endl;
    }
    fileWriteObject.close();
    /*

    Im using an array of students to perfom the task
    by using a given formular and loop through all
    students
    */
    cout << "\ng) STUDENTS WHO HAVE DP MARKS LESS THAN 50" << endl;
    cout << "stud_name\t stud#\t DP \n ";
    int failures = 0;
    for (int i = 0; i < index; i++)
    {

        int test_marks = student_record[i].test1 + student_record[i].test2 + student_record[i].test3;
        int assign_marks = student_record[i].assignment1 + student_record[i].assignment2 + student_record[i].assignment3;
        int DP = dpCalculator(average(assign_marks, 3), average(test_marks, 3));
        if (DP < 50)
        {
            cout << student_record[i].stud_name << "\t"
                 << student_record[i].stud_num << "\t"
                 << DP << "\n";
            failures++;
        }
    }
    // if there are no failures tell us there are no failures
    !failures && cout << "\nALL STUDENTS HAS MARKS THAT ARE GREATER THAN 50 " << endl;

    return 0;
}

double average(int marks, int n)
{
    return ceil(marks / n); // round up the mark ceil from <cmath>
}
int dpCalculator(int avg_ass, int avg_test)
{
    return .45 * avg_ass + .55 * avg_test;
}
