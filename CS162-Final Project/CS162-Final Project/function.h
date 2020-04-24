#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;


struct nodeStu {
	Student data;
	nodeStu* next;
};

struct LinkedListStu {
	nodeStu* head;
};

struct nodeSta {
	Staff data;
	nodeSta* next;
};

struct LinkedListSta {
	nodeSta* head;
};

struct Staff {
	char* id;
	char* password;
	char* fullname;
	int typeMenu;
	bool sex;
};

struct Student {
	char id[10];
	char* password;
	char* fullname;
	char* classId;

	int day;
	int month;
	int year;

	int typeMenu;
	bool status;
	bool sex;
};


void Login(char* userid, char* userpwd);
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst);
bool LoadDataStudent(ifstream& fi, LinkedListStu& lst);
bool SaveDataStaff(ofstream& fo, int& nstaff, Staff* arr);
bool SaveDataStudent(ofstream& fo, int& nstudent, Student* arr);
void ViewProfileStaff();
void MenuStaff();///type menu =1
void MenuStudent();//type menu=3
void ImportStudentScv();
void EditStudent();
void RemoveStudent();
#endif // !_FUNCTION_H_

