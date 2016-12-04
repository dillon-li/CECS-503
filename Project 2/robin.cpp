/**
Project 2: Round Robin Job Scheduling

Note: I re-used assignment 3 code for linked list implementation

Also, recently pushed to my github at GreenKoopa in case it comes up 
in your checks.

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
	// Last node case
	if (pHead->pNext == NULL)
		free(p);
	else
	{
		pHead = pHead->pNext;
		pHead->pPrevious = NULL;
		free(p);
	}
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
	int endtime = 0;
    
	// Fill linked list with all jobs
    while(!infile.eof())
    {
		getline(infile, line, ',');
        number = stoi(line);
		getline(infile, line, ',');
        arrival = stoi(line);
		getline(infile, line);
        burst = stoi(line);
		endtime = endtime + burst;
		jobs.push_back(number, arrival, burst);
    }  
	
	cout << "Total time: " << endtime << endl;

	// jobs.traverse_and_print();
    infile.close();

	LinkedList jobs_queued;
	int t_queue, t_endqueue, t_global;
	int q = quantum;
	Node *current = jobs.getHead();
	bool end, all_processed = false;
	int currentBurst = -1;
	FILE *output;
	output = fopen("output.txt", "w");
	
	while(t_global < endtime)
	{
		t_queue = t_global;
		t_endqueue = t_queue + quantum;
		while((current != NULL) && (current->getArrival() == t_global))
		{
			jobs_queued.push_back(current->getNumber(), current->getArrival(), current->getBurst());
			current = current->getNext();
		}
		
		if (jobs_queued.getHead() == NULL)
			continue;
		Node *printstart = jobs_queued.getHead();

		// Process queue, 1 second each time
		if (printstart->getBurst() == 0)
		{
			fprintf(output, "Job %d has 0 burst. Job completed.\n", printstart->getNumber());
		jobs_queued.pop_head();
		q = quantum;
		currentBurst = -1;
		continue;
		}
		if ((printstart->getBurst() < quantum) && (currentBurst == -1))
		{
			currentBurst = printstart->getBurst();
		}
		printstart->setBurst(printstart->getBurst() - 1);
		q--;
		t_global++;
		if (printstart->getBurst() == 0)
		{
			fprintf(output, "Job %d processed for %d ms. Job completed\n", printstart->getNumber(), currentBurst);
			cout << "Job " << printstart->getNumber() << " processed for " << currentBurst << " ms. Job Completed\n";
			jobs_queued.pop_head();
			q = quantum;
			currentBurst = -1;
		}
		else if (q == 0)
		{
			fprintf(output, "Job %d processed for %d ms. %d remains.\n", printstart->getNumber(), quantum, printstart->getBurst());
			cout << "Job " << printstart->getNumber() << " processed for " << quantum << " ms. " << printstart->getBurst() << " remains\n";
			jobs_queued.push_back(printstart->getNumber(), printstart->getArrival(), printstart->getBurst());
			jobs_queued.pop_head();
			q = quantum;
		}
	}

	fclose(output);
    return 0;
}


