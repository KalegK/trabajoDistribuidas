#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>


///mnt/c/users/kukya/desktop/universidad/s1 2021/sistemas distribuidos/trabajodistribuidas


struct map{
	char clave[50];
	char valores[4][50];
};



int main()
{
        struct map mapa1 = {"hola", {"primero.html", "segundo.html"}};
        struct map mapa2 = {"casa", {"tecero.html","cuarto.html"}};
        struct map mapa3 = {"auto", {"primero.html", "cuarto.html"}};
        struct map mapa[] = {mapa1, mapa2, mapa3};
        
        int i, sockfd, socket_aceptado;
        struct sockaddr_in my_addr;
        struct sockaddr_in remote_addr;
        int addrlen,buffer;
        char message[100];
        



        // Creacion del socket.
        sockfd = socket (AF_INET, SOCK_STREAM, 0); 

        my_addr.sin_family = AF_INET; //Protocolo TCP
        my_addr.sin_port = htons(3000); //Puerto
        my_addr.sin_addr.s_addr = inet_addr ("127.0.0.3"); // IP por donde recibira paquetes el programa
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

        printf("[+]Servidor creado\n");
        
        // Se llama a accept() y el servidor queda en espera de conexiones. accept() es bloqueante.
        addrlen = sizeof (struct sockaddr);
        socket_aceptado = accept(sockfd, (struct sockaddr *)&remote_addr, &addrlen);
        

        while(!strstr(message,"terminar")){
            read(socket_aceptado,message,100);
            if(strstr(message,"terminar")){
                close(socket_aceptado);
                break;
            }else{
                printf("....Buscando\n");
                printf("....Entregando resultados\n");

                for(int i =0; i<3;i++){
                    if(strstr( mapa[i].clave, message) ){
                        for(int j=0; j<2;j++){
                            write(socket_aceptado, mapa[i].valores[j],100);
                        }   
                    }else{
                        write(socket_aceptado,"no existe resultado\n",100);
                    }
                }
                
            }
        
        }
      

        close(sockfd);
  
    

    return 0;
}