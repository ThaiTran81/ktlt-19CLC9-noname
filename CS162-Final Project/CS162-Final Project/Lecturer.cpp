#include"function.h"
//Creat Linked list lecturer
void PushNodeLecturer(nodeLec*& head, Lecturer new_data)
{
	nodeLec* new_node = new nodeLec;

	new_node->dataLec = new_data;
	new_node->next = head;
	head = new_node;
}
//Save Load Lecturer
void LoadDataLecturer(LinkedListLec& lst)
{
	lst.head = NULL;
	ifstream text;
	Lecturer lec;
	text.open("Lecturer.txt");
	if (!text.is_open())
	{
		cout << "can not open file" << endl;
	}
	else
	{
		text >> lst.numLec;
		if (lst.numLec == 0)
		{
			return;
		}
		else
		{
			for (int i = 0; i < lst.numLec; i++)
			{
				text >> lec.id;
				text >> lec.password;
				text.ignore();
				getline(text, lec.name);
				getline(text, lec.degree);
				text >> lec.sex;
				PushNodeLecturer(lst.head, lec);
			}
		}
		text.close();
	}
}
void SaveDataLecturer(LinkedListLec lst)
{
	ofstream text;
	text.open("Lecturer.txt");
	if (!text.is_open())
	{
		cout << "can not open file" << endl;
	}
	else
	{
		if (lst.head == NULL)
		{
			return;
		}
		nodeLec* cur = lst.head;
		text << lst.numLec << endl;
		while (cur != NULL)
		{
			text << cur->dataLec.id << endl;
			text << cur->dataLec.password << endl;
			text << cur->dataLec.name << endl;
			text << cur->dataLec.degree << endl;
			text << cur->dataLec.sex << endl;
			cur = cur->next;
		}
		text.close();
	}
}
//Delete Node Lecturer
void DeleteNodeLec(nodeLec*& head, string idLec)
{
	nodeLec* temp = head;
	nodeLec* prev = NULL;
	
	if (temp != NULL && temp->dataLec.id == idLec)
	{
		head = temp->next;   
		delete temp;               
		return;
	}
	while (temp != NULL && temp->dataLec.id != idLec)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return;
	else prev->next = temp->next;
	delete temp;  
}
//Change Password Lecturer
void ChangePasswordLecturer(LinkedListLec& lst, string userid)
{
	int choice;
	string curPass;
	string newPass1, newPass2;
	nodeLec* cur = lst.head;
	bool condition = false;
	while (cur != NULL && condition != true)
	{
		if (cur->dataLec.id == userid)
		{
			while (condition == false)
			{
				cout << "Current Password: ";
				getline(cin, curPass);
				cout << "New Password: ";
				getline(cin, newPass1);
				cout << "Type again: ";
				getline(cin, newPass2);
				if ((curPass == cur->dataLec.password) && (newPass1 == newPass2))
				{
					cur->dataLec.password = newPass1;
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
//View Profile Lecturer
void ViewProfileLecturer(LinkedListLec& lst, string userid)
{
	cout << "ID : " << userid << endl;
	nodeLec* cur = lst.head;
	while (cur != NULL)
	{
		if (cur->dataLec.id == userid)
		{
			cout << "Fullname: " << cur->dataLec.name << endl;
			cout << "Degree: " << cur->dataLec.degree << endl;
			cout << "Gender: ";
			if (cur->dataLec.sex == 1)
			{
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
// View all Lecturer
void ViewAllLecturer(LinkedListLec lst)
{
	if (lst.head == NULL)
	{
		cout << "Data Not Found" << endl;
		return;
	}
	int i = 1;
	nodeLec* cur = lst.head;
	cout << setw(33) << "|Lecturers List|" << endl;
	cout << setw(5) << "NO.";
	cout << setw(19) << "| Full name |";
	cout << setw(17) << "| Gender |";
	cout << setw(15) << "| Degree |" << endl;
	cout << "=========================================================" << endl;
	while (cur != NULL)
	{
		cout << setw(4) << i++<<".";
		cout << setw(21) << cur->dataLec.name;
		if (cur->dataLec.sex == 0)
			cout << setw(13) << "Male";
		else
			cout << setw(13) << "Female";
		cout << setw(15) << cur->dataLec.degree << endl;
		cur = cur->next;
	}
}
// DeleteLecturer
void DeleteLecturer(LinkedListLec& lst)
{
	string idlec;
	cout << "Enter id of lecturer which you want to delete:" << endl;
	getline(cin, idlec);
	nodeLec* temp1 = lst.head;
	nodeLec* temp2 = temp1->next;
	if (temp1->dataLec.id == idlec)
	{
		lst.numLec--;
		lst.head = temp1->next;
		delete temp1;
		return;
	}
	while (temp2 != NULL)
	{
		if (temp2->dataLec.id == idlec)
		{
			lst.numLec--;
			temp1->next = temp2->next;
			delete temp2;
			return;
		}
		else {
			temp1 = temp2;
			temp2 = temp2->next;
		}
	}
}
//Create new lecturer
void CreateLecturer(LinkedListLec& lst)
{
	string id;
	string password;
	string name;
	string degree;
	bool sex;
	lst.numLec++;
	cout << "Enter id of lecturer" << endl;
	getline(cin, id);
	cout << "Enter password of lecturer" << endl;
	getline(cin, password);
	cout << "Enter name of lecturer" << endl;
	getline(cin, name);
	cout << "Enter degree of lecturer" << endl;
	getline(cin, degree);
	cin.ignore();
	cout << "Enter sex of lecturer" << endl;
	cin >> sex;
	nodeLec* temp = new nodeLec();
	temp->dataLec.id = id;
	temp->dataLec.password = password;
	temp->dataLec.name = name;
	temp->dataLec.degree = degree;
	temp->dataLec.sex = sex;
	temp->next = lst.head;
	lst.head = temp;
}

//Find lecturer in linked list
nodeLec* FindLecturer(LinkedListLec lst, string id)
{
	nodeLec* cur = lst.head;
	while (cur!=NULL)
	{
		if (cur->dataLec.id == id)
			return cur;
		cur = cur->next;
	}
	return NULL;
}


