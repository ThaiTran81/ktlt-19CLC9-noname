#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
using namespace std;
struct Staff {
	string id;
	string password;
	string fullname;
	int typeMenu;
	bool sex;
};
struct Student {
	string id;
	string password;
	string fullname;
	string classId;

	string day;
	string month;
	string year;

	int typeMenu;
	bool status;
	bool sex;
};
struct nodeStu {
	Student dataStud;
	nodeStu* next;
};

struct LinkedListStu {
	int NumStu;
	nodeStu* head;
};

struct nodeSta {
	Staff dataStaf;
	nodeSta* next;
};

struct LinkedListSta {
	int NumSta;
	nodeSta* head;
};
nodeSta* createNodeStaff(Staff x); // Dung de tao Node cho staff <Done>
nodeStu* createNodeStudent(Student x); // Dung de tao Node cho student <Done>
void Login(char* userid, char* userpwd, LinkedListSta& lstSta, LinkedListStu& lstStu);
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst);// Load du lieu txt vao list staff <Done>
bool LoadDataStudent(ifstream& fi, LinkedListStu& lst);// Load du lieu txt vao list student <Done>
bool SaveDataStaff(ofstream& fo, LinkedListSta& lst); // Save du lieu tu list staff ra txt <Done>
bool SaveDataStudent(ofstream& fo, LinkedListStu& lst);
void ViewProfileStaff(LinkedListSta& lst);
void MenuStaff();///type menu =1
void MenuStudent();//type menu=3
void ImportStudentScv();
void EditStudent();
void RemoveStudent();
#endif // !_FUNCTION_H_

