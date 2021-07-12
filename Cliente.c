#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define MAX_ELEM_RECIBIDOS 1000
#define SEND_TAG 2

int main()
{
    int i, sockfd, socket_aceptado, num;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;
    int addrlen;
    char send_message[1000]="mensaje";
    char message[100];



    // Creacion del socket.
    sockfd = socket (AF_INET, SOCK_STREAM, 0); 

    my_addr.sin_family = AF_INET; //Protocolo TCP
    my_addr.sin_port = htons(3000); //Puerto
    my_addr.sin_addr.s_addr = inet_addr ("127.0.0.3"); // IP por donde recibira paquetes el programa


    connect (sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr));
    printf("[+]Cliente conectado\n");

    while(1){ 
            gets(send_message);     
            if(!strstr(send_message,"terminar")){
                write(sockfd,send_message,strlen(send_message)+1);
                printf("busqueda para -->  ");
                for(int i=0; i<2 ; i++){
                    read(sockfd,message,100);
                    printf("%s \n\n",message);
                }
                
       
            }
        }

   

    close(sockfd);


    
    

    return 0;
}

