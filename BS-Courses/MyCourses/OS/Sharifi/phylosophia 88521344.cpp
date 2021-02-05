// Emad Aghajani
// 8852 1344
 
#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
 
#define N 5 //Philosopher Number

#define THINKING_S 0
#define HUNGRY_S 1
#define EATING_S 2

#define LEFT (ph_num+4)%N  // The left Philosopher number
#define RIGHT (ph_num+1)%N // The right Philosopher number 
sem_t mutex;
sem_t Semo[N];
 

void * myPhilospherFunc(void *num); // use as thread base
void get_fork(int);
void put_fork(int);
void check(int);
 
int state[N];
int phil_num[N];
 
int main()
{
    int i;
	
	for ( i=0; i<N ; i++ )
		phil_num[i] = i ;
    
	pthread_t thread_id[N];
    sem_init(&mutex,0,1);
    for(i=0;i<N;i++)
        sem_init(&Semo[i],0,0);
    for(i=0;i<N;i++)
    {
        pthread_create(&thread_id[i],NULL,myPhilospherFunc,&phil_num[i]);
        printf("Philosopher %d is Thinking\n",i+1);
    }
    for(i=0;i<N;i++)
        pthread_join(thread_id[i],NULL);
}
 
void *myPhilospherFunc(void *num)
{
    while(1)
    {
        int *i = num;
        sleep(1);
        get_fork(*i);
        sleep(0);
        put_fork(*i);
    }
}
 
void check(int ph_num)
{
    if (state[ph_num] == HUNGRY_S && state[LEFT] != EATING_S && state[RIGHT] != EATING_S)
    {
        state[ph_num] = EATING_S;
        sleep(2);
        printf("Philosopher %d Getting fork %d and %d\n",ph_num+1,LEFT+1,ph_num+1);
        printf("Philosopher %d is Eating\n",ph_num+1);
        sem_post(&Semo[ph_num]);
    }
}
 
 void get_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = HUNGRY_S;
    printf("Philosopher %d is Hungry\n",ph_num+1);
    check(ph_num);
    sem_post(&mutex);
    sem_wait(&Semo[ph_num]);
    sleep(1);
}
 
void put_fork(int ph_num)
{
    sem_wait(&mutex);
    state[ph_num] = THINKING_S;
    printf("Philosopher %d Putting fork %d and %d down\n",ph_num+1,LEFT+1,ph_num+1);
    printf("Philosopher %d is Thinking\n",ph_num+1);
    check(LEFT);
    check(RIGHT);
    sem_post(&mutex);
}