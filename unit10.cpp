#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    // Generate array of 1000 random ints
	int array[999];
	for (int i = 0; i < 1000; i++)
	{
	    array[i] = rand() % 101;
	}

	int input[19] = {5,13,24,6,17,20,1,51,36,42,2,19,67,35,64,91,96,84,72};
	cout << "\n";
	int status;
	pid_t children[19];

	for (int i = 0; i <= 18; i++)
	{
		int count = 0;
		children[i] = fork();
		if (children[i] == 0)
		{
			for (int j = 0; j <= 1000; j++)
			{
				if (input[i] == array[j])
					count++;
			}
			cout << "Query: " << input[i];
			cout << "  Count: " << count;
			cout << "  pid: " << getpid() << endl;
			return 0;
		} 
	}

	for (int i = 0; i <= 18; i++)
	{
		waitpid(children[i], &status, 0);
	}
	return 0;
}
