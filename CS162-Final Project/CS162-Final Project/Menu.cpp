#include"function.h"
#include"Menu.h"
void Changecolor(int n)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, n);
}
void LoadingEffect()
{
	
	for (int i = 0; i < 1; i++)
	{
		system("cls");
		cout << "Waiting";
		cout << ". ";
		Sleep(1000);
		cout << ". ";
		Sleep(1000);
		cout << ". ";
		Sleep(1000);
	}
	cout << endl;
}
void Main_menu()
{  
	cout << "0. Logout" << endl;
	cout << "1. View profile info" << endl;
	cout << "2. Change password" << endl;	
	cout << "3. Show menu" << endl;
	cout << "Your choice: ";
}
void ShowMenu_Staff()
{
	cout << "1. Import students of a class such as 18CLC6 from a csv file." << endl;
	cout << "2. Manually add a new student to a class." << endl;
	cout << "3. Edit an existing student." << endl;
	cout << "4. Remove a Student." << endl;
	cout << "5. Change students from class A to class B" << endl;
	cout << "6. View list of classes." << endl;
	cout << "7. View list of students in a class." << endl;
	cout << "8. Create / update / delete / view academic years, and semesters."<<endl;
	cout << "9. From a semester, import courses" << endl;
	cout << "10. Edit an existing course." << endl;
	cout << "11. Remove a course." << endl;
	cout << "12. Remove a specific student from a course." << endl;
	cout << "13. Add a specific student to a course." << endl;
	cout << "14. View list of courses in the current semester." << endl;
	cout << "15. View list of students of a course." << endl;
	cout << "16. View attendance list of a course." << endl;
	cout << "17. Create / update / delete / view all lecturers." << endl;
	cout << "18. Search and view the scoreboard of a course." << endl;
	cout << "19. Export a scoreboard to a csv file." << endl;
	cout << "0. Back." << endl;
	cout << "Your choice: ";
}
void ShowMenu_Lecturer()
{
	cout << "1. View list of courses in a semester." << endl;
	cout << "2. View list of students of a course." << endl;
	cout << "3. View attendance list of a course." << endl;
	cout << "4. Edit an attendance." << endl;
	cout << "5. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file." << endl;
	cout << "6. Edit grade of a student" << endl;
	cout << "7. View a scoreboard" << endl;
	cout << "0. Back." << endl;
	cout << "Your choice: ";
}
void ShowMenu_Student()
{
	cout << "1.Check-in" << endl;
	cout << "2.View check-in result" << endl;
	cout << "3.View schedules" << endl;
	cout << "4.View scores of a course" << endl;
	cout << "0. Back." << endl;
	cout << "Your choice: ";
}