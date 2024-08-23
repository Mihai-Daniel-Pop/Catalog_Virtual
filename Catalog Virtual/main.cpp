#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Student.h"
#include "Functions.h"

using namespace std;

#define MAX_PATH_LENGTH 256



int main()
{
    Student s;
    s.loadStudents();

    while (true) {
            clear_screen();
        visual_menu1();
        int step;
        cin >> step;
        if (step == 1) {
            {
     visual_teacher1();
                char step1;
                cin >> step1;
                clear_screen();
                if(step1=='1')
                s.loginTeacher();
                else
                    if(step1=='2')
                    {
                        std::string name;
                        std::string password;


                        std::cout << "Please enter your name: \n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                        std::getline(std::cin, name);


                        std::cout << "Please enter your password: \n";
                        std::getline(std::cin, password);
                        appendTeacherCredentials(name, password, "Teacher.csv");
                    }
                else
                    continue;
            }
        } else if (step == 2) {
            s.loginStudent();
        } else {
            cout << "Invalid option. Please try again." << endl;
        }
    }
    return 0;
}
