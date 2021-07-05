#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_ELEM_RECIBIDOS 1000

int main()
{
    int i, sockfd, socket_aceptado, num;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    int addrlen;
    int *arr_recibido, num_bytes_recibidos, num_enteros_recibidos;
    arr_recibido = (int *)malloc(sizeof(int)*MAX_ELEM_RECIBIDOS);

    // Creacion del socket.
    sockfd = socket (AF_INET, SOCK_STREAM, 0); 

    my_addr.sin_family = AF_INET; //Protocolo TCP
    my_addr.sin_port = htons(3000); //Puerto
    my_addr.sin_addr.s_addr = inet_addr ("127.0.0.2"); // IP por donde recibira paquetes el programa

    //int connect ( int sockfd, struct sockaddr *serv_addr, int addrlen )
    connect (sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));

    while(1)
    {
        scanf("%d", &num);

        send(sockfd, &num, sizeof(int), 0);

        if (num == -1)
            break;
    }

    close(sockfd);

    return 0;
}

