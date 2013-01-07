/**
 * TCP Server program.
 */
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define BUF_SIZE 100
#define Q_SIZE 20

void reverse(char *c){
	int len = strlen(c);
	int i;
	char t;
	for(i=0;i<len/2;i++){
		t=c[i];
		c[i]=c[len-i-1];
		c[len-i-1]=t;
	}
}	

int main(){
	int port,sd,tsd,k,rec,snd;
	char buf[BUF_SIZE];
	struct sockaddr_in server,client;
	int clientlen;

	printf("Enter the port to be used :");
	scanf("%d",&port);

	sd = socket(AF_INET,SOCK_STREAM, 0);	//Create a socket
	if(sd<0){
		printf("Unable to create socket\n");
		return 0;
	}
	memset(&client,0,sizeof(client));
	memset(&server,0,sizeof(server));
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=port;
	k=bind(sd,(struct sockaddr*)&server, sizeof(server));
	if(k<0){
		printf("Binding Failed\n");
		return 0;	
	}

	k=listen(sd,Q_SIZE);
	if(k<0){
		printf("Error listening\n");
		return 0;
	}

	while(1){
		tsd=accept(sd,(struct sockaddr*)&client,&clientlen);
		if(tsd<0){
			printf("Error in accepting connection\n");
			return 0;
		}	

		rec=recv(tsd,buf,BUF_SIZE,0);
		if(rec<0){
			printf("Receive from client failed.\n");
			continue;
		}
		printf(">%s\n",buf);
		reverse(buf);
		snd=send(tsd,buf,BUF_SIZE,0);
		if(snd<BUF_SIZE){
			printf("Sending failed.\n");
			continue;
		}
		close(tsd);
	}

	close(sd);
	return 0;
}
