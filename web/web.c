#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <fcntl.h>

#define TRUE 1
#define BUF_SIZE 1024
#define SMALL_BUF 100

char webpage [] = "HTTP/1.1 200 OK\r\n"
							"Server:Linux Web Server\r\n"
							"Content-Type: text/html: charset=UTF-8\r\n\r\n"
							"<!DOCTYPE html>\r\n"
							"<html><head><title> My Web Page </title>\r\n"
							"<style>body {background-color: #FFFF00 }</style></head>\r\n"
							"<body><center><h1>Hello world!!</h1><br>\r\n"
							"<img src=\"cat.jpg\"></center></body></html>\r\n";

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t sin_len = sizeof(clnt_adr);
	int clnt_adr_size;
	char buf[BUF_SIZE];
	int option = TRUE;
	int a,b;
	char img_buf[1024];

	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int));

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET;
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
		perror("bind() error");
	if(listen(serv_sock, 20)==-1)
		perror("listen() error");

	while(1)
	{
		clnt_adr_size=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &sin_len);
		printf("Connection Request : %s:%d\n", 
			inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
		read(clnt_sock, buf, BUF_SIZE);
		printf("%s\n",buf);

	if((buf,"GET/cat.jpg")!=NULL){
		a = open("cat.jpg", O_RDONLY);
		if(b=read(a,img_buf,sizeof(img_buf))==-1)
		close(a);

		sprintf(buf,"HTTP/1.1 200 OK\r\n"
		"Server:Linux Web Server\r\n"
		"Content-Type: image/jpeg\r\n"
		"Content-Length: %ld\r\n\r\n", b);

	if(write(clnt_sock,buf,strlen(buf)) < 0) puts("error");
		if(write(clnt_sock,img_buf,b) < 0) puts("error");
		close(clnt_sock);
	}
	else
		if(write(clnt_sock, webpage, sizeof(webpage))==-1)
			close(clnt_sock);
			}
			close(serv_sock);
			return 0;
			}
