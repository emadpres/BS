#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


#define NUMBER_OF_CUSTOMERS 20


using namespace std;


pthread_mutex_t cutting_mutex;
pthread_cond_t customer_cond, barber_cond;

int cutOperation; /* -1: Barber free and no request|| #: Barber is cutting customer number # */


void* customer_work( void* ptr )
{
	int num = (int)ptr;

	pthread_mutex_lock(&cutting_mutex);
	while(cutOperation!=-1) pthread_cond_wait(&customer_cond, &cutting_mutex);
	cutOperation=num;
	
	cout << "I'm Number "<<num<<" Need Cut"<<endl;
	pthread_cond_signal(&barber_cond);
	pthread_mutex_unlock(&cutting_mutex);	
	
	pthread_exit( NULL );
}

void* barber_work( void* ptr )
{
	cout<<"SHOP IS OPEN !\n";
	for ( int i=0; i<NUMBER_OF_CUSTOMERS; i++ )
	{
		pthread_mutex_lock(&cutting_mutex);
		while(cutOperation==-1) pthread_cond_wait(&barber_cond, &cutting_mutex);
		cout << "Welcome number: "<<cutOperation<<flush;
		sleep(2);
		cout << "\t\tNumber: "<<cutOperation<<" has cut \n";
		
		cutOperation=-1;
		pthread_cond_signal(&customer_cond);
		pthread_mutex_unlock(&cutting_mutex);
	}
	cout<<"\n\n\nSHOP IS CLOSE !\n\n";
	pthread_exit( NULL );

}

int main()
{
	cutOperation=-1;

	pthread_mutex_init(&cutting_mutex, NULL);

	pthread_cond_init(&customer_cond, NULL);
	pthread_cond_init(&barber_cond, NULL);

	pthread_t  barber_thread, customer_thread[NUMBER_OF_CUSTOMERS];


	void* (*c)(void*) = customer_work;
	void* (*b)(void*) = barber_work;

	pthread_create( &barber_thread, NULL, b, NULL);

	for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
	{
		pthread_create( &customer_thread[i], NULL, c, (void*)i);
	}


	// Wait for join
	pthread_join(barber_thread, NULL);
	for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++)
		pthread_join(customer_thread[i], NULL);


	return 0;

}

