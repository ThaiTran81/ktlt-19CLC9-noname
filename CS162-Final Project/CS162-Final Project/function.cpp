#include"function.h"

// Login
bool Login(User& user, LinkedListSta lstSta, LinkedListStu lstStu, LinkedListLec lstLec)
{
	cout << "-------------LOGIN-------------" << endl;
	cout << "Id: ";
	cin >> user.id;
	cout << "Password: ";
	cin >> user.password;
	nodeSta* curSta = lstSta.head;
	nodeStu* curStu = lstStu.head;
	nodeLec* curLec = lstLec.head;
	while (curSta!=NULL)
	{
		if (curSta->dataStaf.id == user.id && curSta->dataStaf.password==user.password)
		{
			user.name = curSta->dataStaf.fullname;
			user.sex = curSta->dataStaf.sex;
			cout << "SUCCESSFUL!!!!" << endl;
			return 1;
		}
		curSta = curSta->next;
	}
	while (curStu != NULL)
	{
		if (curStu->dataStud.id == user.id && curStu->dataStud.password == user.password)
		{
			user.name = curStu->dataStud.fullname;
			user.sex = curStu->dataStud.sex;
			cout << "SUCCESSFUL!!!!" << endl;
			return 1;
		}
		curStu = curStu->next;
	}
	while (curLec!=NULL)
	{
		if (curLec->dataLec.id == user.id && curLec->dataLec.password == user.password)
		{
			user.name = curLec->dataLec.name;
			user.sex = curLec->dataLec.sex;
			cout << "SUCCESSFUL!!!!" << endl;
			return 1;
		}
	}
	cout << "Invalid login, please try again" << endl;
	return 0;
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
