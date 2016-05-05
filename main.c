#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include <signal.h>

#define MY_PORT 60004
void client();
void server();
int mySocket;
void ignoreMe();
int main(int argc,char *argv[])
{

if(argc==2)//if the user indicate the IP address , call client 
{

printf("Now you are the client\n");
signal(SIGINT,ignoreMe);//prevent the user use contro c to stop the program
client(argv);
}
  else//if the user doesn't indicate the IP address , call server
{
//signal(SIGINT, ignoreMe);
printf("Now you are the server\n");
signal(SIGINT,ignoreMe);
server();

}
}



void client(char *argv[])
{
  
  struct sockaddr_in  addr;
  int i,bytesRcv;

  char inStr[80];
  char buffer[80]; 
  char guess[80]; //for the guessing progress
  char word[80]; //storing the word that the opponent sent
  char sg[80];
  int correct=0;
  int choice;
  int play=1;
  int win=0;
/* create socket */
  
  mySocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (mySocket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }


/* setup address */
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(argv[1]);
  addr.sin_port = htons((unsigned short) MY_PORT);

/* connect to server */

  i = connect(mySocket, 
              (struct sockaddr *) &addr,
              sizeof(addr));
  if (i<0) {
    printf("client could not connect!\n");
    exit(-1);
  }
   
   
   // do 
 //{
    win=0;
    printf("what is your word?  ");//ask for the word
    fgets(inStr, sizeof(inStr), stdin);
    inStr[strlen(inStr)-1] = '\0';
    strcpy(buffer, inStr);
    send(mySocket, buffer, strlen(buffer), 0);//send to the user


	//receive the word from the opponent
    bytesRcv = recv(mySocket, buffer, sizeof(buffer), 0);
    buffer[bytesRcv] = '\0';
    strcpy(word,buffer);
    int length=strlen(buffer);
	int a;
       for(a=0;a<length;a++)//change the word into *
	{
        if(word[a]!=' ')
	{guess[a]='*';
         }
	else
	{
	guess[a]=' ';
	}
	} 
     guess[length]='\0';
   
/* get input from user and send to server */
  while (1) {
	correct=0;
    printf("This is opponent's word: ");
    printf("%s",guess);//display the guessing progress
  printf("\n");
   printf("What is your guess\n");//promote the user to type the letter or word
  fgets(buffer, sizeof(inStr), stdin);
    buffer[strlen(buffer)-1] = '\0';
  if(strlen(buffer)==1)
   {
    int i;
   for(i=0;i<length;i++)
	{
	if(buffer[0]==word[i])//check if the letter is in the word
	{
	guess[i]=buffer[0];
        correct=1;
	}
	}
	}
	
  else
  {
	if(strcmp(word,buffer)==0)//if the word the user enter is correct
	{
	strcpy(guess,word);
	
	correct=1;
	
	 win=1;
        
        }
 }
if(correct==0)//if it is not correct
{
	printf("incorrect!\n");
}
	send(mySocket, guess, strlen(guess), 0);
       bytesRcv = recv(mySocket, buffer, sizeof(buffer), 0);
       buffer[bytesRcv] = '\0';
       strcpy(sg,buffer);
	printf("This is what opponent's guess: %s\n",sg);
       	if(strcmp(sg,inStr)==0)
	{
	printf("you lose!\n");
	break;
      
      }
     if(strcmp(word,guess)==0||win==1)//if the user wins
	{
	printf("You win the game!\n");
        win=1;
	printf("what do you want to do ?");
	printf("1---play one more round!\n");
	printf("2---quit!\n");
	scanf("%d",&choice);
	break;
	
	}
    
    
       
       

   
  }
 
  

/* close the socket */

  close(mySocket);

  
}
void server()
{

  int myListenSocket;
  struct sockaddr_in  myAddr, clientAddr;
  int i, addrSize, bytesRcv,correct;
   char inStr[80];
  char buffer[30];
   char guess[80]; 
  char word[80];
   char cg[80];
  int choice;
  int win=0;
  int play=0;

/* create socket */

  myListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (myListenSocket < 0) {
    printf("couldn't open socket\n");
    exit(-1);
  }


/* setup my server address */
  memset(&myAddr, 0, sizeof(myAddr));
  myAddr.sin_family = AF_INET;
  myAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myAddr.sin_port = htons((unsigned short) MY_PORT);

/* bind my listen socket */

  i = bind(myListenSocket, 
           (struct sockaddr *) &myAddr,
           sizeof(myAddr));
  if (i < 0) {
    printf("couldn't bind socket\n");
    exit(-1);
  }


/* listen */
  i = listen(myListenSocket, 1);
  if (i < 0) {
    printf("couldn't listen\n");
    exit(-1);
  }


/* wait for connection request */

  addrSize = sizeof(clientAddr);

  mySocket = accept(myListenSocket,
                        (struct sockaddr *) &clientAddr,
                        &addrSize);
  if (mySocket < 0) {
    printf("couldn't accept the connection\n");
    exit(-1);
  }

   win=0;
 printf("What is your word?\n");//promote the user to enter the word
  

    fgets(inStr, sizeof(inStr), stdin);
    inStr[strlen(inStr)-1] = '\0';
    strcpy(buffer, inStr);
    send(mySocket, buffer, strlen(buffer), 0);//send to the opponent

    bytesRcv = recv(mySocket, buffer, sizeof(buffer), 0);//receive word from opponent
    buffer[bytesRcv] = '\0';
    strcpy(word,buffer);
    int length=strlen(buffer);
	int a;
       for(a=0;a<length;a++)//change the word into *
	{
	if(word[a]!=' ')
	{guess[a]='*';
         }
	else
	{
	guess[a]=' ';
	}
	} 
     guess[length]='\0';

/* read message from client and do something with it */
 while (1) {
    correct=0;
    printf("This is opponent's word: ");//display guessing progress
    
  
   printf("%s",guess);
  printf("\n");
   printf("What is your guess\n");
  fgets(buffer, sizeof(inStr), stdin);
    buffer[strlen(buffer)-1] = '\0';
  if(strlen(buffer)==1)
   {
    int i;
   for(i=0;i<length;i++)//if the letter the user enter is in the word
	{
	if(buffer[0]==word[i])
	{
	guess[i]=buffer[0];
	correct=1;
	}
	}

    
   }
	
  else
  {
	if(strcmp(word,buffer)==0)//if the user enter the correct word
	{
	strcpy(guess,word);
	
	correct=1;
  	win=1;
	
  
	}
	
	
	
       
   }
	if(correct==0)//if it is incorrect
{
	printf("incorrect!\n");
}
      send(mySocket, guess, strlen(guess), 0);
       bytesRcv = recv(mySocket, buffer, sizeof(buffer), 0);
       buffer[bytesRcv] = '\0';
       strcpy(cg,buffer);
	 printf("This is what opponent's guess: %s\n",cg);//display the opponent's guessing progress
       if(strcmp(cg,inStr)==0)
	{
	printf("you lose!\n");
	break;
	}

      if(strcmp(word,guess)==0||win==1)//let the winner choose
	{
	printf("You win the game!\n");
	printf("what do you want to do ?\n");
	printf("1---play one more round!\n");
	printf("2---quit!\n");

	scanf("%d",&choice);
	break;
	
	}
    printf("\n");
	
  } 

/* close sockets */

  close(myListenSocket);
  close(mySocket);

  
}

void ignoreMe()
{
printf("IGNORE");
}


