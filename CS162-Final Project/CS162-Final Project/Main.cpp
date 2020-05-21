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
	int choice, level, choice1, choice2;
	bool log;
	LoadDataStudent(fi_stu, lstStu);
	fi_stu.close();
	LoadDataStaff(fi_sta,lstSta);
	fi_sta.close();
	LoadListOfClass(lstCla);
	LoadDataLecturer(lstLec);
	LoadSemester(lstSem);
//lOGING------------------------------------------
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
//CHUC NANG-------------------------------------------------
		if (level == 0)//Student
		{
			do
			{
				system("cls");
				cout << "WELCOME! " << user.name << "- Student" << endl;
				Main_menu();
				cin >> choice1;
				if (choice1 == 1)
				{
					system("cls");
					ViewProfileStudent(lstStu, user.id);
					system("pause");
				}
				if (choice1 == 2)
				{
					system("cls");
					ChangePasswordStudent(lstStu,user.id);
					system("pause");
				}
				if (choice1 == 3)
				{

					do
					{
						system("cls");
						ShowMenu_Student();
						cin >> choice2;
						system("pause");
					} while (choice2 != 0);
				}
			
			} while (choice1 != 0);
		}
		if (level == 1)//Lecturer
		{
			do
			{
				system("cls");
				cout << "WELCOME! " << user.name << "- Lecturer" << endl;
				Main_menu();
				cin >> choice1;
				if (choice1 == 1)
				{
					system("cls");
					ViewProfileLecturer(lstLec, user.id);
					system("pause");
				}
				if (choice1 == 2)
				{
					system("cls");
					ChangePasswordLecturer(lstLec, user.id);
					system("pause");
				}
				if (choice1 == 3)
				{

					do
					{
						system("cls");
						ShowMenu_Lecturer();
						cin >> choice2;
						system("pause");
					} while (choice2 != 0);
				}
			} while (choice1 != 0);
		}
		if (level == 2)////Staff
		{
			do
			{
				system("cls");
				cout << "WELCOME! " << user.name << "- Staff" << endl;
				Main_menu();
				cin >> choice1;
				if (choice1 == 1)
				{
					system("cls");
					ViewProfileStaff(lstSta, user.id);
					system("pause");
				}
				if (choice1 == 2)
				{
					system("cls");
					ChangePasswordStaff(lstSta, user.id);
					system("pause");
				}
				if (choice1 == 3)
				{

					do
					{
						system("cls");
						ShowMenu_Staff();
						cin >> choice2;
						system("pause");
					} while (choice2 != 0);
				}
			} while (choice1 != 0);
		}
	}
	system("cls");
	Changecolor(4);
	cout <<setw(60) <<"SeeYa!" << endl;
	Changecolor(15);
	fo_stu.open("Student.txt");
	SaveDataStudent(fo_stu, lstStu);
	fo_sta.open("Staff.txt");
	SaveDataStaff(fo_sta, lstSta);
	SaveDataLecturer(lstLec);
	SaveSemester(lstSem);
	return 0;
}