#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_ELEM_RECIBIDOS 1000
int ID=0;


int main()
{

        int i, sockfd, socket_aceptado;
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
        //my_addr.sin_addr.s_addr = inet_addr ("192.168.101.68"); // IP por donde recibira paquetes el programa

        // Asignando IP y puerto al socket
        if (-1 == bind (sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr) ))
        {
            perror("bind");
            exit(EXIT_FAILURE);
        }

        // Se habilita el socket para poder recibir conexiones.
        if (-1 == listen(sockfd, 50))
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        
        // Se llama a accept() y el servidor queda en espera de conexiones. accept() es bloqueante.
        addrlen = sizeof (struct sockaddr);
        socket_aceptado = accept(sockfd, (struct sockaddr *)&remote_addr, &addrlen);

        while (1)
        {
        //Recibiendo datos. recv() es bloqueante
        num_bytes_recibidos = recv(socket_aceptado, arr_recibido, sizeof(int)*MAX_ELEM_RECIBIDOS, 0);

        //Condicion de termino
        if (num_bytes_recibidos == sizeof(int) && arr_recibido[0] == -1)
        {
            close(socket_aceptado);
            break;
        }

        num_enteros_recibidos = num_bytes_recibidos/sizeof(int);
        for (i=0; i < num_enteros_recibidos; i++)
        {
            printf("%d", arr_recibido[i]);
        }
        printf("\n\n");
    }

    close(sockfd);
  
    

    return 0;
}