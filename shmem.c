/**
 * Expression evaluation using shared memory.
 */
#include<stdio.h>
#include<stdlib.h>
#include<sys/shm.h>
int main(){
	pid_t pid;
	int a,b,c,d,e,f,res;
	key_t key;
	int segid;
	int *shp,*shc;

	pid=fork();
	if(pid>0){
		printf("Parent Process\n");
		sleep(3);
		printf("enter c and d\n");
		scanf("%d%d",&c,&d);
		e=c*d;
		segid = shmget(key,27,IPC_CREAT|0666);
		shp = shmat(segid,NULL,0);
		*shp = e;
		printf("value of c*d = %d\n",*shp);
		shmdt(shp);
	}else{
		printf("Child Process\n");
		printf("enter a and b\n");
		scanf("%d%d",&a,&b);
		f=a*b;
		sleep(3);
		segid = shmget(key,27,IPC_CREAT|0666);
		shc = shmat(segid,NULL,0);
		res = f+*shc;
		printf("result = %d\n",res);
	}
	return 0;
}
