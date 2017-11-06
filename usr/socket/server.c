/*Required Headers*/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
 
int find(char *str, char ci, int n);
char format(char *str);

int main()
{
    printf("HermitCore simple Socket echo server is running\n"); 
    char str[100];
    char file[100];
    int listen_fd, comm_fd;
    int count;
    FILE *fp; 
    struct sockaddr_in servaddr;
    struct dirent *dp;
 
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    bzero( &servaddr, sizeof(servaddr));
 
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    servaddr.sin_port = htons(22000);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    listen(listen_fd, 10);
 
    printf("IP address is: %s\n", inet_ntoa(servaddr.sin_addr));
    printf("port is: %d\n", (int) ntohs(servaddr.sin_port));
    count = 0;

    while(1) {

        printf("%d connections served. Accepting new client...\n", count);
        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
        bzero(str, 100);
        read(comm_fd, str,100); 
/*
  if (file != NULL){
    if fopen(f, 'r') // fopen
      fwrite
      "HTTP/1.0 200 OK\r\n"
      "Content-Length: %d\r\n\r\n",length
      "file content" 
    else
      write(comm_fd, "HTTP/1.0 404 Not Found\r\n", 23);
  }
  else
    write(comm_fd, "HTTP/1.0 400 Bad Request\r\n", 26);
    send 400 bad request
*/ 
  
        strcpy(file, format(str));
        
        write(comm_fd, file, strlen(file)+1);
        printf("debug\n"); 
        count++;
    }
}

int find(char *str, char c, int n){
    char *tmp; 
    tmp=strchr(str+n, c);
    return (tmp - str + 1);
}

char format(char *str) {
    char get[3], Get[3] = "GET"; // "GET"
    char protocol[8], Protocol[8] = "HTTP/1.0";   // "HTTP/1.0"
    int i;
    int first, second, cr;
    first = find (str, ' ', 0);
    second = find (str, ' ', first);
    cr = find (str, '\r', 0);

    strncpy(get, str, first-1);
    strncpy(protocol, str+second, cr-1);

    for (i =0; i <first; i++){
        if(get[i] !=Get[i])
            return NULL;
    }

    for (i = 0; i < (cr-second); i++){
        if( protocol[i] != Protocol[i])
            return NULL;
    }
        
    char file[second-first];
    
    //debug here!!
    strncpy(file, str+first, second-first);

    return file;
}
