#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9999

#define NUM_RANGE 9
#define SIZE 26

char * grid[NUM_RANGE][NUM_RANGE];

void getNewBoard(){
    //creates a brand new blank board. Returns a pointer to the array 
    int j,k;
    //char * grid[NUM_RANGE][NUM_RANGE];
    for (j = 0; j < NUM_RANGE; j++){
        for (k = 0; k < NUM_RANGE; k++)
        {
            grid[k][j]="   ";
        }//Endfor
    }//Endfor
    return;
}//EndFunction getNewBoard
void drawBoard(){
    int j,k;
    //This function prints out the board that was passed. Returns void
    char * const NLINE = "    A    B    C    D    E    F    G    H    I";
    char * const HLINE = "  +----+----+----+----+----+----+----+----+----+";
    char * const VLINE = "  |    |    |    |    |    |    |    |    |    |";

    printf("%s\n",NLINE);
    printf("%s\n",HLINE);
    for (j = 0; j < NUM_RANGE; j++)
    {  
        printf("%s\n",VLINE);
        printf("%d ",j+1);
        for (k = 0; k < NUM_RANGE; k++)
        {  if(strcmp(grid[k][j],"   ")==0){
                printf("| %s",grid[k][j]);
            }else{
                printf("| %s  ",grid[k][j]);
            }
        }
        printf("%s","|");
        printf("\n");
        printf("%s\n",VLINE);
        printf("%s\n",HLINE);
    }
    return;
}//EndFunction drawBoard
void makePlay(int x, int y, char* c){
    //Arrays are zero indexed but our grid starts at index 1
    grid[x-1][y-1]=c;
    
    return;
}//EndFunction makePlay
void startBoard(int *num, char*l){
    //struct startPlays p1;
    for (int i = 0;i<11;i++)
    {
        printf("%d %d %c \n",*(num +i),*(num +i+11),*(l+i));
        //makePlay(*(num +i),*(num +i+10),strcat(*(l+i),"");
    }
//create fun to generate ran num 1-9, add to array(compare to previous to prevent duplicates)
}//EndFunction startBoard



int Average(int num1, int num2)
{
	return 0;
}
int Sum(int num1, int num2)
{
	return 0;
}
int Range(int num1, int num2)
{
	return 0;
}

void saveWorksheet()
{

}

int main(){

	int listeningsock,ret;
	struct sockaddr_in host_addr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	char buffer[1024]; //toSend data
    pid_t childpid;

	//char client_message[1024]; //toRec data

	listeningsock = socket(AF_INET, SOCK_STREAM, 0); //creating socket on server side ..socket(domain,type of input,IP)
	if (listeningsock <0){
        printf("[-]Connection Error!\n");
        exit(1);
    }
    printf("[+]Server Socket Created Sucessfully.\n");

	    //creating an address to bind to
	memset(&host_addr, '\0', sizeof(host_addr)); 	/* zero out structure */
	host_addr.sin_family = AF_INET;		//address family 
	host_addr.sin_port = htons(PORT);
	host_addr.sin_addr.s_addr = inet_addr("127.0.0.1");	//host machine IP 	*port #

		/* bind socket to the local address */
    ret = bind(listeningsock, (struct sockaddr*)&host_addr, sizeof(host_addr));
	if (ret < 0){
		printf("[-]Binding failed.\n");
        exit(1);
	}
    printf("[+]Binding sucessful, port: %d\n", 4444);

	if(listen(listeningsock, 10) == 0){
        printf("[+]Listning...\n");
    }
    else{
        printf("[-] Error.\n");
    }

    while(1){
        newSocket = accept(listeningsock, (struct sockaddr*)&newAddr, &addr_size);
        if (newSocket < 0){
            exit(1);
        }
        printf("[+] Connection successful from %s %d\n", inet_ntoa(newAddr.sin_addr) ,ntohs(newAddr.sin_port));
        if ((childpid = fork()) == 0){
            close(listeningsock);

            while (1){
                recv(newSocket,buffer,1024,0); //Get x
                if (strcmp(buffer,"shutdown") == 0){
                    printf("[+] Disconnected from %s %d\n", inet_ntoa(newAddr.sin_addr),ntohs(newAddr.sin_port));
                    break;
                }//use else if to terminate if 1st client 'shutdown' 0.0.0.0
                else{
                    // get formula and other data to input in grid 
                    getNewBoard();
                    drawBoard();
                    printf("Client: %s\n", buffer);
                    //send(newSocket,buffer,strlen(buffer),0); //- send grid to client 
                    //bzero(buffer,sizeof(buffer));
                }
            }
        }
    }
    close(newSocket);
    return 0;
}
