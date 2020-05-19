#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/wait.h>


void run (char * commands,char [] ); // execute command
char name [20];
char pass [10];
int main(int argc, char const *argv[])
{
  char command[256]; //command array
  int PORT = atoi(argv[2]);
  strcpy(name, argv[4]);
  strcpy(pass, argv[6]);

    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int flag=1;
    char commands2[1024] = {0};
    valread = read( new_socket , commands2, 1024);
    printf("%s\n",commands2 );
    strcpy(commands2,"true");
    send(new_socket , commands2 , strlen(commands2) , 0 );


    while(flag!=0){
      char commands[1024] = {0};
      valread = read( new_socket , commands, 1024);
      printf("%s\n",commands );
      char output[1024] = {0};
      run(commands,output);
      send(new_socket , output , strlen(output) , 0 );
    }

    close(new_socket);
    return 0;
}

void run(char * commands, char output[]){
  char buf[1024]="";
  int i = 0;
  FILE *p = popen(commands,"r");
  if (p != NULL )
  {
      while (!feof(p) && (i < 1023) )
      {
          fread(&buf[i++],1,1,p);
      }
      buf[i] = 0;
      pclose(p);
      strcpy(output,buf);
  }
 else {
   //strcpy(output,"Error occured");
   printf("fsdaf\n" );
 }
}
