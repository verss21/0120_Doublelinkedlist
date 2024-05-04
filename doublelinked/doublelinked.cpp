#include <iostream>
using namespace std;

struct Node
{
	int noMhs;
	string name;
	Node* next;
	Node* prev;
};

Node* START = NULL;

void addNode()
{
	Node* newNode = new Node(); // step 1: create a new node
	cout << "\nEnter the roll number of the student: ";
	cin >> newNode->noMhs; // Assign value to the data field of the new node
	cout << "\nEnter the name of the student: ";
	cin >> newNode->name; // Assign value to the data field of the new node

	//Insert the new node in the list
	if (START == NULL || newNode->noMhs <= START->noMhs)
	{ // step 2 : insert the new node at the beginning
		if (START != NULL && newNode->noMhs == START->noMhs)
		{
			cout << "\033[31mDuplicate roll numbers not allowed\033[0m" << endl;
			return;
		}
		// If the list is empty, make the new node the START
		newNode->next = START; // step 3 : make the new node point to the first node
		if (START != NULL)
		{
			START->prev = newNode; // step 4 : make the first node point to the new node
		}
		newNode->prev = NULL; // step 5 : make the new node point to NULL
		START = newNode; // step 6 : make the new node the first node
	}
	else
	{
		// insert the new node in the middle or at the end
		Node* current = START; // step 1.a : start from the first node
		Node* previous = NULL; // step 1.b : previous node is NULL initially

		while (current != NULL && current->noMhs < newNode->noMhs)
		{						// step 1.c : traverse the list to find the correct position
			previous = current; // step 1.d : move the previous to the current node
			current = current->next; // step 1.e : move the current to the next node
		}
		newNode->next = current; // step 4 : Make the next field of the new node point to current
		newNode->prev = previous; // step 5 : Make the previous field of the new node point to previous

		if (current != NULL)
		{
			current->prev = newNode; // step 6 : Make the previous field of the current node point to the new node

		}
		if (previous != NULL)
		{
			previous->next = newNode; // step 7 Make the next field of the previous node point to the new node
		}
		else
		{
			// If previous is still NULL, it means newNode is now the first node
			START = newNode;
		}
	}
}

bool search(int rollNo, Node** previous, Node** current)
{
	*previous = NULL;
	*current = START;
	while (*current != NULL && (*current)->noMhs != rollNo)
	{
		*previous = *current;
		*current = (*current)->next;
	}
	return (*current != NULL);
}

void deleteNode()
{
	Node* previous, * current;
	int rollNo;

	cout << "\nEnter the roll number of the student whose record is to be deleted : ";
	cin >> rollNo; // step 3 : get the roll number to be deleted

	if (START == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}

	current = START; // step 1 : start from the forst node
	previous = NULL;

	// Locate the node to be deleted
	while (current != NULL && current->noMhs != rollNo)
	{
		previous = current;
		current = current->next;
	}
	if (current == NULL)
	{
		cout << "\033[31mThe record with roll number" << rollNo << "not found\033[0m" << endl;
		return;
	}

	// Node to be deleted is the first node
	if (current == START)
	{
		START = START->next; // step 2 : update the START pointer
		if (START != NULL)
		{
			START->prev = NULL;
		}
	}
	else
	{
		// Node to be deleted is not the first node
		previous->next = current->next;
		if (current->next != NULL)
			// If there's a successor, update its prev pointer
			current->next->prev = previous;
	}
}
// Release the memory of the node marked as current
void deleteCurrentNode(Node* current, int rollNo) {
	delete current;
	cout << "\x1b[32mRecord with roll number " << rollNo << " deleted\x1b[0m " << endl;
}

bool listEmpty()
{
	return (START == NULL);
}

void traverse() {
	if (listEmpty())
		cout << "\nList is empty" << endl;
	else {
		cout << "\nRecords in ascending order of roll number are : " << endl;
		Node* currentNode = START; // step 1
		while (currentNode != NULL) // step 2
		{
			cout << currentNode->noMhs << " " << currentNode->name << endl; // step 3
			currentNode = currentNode->next; // next 4
		}
	}
}

void revtraverse() {
	if (listEmpty())
		cout << "\nList is empty" << endl;
	else {
		cout << "\nRecords in descending order of roll number are : " << endl;
		Node* currentNode = START;
		while (currentNode->next != NULL)
			currentNode = currentNode->next;

		while (currentNode != NULL)
		{
			cout << currentNode->noMhs << " " << currentNode->name << endl;
			currentNode = currentNode->prev;
		}
	}
}

void searchData() {
	if (listEmpty() == true)
	{
		cout << "\nList is empty" << endl;
	}
	Node* prev, * curr;
	prev = curr = NULL;
	cout << "\nEnter the roll number of the student whose record you want to search:";
	int num;
	cin >> num;
	if (search(num, &prev, &curr) == false)
		cout << "\nRecord not found" << endl;
	else {
		cout << "\nRecord found" << endl;
		cout << "\nRoll number : " << curr->noMhs << endl;
		cout << "\nName : " << curr->name << endl;
	}
}

int main()
{
	while (true)
	{
		try
		{
			cout << "\nMenu" << endl;
			cout << "1. Add a record to the list" << endl;
			cout << "2. Delete a record from the list" << endl;
			cout << "3. View all records in the ascending order of roll numbers" << endl;
			cout << "4. View all records in the descending order of roll numbers" << endl;
			cout << "5. Search for a record in the list" << endl;
			cout << "6. Exit" << endl;
			cout << "\nEnter your choice (1-6) : ";
			char ch;
			cin >> ch;

			switch (ch) {
			case '1':
				addNode();
				break;
			case '2':
				deleteNode();
				break;
			case '3':
				traverse();
				break;
			case '4':
				revtraverse();
				break;
			case '5':
				searchData();
				break;
			case '6':
				return 0;
			default:
				cout << "\nInvalid option" << endl;
				break;
			}
		}
		catch (exception& e)
		{
			cout << "Check for the values entered." << endl;
		}
	}
}