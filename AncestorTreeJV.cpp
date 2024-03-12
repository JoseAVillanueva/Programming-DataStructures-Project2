//Name: Jose Villanueva Vigil
//Course: COSC 2436
//Program set 3, problem 3 (AncestorTree)
//References: I used the PDF covering program set 3
//=================================================================================

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

//this is the GeneralTree class and this class is used to
//create the general tree that will be utilized throughout the program 
class GeneralTree
{
private:

	//a struct with the data type of TreeNode is declared here
	//it contains an integer variable (value) and a vector 
	//with the data type of TreeNode pointers (child)
	struct TreeNode
	{
		int value = 0;
		vector <TreeNode* >child;
	};

	//the varibale with the data type of TreeNode pointer is assigned the nullptr value (root)
	TreeNode* root = nullptr;

	//these are private out-of-line member functions
	//more information regarding these functions can be found below the 
	//GeneralTree class (this class)
	void targetInsert(TreeNode*&, TreeNode*&, int);
	void firstInsert(TreeNode*&, TreeNode*&);
	void destroySubTree(TreeNode*);

public:
	//the default constructor assigns the root variable the nullptr value
	GeneralTree()
	{
		root = nullptr;
	}

	//the deconstructor calls the destroySubTree function, passing the root as its argument
	~GeneralTree()
	{
		destroySubTree(root);
	}
	
	//these are public out-of-line member functions
	//more information regarding these functions can be found below the 
	//GeneralTree class (this class)
	void insertNode(int, int);
	void insert(int);
	void displayLeafs(int&);
	void clearTree();
};

//this is the out-of-line function, firstInsert, and this is used to insert 
//the first node (within the tree) at the root's position (root is assigned the value of the node)
//two TreeNode pointers are passed by reference within its parameter list (nodePtr and newNode)
void GeneralTree::firstInsert(TreeNode*& nodePtr, TreeNode*& newNode)
{
	//if the value of nodePtr is nullptr, then it is assigned the value of newNode
	if (nodePtr == nullptr)
	{
		nodePtr = newNode;
	}
}

//this is the out-of-line function, targetInsert, and this is used to insert 
//TreeNodes into the general tree
//two TreeNode pointers are passed by reference within its parameter list (nodePtr and newNode)
//an integer is passed within its parameter list (tar) 
void GeneralTree::targetInsert(TreeNode*& nodePtr, TreeNode*& newNode, int tar)
{
		//creating a queue here to store and move through the general tree
		//searching through all of the children to find an equivalent target value 
		queue<TreeNode*> target;
		target.push(root);
		
		//while the target is not empty, this loop will continue to iterate
		while (!(target.empty()))
		{
			int size = static_cast<int>(target.size());

			//the for loop is used to move through the target queue
			for (int index = 0; index < size; index++)
			{
				//a new node is created and it will hold the value of the first node in the queue
				TreeNode* temp = target.front();
				target.pop();

				//if the traget value is equal to the temp's value
				//then the new node is added to the temp's child vector list
				//and the queue is cleared, size is also set to its max value
				if (tar == temp->value)
				{
					temp->child.push_back(newNode);

					for (int index2 = 0; index2 < target.size(); index2++)
					{
						target.pop();
						index++;
					}
				}

				//else, all the child nodes within the vector are pushed into the queue
				//and the entire loop will repeat until no node can be found
				else
				{
					for (int index2 = 0; index2 < temp->child.size(); index2++)
					{
						target.push(temp->child[index2]);
					}
				}
			}
		}
}

//this is the out-of-line function, insertNode, and this is used to create a newNode.
//It will also call the targetInsert function to insert the newNode into the general tree
//two integers are passed within its parameter list (num and target)
void GeneralTree::insertNode(int num, int target)
{
	//a new TreeNode is created and its value member is assigned to num
	//the targetInsert function is called and passes root, newNode, and target as its arguments 
	TreeNode* newNode = nullptr;
	newNode = new TreeNode;
	newNode->value = num;
	targetInsert(root, newNode, target);
}

//this is the out-of-line function, insert, this function is almost identical to the
//insertNode function, except this is used to insert the first (root) node into the general tree
//an integer is passed within its parameter list (num)
void GeneralTree::insert(int num)
{
	//a new TreeNode is created and its value member is assigned to num
	//the firstInsert function is called and passes root and newNode 
	TreeNode* newNode = nullptr;
	newNode = new TreeNode;
	newNode->value = num;
	firstInsert(root, newNode);
}

//this is the out-of-line function, destroySubTree,and this is used to destroy the GeneralTree 
//that was/is created through the duration of the program  
//a TreeNode pointer is passed within its parameter list (nodePtr)
void GeneralTree::destroySubTree(TreeNode* nodePtr)
{

	//if nodePtr holds an address, then the following statements are executed 
	if (nodePtr)
	{
		//a queue with the data type of TreeNode pointers is created (temp)
		//and the address of nodePtr is pushed into the queue
		queue<TreeNode*> temp;
		temp.push(nodePtr);

		//the while loop will continue to iterate until the temp queue is empty
		while (!(temp.empty()))
		{
			//an integer is initalized with the amount of elements within the temp queue (size)
			int size = static_cast<int>(temp.size());

			//while the index is less than the size, it will iterate
			for (int index = 0; index < size; index++)
			{
				//new node is created to hold the address of the front node in the queue
				//the front node is then popped off of the queue
				TreeNode* temp2 = temp.front();
				temp.pop();

				//while index2 is less than the size of the child vector, it will queue
				//the elements of the child vector into the queue
				for (int index2 = 0; index2 < temp2->child.size(); index2++)
				{
					temp.push(temp2->child[index2]);
				}

				//once all of the children have been queued, the clear function
				//from the vector STL, is used to clear the vector and temp2 is deleted
				temp2->child.clear();
				delete temp2;
			}
		}
	}
}

//this is the out-of-line function, clearTree, and this is similiar to the destorySubTree function 
//except it clears all of the elements within a general tree and destroys its subTrees
void GeneralTree::clearTree()
{
	//if the root pointer contains an address, then the following statements are executed 
	if (root)
	{
		//a queue with the data type of TreeNode pointers is created (temp)
		//and the address of root is pushed into the queue
		queue<TreeNode*> temp;
		temp.push(root);

		//the while loop will continue to iterate until the temp queue is empty
		while (!(temp.empty()))
		{
			//an integer is initalized with the amount of elements within the temp queue (size)
			int size = static_cast<int>(temp.size());

			//while the index is less than the size, it will iterate
			for (int index = 0; index < size; index++)
			{
				//new node is created to hold the address of the front node in the queue
				//the front node is then popped off of the queue
				TreeNode* temp2 = temp.front();
				temp.pop();

				//while index2 is less than the size of the child vector, it will queue
				//the elements of the child vector into the queue
				for (int index2 = 0; index2 < temp2->child.size(); index2++)
				{
					temp.push(temp2->child[index2]);
				}

				//once all of the children have been queued, the clear function
				//from the vector STL, is used to clear the vector and temp2 is deleted  
				temp2->child.clear();
				delete temp2;
			}
		}

		//the root pointer is set to nullptr
		root = nullptr;
	}
}

//this is the out-of-line function, displayLeafs, and this is used to gather and display the nodes
//within the general tree, that contain no child (children) nodes
//an integer is passed by reference within its parameter list (num)
void GeneralTree::displayLeafs(int& num)
{
	//a queue with the data type of TreeNode pointers is created (temp)
	//and the address of root is pushed into the queue
	//an integer is initalized with the value of 0 (none), this 
	//variable will be used to track the number of childless nodes
	queue<TreeNode*> temp;
	temp.push(root);
	int none = 0;

	//the while loop will continue to iterate until the temp queue is empty
	while (!(temp.empty()))
	{
		//an integer is initalized with the amount of elements within the temp queue (size)
		int size = static_cast<int>(temp.size());

		//while the index is less than the size, it will iterate
		for (int index = 0; index < size; index++)
		{
			//new node is created to hold the address of the front node in the queue
			//the front node is then popped off of the queue
			TreeNode* temp2 = temp.front();
			temp.pop();

			//while index2 is less than the size of the child vector, it will queue
			//the elements of the child vector into the queue
			for (int index2 = 0; index2 < temp2->child.size(); index2++)
			{
				temp.push(temp2->child[index2]);
			}
			
			//if the node contains no children (its child vector is empty)
			//then its value is displayed and none is incremented 
			if (temp2->child.empty())
			{
				cout << temp2->value << " ";
				none++;
			}
		}
	}

	//none is set to equal the value of the none variable 
	num = none;
}

string fileName;
ifstream inputFile;
char caseCheck = 'Y';

int main()
{
	//a new instance of the GeneralTree class is created (tempTree)
	GeneralTree tempTree;

	int tempNum = 0;
	int targetNum = 0;
	int subNum = 0;

	//the while loop will continue to iterate until the value of caseCheck is 'N'
	while (caseCheck != 'N')
	{
		//user input is gathered here using the getline function
		cout << "Enter file name: ";
		getline(cin, fileName);

		//the file is opened here
		inputFile.open(fileName);

		//if the file is not opened susseccfully, then an error message is displayed 
		if (inputFile.fail())
		{
			cout << "Something went wrong, try again.\n";
		}
		//otherwise, the following statements are executed 
		else
		{
			cout << " " << endl;
			int caseTrack = 0;
			int numCases = 0;
			int numNodes = 0;
			int num = 0;

			//the amount of cases within the file is gathered here
			inputFile >> numCases;
			
			//the while loop will continue to iterate until the
			//caseTrack variable equals the numCases variable  
			while (caseTrack != numCases)
			{
				//the number of nodes within the cases are collected here
				//along with the parent(targetNum) and child(subNum) node 
				inputFile >> numNodes;
				inputFile >> targetNum;
				inputFile >> subNum;

				//the tempNum variable is increased by (+2)
				//this indicates that two nodes were added
				tempNum += 2;

				//the targetNum is inserted into the tempTree using the insert function
				//the subNum is inserted into the tempTree using the insertNode function 
				//with targetNum being its parent 
				tempTree.insert(targetNum);
				tempTree.insertNode(subNum, targetNum);

				//the while loop will continue to iterate until the tempNum variable equals 
				//the numNodes variable
				while (tempNum != numNodes)
				{
					//the targetNum and subNum variables are collected here
					inputFile >> targetNum;
					inputFile >> subNum;

					//the subNum is inserted into the tempTree using the insertNode function 
					//with targetNum being its parent and tempNum is incremented by (+1) 
					tempTree.insertNode(subNum, targetNum);
					tempNum++;
				}

				//the displayLeafs function (of tempTree) is called here
				cout << "F" << (caseTrack + 1) << ": ";
				tempTree.displayLeafs(num);

				//if the value of num is equal to one, the following message is printed
				if (num == 1)
				{
					cout << "has no children" << endl;
				}
				//otherwise, this message is printed 
				else
				{
					cout << "have no children" << endl;
				}
				//the clearTree function (of tempTree) is called here 
				//to clear the elements within the tempTree
				tempTree.clearTree();

				//tempNum, numNodes, and num are set to equal zero (0)
				//and the caseTrack variable is incremented by one (+1)
				tempNum = 0;
				numNodes = 0;
				num = 0;
				caseTrack++;
			}
		}

		//the file is closed 
		cout << " " << endl;
		inputFile.close();

		//the user is then asked if they would like to run the program again
		cout << "Run again (Y/N): ";
		cin >> caseCheck;
		cout << endl;
		caseCheck = toupper(caseCheck);

		//the while loop will continue to iterate until a valid input is made
		while (caseCheck != 'Y' && caseCheck != 'N')
		{
			cout << "an invalid selection was made, try again\n";
			cout << "Run again (Y/N): ";
			cin >> caseCheck;
			caseCheck = toupper(caseCheck);
			cout << endl;
		}

		//this is here to remove the buffer character, to allow
		//the getline string to get the fileName in the intial 
		//process
		cin.ignore(1, '\n');
	}
	return 0;
}