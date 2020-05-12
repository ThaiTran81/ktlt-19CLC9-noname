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
			text >> lec.id;
			text >> lec.password;
			text.ignore();
			getline(text, lec.name);
			getline(text, lec.name);
			getline(text, lec.degree);
			getline(text, lec.degree);
			text >> lec.sex;
			PushNodeLecturer(lst.head, lec);
			for (int i = 0; i < lst.numLec - 1; i++)
			{
				text >> lec.id;
				text >> lec.password;
				text.ignore();
				getline(text, lec.name);
				getline(text, lec.name);
				getline(text, lec.degree);
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
	lst.head = NULL;
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
		}
		text.close();
	}
}