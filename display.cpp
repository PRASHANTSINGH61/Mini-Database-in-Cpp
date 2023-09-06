#include <iostream>
#include <queue>
#ifndef NODE_H
#include "B+_Tree.h"


void BPTree::display(Node* cursor) {
    /*
		Depth First Display

    if (cursor != NULL) {
        for (int i = 0; i < cursor->keys.size(); i++)
            cout << cursor->keys[i] << " ";
        cout << endl;
        if (cursor->isLeaf != true) {
            for (int i = 0; i < cursor->ptr2TreeOrData.ptr2Tree.size(); i++)
                display(cursor->ptr2TreeOrData.ptr2Tree[i]);
        }
    }
    */

    /*
        Level Order Display
    */
    if (cursor == NULL) return;
    queue<Node*> q;
    q.push(cursor);

    while (!q.empty()) {
        int sz = q.size();
        for (int i = 0; i < sz; i++) {
            Node* u = q.front(); q.pop();

            //printing keys in self
            for (int val : u->keys)
                cout << val << " ";

            cout << "|| ";//to seperate next adjacent nodes
            
            if (u->isLeaf != true) {
                for (Node* v : u->ptr2TreeOrData.ptr2Tree) {
                    q.push(v);
                }
            }
        }
        cout << endl;
    }
}

/*
Display Method (Level Order):
This display method is used to print the keys of the B+ Tree in level order.
It takes a pointer to a Node named cursor as a parameter. 
This cursor is used to start the traversal from the specified node.
The method uses a queue to perform a level-order traversal of the tree.
It starts by pushing the cursor node into the queue.
The while loop runs until the queue is empty.
Inside the loop, it processes nodes level by level.
For each node, it prints the keys in that node using a range-based loop:
 for (int val : u->keys).
After printing the keys, it prints "|| " to separate adjacent nodes in the same level.
If the current node is not a leaf node,
 it iterates through its child nodes (ptr2TreeOrData.ptr2Tree) and 
 pushes them into the queue for further processing.
*/

void BPTree::seqDisplay(Node* cursor) {
    Node* firstLeft = firstLeftNode(cursor);

    if (firstLeft == NULL) {
        cout << "No Data in the Database yet!" << endl;
        return;
    }
    while (firstLeft != NULL) {
        for (int i = 0; i < firstLeft->keys.size(); i++) {
            cout << firstLeft->keys[i] << " ";
        }

        firstLeft = firstLeft->ptr2next;
    }
    cout << endl;
}
/*
Sequential Display Method:
This seqDisplay method is used to sequentially display the keys of the B+ Tree,
 starting from the leftmost node.
It takes a pointer to a Node named cursor as a parameter.
 This is used to locate the leftmost node in the tree.
The method starts by finding the leftmost node using the firstLeftNode method 
(not shown in the provided code snippet).
 The leftmost node is assigned to the firstLeft pointer.
If there is no data in the database (tree), it prints a message and returns.
If there is data, it enters a loop that iterates through each node in the sequence.
Inside the loop, it iterates through the keys in the current node (firstLeft->keys) 
and prints them.
After printing the keys in the current node, it moves to the next node in the
 sequence by updating firstLeft to its ptr2next.
Both methods offer different ways of displaying the keys stored in the B+ Tree.
 The display method uses a level-order traversal to visualize the structure of the tree, 
 while the seqDisplay method provides a sequential display of the keys as they appear
  in the sequence.

*/
#endif 