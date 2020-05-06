#include"function.h"

int main()
{
	ifstream fi;
	ofstream fo;
	LinkedListCla lstCla;
	LinkedListSta lstSta;
	LinkedListStu lstStu;
	string userid;
	string userpwd;
	int user_menu=10;
	int choice;
	cout << "1. Login" << endl;
	cout << "2. Exit" << endl;
	cout << "---------------------------" << endl;
	cout << "Your choice:";
	LoadListOfClass(lstCla);
	/*LoadDataStudent(fi, lstStu);
	fi.close();
	ImportStudentCsv(lstStu);
	fo.open("Student.txt");
	SaveDataStudent(fo, lstStu);*/
	/*cin >> choice;
	if (choice == 1) {
		Login(userid, userpwd, lstSta, lstStu);
	}
	if (choice == 0) {
		return 0;
	}*/
	return 0;
}