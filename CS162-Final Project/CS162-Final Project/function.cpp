#include"function.h"

#define RESET   "\033[0m"
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

// Login
bool Login(User& user, LinkedListSta lstSta, LinkedListStu lstStu, LinkedListLec lstLec, int& level)
{
	cout << "-------------LOGIN-------------" << endl;
	cout << "Id: ";
	cin >> user.id;
	cout << "Password: ";
	int buffer;
	do
	{
		buffer = _getch();
		cout << "*";
		if(buffer != 13)
		{
			user.password += char(buffer);
		}
		
	} while (buffer != 13);
	cout << endl;
	nodeSta* curSta = lstSta.head;
	nodeStu* curStu = lstStu.head;
	nodeLec* curLec = lstLec.head;
	while (curSta != NULL)
		{
			if (curSta->dataStaf.id == user.id && curSta->dataStaf.password == user.password)
			{
				level = 2;
				user.name = curSta->dataStaf.fullname;
				user.sex = curSta->dataStaf.sex;
				Changecolor(4);
				cout << "SUCCESSFUL!!!!" << endl;
				Sleep(1000);
				Changecolor(15);
				LoadingEffect();
				return true;
			}
			curSta = curSta->next;
		}
	
		while (curStu != NULL)
		{
			if (curStu->dataStud.id == user.id && curStu->dataStud.password == user.password)
			{
				level = 0;
				user.name = curStu->dataStud.fullname;
				user.sex = curStu->dataStud.sex;
				Changecolor(4);
				cout << "SUCCESSFUL!!!!" << endl;
				Sleep(1000);
				Changecolor(15);
				LoadingEffect();
				return true;
			}
			curStu = curStu->next;
		}
	
		while (curLec != NULL)
		{
			if (curLec->dataLec.id == user.id && curLec->dataLec.password == user.password)
			{
				level = 1;
				user.name = curLec->dataLec.name;
				user.sex = curLec->dataLec.sex;
				Changecolor(4);
				cout << "SUCCESSFUL!!!!" << endl;
				Sleep(1000);
				Changecolor(15);
				LoadingEffect();
				return true;
			}
			curLec = curLec->next;
		}
	
	system("cls");
	cout << "Invalid login, please try again" << endl;
	return false;
}

//load-save semester
bool LoadSemester(LinkedListSemes& lst)
{
	ifstream fi("Semester.txt");
	Semester item;
	if (!fi.is_open())
	{
		cout << "not found data of semester." << endl;
		return 0;
	}
	else
	{
		fi >> lst.numSemes;
		for (int i = 0; i < lst.numSemes; i++)
		{
			fi >> item.yearBeg >> item.yearEnd;
			fi.ignore();
			getline(fi, item.name);
			PushNodeSemester(lst.head, item);
		}
	}
	fi.close();
	return 1;
}

bool SaveSemester(LinkedListSemes lst)
{
	ofstream fo("Semester.txt");
	nodeSemes* cur = lst.head;
	fo << lst.numSemes << endl;
	for (int i = 0; i < lst.numSemes && cur != NULL; i++)
	{
		fo << cur->data.yearBeg << " " << cur->data.yearEnd << endl;
		fo << cur->data.name << endl;
		cur = cur->next;
	}
	fo.close();
	return 1;

}


//Create linkedlist of participant
void PushNodeParticipant(nodePar*& head, Participant new_data) {
	nodePar* new_node = new nodePar();
	new_node->dataPar = new_data;
	new_node->next = head;
	head = new_node;
}
//Create linkedlist of semester
void PushNodeSemester(nodeSemes*& head, Semester new_data) {
	nodeSemes* new_node = new nodeSemes();
	new_node->data = new_data;
	new_node->next = head;
	head = new_node;
}
//Create linkedlist of course
void PushNodeCourse(nodeCourse*& head, Course new_data) {
	nodeCourse* new_node = new nodeCourse();
	new_node->data = new_data;
	new_node->next = head;
	head = new_node;
}
//deleteNodeCourse
void DeleteNodeCourse(nodeCourse*& head, string idCourse)
{
	nodeCourse* temp = head;
	nodeCourse* prev = NULL;

	if (temp != NULL && temp->data.id == idCourse)
	{
		head = temp->next;
		delete temp;
		return;
	}
	while (temp != NULL && temp->data.id != idCourse)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return;
	else prev->next = temp->next;

	delete temp;
}

//create semester
void CreateSemester(LinkedListSemes& lst)
{
	Semester new_data;
	cout << "Enter years(ex:2019 2020...):";
	cin >> new_data.yearBeg >> new_data.yearEnd;
	cout << "Semester:";
	cin >> new_data.name;
	lst.numSemes++;
	PushNodeSemester(lst.head, new_data);
}

//import course
void ImportCourse(LinkedListSemes& lstSem, LinkedListLec& lstLec)
{
	Semester semester;
	Course course;
	string idclass, pathfile;
	ifstream fi;
	nodeSemes* cur;
	LinkedListCourse lstCourse;//to update courses to "courses of a specific semester" file
	cout << "Enter academic years(ex: 2019 2020):";
	cin >> semester.yearBeg >> semester.yearEnd;
	cout << "Enter semester:";
	cin >> semester.name;
	cur = FindSemester(lstSem, semester.name, semester.yearBeg, semester.yearEnd);
	if (cur != NULL)
	{
		LoadCourseSemes(semester, lstCourse);//load data to push new node linked list course semester

		cout << "Enter class:";
		cin >> idclass;
		if (!FileClass_Exist(idclass))
		{
			cout << "FAILED: NOT FOUND DATA OF CLASS " << idclass << endl;
			return;
		}
		LoadDataCourseClass(semester, idclass);//load data to push new node linked list course of a class
		cout << "Enter file csv:";
		cin.ignore();
		getline(cin, pathfile);
		fi.open(pathfile.c_str());
		if (!fi.is_open())
		{
			cout << "FAILED: can't open file" << endl;
			return;
		}
		else
		{
			fi.ignore(256, '\n');
			while (!fi.eof())
			{
				fi.ignore(2);
				getline(fi, course.id, ',');
				getline(fi, course.name, ',');
				getline(fi, course.classId, ',');
				getline(fi, course.lec.id, ',');
				getline(fi, course.lec.name, ',');
				getline(fi, course.lec.degree, ',');
				fi >> course.lec.sex;
				if (FindLecturer(lstLec, course.lec.id) == NULL)
				{
					course.lec.password = course.lec.id;
					lstLec.numLec++;
					PushNodeLecturer(lstLec.head, course.lec);
				}
				fi.ignore();
				getline(fi, course.day_start, '/');
				getline(fi, course.month_start, '/');
				getline(fi, course.year_start, ',');
				getline(fi, course.day_end, '/');
				getline(fi, course.month_end, '/');
				getline(fi, course.year_end, ',');
				fi >> course.firstday;
				fi.ignore();
				getline(fi, course.hour_start, ',');
				getline(fi, course.minute_start, ',');
				getline(fi, course.hour_end, ',');
				getline(fi, course.minute_end, ',');
				getline(fi, course.room, '\n');
				if (fi.eof()) break;
				ScheduleCourse(course);
				bool check;
				check = EnrollStuClassToCourse(idclass, semester, course);
				if (check == false)
				{
					cout << "Failed!!!" << endl;
					return;
				}
				semester.course.numCourse++;//update number of courses of class
				lstCourse.numCourse++;// update number of courses of class
				PushNodeCourse(semester.course.head, course);// push node to linked list course of class
				PushNodeCourse(lstCourse.head, course);// push node to linked list course of semester
			}
			SaveFileCourseClass(semester, idclass);// save linked list course of class
			SaveCourseSemes(semester, lstCourse);//save linked list course of semester
			fi.close();
			cout << "Successful!!!" << endl;
		}
	}
	else
	{
		cout << "not found this semester!!!" << endl;
		return;
	}
}

//Save courses of a class in a semester
bool SaveFileCourseClass(Semester data, string idclass)
{
	ofstream fo;
	string namefile;
	namefile = data.yearBeg + "-" + data.yearEnd + "-" + data.name + "-" + idclass + "-Courses.txt";
	fo.open(namefile.c_str());
	if (!fo.is_open())
	{
		cout << "Can't create file save" << endl;
		return 0;
	}
	else
	{
		nodeCourse* cur = data.course.head;
		fo << data.course.numCourse << endl;
		while (cur != NULL)
		{
			fo << cur->data.id << endl;
			fo << cur->data.name << endl;
			fo << cur->data.classId << endl;
			fo << cur->data.lec.id << endl;
			fo << cur->data.lec.name << endl;
			fo << cur->data.lec.degree << endl;
			fo << cur->data.lec.sex << endl;
			fo << cur->data.year_start << " " << cur->data.month_start << " " << cur->data.day_start << endl;
			fo << cur->data.year_end << " " << cur->data.month_end << " " << cur->data.day_end << endl;
			fo << cur->data.firstday << endl;
			fo << cur->data.hour_start << " " << cur->data.minute_start << endl;
			fo << cur->data.hour_end << " " << cur->data.minute_end << endl;
			fo << cur->data.room << endl;
			cur = cur->next;
		}
		fo.close();
	}
	return 1;
}
//check existance of semester
nodeSemes* FindSemester(LinkedListSemes lst, string name, string yearbeg, string yearend)
{
	nodeSemes* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->data.name == name && cur->data.yearBeg == yearbeg && cur->data.yearEnd == yearend)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

// enroll all students of a class to imported course
bool EnrollStuClassToCourse(string idclass, Semester semester, Course course)
{
	Class cla;
	ofstream fo;
	string namefile_course;
	namefile_course = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-" + idclass + "-" + course.id + "-Students.txt";
	fo.open(namefile_course.c_str());
	cla.classID = idclass;

	if (!fo.is_open() && LoadDataStudentFromClassFile(cla) == false)
	{
		cout << "FAILED: has problem with saving file or 'Students class' file!!" << endl;
		return 0;
	}
	else
	{
		LoadDataStudentFromClassFile(cla);
		fo << cla.stu.NumStu << endl;
		nodeStu* cur = cla.stu.head;
		while (cur != NULL)
		{
			fo << cur->dataStud.id << endl;
			fo << cur->dataStud.fullname << endl;
			fo << cur->dataStud.year << " " << cur->dataStud.month << " " << cur->dataStud.day << endl;
			fo << cur->dataStud.classId << endl;
			fo << cur->dataStud.status << endl;
			fo << -1 << endl;//midterm
			fo << -1 << endl;//final
			fo << -1 << endl;//bonus
			fo << -1 << endl;//total
			nodeSche* cur_course = course.schedule.head;
			while (cur_course != NULL)
			{
				fo << cur_course->data.year << " " << cur_course->data.month << " " << cur_course->data.day << " " << -1 << endl;
				cur_course = cur_course->next;
			}
			if (cur->dataStud.status == 0)// status of a student in university
			{
				fo << 0 << endl;// status of a student in course
			}
			else
			{
				fo << 1 << endl;
			}
			cur = cur->next;
		}
		fo.close();
	}
}


//Schedule
nodeSche* CreatNodeShe(Schedule data)
{
	nodeSche* p = new nodeSche;
	p->data = data;
	p->next = NULL;
	return p;
}

void defineDate(int month, int year, int& daymax)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		daymax = 31;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		daymax = 30;
	}
	else
	{
		if (year % 4 == 0)
		{
			daymax = 29;
		}
		else
		{
			daymax = 28;
		}
	}
}

int dayofweek(int d, int m, int y)
{
	static int t[] = { 0, 3, 2, 5, 0, 3,
					   5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y / 4 - y / 100 +
		y / 400 + t[m - 1] + d) % 7 + 1;
}

void AnalysisDate(Schedule start, Schedule end, LinkedListSche& lst, int firstday)
{
	int day, month, year, daymax;
	int day_end, month_end, year_end;
	int temp;
	Schedule data;

	day = atoi(start.day.c_str());
	month = atoi(start.month.c_str());
	year = atoi(start.year.c_str());
	defineDate(month, year, daymax);

	day_end = atoi(end.day.c_str());
	month_end = atoi(end.month.c_str());
	year_end = atoi(end.year.c_str());
	temp = dayofweek(day, month, year);
	while (temp != firstday)
	{

		day++;
		defineDate(month, year, daymax);
		if (day > daymax)
		{
			day = day - daymax;
			month++;
			defineDate(month, year, daymax);
		}
		if (month > 12)
		{
			month = 1;
			year++;
			defineDate(month, year, daymax);
		}
		temp = dayofweek(day, month, year);
	}
	if (day < 10)data.day = '0' + to_string(day);
	else data.day = to_string(day);
	if (month < 10)data.month = '0' + to_string(month);
	else data.month = to_string(month);
	data.year = to_string(year);
	lst.head = CreatNodeShe(data);
	nodeSche* cur = lst.head;
	for (int i = 0; i < 9; i++)
	{
		day = day + 7;
		if (day > daymax)
		{
			day = day - daymax;
			month++;
			defineDate(month, year, daymax);
		}
		if (month > 12)
		{
			month = 1;
			year++;
			defineDate(month, year, daymax);
		}
		if (day < 10)data.day = '0' + to_string(day);
		else data.day = to_string(day);
		if (month < 10)data.month = '0' + to_string(month);
		else data.month = to_string(month);
		data.year = to_string(year);
		cur->next = CreatNodeShe(data);
		cur = cur->next;
	}

}

void ScheduleCourse(Course& course)
{
	Schedule start;
	Schedule end;
	start.day = course.day_start;
	start.month = course.month_start;
	start.year = course.year_start;

	end.day = course.day_end;
	end.month = course.month_end;
	end.year = course.year_end;

	AnalysisDate(start, end, course.schedule, course.firstday);
}

//Load courses of a class in a semester
bool LoadDataCourseClass(Semester& semester, string idclass)
{
	ifstream fi;
	string pathfile;
	Course course;
	pathfile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-" + idclass + "-Courses.txt";
	fi.open(pathfile.c_str());
	if (!fi.is_open()) return 0;
	fi >> semester.course.numCourse;
	fi.ignore();
	for (int i = 0; i < semester.course.numCourse; i++)
	{
		getline(fi, course.id);
		getline(fi, course.name);
		getline(fi, course.classId);
		getline(fi, course.lec.id);
		getline(fi, course.lec.name);
		getline(fi, course.lec.degree);
		fi >> course.lec.sex;
		fi >> course.year_start >> course.month_start >> course.day_start;
		fi >> course.year_end >> course.month_end >> course.day_end;
		fi >> course.firstday;
		fi >> course.hour_start >> course.minute_start;
		fi >> course.hour_end >> course.minute_end;
		fi.ignore();
		getline(fi, course.room);
		PushNodeCourse(semester.course.head, course);
	}
	fi.close();
	return 1;
}

//Create Date
nodeDat* CreateNodeDate(Date data)
{
	nodeDat* p = new nodeDat;
	p->dataDat = data;
	p->next = NULL;
	return p;
}

// load student in a course of a semester

bool LoadStuCourseClass(Semester semester, Course& course, string idclass)
{
	ifstream fi;
	string pathfile;
	Participant participant;
	Date date;
	pathfile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-" + idclass + "-" + course.id + "-Students.txt";
	fi.open(pathfile.c_str());
	if (!fi.is_open()) return 0;
	fi >> course.participant.numPar;
	for (int i = 0; i < course.participant.numPar; i++)
	{
		fi.ignore();
		getline(fi, participant.id);
		getline(fi, participant.fullname);
		fi >> participant.year >> participant.month >> participant.day;
		fi.ignore();
		getline(fi, participant.classId);
		fi >> participant.status;//status in university
		fi >> participant.mid;
		fi >> participant.final;
		fi >> participant.bonus;
		fi >> participant.total;
		fi >> date.year >> date.month >> date.day >> date.checking;
		participant.timeCheck.head = CreateNodeDate(date);
		nodeDat* cur = participant.timeCheck.head;
		for (int i = 0; i < 9; i++)
		{
			fi >> date.year >> date.month >> date.day >> date.checking;
			cur->next = CreateNodeDate(date);
			cur = cur->next;
		}
		fi >> participant.status_course;
		PushNodeParticipant(course.participant.head, participant);
	}
	fi.close();
	return 1;
}

//Menu choice semester
int ChoiceCourseClass(LinkedListSemes lst, Semester& semester, string& idclass)
{
	int choice;
	cout << "Enter years(ex: 2019 2020....):";
	cin >> semester.yearBeg >> semester.yearEnd;
	cout << "Enter semester:";
	cin.ignore();
	getline(cin, semester.name);
	if (FindSemester(lst, semester.name, semester.yearBeg, semester.yearEnd) == NULL)
	{
		cout << "Not found Semester" << endl;
		return -1;

	}
	cout << "Enter Class:";
	getline(cin, idclass);
	if (FileClass_Exist(idclass) == false)
	{
		cout << "not found data of class" << endl;
		return -1;
	}
	PrintListCourseOfClass(semester, idclass);
	cout << "Enter your choice:";
	cin >> choice;
	if (choice <= 0 || choice > semester.course.numCourse)
	{
		cout << "ERROR: please try later" << endl;
		return -1;
	}
	return choice;
}

//view courses of class
void PrintListCourseOfClass(Semester& semester, string idclass)
{
	LoadDataCourseClass(semester, idclass);
	cout << "Semester " << semester.name << "(" << semester.yearBeg << "-" << semester.yearEnd << ")" << endl;
	nodeCourse* cur = semester.course.head;
	for (int i = 0; i < semester.course.numCourse; i++)
	{
		cout << i + 1 << ". " << cur->data.name << " (" << cur->data.id << ")" << endl;
		cur = cur->next;
	}
}

// view students of a course in a class
void ViewStuCourseClass(LinkedListSemes lst)
{
	string idclass;
	Semester semester;
	int choice;
	choice = ChoiceCourseClass(lst, semester, idclass);
	if (choice == -1)
	{
		cout << "ERROR: please try later!!!" << endl;
		return;
	}
	nodeCourse* cur = semester.course.head;
	while (--choice)
	{
		if (cur <= 0) break;
		cur = cur->next;
	}
	LoadStuCourseClass(semester, cur->data, idclass);
	nodePar* cur_par = cur->data.participant.head;
	cout << BOLDGREEN << ">>>>>" << cur->data.name << " (" << cur->data.id << ")" << RESET << endl;
	cout << "No. |";
	cout << setw(20) << "Full name |";
	cout << setw(10) << "Class |";
	cout << setw(10) << "Course status |" << endl;
	cout << "==================================================" << endl;
	for (int i = 0; i < cur->data.participant.numPar; i++)
	{
		cout << setw(3) << i + 1;
		cout << setw(20) << cur_par->dataPar.fullname;
		cout << setw(10) << cur_par->dataPar.classId;
		if (cur_par->dataPar.status_course == 1 && cur_par->dataPar.status == 1)
			cout << setw(10) << GREEN << "Active" << RESET << endl;
		else cout << setw(10) << RED << "Dropped" << RESET << endl;
		cout << "--------------------------------------------------" << endl;
		cur_par = cur_par->next;
	}

}

//Add a new course
void AddACourse(LinkedListSemes lstSemes, LinkedListLec& lstLec)
{
	Semester semester;
	Course course;
	string idclass;
	LinkedListCourse lstCourse;// to push node to "courses of a specific semester" file
	int choice;
	cout << "Enter years(ex:2019 2020,...)";
	cin >> semester.yearBeg >> semester.yearEnd;
	cout << "Enter semester:";
	cin.ignore();
	getline(cin, semester.name);
	nodeSemes* check = FindSemester(lstSemes, semester.name, semester.yearBeg, semester.yearEnd);
	if (check == NULL)
	{
		cout << "ERROR: not found data of semester" << endl;
		return;
	}
	LoadCourseSemes(semester, lstCourse);//load linked list to push node <file course semester>
	cout << "Enter class:";
	cin >> idclass;
	cout << "There are courses of class " << idclass << " in " << semester.name << "(" << semester.yearBeg << "-" << semester.yearEnd << ") semester" << endl;
	PrintListCourseOfClass(semester, idclass);
	cout << "Do you want to add a new course?[Yes(1)/No(0)]" << endl;
	cout << "Your choice: ";
	cin >> choice;
	if (choice == 0) return;
	cout << "Enter id of new course:";
	cin.ignore();
	getline(cin, course.id);
	cout << "Enter name of new course:";
	getline(cin, course.name);
	course.classId = idclass;
	cout << "Enter id of the lecturer in this course: ";
	getline(cin, course.lec.id);
	nodeLec* lecturer = FindLecturer(lstLec, course.lec.id);

	if (lecturer == NULL)
	{
		course.lec.password = course.lec.id;
		cout << "Enter full name of lecturer:";
		getline(cin, course.lec.name);
		cout << "Enter degree of lecturer:";
		getline(cin, course.lec.degree);
		cout << "Enter gender of lecturer(0:male/1:female):";
		cin >> course.lec.sex;
		lstLec.numLec++;
		PushNodeLecturer(lstLec.head, course.lec);
	}
	else
	{
		course.lec = lecturer->dataLec;
	}
	cout << "Enter start date(ex 2020 06 01...):";
	cin >> course.year_start >> course.month_start >> course.day_start;
	cout << "Enter end date(ex 2020 06 01...):";
	cin >> course.year_end >> course.month_end >> course.day_end;
	cout << "Enter day of week:";
	cin >> course.firstday;
	cout << "Enter start time(ex: 7 30...)";
	cin >> course.hour_start >> course.minute_start;
	cout << "Enter end time(ex: 7 30...)";
	cin >> course.hour_end >> course.minute_end;
	cout << "Enter room:";
	cin.ignore();
	getline(cin, course.room);

	// update data
	semester.course.numCourse++;// update number linked list course class
	lstCourse.numCourse++;//update number linked list course semester
	ScheduleCourse(course);
	PushNodeCourse(lstCourse.head, course);// add new data <semester>
	PushNodeCourse(semester.course.head, course);//add new data <class>
	EnrollStuClassToCourse(idclass, semester, course);
	SaveFileCourseClass(semester, idclass);// save file class
	SaveCourseSemes(semester, lstCourse);// save file semester
	cout << "Successful!!!" << endl;
}

//load all courses in a specific semester
bool LoadCourseSemes(Semester semester, LinkedListCourse& lstCourse)
{
	ifstream fi;
	string pathfile;
	Course course;
	pathfile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-Courses.txt";
	fi.open(pathfile.c_str());
	if (!fi.is_open())
	{
		//cout << "ERROR: please try later." << endl;
		return 0;
	}
	fi >> lstCourse.numCourse;
	fi.ignore();
	for (int i = 0; i < lstCourse.numCourse; i++)
	{
		getline(fi, course.id);
		getline(fi, course.name);
		getline(fi, course.classId);
		PushNodeCourse(lstCourse.head, course);
	}
	fi.close();
	return 1;
}

// save all courses in a specific semester
bool SaveCourseSemes(Semester semester, LinkedListCourse lstCourse)
{
	ofstream fo;
	string pathfile;
	pathfile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-Courses.txt";
	fo.open(pathfile.c_str());
	if (!fo.is_open())
	{
		cout << "Can't create file save" << endl;
		return 0;
	}
	nodeCourse* cur = lstCourse.head;
	fo << lstCourse.numCourse << endl;
	while (cur != NULL)
	{
		fo << cur->data.id << endl;
		fo << cur->data.name << endl;
		fo << cur->data.classId << endl;
		cur = cur->next;
	}
	fo.close();
	return 1;
}
void RemoveStuCourse(LinkedListSemes lst) {
	string idclass;
	Semester semester;
	int choice;
	choice = ChoiceCourseClass(lst, semester, idclass);
	if (choice == -1)
	{
		cout << "ERROR: please try later!!!" << endl;
		return;
	}
	nodeCourse* cur = semester.course.head;
	while (--choice)
	{
		if (cur <= 0) break;
		cur = cur->next;
	}
	LoadStuCourseClass(semester, cur->data, idclass);
	nodePar* cur_par = cur->data.participant.head;

}



