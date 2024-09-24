//
// Created by DELL on 2024/9/24.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_socket"

int main(){

    int sock;
    struct sockaddr_un server_addr;
    char message[] = "Hello, server!";

    if((sock = socket(AF_UNIX,SOCK_STREAM,0)) == -1){
        perror("socket");
        exit(1);
    }

    memset(&server_addr,0,sizeof(server_addr));

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path,SOCKET_PATH);

    if(connect(sock,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1){
        perror("connect");
        exit(1);
    }

    write(sock,message,strlen(message));

    close(sock);

    return 0;
}