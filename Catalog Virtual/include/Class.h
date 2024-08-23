#ifndef CLASS_H
#define CLASS_H

#include <vector>
#include <string>
#include "Student.h"

class Class {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& student);
    bool removeStudentByName(const std::string& name);
    Student* findStudentByName(const std::string& name);
    void printAllStudents() const;


    void loadStudentsFromFile(const std::string& filename);
    void saveStudentsToFile(const std::string& filename);
};

#endif
