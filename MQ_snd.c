/**
 * Message Queue Sender.
 */
#include<stdio.h>
#include<sys/msg.h>
#include<string.h>

struct msgbuf
{
	long int mtype;
	char mtext[100];
};

int main(){
	struct msgbuf buf;
	int msgid;
	int i=0;
	int key;
	
	printf("Enter a key:");
        scanf("%d",&key);

	msgid=msgget((key_t)key,0666|IPC_CREAT);
	if(msgid==-1){
		printf("\nError in creating..");
		return 0;
	}

	printf("\nEnter the message to be send : ");
	while(1){
		buf.mtype=1;
		scanf("%s",buf.mtext);
		msgsnd(msgid,(void*)&buf,100,0);
		if(strcmp(buf.mtext,"quit")==0)
			break;
		strcpy(buf.mtext,"\0");
		i++;
	}
	printf("Waiting for replay\n");
	while(i--){
		msgrcv(msgid,(void*)&buf,100,0,0);
		if(strcmp(buf.mtext,"quit")==0)
			break;
		printf(">%s\n",buf.mtext);
	}
	msgctl(msgid,IPC_RMID,0);
	return(0);
}
