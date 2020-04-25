#include"function.h"
//             SAVE, LOAD STAFF             //
nodeSta* createNodeStaff(Staff x)
{
	nodeSta* p = new nodeSta;
	p->dataStaf.id = x.id;
	p->dataStaf.password = x.password;
	p->dataStaf.fullname = x.fullname;
	p->dataStaf.typeMenu = x.typeMenu;
	p->dataStaf.sex = x.sex;
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
