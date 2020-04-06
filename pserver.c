#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 800 
#define PORT 8080 
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char buff[MAX]; 
	//char msg[MAX];
	int n; 
	// infinite loop for chat 
	for (;;) { 
		bzero(buff, MAX); 

		// read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("From client: ", buff);
        if (strncmp("A",buff,1)==0)
        {
            char msg[]= "I am chatbot which was developed as a part of Lab project"
						"\nAuthors- Vaibhav Raj, Divyansh Raina and Shreyas Shirodkar";
            char *p = msg;
            bzero(buff,MAX);
            memcpy(buff,p,sizeof(msg));	
        }
		else if (strncmp("B", buff,1) == 0)
		{
			char msg[]= "People's Education Society (PES) University Ring Road Campus." 
						"\nFormerly PES Institute of Technology"
						"\nIt is one of three private universities under the name PES University in Bengaluru, India." 
						"\nEstablished in 1972, it is focused on five main educational areas:"
						"\nEngineering, Medicine, Management, Law and Life Sciences.";
            char *p = msg;
            bzero(buff,MAX);
            memcpy(buff,p,sizeof(msg));	
		}
        else if (strncmp("C", buff,1) == 0)
		{
			char msg[]= "1) ISA 2 postponded due to Corona pandemic.\n"
						"2) No information yet about the end semester examinations.\n";
            char *p = msg;
            bzero(buff,MAX);
            memcpy(buff,p,sizeof(msg));
		}		 
		else if (strncmp("D", buff,1) == 0)
		{
			char msg[]= "1)Good Friday\n"
						"2)Online classes going on as scheduled.\n";
            char *p = msg;
            bzero(buff,MAX);
            memcpy(buff,p,sizeof(msg));	 
		}
		else if (strncmp("E", buff,1) == 0)
		{
			char msg[]= "1) Rotoract Club\n""2) AEOLUS Club\n""3) CyberPunk Squad\n""4) CODS \n""5) CDSAML\n";
            char *p = msg;
            bzero(buff,MAX);
            memcpy(buff,p,sizeof(msg));
		}
		else if(strncmp("exit", buff, 4) != 0)
		{	
			char google[50]="firefox https://www.google.com/?q=";
    		strcat(google,buff);
    		system(google);
		}
		

		

		// and send that buffer to client 
		write(sockfd, buff, sizeof(buff)); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		}
    }
}    

// Driver function 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully created..\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("socket bind failed...\n"); 
		exit(0); 
	} 
	else
		printf("Socket successfully binded..\n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("Listen failed...\n"); 
		exit(0); 
	} 
	else
		printf("Server listening..\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*)&cli, &len); 
	if (connfd < 0) { 
		printf("server acccept failed...\n"); 
		exit(0); 
	} 
	else
		printf("server acccept the client...\n"); 

	// Function for chatting between client and server 
	func(connfd); 

	// After chatting close the socket 
	close(sockfd); 
} 
