#include "Functions.h"
void visual_menu1() {
    std::cout << "=====================================================\n";
    std::cout << "||           Welcome to the Virtual Catalog        ||\n";
    std::cout << "=====================================================\n";
    std::cout << "||                                                 ||\n";
    std::cout << "||                 Select your role:               ||\n";
    std::cout << "||                                                 ||\n";
    std::cout << "||                 (1) Teacher                     ||\n";
    std::cout << "||                 (2) Student                     ||\n";
    std::cout << "||                                                 ||\n";
    std::cout << "=====================================================\n";
    std::cout << "Input your choice: ";
}

void visual_teacher()
{
    std::cout << "=====================================================\n";
    std::cout << "||           Welcome to the Virtual Catalog        ||\n";
    std::cout << "=====================================================\n";
    std::cout << "||                                                 ||\n";
    std::cout << "||               Select your choice:               ||\n";
    std::cout << "||                                                 ||\n";
    std::cout << "||               (1) View Student Grades           ||\n";
    std::cout << "||               (2) Modify Student  Grades        ||\n";
    std::cout << "||               (3) Enroll Student                ||\n";
    std::cout << "||               (4) Exit                          ||\n";
    std::cout << "||               (5) See the Class                 ||\n";
    std::cout << "||               (6) Messages                      ||\n";
    std::cout << "||                                                 ||\n";
    std::cout << "=====================================================\n";
    std::cout << "Input your choice: ";
}

void visual_teacher1()
{
    std::cout << "=====================================================\n";
    std::cout << "||           Welcome to the Virtual Catalog        ||\n";
    std::cout << "=====================================================\n";
    std::cout << "||                                                 ||\n";
    std::cout << "||                 Select your choice:             ||\n";
    std::cout << "||                                                 ||\n";
    std::cout << "||                 (1) Login                       ||\n";
    std::cout << "||                 (2) Sign up                     ||\n";
    std::cout << "||                                                 ||\n";
    std::cout << "=====================================================\n";
    std::cout << "Input your choice: ";
}


void appendTeacherCredentials(const std::string& name, const std::string& password, const std::string& filename) {
    // Open the file in append mode
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }


    file << name << "," << password << "\n";


    file.close();


    std::cout << "Credentials for " << name << " have been appended to " << filename << std::endl;
}
#include <limits>
void writeMessageToFile(const std::string& filename) {
    std::string name;
    std::string message;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your message: ";
    std::getline(std::cin, message);

    std::ofstream file(filename, std::ios::app);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "From: \"" << name << "\"\n";
    file << "Message: \"" << message << "\"\n";

    file << "-----------------------\n";

    file.close();

    std::cout << "Message saved to " << filename << std::endl;
}

void printCSVContents(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        std::cout << line << std::endl;
    }

    file.close();
}



void clearFileContents(const std::string& filename) {
    std::ofstream file(filename, std::ofstream::trunc);

    if (!file.is_open()) {
        std::cerr << "Failed to open and clear file: " << filename << std::endl;
    } else {
        std::cout << "File contents cleared successfully." << std::endl;
        file.close();
    }
}



void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
