#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

int main(){

    char* ch;
    int clientSocket,ret;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0); // creating client socket
    if (clientSocket <0){
        printf("[-]Connection Error!");
        exit(1);
    }
    printf("[+]Client Socket Created Sucessfully.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr)); /* zero out structure */ 

    serverAddr.sin_family = AF_INET; //address family
    serverAddr.sin_port = htons(PORT);  //port #
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Machine IP

            /*Connects Client to Server*/
    ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret < 0){
        printf("[-]Connection Error.");
        exit(1);
    }
    printf("[+]Connected to Server.\n");
    
    while (1){   
        printf("Enter Input: \n");
        scanf("%s" , &buffer[0]);


            //Send some data to server
        send(clientSocket , buffer , strlen(buffer) , 0);// send formula

        if (strcmp(buffer,"shutdown") == 0){

            break;  
        }

        //Receive a reply from the server
        //if(recv(clientSocket , buffer , 1024 , 0) < 0){
        //    printf("[-]Error in Serverreply");
        //}
        //else{
        //    puts("Server Echo:");
        //    puts(buffer);
        //}
    }

    //printf("[+]Data Recv: %s\n", server_reply);
    printf("Closing the connection.\n");
    close(clientSocket);

} 