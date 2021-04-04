#include <stdio.h>
#include <sys/types.h>	/* system type defintions */
#include <sys/socket.h>	/* network system functions */
#include <netinet/in.h>	/* protocol & struct definitions */
#include <stdlib.h>	/* exit() warnings */
#include <string.h>	/* memset warnings */
#include <unistd.h>

#define BUF_SIZE	1024
#define LISTEN_PORT	60000
#define NUM_RANGE 9

int main(int argc, char *argv[]){
    char * grid[NUM_RANGE][NUM_RANGE];
    int mysock,sock_recv;
    struct sockaddr_in  my_addr,recv_addr;
    int i,addr_size,bytes_received;
    int incoming_len,send_len;
    struct sockaddr remote_addr;
    int recv_msg_size;
    char buf[BUF_SIZE],msg[BUF_SIZE];



 void getNewBoard(){
        //creates a brand new blank board. Returns a pointer to the array 
        for (int j = 0; j < NUM_RANGE; j++){
            for (int k = 0; k < NUM_RANGE; k++)
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


/// need to expand this communicate() func
void communicate(){


 //receive msg from client

        


       //send msg to client
      strcpy(msg," Welcome to server,Enter a formula to send to server for evaluation or type 'quit'to exit");
      int bytes_sent=write(sock_recv,msg,BUF_SIZE);
  while (1){
        

        
       bytes_received=read(sock_recv,buf,BUF_SIZE);
        printf("received:%s\n", buf);
  
       buf[bytes_received]=0;
       msg[bytes_sent]=0;

       strcpy(msg,"Enter a formula to send to server for evaluation or type 'quit'to exit");
      int bytes_sent=write(sock_recv,msg,BUF_SIZE);
        
    if (strcmp(buf,"shutdown") == 0)
        break;
    }

    close(sock_recv);
    close(mysock);






    }
            





            /* create socket for listening */
    mysock=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mysock < 0){
        printf("socket() failed\n");
        exit(0);
    }
        /* make local address structure */
    memset(&my_addr, 0, sizeof (my_addr));  /* zero out structure */
    my_addr.sin_family = AF_INET;   /* address family */
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  /* current machine IP */
    my_addr.sin_port = htons((unsigned short)LISTEN_PORT);

        /* bind socket to the local address */
    i=bind(mysock, (struct sockaddr *) &my_addr, sizeof (my_addr));
    if (i < 0){
        printf("bind() failed\n");
        exit(0);
    }
    
    
        /* listen ... */
    
    i=listen(mysock, 5);
    if (i < 0){
        printf("listen() failed\n");
        exit(0);
    }




        /* get new socket to receive data on */
        /* It extracts the first connection request from the  */
    
    /* listening socket  */
    
    addr_size=sizeof(recv_addr);
    sock_recv=accept(mysock, (struct sockaddr *) &recv_addr, &addr_size);

    printf("A client has connected to this server\n");
    getNewBoard();
    drawBoard();
  

    communicate();



}