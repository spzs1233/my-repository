#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sys/stat.h> 
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <filesystem>
#include <experimental/filesystem>
#include <cstdio>
#include <stdexcept>

typedef long long ll;
using namespace std;
using namespace std::experimental::filesystem;
int menu();
int createFile(string file_name);
bool fileExists(const string& filename);
int stu_menu();
int student_login();
int student_menu(string id);
int change_thing(string filename, string need_change_word, string new_word);
void removeLinesFromFile(const string& filename, const string& lineToRemove);
int register_student();
int register_tea();
int teacher_menu(string id);
int tea_menu();
int admin_menu();
bool isFileEmptyOrWhitespace(ifstream& file);
int read_tea();
int choice_tea();