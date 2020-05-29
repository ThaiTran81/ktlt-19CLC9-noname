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

	srand(time(0));
	int x = 0;
	cout << "Logging ..." << endl;
	for (int i = 0; i < 100; i++) {
		int r = rand() % 1000;
		x++;
		cout << "\r" << setw(-20) << printProg(x) << " " << x << "% completed." << flush;
		if (i < 43) {
			Sleep(r / 16);
		}
		else if (i > 43 && i < 74) {
			Sleep(r / 18);
		}
		else if (i < 98) {
			Sleep(r / 15);
		}
		else if (i > 97 && i != 99) {
			Sleep(1000);
		}
	}
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
	cout << endl;
	cout << "8. Create semesters." << endl;
	cout << "9. Delete semesters." << endl;
	cout << "10. View semester." << endl;
	cout << "11. From a semester, import courses" << endl;
	cout << "12. Edit an existing course." << endl;
	cout << endl;
	cout << "13. Remove a course." << endl;
	cout << "14. Remove a specific student from a course." << endl;
	cout << "15. Add a specific student to a course." << endl;
	cout << "16. View list of courses in the current semester." << endl;
	cout << "17. View list of students of a course." << endl;
	cout << "18. View attendance list of a course." << endl;
	cout << "19. Export an attendence list of a course to a csv file." << endl;
	cout << endl;
	cout << "20. Create lecturers." << endl;
	cout << "21. Delete a lecturer." << endl;
	cout << "22. View All lecturer" << endl;
	cout << endl;
	cout << "23. Search and view the scoreboard of a course." << endl;
	cout << "24. Export a scoreboard to a csv file." << endl;
	cout << endl;
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