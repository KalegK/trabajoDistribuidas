#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct map{
	char clave[50];
	char valores[4][50];
};

void imprimir(struct map a[]);


int main(int argc, char const *argv[])
{

	struct map mapa1 = {"hola", {"primero.html", "segundo.html"}};
	struct map mapa2 = {"casa", {"tecero.html","cuarto.html"}};
	struct map mapa3 = {"auto", {"primero.html", "cuarto.html"}};
	struct map mapa[] = {mapa1, mapa2, mapa3};
	imprimir(mapa);
	printf("%s \n", mapa[0].clave);
	if(strstr( mapa[0].clave, "hola") ){
		imprimir(mapa[0]);
	}else{
		print("no existe resultado");
	}
	printf("\n");
	return 0;
}



void imprimir(struct map a[]){
	for (int i = 0; i < 3; ++i)
	{
		printf("clave: %s", a[i].clave);
		for (int j = 0; j < 2; ++j)
		{
			printf("\nvalor: %s", a[i].valores[j]);
		}
		printf("\n\n");
	}

}