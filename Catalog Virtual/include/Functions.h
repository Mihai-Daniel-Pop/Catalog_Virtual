#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <fstream>

void visual_menu1();
void visual_teacher();
void clear_screen();
void appendTeacherCredentials(const std::string& name, const std::string& password, const std::string& filename);
void visual_teacher1();
void writeMessageToFile(const std::string& filename);
void printCSVContents(const std::string& filename);
void clearFileContents(const std::string& filename);


#endif
