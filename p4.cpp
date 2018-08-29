/**************************************************************************
Akeem Wilkins
CSC 372
Program Title: Program4
Description: Write a C++ object-oriented program to manage an I/O process 
list and a ready process list for an operating system. 
***************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <sstream>

using namespace std;

struct processNode
{
	unsigned int id;		//Process ID
	string name;			//Process name
	unsigned int runTime;	//Process Running Time
	void createProcess();	//Function to create a new process
};

struct tree_node;
typedef tree_node * tree_ptr;
struct tree_node
{
	tree_ptr left;
	processNode data;
	tree_ptr right;
};

class processes
{
public:

	void loadTree();						//Load process lists into list array
	void insertTree(tree_ptr &T, processNode item);	//Insert a process into a process list
	void insertProcess(processNode data);					//dummy function to call insertTree
	tree_ptr find_Min(tree_ptr T);					//Function finds smallest node in the tree
	void deleteNode(tree_ptr &T, int id);				//Delete a process from a process list
	void deleteProcess(int);
	void retrieveProcess(int);			//Retrieve and print an individual a process from a process list
	void retrieve(tree_ptr T, int ID);
	void printProcessTree();				//Prints a process from a process list
	processes();

private:

	void printTree(tree_ptr T) const;			//Prints processes of a list
	//tree_ptr find_Min(tree_ptr T);					//Function finds smallest node in the tree
	tree_ptr T;		//create a binary search tree of my class, T

};

processes::processes()
{
	T = NULL;		//set the T = to NULL, head pointer points no where
}

//tree_ptr &T is used to make sure we have the correct amount of arguments. 
void processes::insertTree(tree_ptr &T, processNode item)
{
		if(T==NULL) //if sub tree is empty
		{
			T = new tree_node; // this creating a new node to insert into the tree. 
			T->left = NULL;
			T->right = NULL;
			T->data = item;
		}
		else
		{
			if(item.id < T->data.id)
				insertTree(T->left,item);
			else
				insertTree(T->right, item);
		}
}

void processes::insertProcess(processNode data)
{
	insertTree(T,data);

}
void processes::loadTree()
{
	ifstream infile;
	string filename;

	//processType temp; // created a temp location
	processNode data;

	//Program asks user in main
	cin >> filename;

	infile.open(filename.c_str());
	while (!infile.eof())
	{
		//data = new processNode;
		infile >> data.id >> data.name >> data.runTime;	
		insertTree(T, data);
	}
	infile.close();
}

void processes::printTree(tree_ptr T) const
{
	if (T != NULL)
	{
		printTree(T->left);
		cout <<" ID: "<<T->data.id <<'\t'<<" Name: "<<T->data.name<<'\t'<<" Run Time: "<<T->data.runTime<<endl;
		printTree(T->right);
	}
}

void processes::printProcessTree()
{
		printTree(T);
		cout <<endl;
}

//Function finds smallest node in the tree
tree_ptr processes:: find_Min(tree_ptr T)
{
	if (T== NULL)
		return NULL;
	if (T->left == NULL)
		return T;
	return find_Min (T->left);
}

void processes::deleteProcess(int id)
{
	deleteNode(T, id);
}

void processes::deleteNode(tree_ptr &T, int ID)
{
	if (T == NULL)
   		return;
	if (ID < T->data.id)
		deleteNode(T->left, ID);
		else if (ID > T->data.id)
			deleteNode(T->right, ID);
		else if (T->left != NULL && T->right != NULL) //two children
		{	
			T->data.id = find_Min(T->right)->data.id; //find smallest on right and copies to root
			deleteNode(T->right, T->data.id); //delete that minimum value from the right sub-tree
		}
	else // node has one child or less
	{
		tree_ptr old_node = T;
		if (T->left != NULL)
			T = T->left;
		else
			T = T->right;
		delete old_node;
	}
}

void processes::retrieveProcess(int ID)
{
	retrieve(T, ID);
	cout<<endl;
}
void processes::retrieve(tree_ptr T, int ID)
{
		if(T->data.id == ID )
	{
		cout <<T->data.id <<'\t'<<T->data.name<<'\t'<<T->data.runTime<<endl;
	}
	else if(T->data.id < ID)
	{
		retrieve(T->right,ID);
	}	
	else 
	{
		retrieve(T->left,ID);
	}
}

void processNode::createProcess()
{
	int listOption;

	processNode p;					//Declare object of process
	
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
int main()
{
	processNode data;
	processes IO;			//Declare object for IO list
	processes Ready;			//Declare object for Ready list
	processNode newProcess;		//Declare object for new process to be created

	ifstream infile;
	int list = -1;				//Deterimines which process list

	char opCode = ' ';			//Initializing opcode variable

	srand (time(NULL));			//Initializes seed

	cout << "To begin, enter file name io.dat: " << endl;
	IO.loadTree();		//Load IO list file
	IO.printProcessTree();
	cout << "Now, enter the file name ready.dat: " << endl;
	Ready.loadTree();	//Load Ready list file
	Ready.printProcessTree();

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
			IO.insertProcess(data);
			cout << endl;
		}
		else if (list == 1)
		{
			cout << "Insert: " << "ID: "<< ID << "Name: " << name<< "Run Time: " << RunTime<< endl;
			Ready.insertProcess(data);
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
			IO.printProcessTree();
		}
		else if (list == 1)
		{
			Ready.printProcessTree();
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
