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
	User user;
	int user_menu=10;
	int choice;
	cout << "1. Login" << endl;
	cout << "2. Exit" << endl;
	cout << "---------------------------" << endl;
	cout << "Your choice:";
	LoadListOfClass(lstCla);
	LoadDataStudent(fi_stu, lstStu);
	LoadDataStaff(fi_sta,lstSta);
	//ImportStudentCsv(lstStu);
	ViewListOfClass(lstCla);
	ViewStuOfClass("19CLC9");
	//RemoveStudent(lstCla, lstStu);
	//AddAStu(lstStu, lstCla);
	//EditStudent(lstCla, lstStu);
	//ChangeClassStudent(lstStu, lstCla);
	fo_stu.open("Student.txt");
	SaveDataStudent(fo_stu, lstStu);
	fo_sta.open("Staff.txt");
	SaveDataStaff(fo_sta, lstSta);
	/*cin >> choice;
	if (choice == 1) {
		Login(userid, userpwd, lstSta, lstStu);
	}
	if (choice == 0) {
		return 0;
	}*/
	return 0;
}