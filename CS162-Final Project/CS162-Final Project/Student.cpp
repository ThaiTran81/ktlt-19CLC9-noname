#include"function.h"
//SAVE AND LOAD STUDENT
nodeStu* createNodeStudent(Student stud) {
	nodeStu* p = new nodeStu;
	p->dataStud.id = stud.id;
	p->dataStud.password = stud.password;
	p->dataStud.fullname = stud.fullname;
	p->dataStud.year = stud.year;
	p->dataStud.month = stud.month;
	p->dataStud.day = stud.day;
	p->dataStud.classId = stud.classId;
	p->dataStud.sex = stud.sex;
	p->next = NULL;
	return p;
}

bool LoadDataStudent(ifstream& fi, LinkedListStu& lst) {

	if (!fi.is_open())
	{
		cout << "Can't open data file " << endl;
		return 0;
	}
	else
	{
		lst.head = NULL;
		Student stud;
		fi >> lst.NumStu;
		if (lst.NumStu == 0) {
			return false;
		}
		fi >> stud.id;
		fi >> stud.password;
		getline(fi, stud.fullname);
		getline(fi, stud.fullname);
		fi >> stud.year >> stud.month >> stud.day;
		fi >> stud.classId;
		fi >> stud.sex;
		fi >> stud.status;
		nodeStu* p = createNodeStudent(stud);
		lst.head = p;
		nodeStu* cur = lst.head;
		for (int i = 0; i < lst.NumStu - 1; i++) {
			fi.ignore();
			getline(fi, stud.id);
			getline(fi, stud.password);
			getline(fi, stud.fullname);
			fi >> stud.year >> stud.month >> stud.day;
			fi >> stud.classId;
			fi >> stud.sex;
			fi >> stud.status;
			nodeStu* p = createNodeStudent(stud);
			cur->next = p;
			cur = cur->next;
		}
		fi.close();
		return true;
	}
}
bool SaveDataStudent(ofstream& fo, LinkedListStu& lst) {
	if (lst.head == NULL) {
		return false;
	}
	nodeStu* cur = lst.head;
	fo << lst.NumStu << endl;
	while (cur != NULL) {
		fo << cur->dataStud.id << endl;
		fo << cur->dataStud.password << endl;
		fo << cur->dataStud.fullname << endl;
		fo << cur->dataStud.year << " " << cur->dataStud.month << " " << cur->dataStud.day << endl;
		fo << cur->dataStud.classId << endl;
		fo << cur->dataStud.sex << endl;
		fo << cur->dataStud.status << endl;
		cur = cur->next;
	}
	fo.close();
	return true;
}

bool SaveDataClassFile(Class cla)
{
	ofstream fo;
	string pathfile = "Students-";
	nodeStu* cur = cla.stu.head;
	pathfile += cla.classID + ".txt";
	fo.open(pathfile.c_str());
	if (!fo.is_open())
	{
		cout << "can't not open file to save!!" << endl;
		return 0;
	}
	else
	{
		fo << cla.stu.NumStu << endl;
		while (cur != NULL) {
			fo << cur->dataStud.id << endl;
			fo << cur->dataStud.password << endl;
			fo << cur->dataStud.fullname << endl;
			fo << cur->dataStud.year << " " << cur->dataStud.month << " " << cur->dataStud.day << endl;
			fo << cur->dataStud.classId << endl;
			fo << cur->dataStud.sex << endl;
			fo << cur->dataStud.status << endl;
			cur = cur->next;
		}
		fo.close();
	}
	return 1;
}

//----------------------load and save class file--------------------------
bool LoadDataStudentFromClassFile(Class& cla)
{
	string pathfile = "Students-";
	ifstream fi;
	Student stu;
	pathfile += cla.classID + ".txt";
	fi.open(pathfile.c_str());
	if (!fi.is_open())
	{
		cout << "Can't open data file of class " << cla.classID << "!!!" << endl;
		return 0;
	}
	else
	{
		cla.stu.head = NULL;
		fi >> cla.stu.NumStu;
		for (int i = 0; i < cla.stu.NumStu; i++)
		{
			fi.ignore();
			getline(fi, stu.id);
			getline(fi, stu.password);
			getline(fi, stu.fullname);
			fi >> stu.year >> stu.month >> stu.day;
			fi.ignore();
			getline(fi, stu.classId);
			fi >> stu.sex;
			fi >> stu.status;
			PushStuClassNode(cla.stu.head, stu);
		}
		fi.close();
		return 1;
	}
}


bool FileClass_Exist(string idclass)
{
	ifstream fi;
	string pathfile = "Students-";
	pathfile += idclass + ".txt";
	fi.open(pathfile.c_str());
	if (fi.is_open())
	{
		fi.close();
		return 1;
	}
	return 0;
}

//Creat password student
string CreatePwdStu(string year, string month, string day)
{
	string pwd;
	pwd = year + month + day;
	return pwd;
}

//Import file of students of a class

void ImportStudentCsv(LinkedListStu& lstStu)
{
	ifstream fi;
	string pathfile;
	Class cla;
	nodeStu* cur = lstStu.head;
	nodeStu* flag;
	Student stu;
	cout << "Enter the local path to your Csv file:" << endl;
	getline(cin, pathfile, '\n');
	fi.open(pathfile.c_str());
	if (!fi.is_open())
	{
		cout << "Can't find the .csv file!" << endl;
	}
	else
	{
		while (cur->next != NULL && lstStu.head!=NULL)
		{
			cur = cur->next;
		}
		flag = cur;
		fi.ignore(256, '\n');
		while (!fi.eof())
		{
			fi.ignore(2);
			getline(fi, stu.id, ',');
			getline(fi, stu.fullname, ',');
			fi >> stu.sex;
			fi.ignore();
			getline(fi, stu.year, '-');
			getline(fi, stu.month, '-');
			getline(fi, stu.day, ',');
			getline(fi, stu.classId, '\n');
			if (fi.eof()) break;
			if (lstStu.head == NULL)
			{
				lstStu.head = createNodeStudent(stu);
				lstStu.NumStu++;
				cur = lstStu.head;
				flag = cur;
				continue;
			}
			stu.password = CreatePwdStu(stu.year, stu.month, stu.day);
			cur->next = createNodeStudent(stu);
			cur = cur->next;
			lstStu.NumStu++;
		}
		if(flag!=NULL) flag = flag->next;
		cla.classID = flag->dataStud.classId;
		//update student in class file
		if (FileClass_Exist(flag->dataStud.classId))
		{
			LoadDataStudentFromClassFile(cla);
		}
		else
		{
			cla.stu.head = NULL;
			cla.stu.NumStu = 0;
		}
		while (flag != NULL)
		{
			PushStuClassNode(cla.stu.head, flag->dataStud);
			cla.stu.NumStu++;
			flag = flag->next;
		}
		SaveDataClassFile(cla);
		//done
		cout << "Done!" << endl;
		//Back to main menu
	}
}

//change password Student
void ChangePasswordStudent(LinkedListStu& lst, string userid)
{
	int choice;
	Class cla;
	string curPass;
	string newPass1, newPass2;
	nodeStu* cur = lst.head;
	bool condition = false;
	while (cur != NULL && condition == false)
	{
		if (cur->dataStud.id == userid)
		{
			cla.classID = cur->dataStud.classId;
			while (condition == false)
			{
				cin.ignore();
				cout << "Current Password: ";
				getline(cin, curPass);
				cout << "New Password: ";
				getline(cin, newPass1);
				cout << "Type again: ";
				getline(cin, newPass2);
				if ((curPass == cur->dataStud.password) && (newPass1 == newPass2))
				{
					cur->dataStud.password = newPass1;
					cout << "--Success--" << endl;
					condition = true;
					//update file class
					nodeStu* cur2;
					LoadDataStudentFromClassFile(cla);
					cur2 = FindStu(cla.stu, userid);
					cur2->dataStud.password = cur->dataStud.password;
					SaveDataClassFile(cla);
				}
				else
				{
					cout << "Failed, Try Again" << endl;
					cout << "Press <0> to stop" << endl;
					cout << "Press <1> to continue " << endl;
					cout << "Your Choice: ";
					cin >> choice;
					if (choice == 0)
						return;
					cin.ignore();
				}
			}
		}
		cur = cur->next;
	}
}
//view profile student
void ViewProfileStudent(const LinkedListStu& lst, string userid)
{
	cout << ">Profile of student:" << endl;
	nodeStu* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataStud.id == userid)
		{
			cout << ">>>>Full name: " << cur->dataStud.fullname << endl;
			cout << ">>>>Gender:";
			if (cur->dataStud.sex == 1)
			{
				cout << "Female" << endl;
			}
			else
			{
				cout << "Male" << endl;
			}
			cout << ">>>>DoB:" << cur->dataStud.year << " " << cur->dataStud.month << " " << cur->dataStud.day << endl;
			cout << ">>>>Class: " << cur->dataStud.classId << endl;
			return;
		}
		cur = cur->next;
	}
	cout << "_________________________________________" << endl;
}
//------------------------------------------------------------------------
//ViewListOfClass
nodeCla* createNodeCLass(Class cla) {
	nodeCla* temp = new nodeCla();
	temp->dataClas.classID = cla.classID;
	temp->next = NULL;
	return temp;
}

void LoadListOfClass(LinkedListCla& lst)
{
	ifstream fi("Class.txt");
	lst.head = NULL;
	Class clas;
	fi >> lst.NumCla;
	fi.ignore();
	getline(fi, clas.classID);
	nodeCla* temp = createNodeCLass(clas);
	lst.head = temp;
	nodeCla* cur = lst.head;
	for (int i = 0; i < lst.NumCla - 1; i++) {
		getline(fi, clas.classID);
		temp = createNodeCLass(clas);
		cur->next = temp;
		cur = cur->next;
	}
	fi.close();
}

void ViewListOfClass(LinkedListCla& lst)
{
	nodeCla* cur = lst.head;
	int i = 1;
	cout << "Class: " << lst.NumCla << endl;
	while (cur != NULL) {
		cout << setw(3) << i++ << "." << cur->dataClas.classID << endl;
		cur = cur->next;
	}
}


//----------------------Edit student from a class-----------------------------
void EditStudent(LinkedListCla& cla, LinkedListStu& stu)
{
	int choice;
	string newname, newmonth, newyear, newday;
	nodeStu* student;
	nodeCla* cur_cla;
	nodeStu* student2;//to update linked list from student.txt
	student = FindStuInClass(cla, cur_cla);
	if (student == NULL)
	{
		cout << "FAILED: not found student" << endl;
		return;
	}
	else
	{
		ViewProfileStudent(cur_cla->dataClas.stu, student->dataStud.id);
		cout << "Do you want to edit this student?[Yes(1)/No(0)] :" << endl;
		cin >> choice;
		if (choice == 0)
		{
			//back to main menu
		}
		else
		{
			student2 = FindStu(stu, student->dataStud.id);//update data student.txt
			cout << "Enter new name:";
			cin.ignore();
			getline(cin, newname);
			cout << "Enter new date of birth[yy mm dd]" << endl;
			cin >> newyear >> newmonth >> newday;
			//update data linked list for Students-Idclass.txt
			student->dataStud.fullname = newname;
			student->dataStud.year = newyear;
			student->dataStud.month = newmonth;
			student->dataStud.day = newday;
			student->dataStud.password = CreatePwdStu(newyear, newmonth, newday);

			//update data linked list for Students.txt
			student2->dataStud.fullname = newname;
			student2->dataStud.year = newyear;
			student2->dataStud.month = newmonth;
			student2->dataStud.day = newday;
			student2->dataStud.password = student->dataStud.password;
			cout << "Successfull !!!(password has been reset)" << endl;
			SaveDataClassFile(cur_cla->dataClas);
			//back to main menu
		}
	}
}


//find student in a class
nodeStu* FindStuInClass(LinkedListCla& lst, nodeCla*& cur_cla)
{
	int choice;
	string idstu;
	cur_cla = lst.head;
	ViewListOfClass(lst);
	do
	{
		cout << "Which class is student in?" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		if (choice > lst.NumCla || choice < 0)
		{
			cout << "Error!!! please enter again!" << endl;
			cout << "Press <0> to back" << endl;
		}
	} while (choice > lst.NumCla && choice != 0 && choice < 0);
	if (choice == 0)
	{
		return NULL;
	}
	else
	{
		while (choice--)
		{
			if (choice == 0) break;
			cur_cla = cur_cla->next;
		}
		if (!LoadDataStudentFromClassFile(cur_cla->dataClas))
		{
			cout << "not found data from class " << cur_cla->dataClas.classID << endl;
			return NULL;
		}
		else
		{
			cout << "Enter id student:";
			cin >> idstu;
			nodeStu* cur_stu = cur_cla->dataClas.stu.head;
			while (cur_stu != NULL)
			{
				if (cur_stu->dataStud.id == idstu)
				{
					break;
				}
				cur_stu = cur_stu->next;
			}
			if (cur_stu == NULL)
			{
				cout << "Not found id student!!!" << endl;
				return NULL;
			}
			else
			{
				return cur_stu;
			}
		}
	}
}
// find student in linked list lstStu
nodeStu* FindStu(LinkedListStu& lst, string id)
{
	nodeStu* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataStud.id == id)
			return cur;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
}

//----------------------Remove Student from a class---------------------------
void RemoveStudent(LinkedListCla& cla, LinkedListStu& stu)
{
	int choice;
	nodeStu* student;
	nodeStu* student2;//to update linked list from student.txt
	nodeCla* cur_cla;
	student = FindStuInClass(cla, cur_cla);
	if (student == NULL)
	{
		//back to main menu
	}
	else
	{
		ViewProfileStudent(stu, student->dataStud.id);
		cout << "Do you want to remove this student?[Yes(1)/No(0)] :" << endl;
		cin >> choice;
		if (choice == 0)
		{
			return;
		}
		else
		{
			student2 = FindStu(stu, student->dataStud.id);
			student->dataStud.status = 0;
			student2->dataStud.status = 0;
			cout << "Successfull !!!(Student has been removed)" << endl;
			SaveDataClassFile(cur_cla->dataClas);
			//back to main menu
		}
	}
}

//create linked list student in a class
void PushStuClassNode(nodeStu*& head, Student new_data)
{
	nodeStu* new_node = new nodeStu;

	new_node->dataStud = new_data;
	new_node->next = head;
	head = new_node;
}
//change student from class A to class B

void DeleteNodeStu(nodeStu*& head, string idstu)
{
	nodeStu* temp = head;
	nodeStu* prev = NULL;

	if (temp != NULL && temp->dataStud.id == idstu)
	{
		head = temp->next;
		delete temp;
		return;
	}
	while (temp != NULL && temp->dataStud.id != idstu)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return;
	else prev->next = temp->next;

	delete temp;
}

void ChangeClassStudent(LinkedListStu& lst, LinkedListCla lstCla)
{
	Class cla2;
	nodeCla* cur_cla;
	nodeStu* student, * student_lst;
	string new_class;
	student = FindStuInClass(lstCla, cur_cla);
	if (student == NULL)
	{
		//back to main menu
	}
	else
	{
		student_lst = FindStu(lst, student->dataStud.id);//find in linkedlist student.txt
		cur_cla->dataClas.classID = student->dataStud.classId;
		LoadDataStudentFromClassFile(cur_cla->dataClas);
		ViewProfileStudent(cur_cla->dataClas.stu, student->dataStud.id);
		cout << "Enter new class you want move student to: ";
		cin.ignore();
		getline(cin, new_class);
		if (FileClass_Exist(new_class) == 0)
		{
			cout << "Sorry!! not found data of class " << new_class << endl;
			//back to main menu
		}
		else
		{
			student_lst->dataStud.classId = new_class;
			cla2.classID = new_class;
			//update class file B
			LoadDataStudentFromClassFile(cla2);
			student->dataStud.classId = new_class;
			PushStuClassNode(cla2.stu.head, student->dataStud);
			cla2.stu.NumStu++;
			//update class file A
			DeleteNodeStu(cur_cla->dataClas.stu.head, student->dataStud.id);
			cur_cla->dataClas.stu.NumStu--;

			//save all file
			SaveDataClassFile(cur_cla->dataClas);
			SaveDataClassFile(cla2);
		}
	}
}


//view students of a class
void ViewStuOfClass(string classid)
{
	Class cla;
	string pathfile = "Students-";
	pathfile += classid + ".txt";
	if (FileClass_Exist(classid))
	{
		int i = 1;
		cla.classID = classid;
		LoadDataStudentFromClassFile(cla);
		nodeStu* cur = cla.stu.head;
		cout << "Class " << classid << " :" << endl;
		cout << setw(5) << "NO.";
		cout << setw(18) << "Full name |";
		cout << setw(8) << "Gender|";
		cout << setw(15) << "Date of birth|";
		cout << setw(8) << "Status" << endl;
		cout << "=================================================================" << endl;
		while (cur != NULL)
		{
			cout << setw(5) << i++;
			cout << setw(18) << cur->dataStud.fullname;
			if (cur->dataStud.sex == 0) cout << setw(8) << "Male";
			else cout << setw(8) << "Female";
			cout << setw(5) << cur->dataStud.day << "-" << cur->dataStud.month << "-" << cur->dataStud.year;
			if (cur->dataStud.status == 0) cout << setw(8) << "Dropped";
			else cout << setw(10) << "Active" << endl;
			cur = cur->next;
		}
	}
	else
	{
		cout << "Not found data of class" << endl;
	}
}


//add a student
void AddAStu(LinkedListStu& lst, LinkedListCla cla)
{
	Student student;
	Class class_;
	ViewListOfClass(cla);
	cout << "Enter Class(19CLC9,...)";
	getline(cin, student.classId);
	if (FileClass_Exist(student.classId) == 0)
	{
		cout << "can't not found data of class " << student.classId << endl;
		//back to main menu
	}
	else
	{
		class_.classID = student.classId;
		LoadDataStudentFromClassFile(class_);
		cout << "Enter id(ex:19127001....):";
		getline(cin, student.id);
		cout << "Enter full name:";
		getline(cin, student.fullname);
		cout << "Gender[0(male)/1(female)]:";
		cin >> student.sex;
		cout << "Enter date of birth(2001 01 28,...):";
		cin >> student.year >> student.month >> student.day;
		student.password = CreatePwdStu(student.year, student.month, student.day);
		class_.stu.NumStu++;
		PushStuClassNode(class_.stu.head, student);
		lst.NumStu++;
		PushStuClassNode(lst.head, student);
		SaveDataClassFile(class_);
		cout << "Sucessful!!!" << endl;
		//back to main menu
	}
}