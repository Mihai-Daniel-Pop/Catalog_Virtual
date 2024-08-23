#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <limits>
#include "Functions.h"

class Student {
public:
    std::string full_name;
    std::string password;
    int math[4] ;
    float math_avg;
    int info[4] ;
    float info_avg ;
    int english[4] ;
    float english_avg;
    Student() : math{0, 0, 0, 0}, math_avg(0),
                info{0, 0, 0, 0}, info_avg(0),
                english{0, 0, 0, 0}, english_avg(0) {}

    void trim(std::string& str);
    void calculateAverages();
    float calculateAverage(int grades[4]);
    void loadStudents();
    void saveStudents();
    Student* findStudentByName(const std::string& name);
    void studentMenu(Student* student);
    void viewStudentGrades();
    void modifyStudentGrade();
    void addStudent();
    void teacherMenu();
    void loginStudent();
    void loginTeacher();

};





#endif
