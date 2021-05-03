#include<stdio.h>
#include<stdlib.h>

#include "code.h"
 
void findpath (int** prices,int total, int* mejorsuma, int* mejorsecuencia, int* camino, int* visited){
    
    printf("suma total es %d", total);
    for (int nodeindex = 0; nodeindex < total; nodeindex +=1){
        printf("INICIANDO %d\n", nodeindex);

        move(camino, 0, nodeindex, 0, total, visited, prices, mejorsecuencia, mejorsuma);
    }

}

void move(int* camino, int paso, int position, int costo, int total, int* visited, int** prices, int* mejorsecuencia, int* mejorsuma){

    visited[position] = 1;
    camino[paso] = position;

    int suma = 0;
    for (int i=0; i<total; i++){
        suma += visited[i];
    }
    printf("suma = %d\n", suma);

    if (suma == total){
        // Lo meto a mejor opcion hasta el minuto si es mejor que la guardada
        if (*mejorsuma > costo){
            printf("Llegue al final\n");
            char lista[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            printf("valor = %d\n", costo);

            *mejorsuma = costo;
            for (int i=0; i<total; i+=1){
                mejorsecuencia[i] = camino[i];
                printf("nodo %c|", lista[camino[i]]);

            }
            printf("\n");

        }
        visited[position] = 0;
        return;
    }
    // Osino no he completado el camino
    for (int i=0; i<total; i++){
        // Si era una opción válida 
        // printf("suma = %d\n",prices[position][i] );
        if((prices[position][i] > 0) && (visited[i] == 0)){
            //printf("COSTO ES %d\n", prices[position][i]);

            // Guardo en el camino la secuencia con este nodo agregado (nodo 0=A)
            camino[paso] = position;
            move(camino, paso + 1, i, costo + prices[position][i], total, visited, prices, mejorsecuencia, mejorsuma);
        }
    }
    visited[position] = 0;
    return;

}
int main()
{
    int total = 7;
    int* fila = calloc(7, sizeof(int));
    int** matrix = calloc(7, sizeof(int*));
    int* fila1 = calloc(7, sizeof(int*));
    fila1[0]=0;
    fila1[1]=10;
    fila1[2]=-1;
    fila1[3]=8;
    fila1[4]=7;
    fila1[5]=-1;
    fila1[6]=-1;
    int* fila2 = calloc(7, sizeof(int*));
    fila2[0]=10;
    fila2[1]=0;
    fila2[2]=12;
    fila2[3]=7;
    fila2[4]=-1;
    fila2[5]=-1;
    fila2[6]=-1;
    int* fila3 = calloc(7, sizeof(int*));
    fila3[0]=-1;
    fila3[1]=12;
    fila3[2]=0;
    fila3[3]=6;
    fila3[4]=-1;
    fila3[5]=7;
    fila3[6]=5;
    int* fila4 = calloc(7, sizeof(int*));
    fila4[0]=8;
    fila4[1]=7;
    fila4[2]=6;
    fila4[3]=0;
    fila4[4]=9;
    fila4[5]=4;
    fila4[6]=-1;
    int* fila5 = calloc(7, sizeof(int*));
    fila5[0]=7;
    fila5[1]=-1;
    fila5[2]=-1;
    fila5[3]=9;
    fila5[4]=0;
    fila5[5]=-1;
    fila5[6]=-1;
    int* fila6 = calloc(7, sizeof(int*));
    fila6[0]=-1;
    fila6[1]=-1;
    fila6[2]=7;
    fila6[3]=4;
    fila6[4]=-1;
    fila6[5]=0;
    fila6[6]=3;
    int* fila7 = calloc(7, sizeof(int*));
    fila7[0]=-1;
    fila7[1]=-1;
    fila7[2]=5;
    fila7[3]=-1;
    fila7[4]=-1;
    fila7[5]=3;
    fila7[6]=0;
    matrix[0]= fila1;
    matrix[1]= fila2;
    matrix[2]= fila3;
    matrix[3]= fila4;
    matrix[4]= fila5;
    matrix[5]= fila6;
    matrix[6]= fila7;


	int* mejorsuma = calloc(1, sizeof(int));
    *mejorsuma = 1000000;
    int* mejorsecuencia = calloc(total, sizeof(int));
    int * camino = calloc(total, sizeof(int));
    int * visited = calloc(total, sizeof(int));
    findpath(matrix, total, mejorsuma, mejorsecuencia, camino, visited);
    printf("Best price is %d \n", *mejorsuma);
	
	return 0;
}