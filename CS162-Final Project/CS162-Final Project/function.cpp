#include"function.h"

string printProg(int x) {
	string s;
	s = "[";
	for (int i = 1; i <= (100 / 2); i++) {
		if (i <= (x / 2) || x == 100)
			s += "=";
		else if (i == (x / 2))
			s += ">";
		else
			s += " ";
	}

	s += "]";
	return s;
}

// Login
bool Login(User& user, LinkedListSta lstSta, LinkedListStu lstStu, LinkedListLec lstLec, int& level)
{
	cout << "-------------LOGIN-------------" << endl;
	cout << "Id: ";
	cin >> user.id;
	cout << "Password: ";
	user.password = "";
	int buffer;
	do
	{
		buffer = _getch();
		if (buffer != 13 && buffer != 8)
		{
			cout << "*";
		}
		if (buffer == 8)
		{
			user.password.erase(user.password.end() - 1, user.password.end());
			cout << "\b";
			cout << " ";
			cout << "\b";
		}
		if (buffer != 13 && buffer != 8)
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
void ViewStuCourseClass(LinkedListSemes lst, string idLec)
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

	//tim course tuong ung
	while (--choice)
	{
		if (cur <= 0) break;
		cur = cur->next;
	}

	//check lecturer whether teaches in this course
	if (idLec != "")
	{
		bool check;
		check = CheckLecCourse(semester, cur->data.id, idclass, idLec);
		if (check == 0)
			return;
	}
	LoadStuCourseClass(semester, cur->data, idclass);//load data student
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
	return 1;
}

//save data student in a course
bool SaveStuCourse(Semester semester, Course& course, string idclass)
{
	ofstream fo;
	string pathfile;
	pathfile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-" + idclass + "-" + course.id + "-Students.txt";
	fo.open(pathfile.c_str());
	if (!fo.is_open())
	{
		cout << "can't save file" << endl;
		return 0;
	}
	nodePar* cur = course.participant.head;
	fo << course.participant.numPar << endl;
	while (cur != NULL)
	{
		fo << cur->dataPar.id << endl;
		fo << cur->dataPar.fullname << endl;
		fo << cur->dataPar.year << " " << cur->dataPar.month << " " << cur->dataPar.day << endl;
		fo << cur->dataPar.classId << endl;
		fo << cur->dataPar.status << endl;
		fo << cur->dataPar.mid << endl;//midterm
		fo << cur->dataPar.final << endl;//final
		fo << cur->dataPar.bonus << endl;//bonus
		fo << cur->dataPar.total << endl;//total
		nodeDat* cur_dat = cur->dataPar.timeCheck.head;
		while (cur_dat != NULL)
		{
			fo << cur_dat->dataDat.year << " " << cur_dat->dataDat.month << " " << cur_dat->dataDat.day << " " << cur_dat->dataDat.checking << endl;
			cur_dat = cur_dat->next;
		}
		fo << cur->dataPar.status_course << endl;
		cur = cur->next;
	}
	fo.close();
	return 1;
}

// remove a course
void RemoveACourse(LinkedListSemes lst)
{
	LinkedListCourse lstCourse;
	Semester semester;
	string idclass;
	int choice;

	cout << RED << "---Remove Course---" << RESET << endl;
	choice = ChoiceCourseClass(lst, semester, idclass);
	if (choice == -1)
	{
		cout << "ERROR: please try later!!!" << endl;
		return;
	}
	LoadCourseSemes(semester, lstCourse);
	nodeCourse* cur_course = semester.course.head;
	while (--choice)
	{
		if (choice == 0) break;
		cur_course = cur_course->next;
	}

	//delete file
	string namefile;
	namefile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-" + idclass + "-" + cur_course->data.id + "-Students.txt";
	remove(namefile.c_str());

	//update file
	semester.course.numCourse--;
	lstCourse.numCourse--;
	DeleteNodeCourse(semester.course.head, cur_course->data.id);
	DeleteNodeCourse(lstCourse.head, cur_course->data.id);
	SaveFileCourseClass(semester, idclass);
	SaveCourseSemes(semester, lstCourse);

}

//view list of attendence of a course
void ViewListAttendence(LinkedListSemes lst, string idLec)
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
	nodeCourse* cur_course = semester.course.head;
	while (--choice)
	{
		if (choice == 0) break;
		cur_course = cur_course->next;
	}
	if (idLec != "")
	{
		bool check;
		check = CheckLecCourse(semester, cur_course->data.id, idclass, idLec);
		if (check == 0)
			return;
	}
	LoadStuCourseClass(semester, cur_course->data, idclass);
	cout << "\t\t\t\t\t\t LIST OF ATTENDENCE-" << cur_course->data.name
		<< "(" << cur_course->data.id << ")- " << cur_course->data.classId << "_"
		<< semester.name << "(" << semester.yearBeg << "-" << semester.yearEnd << ")" << endl;
	cout << endl;
	nodePar* cur_par = cur_course->data.participant.head;
	cout << "NO.";
	cout << setw(12) << "Student ID";
	cout << setw(15) << "Full name";
	cout << setw(10) << "Class";
	cout << "   ";
	nodeDat* cur_dat = cur_par->dataPar.timeCheck.head;
	while (cur_dat != NULL)
	{
		cout << cur_dat->dataDat.day << "-" << cur_dat->dataDat.month << "-" << cur_dat->dataDat.year << "   ";
		cur_dat = cur_dat->next;
	}
	cout << endl;
	cout << "===========================================================================================================================================================================" << endl;
	int i = 0;
	while (cur_par != NULL)
	{
		cout << ++i;
		cout << setw(12) << cur_par->dataPar.id;
		cout << setw(20) << cur_par->dataPar.fullname;
		cout << setw(8) << cur_par->dataPar.classId;
		cur_dat = cur_par->dataPar.timeCheck.head;
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
		cur_par = cur_par->next;
	}
}

//add a student to a course
void AddStuCourse(LinkedListSemes lstSemes, LinkedListStu lstStu)
{
	Student student;
	Participant participant;
	Class cla;
	Semester semester;
	string idclass;
	nodeStu* stu;
	int choice;
	bool check;
	cout << GREEN << "---Add a student to Course---" << RESET << endl;
	cout << endl;
	choice = ChoiceCourseClass(lstSemes, semester, idclass);
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
	cout << "Enter Class which student in:";
	cin.ignore();
	getline(cin, student.classId);
	cla.classID = student.classId;
	check = LoadDataStudentFromClassFile(cla);
	if (check == false)
	{
		cout << "FAIL: not found data of class" << endl;
		return;
	}
	LoadStuCourseClass(semester, cur_course->data, idclass);
	cout << "Enter id of student:";
	getline(cin, student.id);
	stu = FindStu(cla.stu, student.id);
	if (stu == NULL)
	{
		cout << "FAILED: not found data of student" << endl;
		return;
	}
	ViewProfileStudent(lstStu, student.id);
	cout << "Do you want to add this student???[yes(1)/no(0)] ";
	cin >> choice;
	if (choice == 0)
	{
		return;
	}
	participant.classId = stu->dataStud.classId;
	participant.fullname = stu->dataStud.fullname;
	participant.status = stu->dataStud.status;
	participant.day = stu->dataStud.day;
	participant.month = stu->dataStud.month;
	participant.year = stu->dataStud.year;
	participant.id = stu->dataStud.id;
	participant.timeCheck = cur_course->data.participant.head->dataPar.timeCheck;
	nodeDat* cur_dat = participant.timeCheck.head;
	while (cur_dat != NULL)
	{
		cur_dat->dataDat.checking = -1;
		cur_dat = cur_dat->next;
	}
	cur_course->data.participant.numPar++;
	PushNodeParticipant(cur_course->data.participant.head, participant);
	SaveStuCourse(semester, cur_course->data, idclass);
	cout << GREEN << "Done!!!" << RESET << endl;
}

// view list of courses of a semester
void ViewListCourseSemes(LinkedListSemes lst)
{
	Semester semester;
	LinkedListCourse lstCourse;
	cout << "Enter years(ex 2019 2020...):";
	cin >> semester.yearBeg >> semester.yearEnd;
	cout << "Enter semester:";
	cin.ignore();
	getline(cin, semester.name);

	bool check;
	check = LoadCourseSemes(semester, lstCourse);
	if (check == false)
	{
		cout << "FAILED: not found data of semester" << endl;
		return;
	}

	nodeCourse* cur = lstCourse.head;
	int count = 1;
	cout << GREEN << "\t\t\t\tLIST OF COURSES-" << semester.name << "(" << semester.yearBeg << "-" << semester.yearEnd << ")" << RESET << endl;
	cout << "No.";
	cout << setw(36) << " |Course|            ";
	cout << setw(13) << "|ID Class|";
	cout << setw(25) << "|Date|       ";
	cout << setw(8) << "|Room|";
	cout << endl;
	cout << "======================================================================================" << endl;
	while (cur != NULL)
	{
		cout << setw(2) << count << " ";
		cout << GREEN << setw(30) << cur->data.name << " (" << cur->data.id << ")" << RESET;
		cout << setw(8) << cur->data.classId;
		if (cur->data.firstday == 1) cout << setw(14) << "Sunday";
		else if (cur->data.firstday == 2) cout << setw(14) << "Monday";
		else if (cur->data.firstday == 3) cout << setw(14) << "Tuesday";
		else if (cur->data.firstday == 4) cout << setw(14) << "Wednesday";
		else if (cur->data.firstday == 5) cout << setw(14) << "Thursday";
		else if (cur->data.firstday == 6) cout << setw(14) << "Friday";
		else if (cur->data.firstday == 7) cout << setw(14) << "Saturday";
		cout << " (" << cur->data.hour_start << ":" << cur->data.minute_start << " - " << cur->data.hour_end << ":" << cur->data.minute_end << ")";
		cout << setw(6) << cur->data.room << endl;
		cout << "--------------------------------------------------------------------------------------" << endl;
		count++;
		cur = cur->next;
	}
	if (count == 1) cout << RED << "(emptry)" << RESET << endl;
}


void ViewScoreCourse(LinkedListSemes lst, string idLec)
{
	string idclass;
	Semester semester;

	//get data
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
		bool check;
		check = CheckLecCourse(semester, cur_course->data.id, idclass, idLec);
		if (check == 0)
			return;
	}
	LoadStuCourseClass(semester, cur_course->data, idclass);

	//print out
	cout << RED << "\t -----SCOREBOARD_" << cur_course->data.name << "(" << cur_course->data.id << ")_"
		<< cur_course->data.classId << "_" << semester.name << "(" << semester.yearBeg << "-" << semester.yearEnd << ")-----" << RESET << endl;

	nodePar* cur_par = cur_course->data.participant.head;
	int i = 1;
	cout << "===================================================================================================" << endl;
	cout << setw(4) << "NO.";
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
	while (cur_par != NULL)
	{
		cout << setw(3) << i;
		cout << setw(12) << cur_par->dataPar.id;
		cout << setw(20) << cur_par->dataPar.fullname;
		cout << setw(9) << cur_par->dataPar.classId;
		if (cur_par->dataPar.status == 1) cout << setw(12) << GREEN << "ACTIVE" << RESET;
		else cout << setw(12) << RED << "DROPPED" << RESET;
		if (cur_par->dataPar.mid == -1) cout << setw(11) << RED << "-" << RESET;
		else cout << setw(8) << cur_par->dataPar.mid;

		if (cur_par->dataPar.final == -1) cout << setw(9) << RED << "-" << RESET;
		else cout << setw(5) << cur_par->dataPar.final;

		if (cur_par->dataPar.bonus == -1) cout << setw(10) << RED << "-" << RESET;
		else cout << setw(6) << cur_par->dataPar.bonus;

		if (cur_par->dataPar.total == -1) cout << setw(10) << RED << "-" << RESET;
		else cout << setw(5) << cur_par->dataPar.total;

		if (cur_par->dataPar.status_course == 1) cout << setw(12) << GREEN << " ACTIVE" << RESET << endl;
		else cout << setw(12) << RED << " DROPPED" << RESET << endl;
		cout << "---------------------------------------------------------------------------------------------------" << endl;
		i++;
		cur_par = cur_par->next;
	}

}

//edit a course
void EditCourse(LinkedListSemes lstSem, LinkedListLec& lstLec)
{
	string idclass;
	Semester semester;
	LinkedListCourse lstCourse;
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
	ViewProfileCourse(cur_course->data);
	cout << "Do you want to edit this course? [yes(1)/no(0)] ";
	cin >> choice;
	if (choice == 0) return;
	do
	{
		ChoiceEditCourse();
		cin >> choice;
		if (choice == 1)
		{
			LoadCourseSemes(semester, lstCourse);
			nodeCourse* cur1 = lstCourse.head;
			while (cur1 != NULL)
			{
				if (cur1->data.id == cur_course->data.id) break;
				cur1 = cur1->next;
			}

			string namefile;
			namefile = semester.yearBeg + "-" + semester.yearEnd + "-" + semester.name + "-" + idclass + "-" + cur_course->data.id + "-Students.txt";
			remove(namefile.c_str());//delete file have old name id

			cout << "Enter new id of this course:";
			cin.ignore();
			getline(cin, cur_course->data.id);
			cout << "Enter new name of this course:";
			getline(cin, cur_course->data.name);
			cur1->data = cur_course->data;


			SaveCourseSemes(semester, lstCourse);
			SaveStuCourse(semester, cur_course->data, idclass);
			SaveFileCourseClass(semester, idclass);
			cout << "Done" << endl;
		}
		else if (choice == 2)
		{
			cin.ignore();
			cout << "Enter id of the new lecturer for this course: ";
			getline(cin, cur_course->data.lec.id);
			nodeLec* lecturer = FindLecturer(lstLec, cur_course->data.lec.id);

			if (lecturer == NULL)
			{
				cur_course->data.lec.password = cur_course->data.lec.id;
				cout << "Enter full name of lecturer:";
				getline(cin, cur_course->data.lec.name);
				cout << "Enter degree of lecturer:";
				getline(cin, cur_course->data.lec.degree);
				cout << "Enter gender of lecturer(0:male/1:female):";
				cin >> cur_course->data.lec.sex;
				lstLec.numLec++;
				PushNodeLecturer(lstLec.head, cur_course->data.lec);
			}
			else
			{
				cur_course->data.lec = lecturer->dataLec;
			}
			SaveFileCourseClass(semester, idclass);
			cout << "Done" << endl;
		}
		else if (choice == 3)
		{
			LinkedListSche lstSche;
			Schedule start, end;
			cout << "Enter start date(ex 2020 06 01...):";
			cin >> cur_course->data.year_start >> cur_course->data.month_start >> cur_course->data.day_start;
			cout << "Enter end date(ex 2020 06 01...):";
			cin >> cur_course->data.year_end >> cur_course->data.month_end >> cur_course->data.day_end;
			cout << "Enter day of week:";
			cin >> cur_course->data.firstday;
			cout << "Enter start time(ex: 7 30...)";
			cin >> cur_course->data.hour_start >> cur_course->data.minute_start;
			cout << "Enter end time(ex: 7 30...)";
			cin >> cur_course->data.hour_end >> cur_course->data.minute_end;

			start.day = cur_course->data.day_start;
			start.month = cur_course->data.month_start;
			start.year = cur_course->data.year_start;

			end.day = cur_course->data.day_end;
			end.month = cur_course->data.month_end;
			end.year = cur_course->data.year_end;
			AnalysisDate(start, end, lstSche, cur_course->data.firstday);
			AssignScheduleStu(cur_course->data.participant, lstSche);
			SaveStuCourse(semester, cur_course->data, idclass);
			SaveFileCourseClass(semester, idclass);
			cout << "Done" << endl;
		}
		else if (choice == 4)
		{
			cout << "Enter room:";
			cin.ignore();
			getline(cin, cur_course->data.room);
			SaveFileCourseClass(semester, idclass);
			cout << "Done" << endl;
		}
	} while (choice != 0);
}

// view information of a course
void ViewProfileCourse(Course course)
{
	cout << BLUE << course.name << "- " << course.id << "(" << course.classId << ")" << RESET << endl;
	cout << "Lecturer: " << course.lec.name << "(" << course.lec.id << ")" << endl;
	cout << "Start date: " << course.day_start << "-" << course.month_start << "-" << course.year_start << endl;
	cout << "End date: " << course.day_end << "-" << course.month_end << "-" << course.year_end << endl;
	cout << "Day of week: " << course.firstday << endl;
	cout << "Time start from " << course.hour_start << ":" << course.minute_start << " to " << course.hour_end << ":" << course.minute_end << endl;
	cout << "Room: " << course.room << endl;
}

//menu choice for edit course
void ChoiceEditCourse()
{
	cout << BLUE << "what do you want to edit in this course?" << RESET << endl;
	cout << "1. Name and id of this course" << endl;
	cout << "2. Lecturer of this course" << endl;
	cout << "3. Date and time of this course" << endl;
	cout << "4. Room" << endl;
	cout << "0. Nothing" << endl;
	cout << "Enter your choice: ";
}

void AssignScheduleStu(LinkedListPar& lst, LinkedListSche lstSche)
{
	nodePar* curPar = lst.head;
	nodeSche* curSche = lstSche.head;

	Date date;

	date.day = curSche->data.day;
	date.month = curSche->data.month;
	date.year = curSche->data.year;
	lst.head->dataPar.timeCheck.head = CreateNodeDate(date);
	nodeDat* curDat = lst.head->dataPar.timeCheck.head;
	curSche = curSche->next;

	while (curSche != NULL)
	{
		date.day = curSche->data.day;
		date.month = curSche->data.month;
		date.year = curSche->data.year;
		curDat->next = CreateNodeDate(date);
		curDat = curDat->next;
		curSche = curSche->next;
	}

	curPar = curPar->next;
	while (curPar != NULL)
	{
		curPar->dataPar.timeCheck = lst.head->dataPar.timeCheck;
		curPar = curPar->next;
	}
}

//find participant
nodePar* FindParticipant(LinkedListPar& lst, string id)
{
	nodePar* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataPar.id == id)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}
//Remove student
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
	Participant participant;
	cout << "Enter id of participant:" << endl;
	cin >> participant.id;
	while (cur_par != NULL)
	{
		if (cur_par->dataPar.id == participant.id)
		{
			cur_par->dataPar.status_course = 0;
			cout << "the student has been removed" << endl;
			break;
		}
		cur_par = cur_par->next;
	}
	if (cur_par == NULL)
	{
		cout << "Failed:not found student";
		return;
	}
	SaveStuCourse(semester, cur->data, idclass);
}


//check whether the lecturer is in course 
bool CheckLecCourse(Semester semester, string idCourse, string idClass, string idLec)
{
	nodeCourse* cur = semester.course.head;
	while (cur != NULL)
	{
		if (cur->data.id == idCourse) break;
		cur = cur->next;
	}
	if (cur->data.lec.id != idLec)
	{
		cout << "FAILED: you are not the lecturer of this course. " << endl;
		return 0;
	}
	return 1;
}

//Viewsemester 
void ViewSemester(LinkedListSemes lst)
{
	if (lst.head == NULL)
	{
		cout << "Data Not Found" << endl;
		return;
	}
	int i = 1;
	nodeSemes* cur = lst.head;
	while (cur != NULL)
	{

		cout << setw(4) << i++ << ". ";
		cout << cur->data.name<<" ("<< cur->data.yearBeg<<"-"<<cur->data.yearEnd<<")" << endl;
		cur = cur->next;
	}
}
//Export Attendence
void ExportAttendence(LinkedListSemes lst)
{
	string idclass;
	Semester semester;

	//get data
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
	//print out
	nodePar* cur_par = cur_course->data.participant.head;
	ofstream f;
	string temp = idclass + "-Attendence.csv";
	string pathfile;

	cout << "Enter the local path to save file:";
	cin.ignore();
	getline(cin, pathfile);
	pathfile = pathfile + "\\" + temp;
	f.open(pathfile.c_str());
	if (!f.is_open())
	{
		cout << "Can not open file" << endl;
	}
	else
	{
		f << "No.,Studen ID,Full name,Class,";
		nodeDat* cur_dat = cur_par->dataPar.timeCheck.head;
		while (cur_dat != NULL)
		{
			f << cur_dat->dataDat.day << "-" << cur_dat->dataDat.month << "-" << cur_dat->dataDat.year << ",";
			cur_dat = cur_dat->next;
		}
		f << endl;
		int i = 0;
		while (cur_par != NULL)
		{
			f << ++i<<",";
			f <<  cur_par->dataPar.id<<",";
			f <<  cur_par->dataPar.fullname<<",";
			f <<  cur_par->dataPar.classId<<",";
			cur_dat = cur_par->dataPar.timeCheck.head;
			while (cur_dat != NULL)
			{
				if (cur_dat->dataDat.checking == -1)
					f << "Absent,";
				else f <<  "Present,";
				cur_dat = cur_dat->next;
			}
			f << endl;
			cur_par = cur_par->next;
		}
		cout << GREEN << "Successfully!! Your exported file is " << temp << RESET << endl;
		f.close();
	}
}
//export score to csv file
void ExportScore(LinkedListSemes lst) {
	string idclass;
	Semester semester;

	//get data
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
	//print out
	nodePar* cur_par = cur_course->data.participant.head;
	ofstream f;
	string temp = idclass + "-Score.csv";
	string pathfile;

	cout << "Enter the local path to save file:";
	cin.ignore();
	getline(cin, pathfile);
	pathfile = pathfile + "\\" + temp;
	f.open(pathfile.c_str());
	if (!f.is_open())
	{
		cout << "Can not open file" << endl;
	}
	else {
		
		f << "No.,ID Student,Full name,ID Class,Study status,Mid,Final,Bonus,Total,Course status" << endl;
		int i = 0;
		while (cur_par != NULL)
		{
			f << ++i << ",";
			f << cur_par->dataPar.id << ",";
			f << cur_par->dataPar.fullname << ",";
			f << cur_par->dataPar.classId << ",";
			if (cur_par->dataPar.status == 0)
				f << "INACTIVE,";
			else
				f << "ACTIVE,";
			if (cur_par->dataPar.mid == -1)
				f << "-,";
			else
			f << cur_par->dataPar.mid << ",";
			if (cur_par->dataPar.final == -1)
				f << "-,";
			else
			f << cur_par->dataPar.final << ",";
			if (cur_par->dataPar.bonus == -1)
				f << "-,";
			else
			f << cur_par->dataPar.bonus << ",";
			if (cur_par->dataPar.total == -1)
				f << "-,";
			else
			f << cur_par->dataPar.total << ",";
			if (cur_par->dataPar.status_course == 0)
				f << "INACTIVE,";
			else
			f <<"ACTIVE,";
			cur_par = cur_par->next;
			f << endl;
		}
		cout << GREEN << "Successfully!! Your exported file is "<< temp << RESET << endl;
		f.close();
	}
}

