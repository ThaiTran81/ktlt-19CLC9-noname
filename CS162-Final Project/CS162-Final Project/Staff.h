#ifndef _STAFF_H_
#define _STAFF_H_
#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<iomanip>
using namespace std;

struct Staff {
	string id;
	string password;
	string fullname;
	bool sex;
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
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst);// Load du lieu txt vao list staff <Done>
bool SaveDataStaff(ofstream& fo, LinkedListSta& lst); // Save du lieu tu list staff ra txt <Done>
void ViewProfileStaff(const LinkedListSta& lst, string userid);//done
void ChangePasswordStaff(LinkedListSta& lst, string userid);//Doi mat khau cho staff <Done>

#endif // !_STAFF_H_

