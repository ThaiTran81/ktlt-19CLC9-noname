#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include <conio.h>
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include <windows.h>
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
	int numDat=0;
	nodeDat* head=NULL;
};

struct Participant {
	string id;
	string fullname;
	string classId;
	string year, month, day;
	bool status;// in university
	bool status_course=1;// in course
	float mid=-1, final=-1, bonus=-1, total=-1;
	LinkedListDat timeCheck;
};

struct nodePar {
	Participant dataPar;
	nodePar* next;
};

struct LinkedListPar {
	int numPar=0;
	nodePar* head=NULL;
};

struct Schedule {
	string year, month, day;
};

struct nodeSche {
	Schedule data;
	nodeSche* next;
};

struct LinkedListSche {
	int numSche=0;
	nodeSche* head=NULL;
};

struct Course {
	string id;
	string name;
	string classId;
	Lecturer lec;
	string hour_start, minute_start, hour_end, minute_end;
	int firstday;
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
	int numCourse=0;
	nodeCourse* head=NULL;
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
	int numSemes=0;
	nodeSemes* head=NULL;
};


bool Login(User& user, LinkedListSta lstSta, LinkedListStu lstStu, LinkedListLec lstLec,int &level);
void DeleteNodeCourse(nodeCourse*& head, string idCourse);//Mac Tin
void PushNodeParticipant(nodePar*& head, Participant new_data);//Gia Huy<done>
void PushNodeSemester(nodeSemes*& head, Semester new_data);//Gia Huy<done>
void PushNodeCourse(nodeCourse*& head, Course new_data);//Gia Huy<done>
nodeSemes* FindSemester(LinkedListSemes lst, string name, string yearbeg, string yearend);// find semester<done>
bool LoadSemester(LinkedListSemes& lst);//<done>
bool SaveSemester(LinkedListSemes lst);//done
void CreateSemester(LinkedListSemes& lst);//done
bool SaveFileCourseClass(Semester data, string idclass);// save courses of a class in a semester<done>
void ScheduleCourse(Course& course);//schedule date for course <done>
bool EnrollStuClassToCourse(string idclass, Semester semester, Course course);// copy all students to imported courses.<done>
void ImportCourse(LinkedListSemes& lstSem, LinkedListLec& lstLec);// import cousres of a class in a semester<done>
bool LoadStuCourseClass(Semester semester,Course& course, string idclass);//load data student from a course file in a class<done>
bool LoadDataCourseClass(Semester& semester, string idclass);// load data courses in a class <done>
int ChoiceCourseClass(LinkedListSemes lst,Semester& semester, string& idclass);//=-1(failed)<done>
nodeSche* CreatNodeShe(Schedule data);//<done>
nodeDat* CreateNodeDate(Date data);//create date checking for student<done>
void ViewStuCourseClass(LinkedListSemes lst);// view students of a course in a class
void PrintListCourseOfClass(Semester& semester, string idclass);//cout list of courses of a class in a semester<done>
void defineDate(int month, int year, int& daymax);
int dayofweek(int d, int m, int y);
void AnalysisDate(Schedule start, Schedule end, LinkedListSche& lst, int firstday);// creat linkedlist schedule<done>
void AddACourse(LinkedListSemes lstSemes, LinkedListLec& lstLec);//add a course to a class in a specific semester<done>
bool LoadCourseSemes(Semester semester,LinkedListCourse& lstCourse);//load courses of a specific semester<done>
bool SaveCourseSemes(Semester semester, LinkedListCourse lstCourse);// save courses of a specific semester<done>
bool SaveStuCourse(Semester semester, Course& course, string idclass);//save student in course<doen>
void RemoveACourse(LinkedListSemes lst);//remove a course<done>
void ViewListAttendence(LinkedListSemes lst);//view list of attendence of a course<done>
void ViewSemester(LinkedListSemes lst);// Mac Tin
void RemoveStuCourse(LinkedListSemes lst);//Gia Huy<done>
void AddStuCourse(LinkedListSemes lstSemes, LinkedListStu lstStu);// add a student to a course<done>
void ViewListCourseSemes(LinkedListSemes lst);// view list of courses of a semester<Done>
void ViewScoreCourse(LinkedListSemes lst);//view scoreboard of a course<done>
void EditCourse(LinkedListSemes lstSem, LinkedListLec& lstLec);//edit a course 
void ViewProfileCourse(Course course);
void ChoiceEditCourse();
void AssignScheduleStu(LinkedListPar& lst, LinkedListSche lstSche);

//for lecturer<lecturer.cpp>
void ViewStuCourseClassLec(LinkedListSemes lst);
void ViewAttendenceLec(LinkedListSemes lst);
void ImportScore(LinkedListSemes lst);
void EditGradeStu(LinkedListSemes lst);
void EditAttendence(LinkedListSemes lst);

#endif // !_FUNCTION_H_