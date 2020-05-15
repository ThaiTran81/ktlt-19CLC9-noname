#include"function.h"

int main()
{
	ifstream fi_stu("Student.txt");
	ifstream fi_sta("Staff.txt");
	ofstream fo_stu,fo_sta;
	LinkedListCla lstCla;
	LinkedListSta lstSta;
	LinkedListLec lstLec;
	LinkedListStu lstStu;
	LinkedListSemes lstSem;
	User user;
	int user_menu=10;
	int choice;
	cout << "1. Login" << endl;
	cout << "2. Exit" << endl;
	cout << "---------------------------" << endl;
	cout << "Your choice:"<<endl;
	LoadDataStudent(fi_stu, lstStu);
	LoadDataStaff(fi_sta,lstSta);
	LoadSemester(lstSem);
	CreateSemester(lstSem);
	ImportCourse(lstSem);
	SaveSemester(lstSem);
	fo_stu.open("Student.txt");
	SaveDataStudent(fo_stu, lstStu);
	fo_sta.open("Staff.txt");
	SaveDataStaff(fo_sta, lstSta);
	return 0;
}