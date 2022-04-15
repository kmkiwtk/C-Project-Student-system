#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Course;

class Person
{
protected:
    int id, age;
    string name;

public:
    virtual void addCourse(Course* A) = 0;
};
class Student : public Person
{
private:
    int courseNumber;
    Course *courses[4];

public:
    void addCourse(Course* A) override
    {
        courses[courseNumber] = A;
        courseNumber++;
    }
};
class Teacher : public Person
{
private:
    int courseNumber;
    Course *courses[2];

public:
    void addCourse(Course* A) override
    {
        courses[courseNumber] = A;
        courseNumber++;
    }
};

class Course
{
    string name, startTime;
    int code, hours, studentNumber;
    Teacher *teacher;
    Student **students;

public:
    void addStudent(Student* A)
    {
        students[studentNumber] = A;
    }
    void addTeacher(Teacher* A)
    {
        if(teacher != NULL){
            cout << "The teacher will be changed from" endl;
        }
        teacher = A;
    }
};

class System
{
    int studentNumber, teacherNumber, CourseNumber;
    Student **students;
    Teacher **teachers;
    Course **courses;

public:
    void CourseAddStudent()
    {
    }
    void CourseAddTeacher()
    {
    }
    void CourseDeleteStudent()
    {
    }
    void display()
    {
    }
};

int main()
{
    return 0;
}
