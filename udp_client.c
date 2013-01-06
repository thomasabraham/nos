/**
 * UDP Client Program.
 */
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define BUF_SIZE 100

int main(){
	int port,sd,snd,clientlen,rec;
	struct sockaddr_in client;
	char buf[BUF_SIZE];
	
	printf("Enter the port to be used :");
        scanf("%d",&port);

	sd = socket(AF_INET,SOCK_DGRAM, 0);     //Create a socket
        if(sd<0){
                printf("Unable to create socket\n");
                return 0;
        }
	memset(&client,0,sizeof(client));
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port=port;
	
	printf("Enter message\n");
	while(1){
		scanf("%s",buf);
		snd=sendto(sd,buf,BUF_SIZE,0,
			(struct sockaddr*)&client,sizeof(client));
		if(snd<BUF_SIZE){
			printf("Sending failed.\n");
			continue;
		}
		rec=recvfrom(sd,buf,BUF_SIZE,0,
			(struct sockaddr*)&client,&clientlen);
		if(rec<0){
			printf("Receiving failed\n");
			continue;
		}
		printf(">%s\n",buf);
	}

	close(sd);
	return 0;
}
