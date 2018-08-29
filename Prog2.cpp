/**************************************************************************
Akeem Wilkins
CSC 372
9/15/17
Program Title: Program2
Description: Convert program 1 so that it uses linked list instead of arrays.
There is no need to change the main function. You need to make adjustments to
the class and to re-write the function. 
***************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <sstream>

using namespace std;

struct processType; //allows definition of student ptr even though we do not 
					//define student here
typedef processType * processTypeptr; //Typedef creates an alias, node & *nodeptr is equivalent

struct processType
{
	unsigned int id;		//Process ID
	string name;			//Process name
	unsigned int runTime;	//Process Running Time
	void createProcess();	//Function to create a new process
	processTypeptr next;
};

class processes
{
public:
	void searchList(processTypeptr, int,
		processTypeptr &, processTypeptr &);
	void loadList();						//Load process lists into list array
	void insertList(int, string, int);		//Insert a process into a process list
	void deleteProcess(int);				//Delete a process from a process list
	void retrieveProcess(int);				//Retrieve and print an individual a process from a process list
	void printProcessList();			//Prints a proces from a process list
	processes();							// Default Constructor

private:
	processTypeptr processTypes;
	//processType * listptr;	
};

processes::processes()
{
	processTypeptr next = NULL;						//set the listptr = to NULL , head pointer points no where
}
void processes::loadList()
{
	ifstream infile;
	string filename;
	processTypes = NULL;

	//processType temp; // created a temp location
	processTypeptr temp_ptr;

	//cout << "Enter the file you wish to load: " << endl;		//Program asks user in main
	cin >> filename;

	infile.open(filename.c_str());
	while (!infile.eof())
	{
		temp_ptr = new processType;
		infile >> temp_ptr->id >> temp_ptr->name >> temp_ptr->runTime;
		temp_ptr->next = processTypes;
		processTypes = temp_ptr;
	}
	infile.close();

}

void processes::printProcessList()
{
	cout << "printing the list " << endl;
	//processTypes * p;
	for (processTypeptr p = processTypes; p != NULL; p = p->next)
		cout << "ID: " << p->id << " " << "Name: " << p->name << " " << "Run Time: " << p->runTime << endl;
}

void processes::searchList(processTypeptr head, int delProcess,
	processTypeptr & prev,
	processTypeptr & pos)
{
	bool done = false;
	pos = NULL;
	prev = NULL;
	for (processTypeptr p = head; (p != NULL) && (done == false);
		p = p->next)
	{
		if (delProcess == p->id)
		{
			done = true;
			pos = p;
		}
		else
		{
			prev = p;
			//p= p->next;
		}
	}
}

void processes::deleteProcess(int delProcess)
{
	processTypeptr prev;
	processTypeptr pos;
	searchList(this->processTypes, delProcess, prev, pos);

	if (prev == NULL)//no list
		processTypes = processTypes->next; //delete first node
	else if (pos == NULL) //no list
		prev->next = NULL; //delete last node
	else
	{
		prev->next = pos->next;
		delete pos;
	}
}
void processes::insertList(int tempID, string tempName, int tempRT)
{	
	processType * item;		// this creates a pointer of item type ProcessType
	item = new processType; // this and item that looks like the struct of processType and creates a new node

	item->id = tempID;			//Assign TempID to size.id location
	item->name = tempName;		//Assign tempName to tempName location
	item->runTime = tempRT;		//Assign tempRT to runTime location	
	
	item->next = processTypes;	// item points the next item in list, this is done first  before you point the header to
								// the new item. 
	processTypes = item;		// header gets the address of item so that the header is pointing at the new item that's
								//connected to the linked list. 
}
void processes::retrieveProcess(int retrieveID)
{
	
	for(processTypeptr p = processTypes; p != NULL; p = p->next)
	{
		if(retrieveID == p->id)		//Compare ID to be deleted with rest of list until found
			cout << "ID: " << p->id << " Name: " << p->name 
			     << " Run Time: " << p->runTime << endl;
	}
	cout << endl;
}
void processType::createProcess()
{
	int listOption;

	processType * p;					//Declared a pointer P of processType
	
	p = new processType;  // creating a new processType for each new random data
	
	//Create process ID
	p->id = rand() % 100;			//ID range 0 - 99

	//Create Process Name
	stringstream ss;
	ss << p->id;						//Convert ID to string
	string str = ss.str();
	p->name = 'p' + str;				//Concatenate p + string ID
	
	//Create Process Run Time
	p->runTime = rand () % 1000;		//Run Time range 0 - 999

	//Create list Option (I/O or Ready)
	listOption = rand() % 2;		//Range 0 - 1
	
	cout << "ID: " << p->id << " Name: " << p->name << " Run Time: " 
		 << p->runTime << " List " << listOption << endl;
}
int main()
{

	processes IO;			//Declare object for IO list
	processes Ready;			//Declare object for Ready list
	processType newProcess;		//Declare object for new process to be created

	int size;
	ifstream infile;
	int list = -1;				//Deterimines which process list

	char opCode = ' ';			//Initializing opcode variable

								//srand (time(NULL));			//Initializes seed

	cout << "To begin, enter file name io.dat: " << endl;
	IO.loadList();		//Load IO list file
	cout << "Now, enter the file name ready.dat: " << endl;
	Ready.loadList();	//Load Ready list file

	infile.open("process.DAT");		//Open Process File

	while (!infile.eof())
	{
		infile >> opCode;			//Reads in first character and saves into opcode

		if (opCode == 'i')
		{
			int ID, RunTime;
			string name;

			infile >> ID;
			infile >> name;
			infile >> RunTime;
			infile >> list;

			if (list == 0)
			{
				cout << "Insert: " << "ID: "<< ID << "Name: " << name<< "Run Time: " << RunTime<< endl;
				IO.insertList(ID, name, RunTime);
				cout << endl;
			}
			else if (list == 1)
			{
				cout << "Insert: " << "ID: "<< ID << "Name: " << name<< "Run Time: " << RunTime<< endl;
				Ready.insertList(ID, name, RunTime);
				cout << endl;
			}
		}

		else if (opCode == 'd')
		{
			int delCode;
			infile >> delCode;
			infile >> list;

			if (list == 0)
			{
				cout << "Delete Process ID: "<< delCode<<endl;
				IO.deleteProcess(delCode);
			}
			else if (list == 1)
			{
				cout << "Delete Process ID: "<< delCode<<endl;
				Ready.deleteProcess(delCode);
			}

		}

		else if(opCode == 'r')
		{
			int retrieve;
			infile >> retrieve;
			infile >> list;

			
				if(list == 0)
				{
					cout << "Retrieve: " << "ID: "<< retrieve<<endl;
					IO.retrieveProcess(retrieve);
				}
					else if(list == 1)
						{
							cout << "Retrieve: " << "ID: "<< retrieve<<endl;
							Ready.retrieveProcess(retrieve);
						}
		}

		else if (opCode == 'p')
		{
			infile >> list;

			if (list == 0)
			{
				IO.printProcessList();
			}
			else if (list == 1)
			{
				Ready.printProcessList();
			}
		}

				else if(opCode == 'c')
				
					{	
						cout << "Create Process" << endl;
						newProcess.createProcess();
					}
		opCode = ' ';		//Resets opcode to a space
	};

	system("pause");
	return 0;
}

