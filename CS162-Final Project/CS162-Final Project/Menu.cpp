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
	cout << "Waiting";
	for (int i = 0; i < 4; i++)
	{
		cout << ".";
		Sleep(1000);
	}
	cout << endl;
}
void Main_menu()
{  
	cout << "0. Logout" << endl;
	cout << "1. View profile info" << endl;
	cout << "2. Change password" << endl;	
}
void ShowMenu_Staff()
{
	cout << "3. Import students of a class such as 18CLC6 from a csv file." << endl;
	cout << "4. Manually add a new student to a class." << endl;
	cout << "5. Edit an existing student." << endl;
	cout << "6. Remove a Student." << endl;
	cout << "7. Change students from class A to class B" << endl;
	cout << "8. View list of classes." << endl;
	cout << "9. View list of students in a class." << endl;
	cout << "10. Create / update / delete / view academic years, and semesters."<<endl;
	cout << "11. From a semester, import courses" << endl;
	cout << "12. Edit an existing course." << endl;
	cout << "13. Remove a course." << endl;
	cout << "14. Remove a specific student from a course." << endl;
	cout << "15. Add a specific student to a course." << endl;
	cout << "16. View list of courses in the current semester." << endl;
	cout << "17. View list of students of a course." << endl;
	cout << "18. View attendance list of a course." << endl;
	cout << "19. Create / update / delete / view all lecturers." << endl;
	cout << "20. Search and view the scoreboard of a course." << endl;
	cout << "21. Export a scoreboard to a csv file." << endl;
	cout << "Your choice: ";
}
void ShowMenu_Lecturer()
{
	cout << "3. View list of courses in the current semester." << endl;
	cout << "4. View list of students of a course." << endl;
	cout << "5. View attendance list of a course." << endl;
	cout << "6. Edit an attendance." << endl;
	cout << "7. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file." << endl;
	cout << "8. Edit grade of a student" << endl;
	cout << "9. View a scoreboard" << endl;
	cout << "Your choice: ";
}
void ShowMenu_Student()
{
	cout << "3.Check-in" << endl;
	cout << "4.View check-in result" << endl;
	cout << "5.View schedules" << endl;
	cout << "6.View scores of a course" << endl;
	cout << "Your choice: ";
}
