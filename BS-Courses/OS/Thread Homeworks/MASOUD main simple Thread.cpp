// Masoud Jalili
// 88521103

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <vector>

#define NUMBER_OF_THREADS 10
#define NUMBER_OF_PRINTS 10

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
vector<char*> vec;

void* print_message_function( void* ptr )
{
	char* message;
	message = (char*) ptr;

	for (int i = 0; i < NUMBER_OF_PRINTS; i++)
	{
		printf("%s \n", message);

		pthread_mutex_lock(&mutex);
		vec.push_back(message);
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{

	pthread_t threads[NUMBER_OF_THREADS];

	char message[NUMBER_OF_THREADS][20];
	char number[2];

	void* (*t)(void*) = print_message_function;


	for (int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		strcpy(message[i], "Thread ");

		number[0] = i+'0';
		number[1] = 0;

		strcat(message[i], number);
		pthread_create( &threads[i], NULL, t, (void*) message[i]);
	}


	// Wait for join
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
		pthread_join(threads[i], NULL);


	cout << endl << "------------------ Some Statistics --------------------" << endl << endl;
	float per[NUMBER_OF_THREADS];

	for (int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		memset(per, 0, sizeof(per));

		for (int j = 0; j < NUMBER_OF_PRINTS; j++)
		{
			per[ vec[i * NUMBER_OF_PRINTS + j][7]-'0']++;
		}

		cout << "Prints from " << i * NUMBER_OF_PRINTS << " to " << (i+1) * NUMBER_OF_PRINTS << ":" << endl;

		for (int j = 0; j < NUMBER_OF_THREADS; j++)
			cout << "Thread " << j << " :" << 100 * per[j]/NUMBER_OF_PRINTS << "%" << endl;
		cout << "-----------------------------------" << endl << endl;
	}


	return 0;
}
