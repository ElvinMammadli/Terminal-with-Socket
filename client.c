#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[1024];
    char name [1024];
    char pass [10];
    strcpy(name, argv[4]);
    strcpy(pass, argv[6]);
    int PORT = atoi(argv[2]);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Socket creation error");
        return -1;
    }


    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("Invalid address/ Address not supported");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("Connection Failed");
        return -1;
    }
    int flag=1;
    send(sock , name , strlen(name) , 0 );
    char buffer2[1024] = {0};
    strcpy(name,pass);
    valread = read( sock , buffer2, 1024);
    printf("buf2 %s\n",buffer2 );

    while(flag!=0){
      char buffer[1024] = {0};

    printf("Write your message\n");
  scanf(" %[^\n]%*c",hello);
    send(sock , hello , strlen(hello) , 0 );

    valread = read( sock , buffer, 1024);
    printf("%s",buffer );
  }
  close(sock);
    return 0;
}
