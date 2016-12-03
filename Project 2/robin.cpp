/**
Project 2: Round Robin Job Scheduling

Note: I re-used assignment 3 code for linked list implementation

 */

#include <iostream>
#include <cstddef>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

/* definition of the list node class */
class Node
{
    friend class LinkedList;
private:
    int number, arrival, burst; 
    Node *pNext; 
    Node *pPrevious;
    
public:
    /* Constructors with No Arguments */
    Node(void)
    : pNext(NULL)
    { }
    
    /* Constructors with a given value */
    Node(int number, int arrival, int burst)
    : number(number), arrival(arrival), burst(burst), pNext(NULL)
    {}
    
    /* Constructors with a given value and a link of the next node */
    Node(int number, int arrival, int burst, Node* next)
    : number(number), arrival(arrival), burst(burst), pNext(next)
    {}
    
    /* Getters */
    int getNumber(void)
    { return number; }
    
    int getArrival(void)
    { return arrival; }
    
    int getBurst(void)
    { return burst; }
    
    Node* getNext(void)
    { return pNext; }

	/* Setters */
	void setBurst(int newBurst)
	{ burst = newBurst; }
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
    
    /* Constructor with first node */
    LinkedList(int number, int arrival, int burst);
    
    /* Destructor */
    ~LinkedList();

	/* Getter for head */
	Node* getHead(void)
	{ return pHead; }
    
    /* Traversing the list and printing the value of each node */
    void traverse_and_print();
	
	/* Add node to tail of list */
	void push_back(int number, int arrival, int burst);

	void pop_head();	
};

LinkedList::LinkedList(void)
{
    /* Initialize the head and tail node */
    pHead = pTail = NULL;
}

LinkedList::LinkedList(int number, int arrival, int burst)
{
    /* Create a new node, acting as both the head and tail node */
    pHead = new Node(number, arrival, burst);
    pTail = pHead;
}

LinkedList::~LinkedList()
{
    
}

void LinkedList::traverse_and_print()
{
    Node *p = pHead;
	cout << p->arrival << endl;
    
    /* The list is empty? */
    if (pTail == NULL) {
        cout << "The list is empty" << endl;
        return;
    }
    
    cout << "LinkedList: ";
    /* A basic way of traversing a linked list */
    while (p != NULL) { /* while there are some more nodes left */
        /* output the value */
        cout << "Job: " << p->number << "  Arrival: " << p->arrival << " Burst: " << p->burst << endl;
        /* The pointer moves along to the next one */
        p = p->pNext;
    }
    cout << endl;
}

void LinkedList::push_back(int number, int arrival, int burst)
{
     /* Adds node to end, moves tail, sets previous tail as tail->previous */
    Node *temp_prev = pTail;
	if (pTail == NULL)
	{
		pTail = new Node(number, arrival, burst);
		pHead = pTail;
	}
	else 
	{
    	pTail->pNext = new Node(number, arrival, burst);
    	pTail = pTail->pNext;
    	pTail->pPrevious = temp_prev;
	}
} 

// Allows linked list to act like a queue
void LinkedList::pop_head()
{
	Node *p = pHead;
	pHead = pHead->pNext;
	pHead->pPrevious = NULL;
	free(p);
}

int main( int argc, const char* argv[] )
{
	if (argc < 2)
	{
		cout << "Please specify  time quantum as a paramter" << endl;
		return 0;
	}

    LinkedList jobs;
    ifstream infile("job.txt");
    char * pch;
    string line;
    int number, arrival, burst;
	int quantum = atoi(argv[1]);
    
	// Fill linked list with all jobs
    while(!infile.eof())
    {
		getline(infile, line, ',');
        number = stoi(line);
        // cout << "Number is: " << number << endl;
		getline(infile, line, ',');
        arrival = stoi(line);
		// cout << "Arrival is: " << line << endl;
		getline(infile, line);
        burst = stoi(line);
		// cout << "Burst is: " << line << endl;
		jobs.push_back(number, arrival, burst);
		// jobs.traverse_and_print();
        //system("pause");
    }  
	
	// jobs.traverse_and_print();
    infile.close();

	LinkedList jobs_queued;
	int t_queue, t_endqueue, t_global = 0;
	Node *current = jobs.getHead();
	bool end, all_processed = false;
	
	while(!end)
	{
		cout << "Time is " << t_global << endl << endl;
		t_queue = t_global;
		t_endqueue = t_queue + quantum;
		
		while((current->getArrival() <= t_endqueue)&&(!all_processed))
		{
			jobs_queued.push_back(current->getNumber(), current->getArrival(), current->getBurst());
			if (current->getNext() == NULL)
				all_processed = true;
			else
				current = current->getNext();
		}
		
		if (jobs_queued.getHead() == NULL)
			continue;
		Node *printstart = jobs_queued.getHead();
		while (printstart != NULL)
		{
			// Job Finishes
			if (printstart->getBurst() <= quantum)
			{
				cout << "Job number " << printstart->getNumber() << " processed for " << printstart->getBurst() << " ms. Job Finished" << endl;
				jobs_queued.pop_head();
				t_global = t_global + printstart->getBurst();
				cout << "Time is " << t_global << endl;
			}
			// Quantum completes; Job not finished
			else
			{
				cout << "Job number " << printstart->getNumber() << " processed for " << quantum << " ms. ";
				int newBurst = printstart->getBurst() - quantum;
				cout << newBurst << " ms. remains" << endl;
				jobs_queued.push_back(printstart->getNumber(), printstart->getArrival(), newBurst);
				jobs_queued.pop_head();
				t_global = t_global + quantum;
				cout << "Time is " << t_global << endl;
			}
			printstart = printstart->getNext();
		}
	}

    return 0;
}

