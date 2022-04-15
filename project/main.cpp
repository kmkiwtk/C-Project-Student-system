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
    Person(int id, int age, string name) : id(id), age(age), name(name) {}
    virtual void addCourse(Course *A) = 0;
};
class Student : public Person
{
private:
    int courseNumber;
    Course *courses[4];

public:
    Student(int id, int age, string name) : Person(id, age, name)
    {
        courseNumber = 0;
    }
    void addCourse(Course *A) override
    {
        courses[courseNumber] = A;
        courseNumber++;
    }
    friend class System;
};
class Teacher : public Person
{
private:
    int courseNumber;
    Course *courses[2];

public:
    Teacher(int id, int age, string name) : Person(id, age, name)
    {
        courseNumber = 0;
    }
    void addCourse(Course *A) override
    {
        courses[courseNumber] = A;
        courseNumber++;
    }

    friend class System;
};

class Course
{
    string name, startTime;
    int code, hours, studentNumber;
    Teacher *teacher;
    Student **students;

public:
    Course(string name, string startTime, int code, int hours) : name(name), startTime(startTime), code(code), hours(hours)
    {
        teacher = nullptr;
        studentNumber = 0;
        students = nullptr;
    }
    void addStudent(Student *A)
    {
        students[studentNumber] = A;
    }
    void addTeacher(Teacher *A)
    {
        if (teacher != NULL)
        {
            cout << "The teacher will be changed from" << endl;
        }
        teacher = A;
    }

    friend class System;
};

class System
{
    int studentNumber, teacherNumber, courseNumber, studentCapacity, teacherCapacity, courseCapacity;
    Student **students;
    Teacher **teachers;
    Course **courses;

public:
    System()
    {
        studentCapacity = teacherCapacity = courseCapacity = 10;
        studentNumber = teacherNumber = courseNumber = 0;
        students = new Student *[studentCapacity];
        teachers = new Teacher *[teacherCapacity];
        courses = new Course *[courseCapacity];
    }
    void CourseAddStudent(Student *A)
    {
    }
    void CourseChangeTeacher()
    {
    }
    void CourseDeleteStudent()
    {
    }
    void addCourse(Course *A)
    {
        if (courseNumber < courseCapacity)
        {
            courses[courseNumber] = A;
            courseNumber++;
        }
        else
        {
        }
    }
    void addStudent(Student *A)
    {
    }
    void addTeacher(Teacher *A)
    {
    }
    Course *findCourse(string courseName) const
    {
        for (int i = 0; i < courseNumber; i++)
        {
            Course *temp = courses[i];
            if (temp->name == courseName)
            {
                return temp;
            }
        }
        return nullptr;
    }
    Course *findCourse(int code) const
    {
        for (int i = 0; i < courseNumber; i++)
        {
            Course *temp = courses[i];
            if (temp->code == code)
            {
                return temp;
            }
        }
        return nullptr;
    }

    Teacher *findTeacher(int id) const
    {
        for (int i = 0; i < courseNumber; i++)
        {
            Teacher *temp = teachers[i];
            if (temp->id == id)
            {
                return temp;
            }
        }
        return nullptr;
    }

    Teacher *findTeacher(string name) const
    {
        for (int i = 0; i < teacherNumber; i++)
        {
            Teacher *temp = teachers[i];
            if (temp->name == name)
            {
                return temp;
            }
        }
        return nullptr;
    }

    Student *findStudent(string name) const
    {
        for (int i = 0; i < teacherNumber; i++)
        {
            Student *temp = students[i];
            if (temp->name == name)
            {
                return temp;
            }
        }
        return nullptr;
    }

    Student *findStudent(int id) const
    {
        for (int i = 0; i < teacherNumber; i++)
        {
            Student *temp = students[i];
            if (temp->id == id)
            {
                return temp;
            }
        }
        return nullptr;
    }

    void writeBack()
    {
    }

    void display()
    {
        bool flag = true;
        string commend;
        while (flag)
        {
            cout << "Welcome to Student course management system！ Please enter instructions：" << endl;
            cout << "  "
                 << "1.display: "
                 << "Show the table." << endl;
            cout << "  "
                 << "2.addStudent: "
                 << "Add students to the course." << endl;
            cout << "  "
                 << "3.changeTeacher: "
                 << "Change teachers for courses." << endl;
            cout << "  "
                 << "4deleteStudent: "
                 << "Delete student for course." << endl;
        }
    }
    void init()
    {
    }

    ~System()
    {
        writeBack();
    }
};

int main()
{
    return 0;
}
