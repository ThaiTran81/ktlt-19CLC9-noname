#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;

struct User {
	string id;
	string password;
	bool sex;
	string name;
};

struct Staff {
	string id;
	string password;
	string fullname;
	int typeMenu=100;
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

	int typeMenu=300;
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

struct Lecturer {
	string id;
	string password;
	string name;
	string degree;
	bool sex;
};

struct nodeLec {
	Lecturer dataLec;
	nodeLec* next;
};

struct LinkedListLec {
	int numLec;
	nodeLec* head;
};

struct Date {
	string year;
	string month;
	string day;
	string hour, minute;
	int checking=-1;
};

struct nodeDat {
	Date dataDat;
	nodeDat* next;
};

struct LinkedListDat {
	int numDat;
	nodeDat* head;
};

struct Participant {
	string id;
	string fullname;
	string classId;
	bool status;// in university
	bool status_course;// in course
	float mid, final, bonus, total;
	LinkedListDat timeCheck;
};

struct nodePar {
	Participant dataPar;
	nodePar* next;
};

struct LinkedListPar {
	int numPar;
	nodePar* head;
};

struct Schedule {
	string year, month, day;
};

struct nodeSche {
	Schedule data;
	nodeSche* next;
};

struct LinkedListSche {
	int numSche;
	nodeSche* head;
};

struct Course {
	string id;
	string name;
	string classId;
	Lecturer lec;
	string hour_start, minute_start, hour_end, minute_end;
	int day_week;
	string year_start, month_start, day_start;
	string year_end, month_end, day_end;
	LinkedListPar participant;
	LinkedListSche schedule;
	string room;
};

struct nodeCourse {
	Course data;
	nodeCourse* next;
};

struct LinkedListCourse {
	int numCourse;
	nodeCourse* head;
};

struct Semester {
	string name;
	string yearBeg;
	string yearEnd;
	LinkedListCourse course;
};

struct nodeSemes {
	Semester data;
	nodeSemes* next;
};

struct LinkedListSemes {
	int numSemes;
	nodeSemes* head;
};




nodeSta* createNodeStaff(Staff x); // Dung de tao Node cho staff <Done>
nodeStu* createNodeStudent(Student x); // Dung de tao Node cho student <Done>

bool Login(User& user, LinkedListSta lstSta, LinkedListStu lstStu, LinkedListLec lstLec);
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst);// Load du lieu txt vao list staff <Done>
bool LoadDataStudent(ifstream& fi, LinkedListStu& lst);// Load du lieu txt vao list student <Done>
bool SaveDataStaff(ofstream& fo, LinkedListSta& lst); // Save du lieu tu list staff ra txt <Done>
bool SaveDataStudent(ofstream& fo, LinkedListStu& lst);//done
void ViewProfileStaff(const LinkedListSta& lst, string userid);//done
void MenuStaff_class();///menu->class
string CreatePwdStu(string year, string month, string day);// tao mat khau cho sinh vien
void LoadListOfClass(LinkedListCla& lst);//Lay du lieu tu file class.txt
void ViewListOfClass(LinkedListCla& lst);//cout ra man hinh du lieu lay tu file class.txt<done>
void ViewStuOfClass(string classid);// cout students of a specific class <Done>
void ChangePasswordStaff(LinkedListSta& lst, string userid);//Doi mat khau cho staff <Done>
void ChangePasswordStudent(LinkedListStu& lst, string userid);//Doi mat khau cho student <Done>
void ViewProfileStudent(const LinkedListStu& lst, string userid);//@Mac Tin
void MenuStudent();//type menu=3
void ImportStudentCsv(LinkedListStu& lst);//import file csv <Done>
bool LoadDataStudentFromClassFile(Class& cla);
void EditStudent(LinkedListCla& cla, LinkedListStu& stu);
nodeStu* FindStuInClass(LinkedListCla& lst,nodeCla*&cur_cla);// tim sinh vien tu 1 mot lop cu the
nodeStu* FindStu(LinkedListStu lst, string id);//tim sinh vien tu file student.txt
void RemoveStudent(LinkedListCla& cla, LinkedListStu& stu);// Delete student(status=0)
void PushStuClassNode(nodeStu*&head,Student new_data);// creat a linkedlist student for a class
bool FileClass_Exist(string idclass);//check the existance of class file
void ChangeClassStudent(LinkedListStu& lst, LinkedListCla lstCla);// move student from class A to B<Done>
void DeleteNodeStu(nodeStu*& head, string idstu);//delete a specific student
void AddAStu(LinkedListStu& lst, LinkedListCla cla);// add a student to a class <Done>

void DeleteNodeCourse(nodeCourse*& head, string id_course);//Mac Tin
void DeleteNodeLecturer(nodeLec*& head, string id_lec);//Mac Tin<done>
void PushNodeParticipant(nodePar*& head, Participant new_data);//Gia Huy
void PushNodeSemester(nodeSemes*& head, Semester new_data);//Gia Huy
void PushNodeCourse(nodeCourse*& head, Course new_data);//Gia Huy
void PushNodeLecturer(nodeLec*& head, Lecturer new_data);// creat linked list lecturer <Done>
void LoadDataLecturer(LinkedListLec& lst);//Anh Tuan<done>
void SaveDataLecturer(LinkedListLec lst);//Anh Tuan<done>
#endif // !_FUNCTION_H_
