/**
 * TCP Client Program.
 */
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define BUF_SIZE 100

int main(){
	int port,sd,snd,clientlen,rec,k;
	struct sockaddr_in client;
	char buf[BUF_SIZE];
	
	printf("Enter the port to be used :");
        scanf("%d",&port);

	sd = socket(AF_INET,SOCK_STREAM, 0);     //Create a socket
        if(sd<0){
                printf("Unable to create socket\n");
                return 0;
        }
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=port;
	
	k=connect(sd,(struct sockaddr*)&client,sizeof(client));
	if(k<0){
		printf("Unable to connect to server.\n");
		return 0;
	}
	
	printf("Enter message\n");
	scanf("%s",buf);
	snd=send(sd,buf,BUF_SIZE,0);
	if(snd<BUF_SIZE){
		printf("Sending failed.\n");
		return 0;
	}
	rec=recv(sd,buf,BUF_SIZE,0);
	if(rec<0){
		printf("Receiving failed\n");
		return 0;
	}
	printf(">%s\n",buf);

	close(sd);
	return 0;
}
