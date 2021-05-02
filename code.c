#include<stdio.h>
#include<stdlib.h>

#include "code.h"
 
void findpath (uint32_t** prices,uint32_t total, uint32_t* mejorsuma, uint32_t* mejorsecuencia){
    
    uint32_t * camino = calloc(total, sizeof(uint32_t));
    uint32_t * visited = calloc(total, sizeof(uint32_t));

    for (uint32_t nodeindex = 0; nodeindex < total; nodeindex +=1){
        printf("INICIANDO %d\n", nodeindex);

        move(camino, 0, nodeindex, 0, total, visited, prices, mejorsecuencia, mejorsuma);
    }

}

void move(uint32_t* camino, uint32_t paso, uint32_t position, uint32_t costo, uint32_t total, uint32_t* visited, uint32_t** prices, uint32_t* mejorsecuencia, uint32_t* mejorsuma){

    visited[position] = 1;
    camino[paso] = position;

    uint32_t suma = 0;
    for (uint32_t i=0; i<total; i++){
        suma += visited[i];
    }
    //printf("suma = %d\n", suma);

    if (suma == total){
        // Lo meto a mejor opcion hasta el minuto si es mejor que la guardada
        if (*mejorsuma > costo){
            printf("Llegue al final\n");
            char lista[7] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
            printf("valor = %d\n", costo);

            *mejorsuma = costo;
            for (uint32_t i=0; i<total; i+=1){
                mejorsecuencia[i] = camino[i];
                printf("nodo %c|", lista[camino[i]]);

            }
            printf("\n");

        }
        visited[position] = 0;
        return;
    }
    // Osino no he completado el camino
    for (uint32_t i=0; i<total; i++){
        // Si era una opción válida 
        if((prices[position][i] > 0) && (visited[i] == 0)){
            printf("COSTO ES %d\n", prices[position][i]);

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
    uint32_t total = 7;
    uint32_t* fila = calloc(7, sizeof(uint32_t));
    uint32_t** matrix = calloc(7, sizeof(uint32_t*));
    uint32_t* fila1 = calloc(7, sizeof(uint32_t*));
    fila1[0]=0;
    fila1[1]=10;
    fila1[2]=-1;
    fila1[3]=8;
    fila1[4]=7;
    fila1[5]=-1;
    fila1[6]=-1;
    uint32_t* fila2 = calloc(7, sizeof(uint32_t*));
    fila2[0]=10;
    fila2[1]=0;
    fila2[2]=12;
    fila2[3]=7;
    fila2[4]=-1;
    fila2[5]=-1;
    fila2[6]=-1;
    uint32_t* fila3 = calloc(7, sizeof(uint32_t*));
    fila3[0]=-1;
    fila3[1]=12;
    fila3[2]=0;
    fila3[3]=6;
    fila3[4]=-1;
    fila3[5]=7;
    fila3[6]=5;
    uint32_t* fila4 = calloc(7, sizeof(uint32_t*));
    fila4[0]=8;
    fila4[1]=7;
    fila4[2]=6;
    fila4[3]=0;
    fila4[4]=9;
    fila4[5]=4;
    fila4[6]=-1;
    uint32_t* fila5 = calloc(7, sizeof(uint32_t*));
    fila5[0]=7;
    fila5[1]=-1;
    fila5[2]=-1;
    fila5[3]=9;
    fila5[4]=0;
    fila5[5]=-1;
    fila5[6]=-1;
    uint32_t* fila6 = calloc(7, sizeof(uint32_t*));
    fila6[0]=-1;
    fila6[1]=-1;
    fila6[2]=7;
    fila6[3]=4;
    fila6[4]=-1;
    fila6[5]=0;
    fila6[6]=3;
    uint32_t* fila7 = calloc(7, sizeof(uint32_t*));
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


//    uint32_t matrix[] = {{0,10,-1,8,7,-1,-1},
//                     {10,0,12,7,-1,-1,-1},
//                     {-1,12,0,6,-1,7,5},
//                     {8,7,6,0,9,4,-1},
//                     {7,-1,-1,9,0,-1,1},
//                     {-1,-1,7,4,-1,0,3},
//                     {-1,-1,5,-1,1,3,0}};

	uint32_t* mejorsuma = calloc(1, sizeof(uint32_t));
    *mejorsuma = 1000000;
    uint32_t* mejorsecuencia = calloc(total, sizeof(uint32_t));
    findpath(matrix, total, mejorsuma, mejorsecuencia);
    printf("Best price is %d \n", *mejorsuma);
	
	return 0;
}