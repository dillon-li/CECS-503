#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void *multiply(void *param);
int input[100000];
int product[10];

int main()
{
	// Read Input
	FILE *read;
	read = fopen("input.txt", "r");
	for (int i = 0; i < 100000; i++)
	{
		fscanf(read, "%d", &input[i]);
	} 

	int product_final = 1;
    pthread_t workers[10];
    pthread_attr_t attr;
    
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&workers[i], &attr, multiply, &i);
		printf("Thread created\n");
    }

	for (int i = 0; i < 10; i++)
	{
		pthread_join(workers[i], NULL);
		printf("Thread joined\n");
	}

	for (int i = 0; i < 10; i++)
	{
		product_final = product_final * product[i];
	}

	printf("End product is %d\n", product_final);

	return 0;
}

void *multiply(void *param)
{
	int x = *((int*) param);
	printf("X is %d\n", x);
	int start = x * 10000;
	int end = start + 10000;
	int result = 1;
	for (int i = start; i <= end; i++)
	{
		result = result * input[i];
	}
	product[x] = result;

	pthread_exit(0);
	
}
