/*
It looks like you've provided a code snippet for a B+ Tree implementation in C++. 
This code defines classes Node and BPTree for creating and managing B+ Trees.
 The B+ Tree is a data structure commonly used for indexing and managing large amounts of
  data efficiently, particularly in databases and file systems.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
//#include <filesystem>
using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
    /*
		Generally size of the this node should be equal to the block size.
         Which will limit the number of disk access and increase the accesssing time.
		Intermediate nodes only hold the Tree pointers which is of considerably
         small size(so they can hold more Tree pointers) and only Leaf nodes hold
		the data pointer directly to the disc.

		IMPORTANT := All the data has to be present in the leaf node
	*/
   public:
    bool isLeaf;
    vector<int> keys;
    //Node* ptr2parent; //Pointer to go to parent node CANNOT USE check https://stackoverflow.com/questions/57831014/why-we-are-not-saving-the-parent-pointer-in-b-tree-for-easy-upward-traversal-in
    Node* ptr2next;              //Pointer to connect next node for leaf nodes
    union ptr {                  //to make memory efficient Node
        vector<Node*> ptr2Tree;  //Array of pointers to Children sub-trees for intermediate Nodes
        vector<FILE*> dataPtr;   // Data-Pointer for the leaf node

        ptr();   // To remove the error !?
        ~ptr();  // To remove the error !?
    } ptr2TreeOrData;

    friend class BPTree;  // to access private 
    //members of the Node and hold the 
    //encapsulation concept
   public:
    Node();
};

class BPTree {
    /*
		::For Root Node :=
			The root node has, at least two tree pointers
		::For Internal Nodes:=
			1. ceil(maxIntChildLimit/2)     <=  #of children <= maxIntChildLimit
			2. ceil(maxIntChildLimit/2)-1  <=  #of keys     <= maxIntChildLimit -1
		::For Leaf Nodes :=
			1. ceil(maxLeafNodeLimit/2)   <=  #of keys     <= maxLeafNodeLimit -1
	*/
   private:
    int maxIntChildLimit;                                   //Limiting  #of children for internal Nodes!
    int maxLeafNodeLimit;                                   // Limiting #of nodes for leaf Nodes!!!
    Node* root;                                             //Pointer to the B+ Tree root
    void insertInternal(int x, Node** cursor, Node** child);  //Insert x from child in cursor(parent)
    Node** findParent(Node* cursor, Node* child);
    Node* firstLeftNode(Node* cursor);

   public:
    BPTree();
    BPTree(int degreeInternal, int degreeLeaf);
    Node* getRoot();
    int getMaxIntChildLimit();
    int getMaxLeafNodeLimit();
    void setRoot(Node *);
    void display(Node* cursor);
    void seqDisplay(Node* cursor);
    void search(int key);
    void insert(int key, FILE* filePtr);
    void removeKey(int key);
    void removeInternal(int x, Node* cursor, Node* child);
};

#endif
// OOPS  
/* 
Abstraction: The Node and BPTree classes abstract away the complexity of the B+ Tree data structure and its operations.

Encapsulation: Private members and methods are used to encapsulate the internal details and logic of the B+ Tree implementation.

Inheritance: Although not explicitly shown in this snippet, OOP supports inheritance, where one class can inherit attributes and behaviors from another class. The classes in this snippet don't seem to have explicit inheritance, but the concept can be applied when extending or customizing these classes.

Polymorphism: Polymorphism allows objects of different classes to be treated as objects of a common superclass. While this snippet doesn't explicitly showcase polymorphism, it's a broader concept within OOP.

The classes and methods in the code snippet follow the fundamental concepts of OOP, providing a structured and modular approach to handling B+ Trees and their operations.
*/

/*
Class Definition: This code defines a class named Node. This class represents a node in the B+ 
Tree data structure.

Public Members:

bool isLeaf: This boolean variable indicates whether the node is a leaf node (true) or an intermediate node (false).
vector<int> keys: This vector holds the keys that are stored in the node. For internal nodes, these keys represent separation values, and for leaf nodes, they represent the actual data.
Node* ptr2next: This pointer is used to link leaf nodes together in a linked list fashion. It points to the next leaf node in the sequence.
union ptr: This is a union that allows the node to hold either pointers to children sub-trees (ptr2Tree) for internal nodes or data pointers (dataPtr) for leaf nodes. Since internal and leaf nodes have different structures, this union provides memory efficiency by allowing the node to hold either type of information without wasting space.
friend class BPTree;: This line declares the BPTree class as a friend of the Node class. This means that the BPTree class can access the private members of the Node class.
Public Constructor:

Node();: This is the constructor for the Node class. It is used to create instances of the Node class. The implementation of this constructor is not provided in the snippet.
Union and Memory Efficiency:

The ptr union is used to ensure memory efficiency. Since a B+ Tree can have both internal and leaf nodes with different structures, using a union allows the same memory location to be used for different types of information depending on whether the node is an internal or leaf node.
ptr2Tree inside the ptr union is a vector that holds pointers to children sub-trees for internal nodes.
dataPtr inside the ptr union is a vector that holds data pointers to actual data on disk for leaf nodes.
Friend Class:

The friend class BPTree; line indicates that the BPTree class can access the private members of the Node class. This is often done to allow the main controlling class (BPTree in this case) to manage and manipulate the nodes efficiently.
This Node class defines the basic structure of nodes within the B+ Tree. The use of the ptr union allows the nodes to adapt to the requirements of internal and leaf nodes, while the class structure helps encapsulate the properties and behavior of nodes in the B+ Tree implementation.



Class Definition: This code defines a class named BPTree. This class represents the B+ Tree data structure and provides methods for managing and interacting with the tree.

Private Members:

int maxIntChildLimit: This integer stores the maximum limit of children for internal nodes.
int maxLeafNodeLimit: This integer stores the maximum limit of keys for leaf nodes.
Node* root: This pointer holds the address of the root node of the B+ Tree.
void insertInternal(int x, Node** cursor, Node** child): This private method is responsible for inserting a key x into the B+ Tree by modifying the tree structure. It is used internally within the class to handle insertion operations.
Node** findParent(Node* cursor, Node* child): This private method is used to find the parent node of a given child node in the tree. It returns a pointer to the parent node.
Node* firstLeftNode(Node* cursor): This private method is used to find the first left node under a given cursor node. This is used for traversing the tree.
Public Members and Methods:

BPTree(): Default constructor for the BPTree class. It initializes the tree with default values.
BPTree(int degreeInternal, int degreeLeaf): This constructor allows you to specify the maximum limits for internal and leaf nodes when creating a B+ Tree instance.
Node* getRoot(): This method returns a pointer to the root node of the B+ Tree.
int getMaxIntChildLimit(): This method returns the maximum limit of children for internal nodes.
int getMaxLeafNodeLimit(): This method returns the maximum limit of keys for leaf nodes.
void setRoot(Node*): This method allows you to set the root node of the B+ Tree.
void display(Node* cursor): This method displays the content of the tree, starting from the given cursor node.
void seqDisplay(Node* cursor): This method performs a sequential display of the tree's content, starting from the given cursor node.
void search(int key): This method searches for a given key in the tree and provides information about its presence.
void insert(int key, FILE* filePtr): This method is used to insert a new key along with an associated filePtr (data pointer) into the B+ Tree.
void removeKey(int key): This method removes a specified key from the B+ Tree.
void removeInternal(int x, Node* cursor, Node* child): This method is responsible for removing an internal x key from the tree structure while adjusting the parent and child nodes accordingly.
The BPTree class encapsulates the operations and properties of the B+ Tree data structure. It provides methods for creating, displaying, inserting, searching, and removing keys. The class aims to manage the intricacies of B+ Tree operations and maintain the structure of the tree for efficient data access.






*/