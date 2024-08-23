#include "Class.h"
#include <iostream>
#include <algorithm>


void Class::loadStudentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string name, tmp;
        int score;

        getline(ss, name, ',');
        getline(ss, tmp, ',');
        Student student;
        student.full_name = name;
        student.password = tmp;

        if (getline(file, line)) {
            std::istringstream grades(line);
            for (int& grade : student.math) {
                grades >> grade;
            }
        }

        if (getline(file, line)) {
            std::istringstream grades(line);
            for (int& grade : student.info) {
                grades >> grade;
            }
        }

        if (getline(file, line)) {
            std::istringstream grades(line);
            for (int& grade : student.english) {
                grades >> grade;
            }
        }

        student.calculateAverages();
        students.push_back(student);
    }

    file.close();
    std::cout << "Loaded " << students.size() << " students from file." << std::endl;
}




void Class::addStudent(const Student& student) {
    students.push_back(student);
}

bool Class::removeStudentByName(const std::string& name) {
    auto it = std::find_if(students.begin(), students.end(),
                           [&](const Student& s) { return s.full_name == name; });
    if (it != students.end()) {
        students.erase(it);
        return true;
    }
    return false;
}

Student* Class::findStudentByName(const std::string& name) {
    for (auto& student : students) {
        if (student.full_name == name) {
            return &student;
        }
    }
    return nullptr;
}


void Class::printAllStudents() const {
    for (const auto& student : students) {
        std::cout << "Student: " << student.full_name
                  << ", Math Avg: " << student.math_avg
                  << ", Info Avg: " << student.info_avg
                  << ", English Avg: " << student.english_avg << std::endl;
    }
}




void Class::saveStudentsToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "Name,Password,Math Grades,Info Grades,English Grades\n";

    for (const auto& student : students) {
        file << student.full_name << "," << student.password << ",";

        for (int i = 0; i < 4; ++i) {
            file << student.math[i] << (i < 3 ? " " : ",");
        }

        for (int i = 0; i < 4; ++i) {
            file << student.info[i] << (i < 3 ? " " : ",");
        }

        for (int i = 0; i < 4; ++i) {
            file << student.english[i] << (i < 3 ? " " : "");
        }

        file << "\n";
    }

    file.close();
    std::cout << "Students saved to " << filename << std::endl;
}

