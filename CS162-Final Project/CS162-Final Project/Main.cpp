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
	int choice,level,choice1;
	bool log;
	LoadDataStudent(fi_stu, lstStu);
	LoadDataStaff(fi_sta, lstSta);
	LoadSemester(lstSem);
	LoadDataLecturer(lstLec);
	LoadListOfClass(lstCla);
	cout << "1. Login" << endl;
	cout << "0. Exit" << endl;
	cout << "---------------------------" << endl;
	cout << "Your choice: ";
	cin >> choice;
	if (choice == 1)
	{
		do 
		{
			system("cls");
			log = Login(user, lstSta, lstStu, lstLec,level);
			if (log == false)
			{
				cout << "1. Continue" << endl;
				cout << "0. Exit" << endl;
				cout << "---------------------------" << endl;
				cout << "Your choice: ";
				cin >> choice;
				if (choice == 0)
					return 0;
			}
		} while (log != true);
		if (level == 0)//Student
		{
			do
			{
				system("cls");
				Main_menu();
				ShowMenu_Student();
				cin >> choice1;
				if (choice1 == 1)
				{
					system("cls");
					ViewProfileStudent(lstStu, user.id);
					system("pause");
				}
			
			} while (choice1 != 0);
		}
		if (level == 1)//Lecturer
		{
			do
			{
				system("cls");
				Main_menu();
				ShowMenu_Lecturer();
				cin >> choice1;
				if (choice1 == 1)
				{
					system("cls");
					ViewProfileLecturer(lstLec, user.id);
					system("pause");
				}
			} while (choice1 != 0);
		}
		if (level == 2)////Staff
		{
			do
			{
				system("cls");
				Main_menu();
				ShowMenu_Staff();
				cin >> choice1;
				if (choice1 == 1)
				{
					system("cls");
					ViewProfileStaff(lstSta, user.id);
					system("pause");
				}
			} while (choice1 != 0);
		}
	}
	system("cls");
	Changecolor(4);
	cout <<setw(60) <<"SeeYa!" << endl;
	Changecolor(15);
	return 0;
}