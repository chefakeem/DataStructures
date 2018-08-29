/**************************************************************************
*********
Akeem Wilkins
CSC 372
9/15/17
Program Title: Program 3
Description: Convert program 1 so that is uses STL instead of arrays.
There is no need to change the main function. You need to make adjustments to
the class and to re-write the function.
***************************************************************************/

#include <iostream>
using namespace std;

#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <list>
#include <algorithm>

struct processType
{
	unsigned int id;		//Process ID
	string name;			//Process name
	unsigned int runTime;	//Process Running Time	
	void createProcess();	//Function to create a new process
	
	bool operator == (const processType& p)
	  {
        if (id== p.id)
           return true;
        else
            return false;
       } 
	
};
typedef list<processType> processType_list;
typedef processType_list:: iterator list_it;

class processes
{
public:
	//void searchList(processTypeptr, int,processTypeptr &, processTypeptr &);
	void loadList();						//Load process lists into list array
	void insertList(int, string, int);		//Insert a process into a process list
	void deleteProcess(int);				//Delete a process from a process list
	void retrieveProcess(int);				//Retrieve and print an individual a process from a process list
	void printProcessList();			//Prints a proces from a process list

private:
	processType_list listProcess; 		// name of your STL list	
};
void processes::loadList()
{
	ifstream infile;
	string filename;

	processType temp; // created a temp location
	//processTypeptr temp_ptr;

	//cout << "Enter the file you wish to load: " << endl;		//Program asks user in main
	cin >> filename;

	infile.open(filename.c_str());
	while (!infile.eof())
	{
		infile >> temp.id >> temp.name >> temp.runTime;
		listProcess.push_back(temp);
	}
	infile.close();
}
void processes::printProcessList()
{
	processType_list processTypes;
	cout << "printing the list " <<endl;
	
	for (list_it p  = listProcess.begin();  p != listProcess.end(); p++)
		cout << "ID:"<< p->id<<"  "<<"Name:"<<p->name<<"  "<<"RunTime: "<<p->runTime<<" " <<endl;
}
void processes::insertList(int tempID, string tempName, int tempRT)
{
	processType temp_ptr;
	
	temp_ptr.id = tempID;			//Assign TempID to id location
	temp_ptr.name = tempName;		//Assign tempName to tempName location
	temp_ptr.runTime = tempRT;		//Assign tempRT to runTime location
	listProcess.push_front(temp_ptr);
}
void processes::retrieveProcess(int retrieveID)
{
	
	for(list_it p =listProcess.begin(); p != listProcess.end(); p++)
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

	processType p;					//Declared a pointer P of processType
	
	//Create process ID
	p.id = rand() % 100;			//ID range 0 - 99

	//Create Process Name
	stringstream ss;
	ss << p.id;						//Convert ID to string
	string str = ss.str();
	p.name = 'p' + str;				//Concatenate p + string ID
	
	//Create Process Run Time
	p.runTime = rand () % 1000;		//Run Time range 0 - 999

	//Create list Option (I/O or Ready)
	listOption = rand() % 2;		//Range 0 - 1
	
	cout << "ID: " << p.id << " Name: " << p.name << " Run Time: " 
		 << p.runTime << " List " << listOption << endl;
}
void processes::deleteProcess(int tempDelCode)
{
	processType temp_Ptr;	     	//create a node that looks like processType
	temp_Ptr.id = tempDelCode;     //temp.id gets access of the id that is being passed
	listProcess.remove(temp_Ptr);	//call the name of your list to get access of 
								//of the remove function to remove the temp variable
								//that was passed from main.  
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
