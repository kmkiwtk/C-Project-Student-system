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
    virtual bool addCourse(Course *A) = 0;
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
    bool addCourse(Course *A) override
    {
        if (courseNumber < 4)
        {
            courses[courseNumber] = A;
            courseNumber++;
            return true;
        }
        return false;
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
    bool addCourse(Course *A) override
    {
        if (courseNumber < 2)
        {
            courses[courseNumber] = A;
            courseNumber++;
            return true;
        }
        return false;
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
            cout << "The teacher will be changed" << endl;
        }
        teacher = A;
    }
    int findStudent(Student *A)
    {
        for(i = 0; i < studentNumber, i++)
        {
            if (Student[i].name == A.name)
            {
                return i;
            }
            else
            {
                return -1;
            }
        }
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

    bool CourseAddStudent(int CC, string SN)
    {
        Course *C;
        Student *S;
        C = findCourse(CC);
        S = findStudent(SN);

        if (C != nullptr && S != nullptr)
        {
            if(S.addCourse(C))
            {
                C.addStudent(S);
                return true;
            }
        }
        return false;
    }
    bool CourseChangeTeacher(int CC, string TN)
    {
        Course *C;
        Teacher *T;
        C = findCourse(CC);
        T = findTeacher(TN);

        if (C != nullptr && T != nullptr)
        {
            if(T.addCourse(C))
            {
                C.addTeacher(T);
                return true;
            }
        }
        return false;
    }
    bool CourseDeleteStudent(int CC, string SN)
    {
        Course *C;
        Student *S
        C = findCourse(CC);
        S = findStudent(SN);
        int index = C.findStudent(S);
        if(index != -1)
        {
            for(int i = index; i<C.studentNumber-1; i++)
            {
                C.students[i] = C.students[i+1];
            }
            C.students[C.studentNumber] = nullptr;
            C.studentNumber--;
        }

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
            courseCapacity = 2 * courseCapacity;
            Course **temp = new Course *[courseCapacity];
            for (int i = 0; i < courseNumber; i++)
            {
                temp[i] = courses[i];
            }
            delete[] courses;
            courses = temp;
        }
    }
    void addStudent(Student *A)
    {

        if (studentNumber < studentCapacity)
        {
            students[studentNumber] = A;
            studentNumber++;
        }
        else
        {
            studentCapacity = 2 * studentCapacity;
            Student **temp = new Student *[studentCapacity];
            for (int i = 0; i < studentNumber; i++)
            {
                temp[i] = students[i];
            }
            delete[] students;
            students = temp;
        }
    }
    void addTeacher(Teacher *A)
    {
        if (teacherNumber < teacherCapacity)
        {
            teachers[teacherNumber] = A;
            teacherNumber++;
        }
        else
        {
            teacherCapacity = 2 * teacherCapacity;
            Teacher **temp = new Teacher *[teacherCapacity];
            for (int i = 0; i < teacherNumber; i++)
            {
                temp[i] = teachers[i];
            }
            delete[] teachers;
            teachers = temp;
        }
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
        for (int i = 0; i < studentNumber; i++)
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
        for (int i = 0; i < studentNumber; i++)
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
