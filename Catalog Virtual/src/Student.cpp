#include "Student.h"
#include "Functions.h"
#include "Class.h"

using namespace std;

char username[50] = "";
string folder_path = "C:/School things/Codebloks-Projects/Catalog Virtual/";
string student12_csv = "Students.csv";
string teachers_csv = "Teacher.csv";
vector<Student> students;


void Student::trim(string& str) {
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) { return !isspace(ch); }));
    str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), str.end());
}


void Student::calculateAverages() {
        math_avg = calculateAverage(math);
        info_avg = calculateAverage(info);
        english_avg = calculateAverage(english);
    }

    float Student::calculateAverage(int grades[4]) {
        int sum = 0;
        int count = 0;
        for (int i = 0; i < 4; ++i) {
            if (grades[i] != 0) {
                sum += grades[i];
                count++;
            }
        }
        return (count == 0) ? 0 : static_cast<float>(sum) / count;
    }




void Student::loadStudents() {
    ifstream file(folder_path + student12_csv);
    if (!file.is_open()) {
        cerr << "Error opening student database at: " << folder_path + student12_csv << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        Student student;
        stringstream ss(line);
        getline(ss, student.full_name, ',');
        getline(ss, student.password, ',');

        trim(student.full_name);
        trim(student.password);

        for (int i = 0; i < 4; ++i) {
            file >> student.math[i];
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < 4; ++i) {
            file >> student.info[i];
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < 4; ++i) {
            file >> student.english[i];
        }
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        student.calculateAverages();
        students.push_back(student);
    }

    file.close();
}

void Student::saveStudents() {
    ofstream file(folder_path + student12_csv);
    if (!file.is_open()) {
        cerr << "Error opening student database." << endl;
        return;
    }

    for (const auto& student : students) {
        file << student.full_name << "," << student.password << endl;
        for (int i = 0; i < 4; ++i)
            file << student.math[i] << " ";
        file << endl;
        for (int i = 0; i < 4; ++i)
            file << student.info[i] << " ";
        file << endl;
        for (int i = 0; i < 4; ++i)
            file << student.english[i] << " ";
        file << endl;
    }

    file.close();
}

Student* Student::findStudentByName(const string& name) {
    for (auto& student : students) {
        if (student.full_name == name)
            return &student;
    }
    return nullptr;
}

void Student::studentMenu(Student* student) {
    char choice;

    do{
        clear_screen();
        cout<<"==============================================\n";
        cout << "||              Welcome " << student->full_name << endl;
        cout<<"==============================================\n";

        cout << "|| Math grades: ";
        for (int i = 0; i < 4; ++i)
            cout << student->math[i] << " ";
        cout << "(Average: " << student->math_avg << ")" << endl;

        cout << "|| Info grades: ";
        for (int i = 0; i < 4; ++i)
            cout << student->info[i] << " ";
        cout << "(Average: " << student->info_avg << ")" << endl;

        cout << "|| English grades: ";
        for (int i = 0; i < 4; ++i)
            cout << student->english[i] << " ";
        cout << "(Average: " << student->english_avg << ")" << endl;
        cout<<"==============================================\n";

        cout << "Options: \n(1) Send message to teacher \n(2) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == '2') {
            cout << "Exiting...\n";
            exit(0);
        } else if (choice != '1') {
            cout << "Invalid option. Please try again.\n";
        }
        else if (choice == '1')
        {
            clear_screen();
         writeMessageToFile("Messages.csv");


        }


    } while (choice != '2');
}

void Student::viewStudentGrades() {
    cout << "Enter the full name of the student to view grades: ";
    string name;
    cin.ignore();
    getline(cin, name);
    //clear_screen();
    Student* student = findStudentByName(name);
    if (student) {
        cout<<"=====================================\n";
        cout << "|| Grades for " << student->full_name << ":" << endl;
        cout << "|| Math grades: ";
        for (int i = 0; i < 4; ++i)
            cout << student->math[i] << " ";
        cout << "(Average: " << student->math_avg << ")" << endl;

        cout << "|| Info grades: ";
        for (int i = 0; i < 4; ++i)
            cout << student->info[i] << " ";
        cout << "(Average: " << student->info_avg << ")" << endl;

        cout << "|| English grades: ";
        for (int i = 0; i < 4; ++i)
            cout << student->english[i] << " ";
        cout << "(Average: " << student->english_avg << ")" << endl;
                cout<<"=====================================\n";

        cout<<"Press ENTER to get back to main";
        std::string userInput;
        std::getline(std::cin, userInput);



    } else {
        cout << "Student not found.Press ENTER" << endl;
        std::string userInput;
        std::getline(std::cin, userInput);
    }
}

void Student::modifyStudentGrade() {
    cout << "Enter the full name of the student to modify grades: ";
    string name;
    cin.ignore();
    getline(cin, name);

    Student* student = findStudentByName(name);
    if (student) {
        cout << "Select subject to modify:\n1. Math\n2. Informatics\n3. English\n";
        int subjectChoice;
        cin >> subjectChoice;

        int* grades = nullptr;
        switch (subjectChoice) {
            case 1:
                grades = student->math;
                break;
            case 2:
                grades = student->info;
                break;
            case 3:
                grades = student->english;
                break;
            default:
                cout << "Invalid choice." << endl;
                return;
        }

        cout << "Select grade number to modify (1-4): ";
        int gradeIndex;
        cin >> gradeIndex;

        if (gradeIndex < 1 || gradeIndex > 4) {
            cout << "Invalid grade number." << endl;
            return;
        }

        cout << "Enter new grade value: ";
        int newGrade;
        cin >> newGrade;

        grades[gradeIndex - 1] = newGrade;
        student->calculateAverages();
        saveStudents();

        cout << "Grade updated successfully." << endl;
    } else {
        cout << "Student not found." << endl;
    }
}

void Student::addStudent() {
    cout << "Enter the full name of the new student: ";
    string full_name;
    cin.ignore();
    getline(cin, full_name);

    cout << "Enter the password for the new student: ";
    string password;
    getline(cin, password);

    Student new_student;
    new_student.full_name = full_name;
    new_student.password = password;

    students.push_back(new_student);
    ofstream file(folder_path + student12_csv, ios::app);
    if (file.is_open()) {
        file << new_student.full_name << "," << new_student.password << endl;
        file << "0 0 0 0" << endl;
        file << "0 0 0 0" << endl;
        file << "0 0 0 0" << endl;
        file.close();
    }

    cout << "New student added successfully." << endl;
}

void Student::teacherMenu() {
    char choice;
    do {
        clear_screen();
        visual_teacher();
        std::cin >> choice;

        switch (choice) {
            case '1': {
                viewStudentGrades();
                break;
            }
            case '2': {
                modifyStudentGrade();
                break;
            }
            case '3': {
                addStudent();
                //Class myClass;
                //myClass.saveStudentsToFile("Class.csv");
                break;
            }
            case '4': {
                std::cout << "Exiting...\n";
                exit(0);
                break;
            }
            case '5': {
                Class myClass;
                std::cout<<"=====================================================\n";
                myClass.loadStudentsFromFile("students.csv");
                myClass.printAllStudents();
                std::cout<<"=====================================================\n";

                std::string input;
                std::cout << "Press Enter to get back to main: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, input);
                break;
            }
            case '6': {
                 clear_screen();
                 char n=0;
                 while(n!=1 && n!=2)
                 {
                std::cout<<"(1) See your messages\n(2)Delete all messages\n(3)Exit to main\nInput your choice:\n";

                 std::cin>>n;
                 if(n=='1')
                     {
                         std::cout<<"Here are your messages: \n========================================\n";
                         printCSVContents("Messages.csv");
                     }
                     else if(n=='2')
                     {
                         clear_screen();
                         std::cout<<"Messages deleted\n";
                             clearFileContents("Messages.csv");

                     }
                     else if(n=='3')
                     {
                         break;
                     }
                        else
                        {
                            std::cout<<"Wrong input, try again:";
                        }
                 }
                 std::string input;
                std::cout << "Press Enter to get back to main: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, input);

                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != '4');
}


void Student::loginStudent() {
    char password[50];
    int attempts = 5;
    clear_screen();
    cout << "Enter your name and surname: ";
    cin.ignore();
    cin.getline(username, sizeof(username));

    Student* student = findStudentByName(username);
    if (student) {
        do {
            cout << "Enter your password (Attempts left: " << attempts << "): ";
            cin.getline(password, sizeof(password));
            if (student->password == password) {
                studentMenu(student);
                return;
            } else {
                cout << "Password is incorrect." << endl;
                attempts--;
            }
        } while (attempts > 0);

        cout << "You have exceeded the maximum number of attempts. Exiting..." << endl;
        exit(0);
    } else {
        cout << "There is no account under this name." << endl;
    }

    cout << "The program will now restart..." << endl;
}

void Student::loginTeacher() {
    char password[50];
    int attempts = 5;
    clear_screen();
    cout << "Enter your name and surname: ";
    cin.ignore();
    cin.getline(username, sizeof(username));

    ifstream file(folder_path + teachers_csv);
    if (file.is_open()) {
        string line;
        bool user_found = false;
        while (getline(file, line)) {
            string stored_username, stored_password;
            stringstream ss(line);
            getline(ss, stored_username, ',');
            getline(ss, stored_password, ',');

            trim(stored_username);
            trim(stored_password);

            if (stored_username == username) {
                user_found = true;
                do {
                    cout << "Enter your password (Attempts left: " << attempts << "): ";
                    cin.getline(password, sizeof(password));
                    if (stored_password == password) {
                        cout << "Welcome, " << username << endl;
                        teacherMenu();
                        file.close();
                        return;
                    } else {
                        cout << "Password is incorrect." << endl;
                        attempts--;
                    }
                } while (attempts > 0);

                cout << "You have exceeded the maximum number of attempts. Exiting..." << endl;
                file.close();
                exit(0);
            }
        }
        file.close();
        if (!user_found) {
            cout << "There is no account under this name." << endl;
        }
    } else {
        cout << "Error opening teacher database." << endl;
    }

    cout << "There is no account under this name." << endl;
    cout << "The program will now restart..." << endl;
}
