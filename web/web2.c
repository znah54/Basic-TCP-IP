#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define TRUE 1
#define BUF_SIZE 1024
#define SMALL_BUF 100

char webpage[] = "HTTP/1.1 200 OK\r\n"
                 "Server: Linux Web Server\r\n"
                 "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                 "<!DOCTYPE html>\r\n"
                 "<html><head><title> My Web Page </title>\r\n"
                 "<style>body {background-color: #FFFF00 }</style></head>\r\n"
                 "<body><center><h1>Hello world!!</h1><br>\r\n"
                 "<img src=\"cat.jpg\"></center></body></html>\r\n";

void error_handling(char *message) {
    perror(message);
    exit(1);
}

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t sin_len = sizeof(clnt_adr);
    char buf[BUF_SIZE];
    int option = TRUE;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");
    
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 20) == -1)
        error_handling("listen() error");

    while (1) {
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &sin_len);
        if (clnt_sock == -1) {
            perror("accept() error");
            continue;
        }

        printf("Connection Request: %s:%d\n", inet_ntoa(clnt_adr.sin_addr), ntohs(clnt_adr.sin_port));
        read(clnt_sock, buf, BUF_SIZE);
        printf("%s\n", buf);

        if (strstr(buf, "GET /cat.jpg") != NULL) {
            int img_fd = open("cat.jpg", O_RDONLY);
            if (img_fd == -1) {
                perror("open() error");
                close(clnt_sock);
                continue;
            }

            char img_buf[BUF_SIZE];
            ssize_t read_bytes, total_bytes = 0;

            while ((read_bytes = read(img_fd, img_buf, sizeof(img_buf))) > 0) {
                total_bytes += read_bytes;
            }
            lseek(img_fd, 0, SEEK_SET);

            sprintf(buf, "HTTP/1.1 200 OK\r\n"
                         "Server: Linux Web Server\r\n"
                         "Content-Type: image/jpeg\r\n"
                         "Content-Length: %ld\r\n\r\n", total_bytes);

            if (write(clnt_sock, buf, strlen(buf)) < 0) {
                perror("write() header error");
            }

            while ((read_bytes = read(img_fd, img_buf, sizeof(img_buf))) > 0) {
                if (write(clnt_sock, img_buf, read_bytes) < 0) {
                    perror("write() image error");
                    break;
                }
            }
            close(img_fd);
        } else {
            if (write(clnt_sock, webpage, sizeof(webpage)) == -1) {
                perror("write() webpage error");
            }
        }
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;
}
