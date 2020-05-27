#include"function.h"
#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define YELLOW  "\033[33m"      /* Yellow */

// Checking student 
void CheckingStu(LinkedListSemes lstSem, string id_user)
{
	time_t t = time(NULL);
	tm cur_time;
	localtime_s(&cur_time, &t);
	int day, month, year, hour, min;

	cout << BLUE << "Current time:" << cur_time.tm_mday << "-" << cur_time.tm_mon + 1 << "-" << cur_time.tm_year + 1900 << "  ";
	cout << cur_time.tm_hour << ":" << cur_time.tm_min << ":" << cur_time.tm_sec << RESET << endl;

	//search and load data course
	string idclass;
	Semester semester;

	int choice;
	choice = ChoiceCourseClass(lstSem, semester, idclass);
	if (choice == -1)
	{
		cout << "ERROR: please try later!!!" << endl;
		return;
	}
	nodeCourse* cur_course = semester.course.head;
	while (--choice)
	{
		if (choice == 0) break;
		cur_course = cur_course->next;
	}
	LoadStuCourseClass(semester, cur_course->data, idclass);

	nodePar* par_user = FindParticipant(cur_course->data.participant, id_user);
	nodeDat* cur_dat;
	cur_dat = CheckDay(par_user->dataPar, cur_course->data);
	if (cur_dat == NULL)
	{
		cout << RED << "FAILED: You're late" << RESET << endl;
		return;
	}
	cur_dat->dataDat.checking = 1;
	SaveStuCourse(semester, cur_course->data, idclass);
	cout << GREEN << "Check in successfully!!!!" << RESET << endl;
}

//find and check date of participant whether is current day
nodeDat* CheckDay(Participant& participant, Course course)
{
	time_t t = time(NULL);
	tm cur_time;
	localtime_s(&cur_time, &t);
	int day, month, year, hour, min;
	nodeDat* cur_dat = participant.timeCheck.head;
	int hour_start, min_start, hour_end, min_end;

	hour_start = atoi(course.hour_start.c_str());
	min_start = atoi(course.minute_start.c_str());
	hour_end = atoi(course.hour_end.c_str());
	min_end = atoi(course.minute_end.c_str());
	while (cur_dat != NULL)
	{
		day = atoi(cur_dat->dataDat.day.c_str());
		month = atoi(cur_dat->dataDat.month.c_str());
		year = atoi(cur_dat->dataDat.year.c_str());

		if (cur_time.tm_year + 1900 == year)
		{
			if (cur_time.tm_mon + 1 == month)
			{
				if (cur_time.tm_mday == day)
				{
					if (cur_time.tm_hour >= hour_start)
					{
						if (cur_time.tm_hour == hour_start && cur_time.tm_min < min_start)
							return NULL;
						if (cur_time.tm_hour <= hour_end)
						{
							if (cur_time.tm_hour == hour_end && cur_time.tm_min > min_end) return NULL;
							return cur_dat;
						}
					}

				}
			}
		}
		cur_dat = cur_dat->next;
	}
	return NULL;
}


//edit checking attendence
void EditAttendence(LinkedListSemes lstSem)
{
	//search and load data course
	string idclass;
	Semester semester;
	string id_par;

	int choice;
	choice = ChoiceCourseClass(lstSem, semester, idclass);
	if (choice == -1)
	{
		cout << "ERROR: please try later!!!" << endl;
		return;
	}
	nodeCourse* cur_course = semester.course.head;
	while (--choice)
	{
		if (choice == 0) break;
		cur_course = cur_course->next;
	}
	LoadStuCourseClass(semester, cur_course->data, idclass);


	cout << "Enter id of attendence:";
	cin.ignore();
	getline(cin, id_par);
	nodePar* attendence = FindParticipant(cur_course->data.participant, id_par);
	if (attendence == NULL)
	{
		cout << "ERROR: Not found attendence" << endl;
		return;
	}

	cout << setw(48) << BLUE << "(" << 1 << ")          " << RESET;
	for (int j = 1; j < 10; j++)
	{
		cout << setw(4) << BLUE << "(" << j + 1 << ")          " << RESET;
	}
	cout << endl;
	cout << setw(12) << "Student ID";
	cout << setw(15) << "Full name";
	cout << setw(10) << "Class";
	cout << "   ";
	nodeDat* cur_dat = attendence->dataPar.timeCheck.head;
	while (cur_dat != NULL)
	{
		cout << cur_dat->dataDat.day << "-" << cur_dat->dataDat.month << "-" << cur_dat->dataDat.year << "   ";
		cur_dat = cur_dat->next;
	}
	cout << endl;
	cout << "===========================================================================================================================================================================" << endl;
	cout << setw(10) << attendence->dataPar.id;
	cout << setw(20) << attendence->dataPar.fullname;
	cout << setw(8) << attendence->dataPar.classId;
	cur_dat = attendence->dataPar.timeCheck.head;
	while (cur_dat != NULL)
	{
		if (cur_dat->dataDat.checking == -1)
			cout << setw(9) << RED << "Absent" << RESET;
		else cout << setw(9) << GREEN << "Present" << RESET;
		cout << "   ";
		cur_dat = cur_dat->next;
	}
	cout << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	int check;
	choice = 0;
	do
	{
		int temp;
		check = choice;
		cout << "which date do you want to edit?" << RED << " (Press 0 to stop)" << RESET << endl;
		cout << "Your choice( from (1) to (10) ):";
		cin >> choice;
		temp = choice;
		if (choice < 0 || choice >10)
		{
			cout << RED << "ERROR: Please try again" << RESET << endl;
			continue;
		}

		cur_dat = attendence->dataPar.timeCheck.head;
		while (temp--)
		{
			if (temp == 0) break;
			cur_dat = cur_dat->next;
		}

		cout << "Enter new check in status (-1:absent/ 1:present):";
		cin >> cur_dat->dataDat.checking;
		if (cur_dat->dataDat.checking != -1 && cur_dat->dataDat.checking != 1)
		{
			cout << RED << "ERROR: Please try again" << RESET << endl;
		}
	} while (choice != 0);
	if (check == 0) return;

	SaveStuCourse(semester, cur_course->data, idclass);

	//view update
	cout << endl;
	cout << setw(12) << "Student ID";
	cout << setw(15) << "Full name";
	cout << setw(10) << "Class";
	cout << "   ";
	cur_dat = attendence->dataPar.timeCheck.head;
	while (cur_dat != NULL)
	{
		cout << cur_dat->dataDat.day << "-" << cur_dat->dataDat.month << "-" << cur_dat->dataDat.year << "   ";
		cur_dat = cur_dat->next;
	}
	cout << endl;
	cout << "===========================================================================================================================================================================" << endl;
	cout << setw(10) << attendence->dataPar.id;
	cout << setw(20) << attendence->dataPar.fullname;
	cout << setw(8) << attendence->dataPar.classId;
	cur_dat = attendence->dataPar.timeCheck.head;
	while (cur_dat != NULL)
	{
		if (cur_dat->dataDat.checking == -1)
			cout << setw(9) << RED << "Absent" << RESET;
		else cout << setw(9) << GREEN << "Present" << RESET;
		cout << "   ";
		cur_dat = cur_dat->next;
	}
	cout << endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

	cout << GREEN << "Successfully" << RESET << endl;
}

//edit grade student
void EditGradeStu(LinkedListSemes lstSem)
{
	//search and load data course
	string idclass;
	Semester semester;
	string id_par;

	int choice;
	choice = ChoiceCourseClass(lstSem, semester, idclass);
	if (choice == -1)
	{
		cout << "ERROR: please try later!!!" << endl;
		return;
	}
	nodeCourse* cur_course = semester.course.head;
	while (--choice)
	{
		if (choice == 0) break;
		cur_course = cur_course->next;
	}
	LoadStuCourseClass(semester, cur_course->data, idclass);


	cout << "Enter id of attendence:";
	cin.ignore();
	getline(cin, id_par);
	nodePar* attendence = FindParticipant(cur_course->data.participant, id_par);
	if (attendence == NULL)
	{
		cout << "ERROR: Not found attendence" << endl;
		return;
	}


	cout << setw(63) << BLUE << "(" << 1 << ")  " << RESET;
	for (int j = 1; j < 4; j++)
	{
		cout << setw(4) << BLUE << "(" << j + 1 << ")   " << RESET;
	}
	cout << endl;
	cout << setw(10) << "  ID student";
	cout << setw(15) << "Full name";
	cout << setw(14) << "ID Class";
	cout << setw(15) << "Study status";
	cout << setw(6) << "Mid ";
	cout << setw(5) << "Final ";
	cout << setw(5) << "Bonus ";
	cout << setw(5) << "Total ";
	cout << setw(15) << "Course status" << endl;
	cout << "===================================================================================================" << endl;
	cout << setw(11) << attendence->dataPar.id;
	cout << setw(20) << attendence->dataPar.fullname;
	cout << setw(9) << attendence->dataPar.classId;
	if (attendence->dataPar.status == 1) cout << setw(12) << GREEN << "ACTIVE" << RESET;
	else cout << setw(12) << RED << "DROPPED" << RESET;
	if (attendence->dataPar.mid == -1) cout << setw(11) << RED << "-" << RESET;
	else cout << setw(8) << attendence->dataPar.mid;

	if (attendence->dataPar.final == -1) cout << setw(9) << RED << "-" << RESET;
	else cout << setw(5) << attendence->dataPar.final;

	if (attendence->dataPar.bonus == -1) cout << setw(10) << RED << "-" << RESET;
	else cout << setw(6) << attendence->dataPar.bonus;

	if (attendence->dataPar.total == -1) cout << setw(10) << RED << "-" << RESET;
	else cout << setw(5) << attendence->dataPar.total;

	if (attendence->dataPar.status_course == 1) cout << setw(12) << GREEN << " ACTIVE" << RESET << endl;
	else cout << setw(12) << RED << " DROPPED" << RESET << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	choice = 0;
	int check;
	do
	{
		check = choice;
		cout << "which grade do you want to edit??" << RED << " (Press 0 to stop)" << RESET << endl;
		cout << "Your choice:";
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter new mid grade:";
			cin >> attendence->dataPar.mid;
		}
		else if (choice == 2)
		{
			cout << "Enter new final grade:";
			cin >> attendence->dataPar.final;
		}
		else if (choice == 3)
		{
			cout << "Enter new bonus grade:";
			cin >> attendence->dataPar.bonus;
		}
		else if (choice == 4)
		{
			cout << "Enter new mid grade:";
			cin >> attendence->dataPar.total;
		}
		else if (choice != 0)
		{
			cout << RED << "ERROR: Please try again" << RESET << endl;
		}
	} while (choice != 0);

	if (check == 0) return;
	//view update
	cout << setw(10) << "  ID student";
	cout << setw(15) << "Full name";
	cout << setw(14) << "ID Class";
	cout << setw(15) << "Study status";
	cout << setw(6) << "Mid ";
	cout << setw(5) << "Final ";
	cout << setw(5) << "Bonus ";
	cout << setw(5) << "Total ";
	cout << setw(15) << "Course status" << endl;
	cout << "===================================================================================================" << endl;
	cout << setw(11) << attendence->dataPar.id;
	cout << setw(20) << attendence->dataPar.fullname;
	cout << setw(9) << attendence->dataPar.classId;
	if (attendence->dataPar.status == 1) cout << setw(12) << GREEN << "ACTIVE" << RESET;
	else cout << setw(12) << RED << "DROPPED" << RESET;
	if (attendence->dataPar.mid == -1) cout << setw(11) << RED << "-" << RESET;
	else cout << setw(8) << attendence->dataPar.mid;

	if (attendence->dataPar.final == -1) cout << setw(9) << RED << "-" << RESET;
	else cout << setw(5) << attendence->dataPar.final;

	if (attendence->dataPar.bonus == -1) cout << setw(10) << RED << "-" << RESET;
	else cout << setw(6) << attendence->dataPar.bonus;

	if (attendence->dataPar.total == -1) cout << setw(10) << RED << "-" << RESET;
	else cout << setw(5) << attendence->dataPar.total;

	if (attendence->dataPar.status_course == 1) cout << setw(12) << GREEN << " ACTIVE" << RESET << endl;
	else cout << setw(12) << RED << " DROPPED" << RESET << endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;

	//save update
	SaveStuCourse(semester, cur_course->data, idclass);
	cout << GREEN << "Successfully" << RESET << endl;
}