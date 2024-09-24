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

    int server_fd,client_fd;
    struct sockaddr_un server_addr,client_addr;
    socklen_t addr_size;
    char buffer[1024];

    if((server_fd = socket(AF_UNIX,SOCK_STREAM,0)) == -1){
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr,0,sizeof(server_addr));

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path,SOCKET_PATH);

    if(bind(server_fd,(struct sockaddr*)&server_addr,sizeof(server_addr)) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(server_fd,5) == -1){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    addr_size = sizeof(client_addr);
    if((client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&addr_size)) == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    read(client_fd,buffer,sizeof(buffer) - 1);
    printf("Received : %s\n",buffer);

    close(client_fd);
    close(server_fd);

    unlink(SOCKET_PATH);
    return 0;
}