#include"function.h"

int main()
{
	ifstream fi_stu("Student.txt");
	ifstream fi_sta("Staff.txt");
	ofstream fo_stu, fo_sta;
	LinkedListCla lstCla;
	LinkedListSta lstSta;
	LinkedListLec lstLec;
	LinkedListStu lstStu;
	LinkedListSemes lstSem;
	User user;
	int user_menu = 10;
	int choice, level, choice1, choice2;
	bool log;
	LoadDataStudent(fi_stu, lstStu);
	fi_stu.close();
	LoadDataStaff(fi_sta, lstSta);
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
			log = Login(user, lstSta, lstStu, lstLec, level);
			if (log == false)
			{
				cout << "1. Continue" << endl;
				cout << "0. Exit" << endl;
				cout << "---------------------------" << endl;
				cout << "Your choice: ";
				cin >> choice;
				if (choice == 0)
					break;
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
					ChangePasswordStudent(lstStu, user.id);
					system("pause");
				}
				if (choice1 == 3)
				{

					do
					{
						system("cls");
						ShowMenu_Student();
						cin >> choice2;
						if (choice2 == 1)//Check-in
						{
							system("cls");
							CheckingStu(lstSem, user.id);
							system("pause");
						}
						if (choice2 == 2)//View check-in result
						{
							system("cls");
							ViewMyAttendence(lstSem, user.id);
							system("pause");
						}
						if (choice2 == 3)//View schedules
						{
							system("cls");
							ViewMySchedule(lstSem, user.id);
							system("pause");
						}
						if (choice2 == 4)//View scores of a course
						{
							system("cls");
							ViewMyScore(lstSem, user.id);
							system("pause");
						}
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
						if (choice2 == 1)//View list of courses in the current semester
						{
							system("cls");
							ViewListCourseSemes(lstSem);
							system("pause");
						}
						if (choice2 == 2)//View list of students of a course
						{
							system("cls");
							ViewStuCourseClass(lstSem, user.id);
							system("pause");
						}
						if (choice2 == 3)//View attendance list of a course
						{
							system("cls");
							ViewListAttendence(lstSem,user.id);
							system("pause");
						}
						if (choice2 == 4)//Edit an attendance
						{
							system("cls");
							EditAttendence(lstSem,user.id);
							system("pause");
						}
						if (choice2 == 5)//Import scoreboard of a course(midterm, final, lab, bonus) from a csv file
						{
							system("cls");
							ImportScoreBoard(lstSem, user.id);
							system("pause");
						}
						if (choice2 == 6)//Edit grade of a student
						{
							system("cls");
							EditGradeStu(lstSem);
							system("pause");
						}
						if (choice2 == 7)//View Score Board
						{
							system("cls");
							ViewScoreCourse(lstSem);
							system("pause");
						}
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
						if (choice2 == 1)//Import Student from a csv file 
						{
							system("cls");
							ImportStudentCsv(lstStu);
							system("pause");
						}
						else if (choice2 == 2)//Manually add a new student to a class
						{
							system("cls");
							AddAStu(lstStu, lstCla);
							system("pause");
						}
						else if (choice2 == 3)//Edit an existing student(!)
						{
							system("cls");
							EditStudent(lstCla, lstStu);
							system("pause");
						}
						else if (choice2 == 4)// Remove a Student
						{
							system("cls");
							RemoveStudent(lstCla, lstStu);
							system("pause");
						}
						else if (choice2 == 5)//Change students from class A to class B
						{
							system("cls");
							ChangeClassStudent(lstStu, lstCla);
							system("pause");
						}
						else if (choice2 == 6)//View list of classes
						{
							system("cls");
							ViewListOfClass(lstCla);
							system("pause");
						}
						else if (choice2 == 7)//View list of students in a class.(!)
						{
							string idclass;
							system("cls");
							cout << "Enter Class which you want to see:" << endl;
							cin.ignore();
							getline(cin, idclass);
							ViewStuOfClass(idclass);
							system("pause");
						}
						else if (choice2 == 8)// creat semester
						{
							system("cls");
							CreateSemester(lstSem);
							system("pause");
						}
						else if (choice2 == 9)//delete semester
						{
							system("pause");
						}
						else if (choice2 == 10)//view semester
						{
							system("cls");
							ViewSemester(lstSem);
							system("pause");
						}
						else if (choice2 == 11)//import course
						{
							system("cls");
							ImportCourse(lstSem, lstLec);
							system("pause");
						}
						else if (choice2 == 12)// edit course
						{
							system("cls");
							EditCourse(lstSem, lstLec);
							system("pause");
						}
						else if (choice2 == 13)//remove course
						{
							system("cls");
							RemoveACourse(lstSem);
							system("pause");
						}
						else if (choice2 == 14)//remove a student from a course
						{
							system("cls");
							RemoveStuCourse(lstSem);
							system("pause");
						}
						else if (choice2 == 15)// add a student to a course
						{
							system("cls");
							AddStuCourse(lstSem, lstStu);
							system("pause");
						}
						else if (choice2 == 16)//View list of courses in the current semester.
						{
							system("cls");
							ViewListCourseSemes(lstSem);
							system("pause");
						}
						else if (choice2 == 17)//View list of students of a course.
						{
							system("cls");
							ViewStuCourseClass(lstSem);
							system("pause");
						}
						else if (choice2 == 18)//View attendance list of a course.
						{
							system("cls");
							ViewListAttendence(lstSem);
							system("pause");
						}
						else if (choice2 == 19)//Export attendance list of a course.
						{
							system("cls");
							ExportAttendence(lstSem);
							system("pause");
						}
						else if (choice2 == 20)//creat lecturer
						{
							system("cls");
							cin.ignore();
							CreateLecturer(lstLec);
							system("pause");
						}
						else if (choice2 == 21)//delete Lecturer
						{
							system("cls");
							cin.ignore();
							DeleteLecturer(lstLec);
							system("pause");
						}
						else if (choice2 == 22)//view Lecturer
						{
							system("cls");
							ViewAllLecturer(lstLec);
							system("pause");
						}
						else if (choice2 == 23)//view scoreboard
						{
							system("cls");
							ViewScoreCourse(lstSem);
							system("pause");
						}
						else if (choice2 == 24)//export score
						{
							system("cls");
							ExportScore(lstSem);
							system("pause");
						}
					} while (choice2 != 0);
				}
			} while (choice1 != 0);
		}
	}
	system("cls");
	Changecolor(4);
	cout << setw(60) << "SeeYa!" << endl;
	Changecolor(15);
	fo_stu.open("Student.txt");
	SaveDataStudent(fo_stu, lstStu);
	fo_sta.open("Staff.txt");
	SaveDataStaff(fo_sta, lstSta);
	SaveDataLecturer(lstLec);
	SaveSemester(lstSem);
	return 0;
}