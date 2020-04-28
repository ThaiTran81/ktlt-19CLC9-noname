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
	fi.ignore();
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