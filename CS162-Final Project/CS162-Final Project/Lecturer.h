#ifndef _LECTURER_H_
#define _LECTURER_H_

#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;

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


void DeleteNodeLec(nodeLec*& head, string idLec);//Mac Tin<done>
void PushNodeLecturer(nodeLec*& head, Lecturer new_data);// creat linked list lecturer <Done>
void LoadDataLecturer(LinkedListLec& lst);//Anh Tuan<done>
void SaveDataLecturer(LinkedListLec lst);//Anh Tuan<done>
void ChangePasswordLecturer(LinkedListLec& lst, string userid);//Anh Tuan<Done>
void ViewProfileLecturer(LinkedListLec& lst, string userid );//Anh Tuan <Done>
#endif // !_LECTURER_H_

