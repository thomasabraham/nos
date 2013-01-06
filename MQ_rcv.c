/**
 * Message Queue receiver.
 */
#include<sys/msg.h>
#include<stdio.h>
#include<string.h>
struct mbuf{
	long int mtype;
	char mtext[100];
};

int main(){
	struct mbuf buf;
	int msgid,i,len,j=0;
	int key;
	char temp[100][100];

	printf("Enter a key:");
	scanf("%d",&key);

	printf("Initializing Message Queue\n");
	msgid=msgget((key_t)key,0666|IPC_CREAT);
	printf("The received data is \n");
	if(msgid==-1){
		printf("\nError in creating Message queue..");
		return 0;
	}
	while(1){
		strcpy(buf.mtext,"\0");
		strcpy(temp[j],"\0");
		buf.mtype=1;
		msgrcv(msgid,(void*)&buf,100,0,0);
		if(strcmp(buf.mtext,"quit")==0)
			break;
		printf(">%s\n",buf.mtext);
		strcpy(temp[j],buf.mtext);
		j++;
	}
	printf("Sending replay.\n");
	for(i=0;i<j;i++){
		buf.mtype=2;
		strcpy(buf.mtext,temp[i]);
		msgsnd(msgid,(void*)&buf,100,0);
	}	
	printf("Sending Quit\n");
	if(i==j){
		strcpy(buf.mtext,"quit");
		msgsnd(msgid,(void*)&buf,100,0);
	}
	return(0);
}
