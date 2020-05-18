#include"function.h"
//             SAVE, LOAD STAFF             //
nodeSta* createNodeStaff(Staff staf)
{
	nodeSta* p = new nodeSta;
	p->dataStaf.id = staf.id;
	p->dataStaf.password = staf.password;
	p->dataStaf.fullname = staf.fullname;
	p->dataStaf.sex = staf.sex;
	p->next = NULL;
	return p;
}
bool LoadDataStaff(ifstream& fi, LinkedListSta& lst)
{
	lst.head = NULL;
	Staff staf;
	fi >> lst.NumSta;
	if (!fi.is_open())
	{
		cout << "can't open staff file " << endl;
		return false;
	}
	else
	{
		if (lst.NumSta == 0)
		{
			return false;
		}
		else
		{
			fi >> staf.id;
			fi >> staf.password;
			fi.ignore();
			getline(fi, staf.fullname);
			fi >> staf.sex;
			nodeSta* p = createNodeStaff(staf);
			lst.head = p;
			nodeSta* cur = lst.head;
			for (int i = 0; i < lst.NumSta - 1; i++)
			{
				fi >> staf.id;
				fi >> staf.password;
				fi.ignore();
				getline(fi, staf.fullname);
				fi >> staf.sex;
				p = createNodeStaff(staf);
				cur->next = p;
				cur = cur->next;
			}
			fi.close();
			return true;
		}
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
	fo.close();
	return true;
}

// view profile staff
void ViewProfileStaff(const LinkedListSta& lst, string userid)
{
	cout << "id: " << userid << endl;
	nodeSta* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataStaf.id == userid)
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

//-------------------Doi mat khau---------------------------
//Staff
void ChangePasswordStaff(LinkedListSta& lst, string userid)
{
	int choice;
	string curPass;
	string newPass1, newPass2;
	nodeSta* cur = lst.head;
	bool condition = false;
	while (cur != NULL && condition != true)
	{
		if (cur->dataStaf.id == userid)
		{
			while (condition == false)
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
					cin.ignore();
				}
			}
		}
		cur = cur->next;
	}
}
//View All Staff
void ViewAllStaff(LinkedListSta lst)
{
	if (lst.head == NULL)
	{
		cout << "Data Not Found" << endl;
		return;
	}
	int i = 1;
	nodeSta* cur = lst.head;
	cout << setw(28) << "*Staff List*" << endl;
	cout << setw(5) << "NO.";
	cout << setw(20) << "| Full name |";
	cout << setw(17) << "| Gender |" << endl;
	cout << "=============================================" << endl;
	while (cur != NULL)
	{
		cout << setw(4) << i++ << ".";
		cout << setw(22) << cur->dataStaf.fullname;
		if (cur->dataStaf.sex == 0)
			cout << setw(13) << "Male";
		else
			cout << setw(13) << "Female";
		cout << endl;
		cur = cur->next;
	}
}
