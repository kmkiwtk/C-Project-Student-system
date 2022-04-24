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
    virtual bool deleteCourse(Course *A) = 0;
    virtual int findCourse(Course *A) = 0;
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
    // Check the availability and add a course for a student
    bool addCourse(Course *A) override
    {
        for (int i = 0; i < courseNumber; i++)
        {
            if (courses[i] == A)
            {
                cout << "Course already taken!" << endl;
                return false;
            }
        }
        if (courseNumber < 4)
        {
            courses[courseNumber] = A;
            courseNumber++;
            return true;
        }
        cout << name << " can't take more course " << endl;
        return false;
    }
    // Check the availability and delete a course for a student
    bool deleteCourse(Course *A) override
    {
        int index = findCourse(A);
        if (index != -1)
        {
            for (int i = index; i < courseNumber - 1; i++)
            {
                courses[i] = courses[i + 1];
            }
            courses[courseNumber--] = nullptr;
            return true;
        }
        return false;
    }
    // Check whether a student has take a specific course, return the index of that course or return -1
    int findCourse(Course *A) override
    {
        for (int i = 0; i < courseNumber; i++)
        {
            if (courses[i] == A)
            {
                // cout << i << endl;
                return i;
            }
        }
        cout << name << " doesn't take this course." << endl;
        return -1;
    }

    friend class System;
    friend class Course;
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
    // Check the availability and add a course for a teacher
    bool addCourse(Course *A) override
    {
        if (courseNumber < 2)
        {
            courses[courseNumber] = A;
            courseNumber++;
            return true;
        }
        cout << name << " can't teach more courses." << endl;
        return false;
    }
    // Check the availability and delete a course for a student
    bool deleteCourse(Course *A) override
    {
        int index = findCourse(A);
        if (index != -1)
        {
            for (int i = index; i < courseNumber - 1; i++)
            {
                courses[i] = courses[i + 1];
            }
            courses[courseNumber--] = nullptr;
            return true;
        }

        cout << "Delete failed!" << endl;
        return false;
    }
    // Check whether a teacher is teaching a specific course, return the index of that course or return -1
    int findCourse(Course *A) override
    {
        for (int i = 0; i < courseNumber; i++)
        {
            if (courses[i] == A)
            {
                return i;
            }
        }
        cout << name << " doesn't teach this course " << endl;
        return -1;
    }

    friend class System;
};

class Course
{
    string name, startTime;
    int code, hours, studentNumber, studentCapacity;
    Teacher *teacher;
    Student **students;

public:
    Course(string name, string startTime, int code, int hours) : name(name), startTime(startTime), code(code), hours(hours)
    {
        teacher = nullptr;
        studentNumber = 0;
        studentCapacity = 10;
        students = new Student *[studentCapacity];
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
    // Add a teacher to a course
    void addTeacher(Teacher *A)
    {
        if (teacher != nullptr)
        {
            char response;
            cout << "The teacher will be changed. Do you want to change?[y/n]" << endl;
            cin >> response;
            if (response == 'y' || response == 'Y')
            {
                teacher = A;
            }
        }
        else
        {
            teacher = A;
        }
    }
    // Check whether a student takes this course, return the index of that student or return -1
    int findStudent(Student *S)
    {
        for (int i = 0; i < studentNumber; i++)
        {
            if (students[i] == S)
            {
                return i;
            }
        }
        cout << S->name << " doesn't take " << name << endl;
        return -1;
    }

    // Check availability and delete a student from this course
    bool deleteStudent(Student *A)
    {
        int index = findStudent(A);
        if (index != -1)
        {
            for (int i = 0; i < studentNumber - 1; i++)
            {
                students[i] = students[i + 1];
            }
            students[studentNumber--] = nullptr;
            return true;
        }
        else
        {
            cout << "Delete failed!" << endl;
            return false;
        }
    }

    friend class System;
    friend class Teacher;
    friend class Student;
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
    // Adding a student to a course
    bool CourseAddStudent(int CC, string SN)
    {
        Course *C;
        Student *S;
        C = findCourse(CC);
        S = findStudent(SN);

        if (C != nullptr && S != nullptr)
        {
            if (S->addCourse(C))
            {
                C->addStudent(S);
                cout << "Add success!" << endl;
                return true;
            }
        }
        cout << "Add failed!" << endl;
        return false;
    }

    // Change the teacher of a course
    bool CourseChangeTeacher(int CC, string TN)
    {
        Course *C;
        Teacher *T;
        C = findCourse(CC);
        T = findTeacher(TN);

        if (C != nullptr && T != nullptr)
        {
            Teacher *old = C->teacher;

            if (T->addCourse(C))
            {
                C->addTeacher(T);
                old->deleteCourse(C);
                cout << "Change success!" << endl;
                return true;
            }
        }
        cout << "Change failed!" << endl;
        return false;
    }

    // Deleting a student from a course
    bool CourseDeleteStudent(int CC, string SN)
    {
        Course *C;
        Student *S;
        C = findCourse(CC);
        S = findStudent(SN);
        if (S != nullptr && C != nullptr)
        {
            if (S->deleteCourse(C))
            {
                C->deleteStudent(S);
                cout << "Course delete student :Delete success!" << endl;
                return true;
            }
        }
        cout << "Delete failed!" << endl;
        return false;
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

    // Search for the course name provided by user, return the pointer of that course. Return nullptr while not found.
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
        cout << "Course doesn't exist" << endl;
        return nullptr;
    }

    // Search for the course code provided by user, return the pointer of that course. Return nullptr while not found.
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
        cout << "Course doesn't exist" << endl;
        return nullptr;
    }

    // Search for the teacher's ID provided by user, return the pointer of that teacher. Return nullptr while not found.
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

    // Search for the teacher's name code provided by user, return the pointer of that teacher. Return nullptr while not found.
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
        cout << "Teacher: " << name << " not found." << endl;
        return nullptr;
    }

    // Search for the student's name provided by user, return the pointer of that student. Return nullptr while not found.
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
        cout << "Student: " << name << " not found." << endl;
        return nullptr;
    }

    // Search for the student's ID provided by user, return the pointer of that student. Return nullptr while not found.
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

    // Show all the data to the user on the screen
    void displayTable()
    {
        int fwidth = 18;
        int width = 10;
        cout << "Course:" << endl;
        cout << left << setw(fwidth)
             << "Name"
             << left << setw(width)
             << "Code"
             << left << setw(width)
             << "Teacher"
             << left << setw(width)
             << "Hours"
             << left << setw(width)
             << "Time" << endl;
        for (int i = 0; i < courseNumber; i++)
        {
            Course *temp = courses[i];

            cout << left << setw(fwidth)
                 << temp->name
                 << left << setw(width)
                 << temp->code
                 << left << setw(width)
                 << temp->teacher->name
                 << left << setw(width)
                 << temp->hours
                 << left << setw(width)
                 << temp->startTime
                 << endl;
        }
        cout << "Member:" << endl;
        cout << left << setw(fwidth)
             << "Name"
             << left << setw(width)
             << "Identity"
             << left << setw(width)
             << "Id"
             << left << setw(width)
             << "Age"
             << left << setw(width)
             << "Courses" << endl;
        for (int i = 0; i < teacherNumber; i++)
        {
            Teacher *temp = teachers[i];

            cout << left << setw(width)
                 << temp->name
                 << left << setw(width)
                 << "teacher"
                 << left << setw(width)
                 << temp->id
                 << left << setw(width)
                 << temp->age;
            for (int j = 0; j < temp->courseNumber; j++)
            {
                cout << temp->courses[j]->name << " ";
            }
            cout << endl;
        }
        for (int i = 0; i < studentNumber; i++)
        {
            Student *temp = students[i];

            cout << left << setw(width)
                 << temp->name
                 << left << setw(width)
                 << "student"
                 << left << setw(width)
                 << temp->id
                 << left << setw(width)
                 << temp->age;
            for (int j = 0; j < temp->courseNumber; j++)
            {
                cout << temp->courses[j]->name << " ";
            }
            cout << endl;
        }
    }

    // Write the data back into the original files
    void writeBack()
    {
        int fwidth = 18;
        int width = 10;
        ofstream courseData("./course.data");
        ofstream memberData("./member.data");
        courseData << left << setw(fwidth)
                   << "Name"
                   << left << setw(width)
                   << "Code"
                   << left << setw(width)
                   << "Teacher"
                   << left << setw(width)
                   << "Hours"
                   << left << setw(width)
                   << "Time" << endl;
        cout << "save course! : " << courseNumber << endl;
        for (int i = 0; i < courseNumber; i++)
        {
            Course *temp = courses[i];

            courseData << left << setw(fwidth)
                       << temp->name
                       << left << setw(width)
                       << temp->code
                       << left << setw(width)
                       << temp->teacher->name
                       << left << setw(width)
                       << temp->hours
                       << left << setw(width)
                       << temp->startTime;
            if (i != courseNumber - 1)
            {
                courseData << endl;
            }
        }
        memberData << left << setw(width)
                   << "Name"
                   << left << setw(width)
                   << "Identity"
                   << left << setw(width)
                   << "Id"
                   << left << setw(width)
                   << "Age"
                   << left << setw(width)
                   << "Number"
                   << left << setw(width)
                   << "Courses" << endl;
        cout << "save teacher" << endl;
        for (int i = 0; i < teacherNumber; i++)
        {
            Teacher *temp = teachers[i];

            memberData << left << setw(width)
                       << temp->name
                       << left << setw(width)
                       << "teacher"
                       << left << setw(width)
                       << temp->id
                       << left << setw(width)
                       << temp->age
                       << left << setw(width)
                       << temp->courseNumber;
            for (int j = 0; j < temp->courseNumber; j++)
            {
                memberData << temp->courses[j]->name << " ";
            }
            memberData << endl;
        }
        cout << "save student" << endl;
        for (int i = 0; i < studentNumber; i++)
        {
            Student *temp = students[i];

            memberData << left << setw(width)
                       << temp->name
                       << left << setw(width)
                       << "student"
                       << left << setw(width)
                       << temp->id
                       << left << setw(width)
                       << temp->age
                       << left << setw(width)
                       << temp->courseNumber;
            for (int j = 0; j < temp->courseNumber; j++)
            {
                memberData << temp->courses[j]->name << " ";
            }
            if (i != studentNumber - 1)
            {
                memberData << endl;
            }
        }
        memberData.close();
        courseData.close();
    }

    // Display the user interface of this program
    void display()
    {
        bool flag = true;
        cout << "Welcome to Student course management system！ Please enter instructions：" << endl;
        cout << "  "
             << "1.display: "
             << "Show the table." << endl;
        cout << "  "
             << "2.CourseAddStudent: "
             << "Add students to the course." << endl;
        cout << "  "
             << "3.CourseChangeTeacher: "
             << "Change teachers for courses." << endl;
        cout << "  "
             << "4.CourseDeleteStudent: "
             << "Delete student from course." << endl;
        cout << "  "
             << "5.quit: "
             << "Quit the program." << endl;
        while (flag)
        {
            int code;
            string sName;
            cout << "please insert your selection:";
            char choose;
            cin >> choose;
            switch (choose)
            {
            case '1':
                displayTable();
                break;
            case '2':

                cout << "Please insert Course Code:";
                cin >> code;
                cout << "Please insert student's name:";
                cin >> sName;
                CourseAddStudent(code, sName);
                break;
            case '3':
                cout << "Please insert Course Code:";
                cin >> code;
                cout << "Please insert teacher's name:";
                cin >> sName;
                CourseChangeTeacher(code, sName);
                break;
            case '4':
                cout << "Please insert Course Code:";
                cin >> code;
                cout << "Please insert student's name:";
                cin >> sName;
                CourseDeleteStudent(code, sName);
                break;
            case '5':
                flag = false;
                break;
            default:
                cout << "Error command" << endl;
            }
        }
    }
    // Initializing the whole system, reading data from files
    void init()
    {
        ifstream courseData("./course.data");
        ifstream memberData("./member.data");

        // check if file exist or not
        if (courseData.is_open() || memberData.is_open())
        {

            cout << "File is open and ready" << '\n';
            cout << " " << '\n';
            //            return; // use this for program testing to check file is open only without reading the data
        }
        else
        {
            cout << "File not found!" << '\n';
            cout << "check if path is .././src/***" << '\n';
            cout << " " << '\n';
            return;
        }

        string l;
        getline(courseData, l);
        getline(memberData, l);
        // cout << "文件跳过第一行";
        while (!courseData.eof())
        {
            string name;
            int code;
            int hours;
            string teacherName;
            string time;
            courseData >> name >> code >> teacherName >> hours >> time;
            // cout << name << " " << code << " " << hours << " " << time << endl;
            Course *temp = new Course(name, time, code, hours);
            this->addCourse(temp);
        }

        while (!memberData.eof())
        {
            string name;
            string identity;
            int id;
            int age;
            int courseNumber;
            string course;

            memberData >> name >> identity >> id >> age >> courseNumber;
            // cout << name << " " << identity << " " << id << " " << age << " " << courseNumber << endl;

            if (identity == "teacher")
            {
                Teacher *temp = new Teacher(id, age, name);
                for (int i = 0; i < courseNumber; i++)
                {
                    memberData >> course;
                    // cout << course << " ";
                    Course *A = findCourse(course);
                    if (A != nullptr)
                    {
                        temp->addCourse(A);
                        A->addTeacher(temp);
                    }
                    else
                    {
                        // cout << course << " don't find." << endl;
                    }
                }
                addTeacher(temp);
                // cout << endl;
            }
            else if (identity == "student")
            {
                Student *temp = new Student(id, age, name);
                for (int i = 0; i < courseNumber; i++)
                {
                    memberData >> course;
                    // cout << course << " ";
                    Course *A = findCourse(course);
                    if (A != nullptr)
                    {
                        temp->addCourse(A);
                        A->addStudent(temp);
                    }
                    else
                    {
                        // cout << course << " don't find." << endl;
                    }
                }
                addStudent(temp);
                cout << endl;
            }
            else
            {
                // cout << "unknown person" << endl;
            }
        }
        courseData.close();
        memberData.close();
        cout << "init success" << endl;
    }

    // Save changes before quit the program
    ~System()
    {
        cout << "start save!" << endl;
        writeBack();
        if (studentNumber != 0)
        {
            for (int i = 0; i < studentNumber; i++)
            {
                delete students[i];
            }
            delete[] students;
        }
        if (teacherNumber != 0)
        {
            for (int i = 0; i < teacherNumber; i++)
            {
                delete teachers[i];
            }
            delete[] teachers;
        }
        if (courseNumber != 0)
        {
            for (int i = 0; i < courseNumber; i++)
            {
                delete courses[i];
            }
            delete[] courses;
        }
    }
};

int main()
{
    System Sys;
    Sys.init();
    Sys.display();
    return 0;
}
