#include"function.h"
//             SAVE, LOAD STAFF             //
nodeSta* createNodeStaff(Staff staf)
{
	nodeSta* p = new nodeSta;
	p->dataStaf.id = staf.id;
	p->dataStaf.password = staf.password;
	p->dataStaf.fullname = staf.fullname;
	p->dataStaf.typeMenu = staf.typeMenu;
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
		fi >> staf.typeMenu;
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
			fi >> staf.typeMenu;
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
	fo << lst.NumSta;
	while (cur != NULL)
	{
		fo << cur->dataStaf.id << endl;
		fo << cur->dataStaf.password << endl;
		fo << cur->dataStaf.fullname << endl;
		fo << cur->dataStaf.typeMenu << endl;
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
	p->dataStud.typeMenu = stud.typeMenu;
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
		fi >> stud.year>> stud.month>> stud.day;
		fi >> stud.classId;
		fi >> stud.sex;
		fi >> stud.typeMenu;
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
			fi >> stud.typeMenu;
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
	fo <<lst.NumStu;
	while (cur != NULL) {
		fo << cur->dataStud.id << endl;
		fo << cur->dataStud.password << endl;
		fo << cur->dataStud.fullname << endl;
		fo << cur->dataStud.year << " " << cur->dataStud.month << " " << cur->dataStud.day << endl;
		fo << cur->dataStud.classId << endl;
		fo << cur->dataStud.sex << endl;
		fo << cur->dataStud.typeMenu << endl;
	}
	return true;
}



