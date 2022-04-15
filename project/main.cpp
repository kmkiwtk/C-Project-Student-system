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
    virtual void addCourse(Course A) = 0;
};
class Student : public Person
{
private:
    int courseNumber;
    Course *courses[4];

public:
    void addCourse(Course A) override
    {
    }
};
class Teacher : public Person
{
private:
    int courseNumber;
    Course *courses[2];

public:
    void addCourse(Course A) override
    {
    }
};

class Course
{
    string name, stratTime;
    int code, hours;
    Teacher *teacher;
    Student **students;

public:
    void addStudent()
    {
    }
    void addTeacher()
    {
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