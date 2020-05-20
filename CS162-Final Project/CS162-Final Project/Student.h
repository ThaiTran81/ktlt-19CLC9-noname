#ifndef _STUDENT_H_
#define _STUDENT_H_
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;

struct Student {
	string id;
	string password;
	string fullname;
	string classId;

	string day;
	string month;
	string year;

	bool status = 1;
	bool sex;
};


struct nodeStu {
	Student dataStud;
	nodeStu* next;
};

struct LinkedListStu {
	int NumStu = 0;
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


nodeStu* createNodeStudent(Student x); // Dung de tao Node cho student <Done>
bool LoadDataStudent(ifstream& fi, LinkedListStu& lst);// Load du lieu txt vao list student <Done>
bool SaveDataStudent(ofstream& fo, LinkedListStu& lst);//done
void ChangePasswordStudent(LinkedListStu& lst, string userid);//Doi mat khau cho student <Done>
void ViewProfileStudent(const LinkedListStu& lst, string userid);//@Mac Tin <done>
string CreatePwdStu(string year, string month, string day);// tao mat khau cho sinh vien
void LoadListOfClass(LinkedListCla& lst);//Lay du lieu tu file class.txt
void ViewListOfClass(LinkedListCla& lst);//cout ra man hinh du lieu lay tu file class.txt<done>
void ViewStuOfClass(string classid);// cout students of a specific class <Done>
void ImportStudentCsv(LinkedListStu& lstStu);//import file csv <Done>
bool LoadDataStudentFromClassFile(Class& cla);
void EditStudent(LinkedListCla& cla, LinkedListStu& stu);
nodeStu* FindStuInClass(LinkedListCla& lst, nodeCla*& cur_cla);// tim sinh vien tu 1 mot lop cu the
nodeStu* FindStu(LinkedListStu& lst, string id);//tim sinh vien tu file student.txt
void RemoveStudent(LinkedListCla& cla, LinkedListStu& stu);// Delete student(status=0)
void PushStuClassNode(nodeStu*& head, Student new_data);// creat a linkedlist student for a class
bool FileClass_Exist(string idclass);//check the existance of class file
void ChangeClassStudent(LinkedListStu& lst, LinkedListCla lstCla);// move student from class A to B<Done>
void DeleteNodeStu(nodeStu*& head, string idstu);//delete a specific student
void AddAStu(LinkedListStu& lst, LinkedListCla cla);// add a student to a class <Done>


#endif // !_STUDENT_H_

