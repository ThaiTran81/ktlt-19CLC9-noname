#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
#include"Lecturer.h"
#include"Student.h"
#include"Staff.h"
#include"Menu.h"
using namespace std;


struct User {
	string id;
	string password;
	bool sex;
	string name;
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


bool Login(User& user, LinkedListSta lstSta, LinkedListStu lstStu, LinkedListLec lstLec);
void DeleteNodeCour(nodeCourse*& head, string idCour);//Mac Tin
void PushNodeParticipant(nodePar*& head, Participant new_data);//Gia Huy<done>
void PushNodeSemester(nodeSemes*& head, Semester new_data);//Gia Huy<done>
void PushNodeCourse(nodeCourse*& head, Course new_data);//Gia Huy<done>

#endif // !_FUNCTION_H_
