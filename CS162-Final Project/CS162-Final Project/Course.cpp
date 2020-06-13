#include"function.h"

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
		cout << RED << "FAILED: You're late or You checked in too early" << RESET << endl;
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
void EditAttendence(LinkedListSemes lstSem, string idLec)
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
	if (idLec != "")
	{
		bool check1;
		check1 = CheckLecCourse(semester, cur_course->data.id, idclass, idLec);
		if (check1 == 0)
			return;
	}

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
	ViewAAtendence(attendence);
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
		if (choice == 0)
		{
			break;
		}

		nodeDat* cur_dat = attendence->dataPar.timeCheck.head;
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
	ViewAAtendence(attendence);

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

	ViewAScore(attendence);

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
	ViewAScore(attendence);

	//save update
	SaveStuCourse(semester, cur_course->data, idclass);
	cout << GREEN << "Successfully" << RESET << endl;
}

// view score of a student
void ViewAScore(nodePar* attendence)
{
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
}

//view check in of a student
void ViewAAtendence(nodePar* attendence)
{
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
}

//for student view his score
void ViewMyScore(LinkedListSemes lst, string id)
{
	//search and load data course
	string idclass;
	Semester semester;

	int choice;
	choice = ChoiceCourseClass(lst, semester, idclass);
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

	nodePar* attendence = FindParticipant(cur_course->data.participant, id);
	if (attendence == NULL)
	{
		cout << RED << "FAILED: you are not in this course!!!" << RESET << endl;
		return;
	}

	cout << GREEN << ">>>>>> " << cur_course->data.name << " (" << cur_course->data.id << ")" << RESET << endl;
	ViewAScore(attendence);
}

//for student view his attendence
void ViewMyAttendence(LinkedListSemes lst, string id)
{
	//search and load data course
	string idclass;
	Semester semester;

	int choice;
	choice = ChoiceCourseClass(lst, semester, idclass);
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

	nodePar* attendence = FindParticipant(cur_course->data.participant, id);
	if (attendence == NULL)
	{
		cout << RED << "FAILED: you are not in this course!!!" << RESET << endl;
		return;
	}

	cout << GREEN << ">>>>>> " << cur_course->data.name << " (" << cur_course->data.id << ")" << RESET << endl;
	ViewAAtendence(attendence);
}

//for student view his schedule
void ViewMySchedule(LinkedListSemes lst, string id)
{
	Semester semester;
	LinkedListCourse lstC;
	string namefile;
	int count = 0;

	int choice;
	cout << "Enter years(ex: 2019 2020....):";
	cin >> semester.yearBeg >> semester.yearEnd;
	cout << "Enter semester:";
	cin.ignore();
	getline(cin, semester.name);
	if (FindSemester(lst, semester.name, semester.yearBeg, semester.yearEnd) == NULL)
	{
		cout << "Not found Semester" << endl;
		return;
	}

	LoadCourseSemes(semester, lstC);
	nodeCourse* cur = lstC.head;

	cout << YELLOW << "****Your Schedule in " << semester.name << " (" << semester.yearBeg << "-" << semester.yearEnd << ")****" << RESET << endl;
	cout << "No.";
	cout << setw(36) << " |Course|            ";
	cout << setw(13) << "|ID Class|";
	cout << setw(25) << "|Date|       ";
	cout << setw(8) << "|Room|";
	cout << endl;
	cout << "======================================================================================" << endl;
	while (cur != NULL)
	{
		Semester temp_semes;
		temp_semes.name = semester.name;
		temp_semes.yearBeg = semester.yearBeg;
		temp_semes.yearEnd = semester.yearEnd;
		LoadStuCourseClass(semester, cur->data, cur->data.classId);
		nodePar* participant = FindParticipant(cur->data.participant, id);
		if (participant == NULL)
		{
			cur = cur->next;
			continue;
		}
		LoadDataCourseClass(temp_semes, cur->data.classId);
		nodeCourse* course = FindCourse(temp_semes.course, cur->data.id);
		if (course == NULL)
		{
			cout << "ERROR: Has problem with file data_course_class " << endl;
			return;
		}

		cout << setw(2) << count + 1 << " ";
		cout << GREEN << setw(30) << course->data.name << " (" << course->data.id << ")" << RESET;
		cout << setw(8) << course->data.classId;
		if (course->data.firstday == 1) cout << setw(14) << "Sunday";
		else if (course->data.firstday == 2) cout << setw(14) << "Monday";
		else if (course->data.firstday == 3) cout << setw(14) << "Tuesday";
		else if (course->data.firstday == 4) cout << setw(14) << "Wednesday";
		else if (course->data.firstday == 5) cout << setw(14) << "Thursday";
		else if (course->data.firstday == 6) cout << setw(14) << "Friday";
		else if (course->data.firstday == 7) cout << setw(14) << "Saturday";
		cout << " (" << course->data.hour_start << ":" << course->data.minute_start << " - " << course->data.hour_end << ":" << course->data.minute_end << ")";
		cout << setw(6) << course->data.room << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		count++;
		cur = cur->next;
	}

	if (count == 0)
		cout << RED << "Not available!!!" << RESET << endl;
}


//find course in a class
nodeCourse* FindCourse(LinkedListCourse lst, string id)
{
	nodeCourse* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->data.id == id)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

void ImportScoreBoard(LinkedListSemes lst, string idLec)
{
	//search and load data course
	string idclass;
	Semester semester;
	string pathfile;
	bool check;
	int fail = 0, success = 0;

	int choice;
	choice = ChoiceCourseClass(lst, semester, idclass);
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
	if (idLec != "")
	{
		bool check1;
		check1 = CheckLecCourse(semester, cur_course->data.id, idclass, idLec);
		if (check1 == 0)
			return;
	}
	check = LoadStuCourseClass(semester, cur_course->data, idclass);
	if (check == 0) return;

	//open file and update score
	ifstream fi;
	cout << "Enter the local path to your score .csv file: ";
	cin.ignore();
	getline(cin, pathfile);
	fi.open(pathfile.c_str());
	fi.ignore(256, '\n');
	while (!fi.eof())
	{
		Participant par;
		fi.ignore(2);
		getline(fi, par.id, ',');
		getline(fi, par.fullname, ',');
		fi >> par.mid;
		fi.ignore();
		fi >> par.final;
		fi.ignore();
		fi >> par.bonus;
		fi.ignore();
		fi >> par.total;
		fi.ignore();
		if (fi.eof()) break;
		nodePar* par_exist = FindParticipant(cur_course->data.participant, par.id);
		if (par_exist == NULL)
		{
			fail++;
			continue;
		}
		par_exist->dataPar.mid = par.mid;
		par_exist->dataPar.final = par.final;
		par_exist->dataPar.bonus = par.bonus;
		par_exist->dataPar.total = par.total;
		success++;
	}
	fi.close();
	cout << YELLOW << "***Import: " << GREEN << success << " success, " << RED << fail << " fail" << RESET << endl;
	SaveStuCourse(semester, cur_course->data, idclass);
}