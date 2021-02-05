// Masoud Jalili
// 88521103

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>


#define NUMBER_OF_PHILS 5


using namespace std;


pthread_mutex_t chopstick[NUMBER_OF_PHILS];


void* philosophers_work( void* ptr )
{
	int num = (int)ptr;

	clock_t start = clock(), now;

	while (true)
	{
		// Thinking
		printf("Philosopher %d starts Thinking!\n", num);
//		cout << "Philosopher " << num << " starts " << "Thinking!" << endl;
		usleep((rand()%20 + 5) * 100 * 1000);

		// Waiting
		printf("Philosopher %d starts Waiting!\n", num);
//		cout << "Philosopher " << num << " starts " << "Waiting!" << endl;
		if (num % 2 == 0)
		{
			pthread_mutex_lock(&chopstick[num]);
			pthread_mutex_lock(&chopstick[(num+1) % NUMBER_OF_PHILS]);

		}
		else
		{
			pthread_mutex_lock(&chopstick[(num+1) % NUMBER_OF_PHILS]);
			pthread_mutex_lock(&chopstick[num]);
		}

		// Dining
		printf("Philosopher %d starts Dining!\n", num);
//		cout << "Philosopher " << num << " starts " << "Dining!" << endl;
		usleep((rand()%20 + 5) * 100 * 1000);
		pthread_mutex_unlock(&chopstick[(num+1) % NUMBER_OF_PHILS]);
		pthread_mutex_unlock(&chopstick[num]);

		now = clock();
		if (now - start > 10)
			break;
	}

	pthread_exit( NULL );
}

int main()
{
	for (int i = 0; i < NUMBER_OF_PHILS; i++)
		chopstick[i] = PTHREAD_MUTEX_INITIALIZER;

	srand(time(NULL));

	pthread_t threads[NUMBER_OF_PHILS];

	void* (*t)(void*) = philosophers_work;


	for (int i = 0; i < NUMBER_OF_PHILS; i++)
	{
		pthread_create( &threads[i], NULL, t, (void*)i);
	}


	// Wait for join
	for (int i = 0; i < NUMBER_OF_PHILS; i++)
		pthread_join(threads[i], NULL);


	return 0;
}
