/***********************************************************************
Akeem Wilkins
CSC 372
9/20/17
Program: TO manage an I/O process list and a ready process list for an
operating system. 
***********************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct parts
{
	int id;
	string name;
	int runningTime;
};

class process
{
	private:
		parts processArray[200];
		int size;
		void printProcess();
	public:
		process ();
		void load();
		void retrieve(int ID);
		void create();
		void insert(int id, string name, int runninTime);
		void deletep(int ID);
		void printList();	
};

process::process()
{
	size = 0;
}
void process::load()
{
	string file_name;
	
		cin >> file_name;
		cout << endl;
		
		ifstream infile(file_name.c_str());
		size = 0;
		
		while (!infile.eof())
		{
			infile >> processArray[size].id;
			infile >> processArray[size].name;
			infile >> processArray[size].runningTime;
			size ++;
		}
		infile.close(); //Close file after loop so reads all the entries
}
void process::retrieve(int ID)
{
	bool found = false;
	int pos;
	int i;
	
	pos=-1;
	
	if (found == false)
	{
		cout<<endl;
	}
		
	else
	{	
		for (int i = pos ; i < size-1; i++)
		{
			found = true;
			pos = i;	
		}	
	}		
}
void process::create()
{
	/*you have to ask the user to input a ID number also ask the user to input 0 or 1 to determine what list the ID number is subject to
	int ID;
	int number;
	
	cout << "Please enter an ID number:";
	cin >> ID ;
	cout << endl;
	cout << " Please enter number 0 or 1 to determine the list desired: ";
	cin >> number;
	cout << endl;*/
}
void process::insert(int id, string name, int runningTime)
{
	cout << "This is the insert function. " << endl;
	processArray[size].id= id;
	processArray[size].name = name;
	processArray[size].runningTime = runningTime;
	size++;
}
void process::deletep(int ID)
{
	bool found = false;
	int pos;

	//search operations
		pos = -1; //starts at -1 because the array starts at 0.
	
	for (int i = 0; i < size; i++)
	{
		// id number will compare to the
		if (processArray[i].id == ID) // the processArray[i].id is the struct we made earlier comparing to the ID which we grabbed from inside Main.
		{
			found = true;
			pos = i;//this is the position of the data
		}
	}
	//delete operations
	if (found == false)
		cout <<" Does not exist" << endl;
	else
	{
		//deletion process this will overwrite that number or data. 
		for (int i = pos ; i < size-1; i++)
			processArray[i] = processArray[i+1];
		size--;
	}
}
void process::printList()
{
	for (int i = 0; i < size; i++)
	{
		cout << endl;
		cout << "ID: " << processArray[i].id << endl;
		cout << "Name: " << processArray[i].name << endl;
		cout << "Running Time: " << processArray[i].runningTime << endl;
	}
}

int main()
{		//delcaring the titles of the functions to a variables. To compare the code infile to complete the function operations
		char insert = 'i';
		char deletep = 'd';
		char retrieve = 'r';
		char print = 'p';
		char code = ' ';
		int list;
		
		
		process io; //objects for class
		process ready; //objects for class
	
	//ask the user to input the file name, then	
	cout << "Enter file name of io.dat : ";
	
		io.load();
			
	cout << "Enter file name of ready.dat : ";
		ready.load();
	
	ifstream infile;
		infile.open("process.dat");
		while (!infile.eof())
		{
			infile >> code;
		
		if(code == insert)
			{
				//delcare
				int id;
				string name;
				int runningTime;
				
				infile >> id;
				infile >> name;
				infile >> runningTime;
				infile >> list;
				if(list == 0)
				{
				 	io.insert(id, name, runningTime);
				 	io.printList();
				}
				else if (list ==1)
				{
					ready.insert(id, name, runningTime);
					ready.printList();
				}
			}
			else if (code == deletep)
			{
				int ID;
				//grabs the id number
				infile >> ID;
				infile >> list;
				//goes into desired list, then calls delete function
					if(list == 0)
				{
				 	io.deletep(ID);
				 	io.printList();
				}
				else if (list ==1)
				{
					ready.deletep(ID);
					ready.printList();
				}
				
			}
			else if (code == retrieve)
			{
				int ID;
				//grabs the id number
				infile >> ID;
				infile >> list;
				//goes into desired list, then calls delete function
				
					if(list == 0)
				{
				 	io.retrieve(ID);
				}
				else if (list ==1)
				{
					ready.retrieve(ID);
				}
			}
			else if (code== print)
			{
				if(list ==0)
				{
					io.printList();
					cout << "This is the print I/O List: " << endl;
				}
				else if (list ==1)
				{
					ready.printList();
					cout << "This is the print Ready List: " << endl;
				}
			}
		}
			
	infile.close();	
}
