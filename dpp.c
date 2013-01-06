/**
 * Dining philosophers problem using thread and mutex.
 */
#include<stdio.h>
#include<pthread.h>

pthread_t phi[5];
pthread_mutex_t stick[5];
void* doit(int n);

int main(){
	int i,k;
	void *msg;
	for(i=0;i<5;i++){
		k=pthread_mutex_init(&stick[i],NULL);
		if(k!=0){
			printf("mutex creation failed\n");
			return 0;	
		}
	}
	for(i=0;i<5;i++){
		k=pthread_create(&phi[i],NULL,(void *)doit,(int *)i);
		if(k!=0){
			printf("Failed\n");
			return 0;
		}
	}
	for(i=0;i<5;i++){
		k=pthread_join(phi[i],NULL);
		if(k!=0){
			printf("Join failed\n");
			return 0;
		}
	}
	for(i=0;i<5;i++){
		k=pthread_mutex_destroy(&stick[i]);
		if(k!=0){
			printf("destroy failed\n");
			return 0;
		}
	}
	return 0;
}

void* doit(int i){
	printf("philosopher%d is thinking\n",i);
	pthread_mutex_lock(&stick[i]);
	pthread_mutex_lock(&stick[(i+1)%5]);
	printf("philosopther%d is eating\n",i);
	sleep(3);
	pthread_mutex_unlock(&stick[i]);
	pthread_mutex_unlock(&stick[(i+1)%5]);
	printf("philosopher%d is sleeping\n",i);
}
