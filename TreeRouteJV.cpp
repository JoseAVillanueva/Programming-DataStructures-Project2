//Name: Jose Villanueva Vigil
//Course: COSC 2436
//Program set 3, problem 1 (TreeRoute)
//References: I used the PDF covering program set 3
//=================================================================================

#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string>
#include <queue>
#include <vector>

using namespace std;

//this is the IntBinaryTree class, and this will be used throughout the 
//duration of the program, to hold the elements of a/the general tree
class IntBinaryTree
{
private:

	//a struct, TreeNode, is created, it contains two TreeNode pointers (right and left, both set to nullptr)
	//it contains a bool (visited set to false)
	//it contains an integer (value set to 0)
	//and it contains a character (l set to 'U', will track a nodes position)
	struct TreeNode
	{
		int value = 0;
		char l = 'U';
		bool visit = false;
		TreeNode* left = nullptr;
		TreeNode* right = nullptr;
	};

	//a TreeNode pointer (root) is assigned the nullptrvalue
	TreeNode* root = nullptr;

	//an integer (dupValue) is initalized to the value (0) 
	int dupValue = 0;

	//this is a private out-of-line member function
	//more information regarding this function can be found below the 
	//IntBinaryTree class (this class)
	void findDupValue(TreeNode*& , bool&, bool&, vector<char>&);

public:
	//the default constructor assigns the root variable the nullptr value
	IntBinaryTree()
	{
		root = nullptr;
	}
	//the deconstructor calls the destroySubTree function, passing the root as its argument
	~IntBinaryTree()
	{
		destroySubTree(root);
	}

	//these are public out-of-line member functions
	//more information regarding these functions can be found below the 
	//IntBinaryTree class (this class)
	void destroySubTree(TreeNode*);
	void makeDeletion(TreeNode*&);

	//this is the in-line, createNode, function and it returns a TreeNode pointer
	//this function creates a new TreeNode
	//an integer is passed within it parameter list (num)
	//a character is passed within its parameter list (let)
	TreeNode* createNode(int num, char let) const
	{
		//a new TreeNode is created 
		//the value member is set to equal num
		//the l member is set to equal let
		//and the left and right pointers are set to nullptr
		TreeNode* newNode = nullptr;
		newNode = new TreeNode;
		newNode->value = num;
		newNode->l = let;
		newNode->left = newNode->right = nullptr;
		return newNode;
	}

	//this is the in-line, levelOrderInsertion, function and this inserts elements into the 
	//tree via a level order traversal
	//a TreeNode pointer is passed within its parameter list (nodePtr)
	//an integer is passed within its parameter list (num) 
	TreeNode* levelOrderInsertion(TreeNode* nodePtr, int num)
	{
		//if the value of root is nullptr, then the create node function is called
		//and the root is set to equal the node returned from the createNode function
		//root is then returned 
		if (root == nullptr)
		{
			root = createNode(num, 'U');
			return root;
		}

		//a qeueue with the data type of TreeNode pointers is created (tempQueue)
		//and the root is pushed into the queue
		queue<TreeNode* > tempQueue;
		tempQueue.push(root);

		//this while loop will contiune to iterate until the queue is empty
		while (!(tempQueue.empty()))
		{
			//a new TreeNode pointer is created and initlaized to the front value in the tempQueue (tempNode)
			//the front value is then popped off of tempQueue
			TreeNode* tempNode = tempQueue.front();
			tempQueue.pop();

			//if the value of the left pointer is not nullptr
			//then it is pushed into the queue
			if (tempNode->left != nullptr)
			{
				tempQueue.push(tempNode->left);
			}
			//otherwise, the createNode function is called, left is set to the value returned
			//by the create node function, and root is returned
			else
			{
				//the arguments passed through the create node function are num and 'L' 
				tempNode->left = createNode(num, 'L');
				return root;
			}

			//if the value of the right pointer is not nullptr
			//then it is pushed into the queue
			if (tempNode->right != nullptr)
			{
				tempQueue.push(tempNode->right);
			}

			//otherwise, the createNode function is called, right is set to the value returned
			//by the create node function, and root is returned
			else
			{
				//the arguments passed through the create node function are num and 'R' 
				tempNode->right = createNode(num, 'R');
				return root;
			}
		}

		//the root is returned 
		return root;
	}

	//this is the in-line, getRoot, function, and it is used to return the root pointer
	TreeNode* getRoot() const
	{
		return root;
	}

	//this is the in-line, findValue, function, and it is used to call the findDupValue function
	//two bools are passed within its parameter list (flag and flag2)
	//a vector with the data type of char is passed by reference (num)
	void findValue(bool& flag, bool& flag2, vector<char>& num)
	{
		//the root, flag, flag2, and num are passed as arguments to the findDupValue function 
		findDupValue(root, flag, flag2, num);
	}

	//this is the in-line, setDupValue, function and it is used to set the dupValue to n
	//an integer is passed within its parameter list (n)
	void setDupValue(int n)
	{
		//dupValue is set to equal the value of n
		dupValue = n;
	}

	//this is the in-line, getDupValue, function and it is used to return the dupValue
	int getDupValue() const
	{
		return dupValue;
	}
};

//this is the out-of-line function, destroySubTree,and this is used to destroy the BinaryTree 
//that was/is created through the duration of the program  
//a TreeNode pointer is passed within its parameter list (nodePtr)
void IntBinaryTree::destroySubTree(TreeNode* nodePtr)
{
	//if nodePtr holds an address, then the following statements are executed 
	if (nodePtr)
	{
		//if the left pointer holds an address, then the destroySubTree function is called
		//passing the left pointer as an argument 
		if (nodePtr->left)
		{
			destroySubTree(nodePtr->left);
		}

		//if the right pointer holds an address, then the destroySubTree function is called
		//passing the right pointer as an argument 
		if (nodePtr->right)
		{
			destroySubTree(nodePtr->right);
		}

		//nodePtr is deleted 
		delete nodePtr;
	}

	//the root is set to the nullptr value
	root = nullptr;
}

//this is the out-of-line, makeDeletion, function and it is used to delete a TreeNode
//a TreeNode pointer is passed by reference within its parameter list (nodePtr)
void IntBinaryTree::makeDeletion(TreeNode*& nodePtr)
{
	delete nodePtr;
}

//this is the out-of-line, findDupValue, function and this is used to return the pathway between duplicate numbers
//a TreeNode is passed by reference within its parameter list (nodepPtr)
//two bools are passed by reference within its parameter list (flagOne and flagTwo)
//a vector with the data type of character is passed by reference within its parameter list (number)
void IntBinaryTree::findDupValue(TreeNode*& nodePtr, bool& flagOne, bool& flagTwo, vector<char>& number)
{

	//if flagTwo is not true, then the following statements are executed 
	if (flagTwo != true)
	{

		//if nodePtr holds an address, then the following statements are executed 
		if (nodePtr)
		{
			//if the value of flagOne is true, and the value of flagTwo is not true
			//and the value of visit is false, the following statements are executed 
			if (flagOne == true && nodePtr->visit == false && flagTwo != true)
			{
				//l is pushed into the number vector 
				//and the visit status of nodePtr is changed to true
				number.push_back(nodePtr->l);
				nodePtr->visit = true;
			}

			//the findDupValue function is called
			//passing nodePtr->left, flagOne, flagTwo, and number as its arguments
			findDupValue(nodePtr->left, flagOne, flagTwo, number);

			//if the value of flagOne is true, and the value of flagTwo is not true
			//and the value of visit is false, the following statements are executed 
			if (flagOne == true && nodePtr->visit == false && flagTwo != true)
			{
				//nodePtr->l is changed to 'U' and is pushed into the number vector 
				//and the visit status of nodePtr is changed to true
				nodePtr->l = 'U';
				number.push_back(nodePtr->l);
				nodePtr->visit = true;
			}

			//the findDupValue function is called
			//passing nodePtr->right, flagOne, flagTwo, and number as its arguments
			findDupValue(nodePtr->right, flagOne, flagTwo, number);

			//if the value of flagOne is true, and the value of flagTwo is not true
			//and the value of visit is false, the following statements are executed 
			if (flagOne == true && nodePtr->visit == false && flagTwo != true)
			{
				//nodePtr->l is changed to 'U' and is pushed into the number vector 
				//and the visit status of nodePtr is changed to true
				nodePtr->l = 'U';
				number.push_back(nodePtr->l);
				nodePtr->visit = true;
			}

			//if the value of flagOne is false and the current node's value is the dupValue
			//flagOne is set to true
			if (flagOne == false && nodePtr->value == dupValue)
			{
				flagOne = true;
			}
			
			//otherwise, if flagOne is true and the current node's value is the dupValue
			//flagTwo is set to true
			else if (flagOne == true && nodePtr->value == dupValue)
			{
				flagTwo = true;
			}

			//ohterwise, if the value of flagOne is true and the left and right pointers
			//of the current node are nullpt, then its address is set to nullptr, the node
			//is then deleted, and its value is removed from the number vector
			else if (flagOne == true && nodePtr->left == nullptr && nodePtr->right == nullptr)
			{
				number.pop_back();
				nodePtr = nullptr;
				makeDeletion(nodePtr);
			}
		}
	}
}

char CaseChecker = 'Y';

string FileName;
ifstream InPutFile;

int main()
{
	//a new instance of the IntBinaryTree is created (tempTree)
	//a pointer with the data type of IntBinaryTree is created and is set to the nullptr value (tempNode)
	IntBinaryTree tempTree;
	IntBinaryTree* tempNode = nullptr;

	//a vector with the data type of charcater is created (numbers)
	vector<char> numbers;

	//the while loop will continue to iterate until the value of CaseCheck is 'N'
	while (CaseChecker != 'N')
	{
		//user input is gathered here using the getline function
		cout << "Enter filename: ";
		getline(cin, FileName);
		cout << " " << endl;

		//the file is opened here
		InPutFile.open(FileName);

		//if the file is not opened susseccfully, then an error message is displayed 
		if (InPutFile.fail())
		{
			cout << "Something went wrong, try again.\n";
		}
		//otherwise, the following statements are executed 
		else
		{
			int NumTestCases = 0;
			int TempCases = 0;
			int track = 0;

			//the amount of cases are gathered here using NumTestCases
			InPutFile >> NumTestCases;

			//the while loop will continue to iterate until the value of TempCases
			//equals the NumTestCases value
			while (TempCases != NumTestCases)
			{
				//TempCases is incremeneted by (+1)
				TempCases++;

				int TreeSize = 0;
				int wantedNum = 0;
				bool tempFlag = false;
				bool tempFlag2 = false;

				//the size of the tree is gathered here, using TreeSize
				InPutFile >> TreeSize;

				//the for loop will continue to iterate until the value of index 
				//equals the TreeSize's value
				for (int index = 0; index < TreeSize; index++)
				{
					//information for an element is drawn here using 
					//the treeNum 
					int treeNum = 0;
					InPutFile >> treeNum;

					//the levelOrderInsertion function is called
					//passing tempTree.getRoot() and treeNum as its arguments
					tempTree.levelOrderInsertion(tempTree.getRoot(), treeNum);
				}
				
				//the duplicate number is drawn here using wantedNum
				//the setDupValue function is called, passing wantedNum as its argument
				//the findValue function is then called, passing tempFlag, tempFlag2, and 
				//numbers as its arguments
				InPutFile >> wantedNum;
				tempTree.setDupValue(wantedNum);
				tempTree.findValue(tempFlag, tempFlag2, numbers);

				cout << "Tree " << (track + 1) << ": Path: ";

				//the pathway between the duplicate number is printed here
				//the for loop will continue to iterate until the index equals 
				//the size of the numbers vector
				for (int index = 0; index < numbers.size(); index++)
				{
					//the current position within the vector is displayed
					cout << numbers[index];
				}
				
				//the vector (numbers) is cleared
				//the destroySubTree function is called, passing tempTree.getRoot() as its argument
				//and track is incremented by (+1)
				numbers.clear();
				tempTree.destroySubTree(tempTree.getRoot());
				cout << " " << endl;
				track++;
			}

			//the inputfile is closed
			cout << " " << endl;
			InPutFile.close();
		}

		//the user is then asked if they would like to run the program again
		cout << "Run again (Y/N): ";
		cin >> CaseChecker;
		CaseChecker = toupper(CaseChecker);
		cout << " " << endl;

		//the while loop will continue to iterate until a valid input is made
		while (CaseChecker != 'Y' && CaseChecker != 'N')
		{
			cout << "Invalid input was made, please try again.\n";
			cout << "Run again (Y/N): ";
			cin >> CaseChecker;
			CaseChecker = toupper(CaseChecker);
			cout << " " << endl;
		}

		//this is here to remove the buffer character, to allow
		//the getline string to get the fileName in the intial 
		//process
		cin.ignore(1, '\n');
	}
	return 0;
}