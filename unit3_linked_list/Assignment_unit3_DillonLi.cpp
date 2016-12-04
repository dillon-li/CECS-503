/**
 * A sample code of Creating C++ linked lists,
 * Including definitions the list node class and linked list class,
 * and how to create a blank linked list and a one-node linked list.
 *
 * Outline: understand the definition and structure of the linked
 * list and build a linked list based on it.
 */

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;




/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int value; 
    Node *pNext; 
    Node *pPrevious;
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : pNext(NULL)
    { }
    
    /* Constructors with a given value */
    Node(int val)
    : value(val), pNext(NULL)
    { }
    
    /* Constructors with a given value and a link of the next node */
    Node(int val, Node* next)
    : value(val), pNext(next)
    {}
    
    /* Getters */
    int getValue(void)
    { return value; }
    
    Node* getNext(void)
    { return pNext; }
};

/* definition of the linked list class */
class LinkedList
{
private:
    /* pointer of head node */
    Node *pHead;
    /* pointer of tail node */
    Node *pTail;
    
public:
    /* Constructors with No Arguments */
    LinkedList(void);
    /* Constructors with a given value of a list node */
    LinkedList(int val);
    /* Destructor */
    ~LinkedList(void);
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();
	
	void push_back(int val); // for assignment
	
	/* Prints list in reverse to show that parent node can be accessed */
	void traverse_print_reversed();
};

LinkedList::LinkedList()
{
    /* Initialize the head and tail node */
    pHead = pTail = NULL;
}

LinkedList::LinkedList(int val)
{
    /* Create a new node, acting as both the head and tail node */
    pHead = new Node(val);
    pTail = pHead;
}

LinkedList::~LinkedList()
{
    
}

void LinkedList::traverse_and_print()
{
    Node *p = pHead;
    
    /* The list is empty? */
    if (pHead == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << p->value;
        if (p != pTail)
           cout << ", "; // Added by me for sake of neatness
        /* The pointer moves along to the next one */
        p = p->pNext;
    }
    cout << endl;
}

void LinkedList::push_back(int val)
{
     /* Adds node to end, moves tail, sets previous tail as tail->previous */
     Node *temp_prev = pTail;
     pTail->pNext = new Node(val);
     pTail = pTail->pNext;
     pTail->pPrevious = temp_prev;
} 

void LinkedList::traverse_print_reversed()
{
    Node *p = pTail;
    
    /* The list is empty? */
    if (pHead == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << p->value;
        if (p != pHead)
           cout << ", "; // Added by me for sake of neatness
        else 
           cout << " (parent node)";
        /* The pointer moves along to the next one */
        p = p->pPrevious;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    /* Create an empty list */
    LinkedList list1;
    cout << "Created an empty list named list1." << endl;
    /* output the result */
    cout << "list1:" << endl;
    list1.traverse_and_print();
    
    /* Create a list with only one node */
    LinkedList list2(10);
    cout << "Created a list named list2 with only one node." << endl;
    /* output the result */
    cout << "list2:" << endl;
    list2.traverse_and_print();
	
	/*your testing code here*/
	
	/* Appends to list with 10 in it: 10, 1, 2, 3, ... 9 */
	for (int i = 0 ; i < 10; i++){
		list2.push_back(i);
	} 
	list2.traverse_and_print();
	
	/* Print out list traversing the other way */
	cout << "\n" << "List2 Reversed:\n";
	list2.traverse_print_reversed();
	cout << "\n";
	
	system("pause");
    return 0;
    
}



