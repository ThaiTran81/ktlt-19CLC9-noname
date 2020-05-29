#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#include<ctime>
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
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define YELLOW  "\033[33m"      /* Yellow */
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
	bool status=-1;// in university
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


string printProg(int x);
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
void ViewStuCourseClass(LinkedListSemes lst, string idLec="");// view students of a course in a class
void PrintListCourseOfClass(Semester& semester, string idclass);//cout list of courses of a class in a semester<done>
void defineDate(int month, int year, int& daymax);
int dayofweek(int d, int m, int y);
void AnalysisDate(Schedule start, Schedule end, LinkedListSche& lst, int firstday);// creat linkedlist schedule<done>
void AddACourse(LinkedListSemes lstSemes, LinkedListLec& lstLec);//add a course to a class in a specific semester<done>
bool LoadCourseSemes(Semester semester,LinkedListCourse& lstCourse);//load courses of a specific semester<done>
bool SaveCourseSemes(Semester semester, LinkedListCourse lstCourse);// save courses of a specific semester<done>
bool SaveStuCourse(Semester semester, Course& course, string idclass);//save student in course<doen>
void RemoveACourse(LinkedListSemes lst);//remove a course<done>
void ViewListAttendence(LinkedListSemes lst, string idLec="");//view list of attendence of a course<done>
void ViewSemester(LinkedListSemes lst);// Mac Tin
void RemoveStuCourse(LinkedListSemes lst);//Gia Huy<done>
void AddStuCourse(LinkedListSemes lstSemes, LinkedListStu lstStu);// add a student to a course<done>
void ViewListCourseSemes(LinkedListSemes lst);// view list of courses of a semester<Done>
void ViewScoreCourse(LinkedListSemes lst, string idLec="");//view scoreboard of a course<done>
void EditCourse(LinkedListSemes lstSem, LinkedListLec& lstLec);//edit a course <done>
void ViewProfileCourse(Course course);//<done>
void ChoiceEditCourse();//<done>
void AssignScheduleStu(LinkedListPar& lst, LinkedListSche lstSche);//<done>
nodePar* FindParticipant(LinkedListPar& lst, string id);//find participant<done>
bool CheckLecCourse(Semester semester, string idCourse, string idClass, string idLec);//check whether the lecturer is in course<done>
void ExportScore(LinkedListSemes lst);//Gia Huy<done>
void ExportAttendence(LinkedListSemes lst);//Anh Tuan
void CheckingStu(LinkedListSemes lstSem, string id_user);
nodeDat* CheckDay(Participant& participant, Course course);
void ViewAScore(nodePar* attendence);// view score of a student<done>
void ViewAAtendence(nodePar* attendence);//view check in of a student<done>
void ViewMyScore(LinkedListSemes lst, string id);//for student view his score<done>
void ViewMyAttendence(LinkedListSemes lst, string id);//for student view his attendence<done>
void ViewMySchedule(LinkedListSemes lst, string id);//for student view his schedule<done>
nodeCourse* FindCourse(LinkedListCourse lst, string id);//find course in a class<done>



//for lecturer
void ImportScoreBoard(LinkedListSemes lst, string idLec = "");//import score
void EditGradeStu(LinkedListSemes lstSem);// edit grade<done>
void EditAttendence(LinkedListSemes lstSem, string idLec="");// edit checking attendence<done>

#endif // !_FUNCTION_H_