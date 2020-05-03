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

struct Class {
	string classID;
	LinkedListStu stu;
};


struct nodeCla {
	Class dataClas;
	nodeCla* next;
};

struct LinkedListCla {
	int NumCla;
	nodeCla* head;
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
void ViewListOfClass(LinkedListCla& lst);//Lay du lieu tu file class.txt va cout ra man hinh<done>
void ViewStuOfClass();
void ChangePasswordStaff(LinkedListSta& lst, string userid);//Doi mat khau cho staff <Done>
void ChangePasswordStudent(LinkedListStu& lst, string userid);//Doi mat khau cho student <Done>
void ViewProfileStudent(const LinkedListStu& lst, string userid);//@Mac Tin
void MenuStudent();//type menu=3
void ImportStudentCsv(LinkedListStu& lst);//import file csv <Done>
bool LoadDataStudentFromClassFile(Class& cla);
void EditStudent(LinkedListCla& cla, LinkedListStu& stu);
nodeStu* FindStuInClass(LinkedListCla& lst);// tim sinh vien tu 1 mot lop cu the
nodeStu* FindStu(LinkedListStu lst, string id);//tim sinh vien tu file student.txt
void RemoveStudent();
#endif // !_FUNCTION_H_

