#include <stdio.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdint.h>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

// void *multiply(void *param);
int input[100000];
int product[10];
mutex blocker;

void multiply(int x)
{
	blocker.lock();
	int start = x * 10000;
	int end = start + 10000;
	long int result = 1;
	printf("(start, end) => (%d, %d)\n", start, end);
	printf("Input start+1 is %d\n", input[start+1]);
	for (int i = start; i < end; i++)
	{
		result = result * input[i];
		if (i == 3)
			printf("result is %ld\n", result);
	}
	product[x] = result;
	printf("Product[%d] is %ld\n", x, result);
	// x = 3;
	// printf("X is %d (should be 3)\n", x);
	blocker.unlock();
}

int main()
{
	// Read Input
	ifstream file;
	file.open("input.txt");
	for (int i = 0; i < 100000; i++)
	{
		file >> input[i];
	} 

	cout << "Input 99,999 is " << input[99999] << endl;

	int product_final = 1;
    thread workers[10];
    
    for (int i = 0; i < 10; i++)
    {
        workers[i] = thread(multiply, i);
	}

	for (int i = 0; i < 10; i++)
	{
		workers[i].join();
		printf("Thread joined\n");
		cout << "Product " << i << " is " << product[i] <<endl;
	}

	for (int i = 0; i < 10; i++)
	{
		product_final = product_final * product[i];
	}

	printf("End product is %d\n", product_final);

	return 0;
}
