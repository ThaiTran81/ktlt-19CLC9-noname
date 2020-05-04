#include"function.h"
//             SAVE, LOAD STAFF             //
nodeSta* createNodeStaff(Staff staf)
{
	nodeSta* p = new nodeSta;
	p->dataStaf.id = staf.id;
	p->dataStaf.password = staf.password;
	p->dataStaf.fullname = staf.fullname;
	//p->dataStaf.typeMenu = staf.typeMenu;
	p->dataStaf.sex = staf.sex;
	p->next = NULL;
	return p;
}
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst)
{
	lst.head = NULL;
	Staff staf;
	fi >> lst.NumSta;
	if (lst.NumSta == 0)
	{
		return false;
	}
	else
	{
		fi >> staf.id;
		fi >> staf.password;
		getline(fi, staf.fullname);
		getline(fi, staf.fullname);
		fi >> staf.sex;
		nodeSta* p = createNodeStaff(staf);
		lst.head = p;
		nodeSta* cur = lst.head;
		for (int i = 0; i < lst.NumSta - 1; i++)
		{
			fi >> staf.id;
			fi >> staf.password;
			getline(fi, staf.fullname);
			getline(fi, staf.fullname);
			fi >> staf.sex;
			p = createNodeStaff(staf);
			cur->next = p;
			cur = cur->next;
		}
		return true;
	}
}
bool SaveDataStaff(ofstream& fo, LinkedListSta& lst)
{
	if (lst.head == NULL)
	{
		return false;
	}
	nodeSta* cur = lst.head;
	fo << lst.NumSta << endl;
	while (cur != NULL)
	{
		fo << cur->dataStaf.id << endl;
		fo << cur->dataStaf.password << endl;
		fo << cur->dataStaf.fullname << endl;
		fo << cur->dataStaf.sex << endl;
		cur = cur->next;
	}
	return true;
}
//________________________________________________________//
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
	nodeStu* p = createNodeStudent(stud);
	lst.head = p;
	nodeStu* cur = lst.head;
	for (int i = 0; i < lst.NumStu - 1; i++) {
		fi >> stud.id;
		fi >> stud.password;
		getline(fi, stud.fullname);
		getline(fi, stud.fullname);
		fi >> stud.year >> stud.month >> stud.day;
		fi >> stud.classId;
		fi >> stud.sex;
		fi >> stud.status;
		nodeStu* p = createNodeStudent(stud);
		cur->next = p;
		cur = cur->next;
	}
	return true;
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
	return true;
}

// Login
void Login(string& userid, string& userpwd, LinkedListSta lstSta, LinkedListStu lstStu)
{
	cout << "-------------LOGIN-------------" << endl;
	cout << "Id: ";
	cin >> userid;
	cout << "Password: ";
	cin >> userpwd;
	nodeSta* curSta = lstSta.head;
	nodeStu* curStu = lstStu.head;
	while (curSta!=NULL)
	{
		if (curSta->dataStaf.id == userid && curSta->dataStaf.password==userpwd)
		{
			cout << "SUCCESSFUL!!!!" << endl;
			return;
		}
		curSta = curSta->next;
	}
	while (curStu != NULL)
	{
		if (curStu->dataStud.id == userid && curStu->dataStud.password == userpwd)
		{
			cout << "SUCCESSFUL!!!!" << endl;
			return;
		}
		curStu = curStu->next;
	}
	cout << "Invalid login, please try again" << endl;
}

void ViewProfileStaff(const LinkedListSta& lst, string userid)
{
	cout << "id: " << userid << endl;
	cout << "Full name: ";
	nodeSta* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataStaf.id == userid )
		{
			cout << "Full name: " << cur->dataStaf.fullname << endl;
			cout << "Gender: ";
			if (cur->dataStaf.sex == 1) {
				cout << "Female" << endl;
			}
			else
			{
				cout << "Male" << endl;
			}
			break;
		}
		cur = cur->next;
	}
	cout << "1. Back to Menu" << endl;
	cout << "0. Exit" << endl;
}

//Menu
void MenuStaff_class()
{
	cout << "Main Menu-> Class" << endl;
	cout << "---------------------" << endl;
	cout << "1. Import students of a class from a scv file" << endl;
	cout << "2. Add a new student to a class" << endl;
	cout << "3. Edit an student" << endl;
	cout << "4. Remove a student" << endl;
	cout << "5. Change students from class A to class B" << endl;
	cout << "6. View list of classes" << endl;
	cout << "7. View list of students in a class" << endl;
	cout << "0. Back to Main Menu" << endl;
}


//Import file of students of a class
string CreatePwdStu(string year,string month,string day)
{
	string pwd;
	pwd = year + month + day;
	return pwd;
}

void ImportStudentCsv(LinkedListStu& lst)
{
	ifstream fi;
	string pathfile;
	nodeStu* cur = lst.head;
	nodeStu* p;
	Student stu;
	cout << "Enter the local path to your Csv file:" << endl;
	getline(cin,pathfile,'\n');
	fi.open(pathfile.c_str());
	if (!fi.is_open())
	{
		cout << "Can't find the .csv file!" << endl;
	}
	else
	{
		while (cur->next!=NULL)
		{
			cur = cur->next;
		}
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
			stu.password = CreatePwdStu(stu.year, stu.month, stu.day);
			cur->next=createNodeStudent(stu);
			cur = cur->next;
			lst.NumStu++;
		}
		cout << "Done!" << endl;
	}
}
//-------------------Doi mat khau---------------------------
//Staff
void ChangePasswordStaff(LinkedListSta& lst, string userid)
{
	int choice;
	string curPass;
	string newPass1,newPass2;
	nodeSta* cur = lst.head;
	bool condition = false;
	while (cur != NULL)
	{
		if (cur->dataStaf.id == userid)
		{
			while (condition==false)
			{
				cout << "Current Password: ";
				getline(cin, curPass);
				cout << "New Password: ";
				getline(cin, newPass1);
				cout << "Type again: ";
				getline(cin, newPass2);
				if ((curPass == cur->dataStaf.password) && (newPass1 == newPass2))
				{
					cur->dataStaf.password = newPass1;
					cout << "--Success--" << endl;
					condition = true;
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
				}
			}
		}
		cur = cur->next;
	}
}
//Student
void ChangePasswordStudent(LinkedListStu& lst, string userid)
{
	int choice;
	string curPass;
	string newPass1, newPass2;
	nodeStu* cur = lst.head;
	bool condition = false;
	while (cur != NULL)
	{
		if (cur->dataStud.id == userid)
		{
			while (condition == false)
			{
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
				}
			}
		}
		cur = cur->next;
	}
}
void ViewProfileStudent(const LinkedListStu& lst, string userid)
{
	cout << "id " << userid << endl;
	cout << "Full name: ";
	nodestu* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataStu.id == userid)
		{
			cout << "Full name: " << cur->dataStu.fullname << endl;
			cout << " Gender:";
			if (cur->dataStu.sex == 1)
			{
				cout << "Female" << endl;
			}
			else
			{
				cout << "Male" << endl;
			}
			cout << "DoB:" << cur->dataStu.Dob << endl;
			cout << "Class: " << cur->dataStu.Class << endl;
		}
	}
}
//------------------------------------------------------------------------
//ViewListOfClass
nodeCla* createNodeCLass(Class cla) {
	nodeCla* temp = new nodeCla();
	temp->dataClas.classID = cla.classID;
	temp->next = NULL;
	return temp;
}
void ViewListOfClass(LinkedListCla& lst) 
{
	ifstream fi("Class.txt");
	lst.head = NULL;
	Class clas;
	fi >> lst.NumCla;
	getline(fi, clas.classID);
	getline(fi, clas.classID);
	nodeCla*temp=createNodeCLass(clas);
	lst.head = temp;
	nodeCla* cur = lst.head;
	for (int i = 0; i < lst.NumCla - 1; i++) {
		getline(fi, clas.classID);
		getline(fi, clas.classID);
		temp = createNodeCLass(clas);
		cur->next = temp;
		cur = cur->next;
	}
	cout << "Class: " << lst.NumCla << endl;
	cur = lst.head;
	while (cur != NULL) {
		cout<< cur->dataClas.classID << endl;
		cur = cur->next;
	}
}

//----------------------load and save class file--------------------------
bool LoadDataStudentFromClassFile(Class& cla)
{
	string pathfile = "Students-";
	ifstream fi;
	nodeStu* p;
	nodeStu* cur = cla.stu.head;
	Student stu;
	pathfile += cla.classID;
	fi.open(pathfile.c_str());
	if (!fi.is_open())
	{
		cout << "Can't open data file of class " << cla.classID << "!!!" << endl;
		return 0;
	}
	else
	{
		fi >> cla.stu.NumStu;
		getline(fi, stu.id);
		getline(fi, stu.password);
		getline(fi, stu.fullname);
		fi >> stu.year >> stu.month >> stu.day;
		fi >> stu.sex;
		fi >> stu.status;
		p = createNodeStudent(stu);
		cla.stu.head = p;
		for (int i = 0; i < cla.stu.NumStu - 1; i++)
		{
			getline(fi, stu.id);
			getline(fi, stu.password);
			getline(fi, stu.fullname);
			fi >> stu.year >> stu.month >> stu.day;
			fi >> stu.sex;
			fi >> stu.status;
			p = createNodeStudent(stu);
			cur->next = p;
			cur = cur->next;
		}
		fi.close();
		return 1;
	}

}

bool SaveDataClassFile(Class cla)
{
	ofstream fo;
	string pathfile = "Students-";
	nodeStu* cur = cla.stu.head;
	pathfile += cla.classID;
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
}
//----------------------Edit student from a class-----------------------------
void EditStudent(LinkedListCla& cla, LinkedListStu& stu)
{
	int choice;
	string newname, newmonth, newyear, newday;
	nodeStu* student;
	nodeStu* student2;//to update linked list from student.txt
	student = FindStuInClass(cla);
	if (student == NULL)
	{
		//back to main menu
	}
	else
	{
		//ViewProfileStudent;
		cout << "Do you want to edit this student?[Yes(1)/No(0)] :" << endl;
		cin >> choice;
		if (choice == 0)
		{
			//back to main menu
		}
		else
		{
			student2 = FindStu(stu, student->dataStud.id);
			cout << "Enter new name:";
			getline(cin, newname);
			cout << "Enter new date of birth[yy mm dd]" << endl;
			cin >> newyear >> newmonth >> newday;
			//update data linked list for Students-Idclass.txt
			student->dataStud.fullname = newname;
			student->dataStud.year = newyear;
			student->dataStud.month = newmonth;
			student->dataStud.day = newday;
			student->dataStud.password = CreatePwdStu(newyear, newmonth, newday);
			SaveDataClassFile(cla.head->dataClas);

			//update data linked list for Students.txt
			student2->dataStud.fullname = newname;
			student2->dataStud.year = newyear;
			student2->dataStud.month = newmonth;
			student2->dataStud.day = newday;
			student2->dataStud.password = student->dataStud.password;
			cout << "Successfull !!!(password has been reset)" << endl;

		}


	}
}

nodeStu* FindStuInClass(LinkedListCla& lst)
{
	int choice;
	string idstu;
	nodeCla* cur_cla = lst.head;
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
	} while (choice< lst.NumCla && choice !=0);
	if (choice ==0)
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

nodeStu* FindStu(LinkedListStu lst, string id)
{
	nodeStu* cur = lst.head;
	while (cur!=NULL)
	{
		if (cur->dataStud.id == id)
			return cur;
		cur = cur->next;
	}
	if (cur == NULL) return NULL;
}

//----------------------Remove Student from a class---------------------------
