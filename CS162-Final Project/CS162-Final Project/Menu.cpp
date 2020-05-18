#include"function.h"
#include"Menu.h"

void Main_menu()
{  
	cout << "2.login" << endl;
	cout << "3. View profile info" << endl;
	cout << "4. Change password" << endl;
	cout << "5. Logout" << endl;
}
void ShowMenu_Staff()
{
	cout << "6. Import students of a class such as 18CLC6 from a csv file." << endl;
	cout << "7. Manually add a new student to a class." << endl;
	cout << "8. Edit an existing student." << endl;
	cout << "9. Remove a Student." << endl;
	cout << "10. Change students from class A to class B" << endl;
	cout << "11. View list of classes." << endl;
	cout << "12. View list of students in a class." << endl;
	cout << "13. Create / update / delete / view academic years, and semesters."<<endl;
	cout << "14. From a semester, import courses" << endl;
	cout << "16. Edit an existing course." << endl;
	cout << "17. Remove a course." << endl;
	cout << "18. Remove a specific student from a course." << endl;
	cout << "19. Add a specific student to a course." << endl;
	cout << "20. View list of courses in the current semester." << endl;
	cout << "21. View list of students of a course." << endl;
	cout << "22. View attendance list of a course." << endl;
	cout << "23. Create / update / delete / view all lecturers." << endl;
	cout << "24. Search and view the scoreboard of a course." << endl;
	cout << "25. Export a scoreboard to a csv file." << endl;
}
void ShowMenu_Lecturer()
{
	cout << "28. View list of courses in the current semester." << endl;
	cout << "29. View list of students of a course." << endl;
	cout << "30. View attendance list of a course." << endl;
		cout << "31. Edit an attendance." << endl;
		cout << "32. Import scoreboard of a course(midterm, final, lab, bonus) from a csv file." << endl;
		cout << "33. Edit grade of a student" << endl;
		cout << "34. View a scoreboard" << endl;
}
