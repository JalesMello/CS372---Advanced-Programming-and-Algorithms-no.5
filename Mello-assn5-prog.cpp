// -----------------------------------------------------------------------------
// CODE FILENAME: Mello-assn5-prog.cpp
// DESCRIPTION: Program will create a Binary Search Tree to store a list of 
//				numbers. Numbers are derived from a file that user inputs. Once
//				the Binary Search Tree is created, program will display the 
//				number's that were added to the list then display a menu. In the
//				menu, the user may choose to display the list, add another
//				number, delete a number, display a subtree, or exit the program.
//				Once the user chooses to exit, the program will de-allocate all
//				the memory used for the nodes and tree.
// DATA FILE DESCRIPTION: 
//    - INPUT: User types in a file name for program to use.
//    - OUTPUT: none
// CLASS/TERM: CS372 8W, 2nd Term
// DESIGNER: Jales H. Mello
// FUNCTIONS: CreateTree - Creates the Binary Search Tree
//			  GetFileName - Gets a file name from the user.
//			  IsEmpty - Checks if the Binary Search Tree is empty.
//			  CreateNode - Creates a new node with a number to add to tree.
//			  InsertNode - Inserts a new node into the tree.
//			  FindNode - Checks if a number is in the tree and returns a pointer.
//			  Menu - Displays a menu of choices for user.
//			  DeleteNode - Deletes a number from the tree.
//			  InOrderDisplay - Displays numbers in order, depending on root.
//			  GetInteger - Gets a number from the user.
//			  FreeNodes - De-allocates all memory used for nodes in tree.
//			  DestoryTree - De-allocates memory used for the tree itself.
// -----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// global structure definitions
// - nodes used in binary tree
struct treeNode {
	int num;
	treeNode *left;
	treeNode *right;
};
// - start of binary tree with a count of the number of nodes in tree
struct treeRoot {
	int count;
	treeNode *root;
};

// function prototypes
treeRoot* CreateTree ();
string GetFileName();
bool IsEmpty(treeRoot* binaryTree);
treeNode* CreateNode (int num);
void InsertNode (treeNode* node, treeRoot* &binaryTree);
bool FindNode (int num, treeRoot* binaryTree, treeNode* &node);
char Menu ();
void DeleteNode (treeNode* node, treeRoot* &binaryTree);
void InOrderDisplay (int count, treeNode* root);
int GetInteger ();
void FreeNodes (treeNode* &node);
void DestoryTree (treeRoot* &binaryTree);


// -----------------------------------------------------------------------------
// FUNCTION: Main
// DESCRIPTION: Mainly call other functions. Performs various tasks to control
//				the flow of the program as a whole.
// INPUT:
//     Parameters: none
//     File: file from user containing numbers for binary search tree.
// OUTPUT:
//     Return Val: int - 0 upon success
//     Parameters: none
//     File: none
// CALLS TO: GetFileName, FindNode, CreateNode, InsertNode, IsEmpty, 
//			InOrderDisplay, Menu, DeleteNode, FreeNodes, DestoryTree
// -----------------------------------------------------------------------------
int main()
{	
	// local variables
	treeRoot* binaryTree = NULL;// binary tree used for program
	string fileName = " ";		// name of file with integers for binary tree
	ifstream file;				// file stream to read data
	int number = 0;				// number read from file / user
	treeNode* newNode = NULL;	// new tree node to be add to tree
	treeNode* tempNode = NULL;	// temporary node use for various functions
	bool inTree = false;		// check if number is in binary search tree
	bool success = true;		// test for various functions
	char selection = ' ';		// user selection from menu
	
	// Program Title
	cout << "Binary Search Tree - Program" << endl;
	cout << " This program will store a list of integers into a binary search" 
		 << " tree." << endl;
	cout << " User will be able to manipulate the binary tree." << endl;
	cout << "-----------------------------------------------" << endl << endl;
	
	
	// 1) Create an empty binary search tree.
	binaryTree = CreateTree();
	
	
	// 2) Read integer data from a text file and add to tree.
	fileName = GetFileName();		// get file name from user
	file.open(fileName.c_str());	// open file to read integers
	file >> number;					// initial file read to test if file empty
	while ((file) && (success)) {	// loop while there are numbers in file
		inTree = FindNode (number, binaryTree, tempNode); // check if num in tree
		// if number already in tree display message
		if (inTree) {
			cout << "Number: " << number << " is already in the tree.";
			cout << " It will be ignored." << endl;
		}
		// if not already in tree, create node for it and add to tree
		else {
			newNode = CreateNode (number); // create a new node for the number
			// if newNode creation successful, add to list
			if (newNode != NULL) {
				InsertNode (newNode, binaryTree);
			}
			// otherwise display error and stop reading from data file
			else {
				cout << "There was an error allocating memory for a new node.";
				cout << " Program will stop reading numbers from data file.";
				cout << endl;
				success = false;	// top stop reading from data file
			}
		} // else statement to add new node to tree
		
		// read next number in file (if any)
		file >> number;
		
	} // end while loop to read data from file & add to tree
	
	// close file after reading all integers
	file.close();
	
	
	// 3) Display the total number of integers in the binary search tree.
	success = IsEmpty (binaryTree);
	cout << endl;
	if (success) {
		cout << "Binary Search Tree is empty." << endl;
	}
	else {
		cout << "Values stored in entire Binary Search Tree are:" << endl;
		InOrderDisplay (0, binaryTree->root);
	}
	cout << endl;
	
	
	// Menu Selection
	do {
		selection = Menu();
		
		if (selection == 'A') {
			cout << endl;
			cout << "Values stored in entire Binary Search Tree are:" << endl;
			InOrderDisplay (0, binaryTree->root);
		} // end 'A' selection
		
		else if (selection == 'B') {
			number = GetInteger ();		// get the number
			inTree = FindNode (number, binaryTree, tempNode);// check if in tree
			
			if (inTree) {
				cout << endl << "Sorry, this number is already in the tree.";
				cout << " It cannot be added. " << endl;
			}
			else {
				newNode = CreateNode (number); // create a new node for the number
				if (newNode != NULL) {
					InsertNode (newNode, binaryTree);
				}
				else {
					cout << "There was an error allocating memory for the node.";
					cout << " Could not enter new number to tree.";
					cout << endl;
				}
			}
		} // end 'B' selection
		
		else if (selection == 'C') {
			number = GetInteger ();		// get the number
			inTree = FindNode (number, binaryTree, tempNode);// check if in tree
			
			if (!inTree) {
				cout << endl << "Sorry, this number is not in the tree.";
				cout << " It cannot be deleted." << endl;
			}
			else {
				DeleteNode (tempNode, binaryTree);
			}
		} // end 'C' selection
		
		else if (selection == 'D') {
			number = GetInteger ();		// get the number
			inTree = FindNode (number, binaryTree, tempNode);// check if in tree
			
			if (!inTree) {
				cout << endl << "Sorry, this number is not in the tree.";
				cout << " It's subroot cannot be displayed." << endl;
			}
			else {
				cout << endl << "Values stored subtree with root " << number
					 << " are: " << endl;
				InOrderDisplay (0, tempNode);
			}
			
		} // end 'D' selection
		
	} while (selection != 'E'); // end menu loop
	
	
	// 4) Before exiting, free up all dynamic memory allocated for the binary tree.
	FreeNodes (binaryTree->root);
	DestoryTree (binaryTree);
	
	return 0;
}

// -----------------------------------------------------------------------------
// FUNCTION: CreateTree
// DESCRIPTION: Allocates memory for a binary tree.
// INPUT:
//     Parameters: none
//     File: none
// OUTPUT:
//     Return Val: binaryTree - a pointer to binary tree
//     Parameters: none
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
treeRoot* CreateTree ()
{
	treeRoot* binaryTree;		// binary search tree to be created
	
	// allocate memory for binary tree
	binaryTree = new (nothrow) treeRoot;
	binaryTree->count = 0;
	binaryTree->root = NULL;
	
	return binaryTree;
}

// -----------------------------------------------------------------------------
// FUNCTION: GetFileName
// DESCRIPTION: Gets a filename from the user that will be used to create the 
//				binary search tree. Validates that the filename exists.
// INPUT:
//     Parameters: none
//     File: none
// OUTPUT:
//     Return Val: filename
//     Parameters: none
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
string GetFileName()
{
	string fileName = " ";		// filename from user
	ifstream file;				// check if file exists
	
	// loop to get the file name from user and test if exists
	do {
		//get file name from user
		cout << "Please enter a file name (ending in .txt) containing the";
		cout << " integers to create the binary tree (no spaces): ";
		cin >> fileName;
		
		// check if file exists
		file.open(fileName.c_str());
		if (!file) {
			cout << "Error! This file name does not exist. Please try again.";
			cout << endl << endl;
		}
		
		// close file
		file.close();
		
	} while (!file); // end loop to get file name
	
	cout << endl;
	
	return fileName;
}

// -----------------------------------------------------------------------------
// FUNCTION: IsEmpty
// DESCRIPTION: Checks if teh binary search tree is empty
// INPUT:
//     Parameters: binaryTree - binary search tree in question
//     File: none
// OUTPUT:
//     Return Val: empty - true/false if tree is empty
//     Parameters: none
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
bool IsEmpty(treeRoot* binaryTree)
{
	bool empty = false;			// if tree is empty or not
	
	// check if tree is empty
	if (binaryTree->count == 0)
		empty = true;
	
	return empty;
}

// -----------------------------------------------------------------------------
// FUNCTION: CreateNode
// DESCRIPTION: Creates a new node to be inserted into tree.
// INPUT:
//     Parameters: num - the number value of the new node
//     File: none
// OUTPUT:
//     Return Val: node - a pointer to the newly created node
//     Parameters: none
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
treeNode* CreateNode (int num)
{
	treeNode* node = NULL;		// new node to be created
	
	// allocate mem. for new node and assign num to it
	node = new (nothrow) treeNode;
	node->num = num;
	node->left = NULL;
	node->right	= NULL;
	
	return node;
}

// -----------------------------------------------------------------------------
// FUNCTION: InsertNode
// DESCRIPTION: Inserts a new node into binary search tree & increments count
// INPUT:
//     Parameters: node - the new node to be inserted
//				   binaryTree - tree in which node is being inserted
//     File: none
// OUTPUT:
//     Return Val: none
//     Parameters: binaryTree - updated binary tree
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
void InsertNode (treeNode* node, treeRoot* &binaryTree)
{
	treeNode* current = NULL;	// current node, for traversing
	treeNode* trail = NULL;		// trailing the current node
	
	// if list empty, make new node the root
	if (binaryTree->root == NULL) {
		binaryTree->root = node;
	}
	// otherwise, find correct location for node
	else {
		current = binaryTree->root;	// set current to root
		trail = current;		// set trail to current
		
		// loop to find insertion point
		while (current != NULL) {	
			// set trail to current
			trail = current;
			
			// traverse tree until current = NULL
			if (node->num < current->num)
				current = current->left;
			else
				current = current->right;
		}// end loop to find insertion point
		
		// insert node
		if (node->num < trail->num) {
			trail->left = node;
		}
		else {
			trail->right = node;
		}
	}
	
	// increment count
	binaryTree->count++;
	
	return;
}

// -----------------------------------------------------------------------------
// FUNCTION: FindNode
// DESCRIPTION: Searches the binary tree to see if a node containing a desired 
//				value is in the tree. Returns true if it is and false if not.
// INPUT:
//     Parameters: num - number being searched in tree
//				   binaryTree - the binary tree to be searched.
//				   node - pointer to node carrying num, or parent, or NULL
//     File: none
// OUTPUT:
//     Return Val: found - if value was found or not.
//     Parameters: node - pointer to found node / parent / or NULL if empty.
//     File: none
// CALLS TO: IsEmpty
// -----------------------------------------------------------------------------
bool FindNode (int num, treeRoot* binaryTree, treeNode* &node)
{
	bool found = false;			// if value was found in tree or not
	treeNode* temp = NULL;		// temp node for search
	node = NULL;				// set temp node to NULL
	
	// first check if tree is empty
	found = IsEmpty (binaryTree);
	
	// if empty, exit function
	if (found)
		found = false;
	
	// otherwise, search the tree
	else {
		node = binaryTree->root;	// set node to root of tree
		temp = node;
		
		// loop to search for value
		while (temp != NULL) {
			// if found, set found to true
			if (temp->num == num){
				node = temp;
				temp = NULL;
				found = true;
			}
			
			// if less, travel down left side of tree
			else if (num < temp->num) {
				node = temp;
				temp = temp->left;
			}
			
			// otherwise, travel down right side of tree
			else {
				node = temp;
				temp = temp->right;
			}
		} // end loop to search tree
	} // end else statement to search tree
	
	return found;
}

// -----------------------------------------------------------------------------
// FUNCTION: Menu
// DESCRIPTION: Displays a Menu for user to chose what to do next with program.
// INPUT:
//     Parameters: none
//     File: none
// OUTPUT:
//     Return Val: selection - the users selection
//     Parameters: none
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
char Menu ()
{
	char selection = ' ';		// user selection
	bool valid = false;			// test if valid entry entered
	
	do {
		cin.clear();
		
		// display menu
		cout << endl;
		cout << "Menu. What do you want to do?" << endl
			 << setw(10) << "A = Show all integers in binary tree." << endl
			 << setw(10) << "B = Add an integer to the binary tree." << endl
			 << setw(10) << "C = Delete an integer from the tree." << endl
			 << setw(10) << "D = Find an integer and display its subtree." << endl
			 << setw(10) << "E = Exit the program." << endl;
		cout << "Choose a letter from above options: ";
		cin >> selection;
		
		switch (selection) {
			case 'A':
			case 'a':
				selection = 'A';
				valid = true;
				break;
			case 'B':
			case 'b':
				selection = 'B';
				valid = true;
				break;
			case 'C':
			case 'c':
				selection = 'C';
				valid = true;
				break;
			case 'D':
			case 'd':
				selection = 'D';
				valid = true;
				break;
			case 'E':
			case 'e':
				selection = 'E';
				valid = true;
				break;
			default:
				cout << "Invalid entry. Please try again." << endl;
		}// end switch statement
		
	} while (!valid); // end loop to get selection from user
	
	return selection;
}

// -----------------------------------------------------------------------------
// FUNCTION: DeleteNode
// DESCRIPTION: Deletes a node from the binary search tree.
// INPUT:
//     Parameters: node - node to delete
//				   binaryTree - tree to delete node from
//     File: none
// OUTPUT:
//     Return Val: none
//     Parameters: binaryTree - the updated binary search tree
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
void DeleteNode (treeNode* node, treeRoot* &binaryTree)
{
	treeNode* current = binaryTree->root;	// pointer to traverse tree
	treeNode* trail = NULL;		// pointer to follow behind current
	treeNode* temp = node;		// pointer to delete node
	
	// find node's parent
	while (current != node) {
		trail = current;
		
		// traverse tree until current = NULL
		if (node->num < current->num)
			current = current->left;
		else
			current = current->right;
	}
	
	// Delete node...
	if ((node->left == NULL) && (node->right == NULL)) {
		temp = node;
		
		if (trail->left == node)
			trail->left = NULL;
		else
			trail->right = NULL;
		
		delete temp;
	}
	else if (node->left == NULL) {
		temp = node;
		
		if (trail->left == node)
			trail->left = node->right;
		else
			trail->right = node->right;
		
		delete temp;
	}
	else if (node->right == NULL) {
		temp = node;
		
		if (trail->left == node)
			trail->left = node->left;
		else
			trail->right = node->left;
		
		delete temp;
	}
	else {
		current = node->right;
		trail = NULL;
		
		// find next largest value
		while (current->left != NULL) {
			trail = current;
			current = current->left;
		}
		
		node->num = current->num;
		
		if (trail == NULL)
			node->right = current->right;
		else
			trail->left = current->right;
		
		delete current;
	} // end else statement
	
	// decrement tree count
	binaryTree->count--;
	
	return;
}

// -----------------------------------------------------------------------------
// FUNCTION: InOrderDisplay
// DESCRIPTION: Recursively displays all integers in the binary search tree, in
//				order.
// INPUT:
//     Parameters: binaryTree - the binary tree in question
//     File: none
// OUTPUT:
//     Return Val: none
//     Parameters: none
//     File: none
// CALLS TO: InOrderDisplay
// -----------------------------------------------------------------------------
void InOrderDisplay (int count, treeNode* root)
{
	
	if (root != NULL){
		InOrderDisplay (count + 1, root->left);
		cout << setw(6) << root->num;
		InOrderDisplay (count + 1, root->right);
		
		if (count % 10 == 0)
			cout << endl;
	}
	
	return;
}

// -----------------------------------------------------------------------------
// FUNCTION: GetInteger
// DESCRIPTION: Get's an integer from user to insert/delete into/from
//				binary search tree.
// INPUT:
//     Parameters: none
//     File: none
// OUTPUT:
//     Return Val: num - the number the user entered
//     Parameters: none
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
int GetInteger ()
{
	int num = 0;				// number to enter
	
	do {
		cout << endl << "Please enter a number: ";
		cin >> num;
		
		if (num <= 0) {
			cout << "Error! The number must be a postive value greater than 0.";
			cout << " Please try again." << endl;
		}
		
	} while (num <= 0);
	
	return num;
}

// -----------------------------------------------------------------------------
// FUNCTION: FreeNodes
// DESCRIPTION: Recursively de-allocates all dynamic memory allocated to nodes
//				in the binary search tree.
// INPUT:
//     Parameters: node - the tree root where all children will be de-allocated
//     File: none
// OUTPUT:
//     Return Val: none
//     Parameters: node - deleted root node
//     File: none
// CALLS TO: FreeNodes
// -----------------------------------------------------------------------------
void FreeNodes (treeNode* &node)
{
	if (node != NULL) {
		FreeNodes (node->left);
		FreeNodes (node->right);
		delete node;
	}
	
	return;
}

// -----------------------------------------------------------------------------
// FUNCTION: DestoryTree
// DESCRIPTION: De-allocates all dynamic memory allocated for the binary search 
//				tree.
// INPUT:
//     Parameters: binaryTree - binary tree to be de-allocated.
//     File: none
// OUTPUT:
//     Return Val: none
//     Parameters: binaryTree - deleted tree.
//     File: none
// CALLS TO: none
// -----------------------------------------------------------------------------
void DestoryTree (treeRoot* &binaryTree)
{
	delete binaryTree;
		
	return;
}



