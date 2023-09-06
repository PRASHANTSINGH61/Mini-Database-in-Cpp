#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
//#include <filesystem>
#include "B+_Tree.h"

#define _CRT_SECURE_NO_DEPRECATE  //for VS 2019

void insertionMethod(BPTree** bPTree) 
{
    /*Function insertionMethod: This function is responsible for inserting records into the B+ tree. 
    It takes a pointer to a BPTree object and performs the following steps:
Takes input for roll number, name, age, and marks.
Constructs a file name based on the roll number and opens a file for writing.
Writes the user's tuple (name, age, marks) to the file.
Calls the insert method of the B+ tree object to insert the roll number and a pointer to the corresponding file.
Closes the file.*/
    int rollNo;
    int age, marks;
    string name;

    cout << "Please provide the rollNo: ";
    cin >> rollNo;

    cout << "\nWhat's the Name, Age and Marks acquired?: ";
    cin >> name >> age >> marks;

    string fileName = "DBFiles/";
    fileName += to_string(rollNo) + ".txt";
    FILE* filePtr = fopen(fileName.c_str(), "w");
    string userTuple = name + " " + to_string(age) + " " + to_string(marks) + "\n";
    fprintf(filePtr, userTuple.c_str());
    //fclose(filePtr);

    (*bPTree)->insert(rollNo, filePtr);
    /*(*bPTree)->insert(rollNo, filePtr);: This line calls the insert method of the BPTree object pointed to by the bPTree pointer. The insert method is responsible for inserting a key (in this case, the rollNo) along with a pointer to a file (in this case, filePtr) into the B+ tree. The (*bPTree) notation is used to dereference the pointer and call the method.

*/
    fclose(filePtr);
    /*fclose(filePtr);:
     After inserting the data into the B+ tree,
      the code proceeds to close the file
       associated with the filePtr pointer. 
       This is done using the fclose function, which ensures that the file is properly closed and resources are released.*/
    cout << "Insertion of roll No: " << rollNo << " Successful"<<endl;
}

void searchMethod(BPTree* bPTree) 
{
    int rollNo;
    cout << "What's the RollNo to Search? ";
    cin >> rollNo;

    bPTree->search(rollNo);
}

void printMethod(BPTree* bPTree) 
{
    int opt;
    cout << "Press \n\t1.Hierarical-Display \n\t2.Sequential-Display\n";
    cin >> opt;

    cout << "\nHere is your File Structure" << endl;
    if (opt == 1)
        bPTree->display(bPTree->getRoot());
    else
        bPTree->seqDisplay(bPTree->getRoot());
}

void deleteMethod(BPTree* bPTree) 
{
    cout << "Showing you the Tree, Choose a key from here: " << endl;
    bPTree->display(bPTree->getRoot());
 
    int tmp;
    cout << "Enter a key to delete: " << endl;
    cin >> tmp;
    bPTree->removeKey(tmp);

    //Displaying
    bPTree->display(bPTree->getRoot());
}

int main() 
{
    /*
		Please have a look at the default schema to get to know about the table
		Reference - img/database.jpg
	*/

    cout << "\n***Welcome to DATABASE SERVER**\n"
         << endl;

    bool flag = true;
    int option;

    int maxChildInt = 4, maxNodeLeaf = 3;
    cout << "Please provide the value to limit maximum child Internal Nodes can have: ";
    cin >> maxChildInt;
    cout << "\nAnd Now Limit the value to limit maximum Nodes Leaf Nodes can have: ";
    cin >> maxNodeLeaf;

    BPTree* bPTree = new BPTree(maxChildInt, maxNodeLeaf);

    do {
        cout << "\nPlease provide the queries with respective keys : " << endl;
        cout << "\tPress 1: Insertion \n\tPress 2: Search \n\tPress 3: Print Tree\n\tPress 4: Delete Key In Tree\n\tPress 5: ABORT!" << endl;
        cin >> option;

        switch (option) {
            case 1:
                insertionMethod(&bPTree);
                break;
            case 2:
                searchMethod(bPTree);
                break;
            case 3:
                printMethod(bPTree);
                break;
            case 4:
                deleteMethod(bPTree);
                break;
            default:
                flag = false;
                break;
        }
    }while (flag);

    return 0;
}
  



  //new in c++
  /*
  #include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include "B+_Tree.h" // Including the header file for B+ tree implementation

#define _CRT_SECURE_NO_DEPRECATE  // Disabling deprecation warnings for VS 2019

// Function for inserting records into the B+ tree
void insertionMethod(BPTree** bPTree) {
    int rollNo;
    int age, marks;
    string name;

    // Taking user input for roll number, name, age, and marks
    cout << "Please provide the rollNo: ";
    cin >> rollNo;

    cout << "\nWhat's the Name, Age and Marks acquired?: ";
    cin >> name >> age >> marks;

    // Constructing the file name and opening a file for writing
    string fileName = "DBFiles/";
    fileName += to_string(rollNo) + ".txt";
    FILE* filePtr = fopen(fileName.c_str(), "w");

    // Creating the user tuple (name, age, marks) and writing it to the file
    string userTuple = name + " " + to_string(age) + " " + to_string(marks) + "\n";
    fprintf(filePtr, userTuple.c_str());

    // Inserting the roll number and file pointer into the B+ tree
    (*bPTree)->insert(rollNo, filePtr);

    // Closing the file after writing
    fclose(filePtr);

    cout << "Insertion of roll No: " << rollNo << " Successful" << endl;
}

// Function for searching a record in the B+ tree
void searchMethod(BPTree* bPTree) {
    int rollNo;
    cout << "What's the RollNo to Search? ";
    cin >> rollNo;

    bPTree->search(rollNo);
}

// Function for printing the B+ tree structure
void printMethod(BPTree* bPTree) {
    int opt;
    cout << "Press \n\t1.Hierarchical-Display \n\t2.Sequential-Display\n";
    cin >> opt;

    cout << "\nHere is your File Structure" << endl;
    if (opt == 1)
        bPTree->display(bPTree->getRoot());
    else
        bPTree->seqDisplay(bPTree->getRoot());
}

// Function for deleting a record from the B+ tree
void deleteMethod(BPTree* bPTree) {
    cout << "Showing you the Tree, Choose a key from here: " << endl;
    bPTree->display(bPTree->getRoot());

    int tmp;
    cout << "Enter a key to delete: " << endl;
    cin >> tmp;
    bPTree->removeKey(tmp);

    // Displaying the updated tree structure
    bPTree->display(bPTree->getRoot());
}

int main() {
    cout << "\n***Welcome to DATABASE SERVER**\n" << endl;

    bool flag = true;
    int option;

    int maxChildInt = 4, maxNodeLeaf = 3;
    cout << "Please provide the value to limit maximum child Internal Nodes can have: ";
    cin >> maxChildInt;
    cout << "\nAnd Now Limit the value to limit maximum Nodes Leaf Nodes can have: ";
    cin >> maxNodeLeaf;

    // Creating a B+ tree object with specified limits
    BPTree* bPTree = new BPTree(maxChildInt, maxNodeLeaf);

    do {
        cout << "\nPlease provide the queries with respective keys : " << endl;
        cout << "\tPress 1: Insertion \n\tPress 2: Search \n\tPress 3: Print Tree\n\tPress 4: Delete Key In Tree\n\tPress 5: ABORT!" << endl;
        cin >> option;

        switch (option) {
            case 1:
                insertionMethod(&bPTree);
                break;
            case 2:
                searchMethod(bPTree);
                break;
            case 3:
                printMethod(bPTree);
                break;
            case 4:
                deleteMethod(bPTree);
                break;
            default:
                flag = false;
                break;
        }
    } while (flag);

    delete bPTree; // Freeing the memory used by the B+ tree object
    return 0;
}


  */