/****************************
	Emad Aghajani
	88511344
	pthread_cond_wait TEST
****************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  condition_var   = PTHREAD_COND_INITIALIZER;

void *functionCount1();
void *functionCount2();
int  count = 1;

main()
{
   pthread_t thread1, thread2;

   pthread_create( &thread1, NULL, &functionCount1, NULL);
   pthread_create( &thread2, NULL, &functionCount2, NULL);

   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);

   exit(0);
}

void *functionCount1() // print 1-5 then 11-15
{
	pthread_mutex_lock( &count_mutex);
	while ( count <= 5 )
		printf("# %d \n",count++);
	//count is 6
	pthread_cond_signal( &condition_var ); // func2 start printing
	
	pthread_cond_wait( &condition_var, &count_mutex ); // wait for func2 end signal
	
	while ( count <= 15 )
		printf("# %d \n",count++);
	
	pthread_mutex_unlock( &count_mutex );
		
	return NULL;
}
void *functionCount2() // print 6-10
{
	pthread_mutex_lock( &count_mutex);
	if ( count < 6 )
		 pthread_cond_wait( &condition_var, &count_mutex ); // unlock and wait
	
	while ( count <= 10 )
		printf("## %d \n",count++);
		
	pthread_cond_signal( &condition_var ); // func1 start second part
	
	pthread_mutex_unlock( &count_mutex );
	
	return NULL;
}
