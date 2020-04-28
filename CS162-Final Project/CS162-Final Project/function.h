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
	int typeMenu=1;
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

	int typeMenu=3;
	bool status=1;
	bool sex;
};
struct nodeStu {
	Student dataStud;
	nodeStu* next;
};

struct LinkedListStu {
	int NumStu=0;
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



void Login(string& userid, string& userpwd, LinkedListSta lstSta, LinkedListStu lstStu);
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst);// Load du lieu txt vao list staff <Done>
bool LoadDataStudent(ifstream& fi, LinkedListStu& lst);// Load du lieu txt vao list student <Done>
bool SaveDataStaff(ofstream& fo, LinkedListSta& lst); // Save du lieu tu list staff ra txt <Done>
bool SaveDataStudent(ofstream& fo, LinkedListStu& lst);//done
void ViewProfileStaff(const LinkedListSta& lst, string userid);//done
void MenuStaff_class();///menu->class
string CreatePwdStu(string year, string month, string day);// tao mat khau cho sinh vien
void ViewListOfClass();//@Gia Huy (lay du lieu tu file class.txt va cout ra man hinh)
void ViewStuOfClass();
void ChangePasswordStaff(LinkedListSta& lst, string userid);//@Anh Tuan (doi mat khau cho user staff)
void ViewProfileStudent(const LinkedListStu& lst, string userid);//@Mac Tin
void MenuStudent();//type menu=3
void ImportStudentCsv(LinkedListStu& lst);//import file csv <Done>
void EditStudent();
void RemoveStudent();
#endif // !_FUNCTION_H_

