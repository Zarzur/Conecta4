#include <stdio.h>
#include <stdlib.h>
#include "../colors.h"

#define NUM_ROWS 6
#define NUM_COL 6
#define MAX_ELEMS NUM_COL*NUM_ROWS
#define X 'X'
#define O 'O'
#define NEUTRO 'n'

char tablero[MAX_ELEMS];

void input_jugador(char * prompt, int *variable){
    do{
        printf("%s", prompt);
        scanf("%d",variable);
        if (!(*variable >= 1 && *variable <= NUM_COL))
            printf(RED"NO VALIDO\n"reset);    
    } while (!(*variable >= 1 && *variable <= NUM_COL));
}

// Dibuja el tablero
void hacer_tablero(){
    system("clear");
    printf(RED"Conecta "GRN"4\n"reset);
    unsigned int num_dash = NUM_COL*4+1;
    printf("\n");
    for (int j = 0; j < NUM_COL; j++)
        printf("  "MAG"%d"reset" ", j+1);
    printf("\n");
            
    for (int i = 0; i < NUM_ROWS; i++){
        printf("|");
        for (int j = 0; j < NUM_COL; j++){
            unsigned int pos = i*NUM_COL+j+1;

            if (tablero[pos-1] == X)
                printf(" "CYN"%c"reset" |", tablero[pos-1]);
            else if (tablero[pos-1] == O)
                printf(" "YEL"%c"reset" |", tablero[pos-1]);
            else
                printf("   |");
        }
        printf("\n");  

        for (unsigned int i = 0; i < num_dash; i++){
            printf("-");
        }
        printf("\n");     
    }
    printf("\n");
}

// returns 1 if columna is full
int meter_ficha(unsigned int columna, char jugador){
    int isFull = 1;
    for (int i = NUM_ROWS-1; i >= 0 && isFull ; i--){
        int pos = i*NUM_COL+columna-1;
        if (tablero[pos] == NEUTRO){
            tablero[pos] = jugador;
            isFull = 0;
        }
    }
    return isFull;
}


int filas(){
    int hay4fila = 0;
    for (int i = 0; i < NUM_ROWS && !hay4fila; i++){
        for (int j = 0; j <= NUM_COL-4 && !hay4fila; j++){
            int pos = i*NUM_COL+j;
            if (tablero[pos] != NEUTRO)
                hay4fila = tablero[pos] == tablero[pos+1] &&  tablero[pos] == tablero[pos+2] &&  tablero[pos] == tablero[pos+3];
        }
    }
    return hay4fila;
}

int columnas(){
     int hay4col = 0;
    for (int i = 0; i <= NUM_ROWS-4 && !hay4col; i++){
        for (int j = 0; j < NUM_COL && !hay4col; j++){
            int pos = i*NUM_COL+j;
            if (tablero[pos] != NEUTRO)
                hay4col = tablero[pos] == tablero[pos+NUM_COL] &&  tablero[pos] == tablero[pos+2*NUM_COL] &&  tablero[pos] == tablero[pos+3*NUM_COL];
        }
    }
    return hay4col;
}

int diagonal1(){
    int en4diag = 0;
    for (unsigned int i = 0; i <= NUM_ROWS-4 && !en4diag; i++){
        for (unsigned int j = 0; j <= NUM_COL-4 && !en4diag; j++){
            unsigned int pos = i*NUM_COL+j;
            if (tablero[pos] != NEUTRO)
                en4diag = tablero[pos] == tablero[pos+NUM_COL+1] && tablero[pos] == tablero[pos+2*(NUM_COL+1)] && tablero[pos] == tablero[pos+3*(NUM_COL+1)];
        }
    }
    return en4diag;    
}

int diagonal2(){
    int en4diag = 0;
    for (unsigned int i = 0; i <= NUM_ROWS-4 && !en4diag; i++){
        for (unsigned int j = NUM_COL-4+1; j < NUM_COL && !en4diag; j++){
            unsigned int pos = i*NUM_COL+j;
            if (tablero[pos] != NEUTRO)
                en4diag = tablero[pos] == tablero[pos+NUM_COL-1] && tablero[pos] == tablero[pos+2*(NUM_COL-1)] && tablero[pos] == tablero[pos+3*(NUM_COL-1)];
        }
        
    }
    return en4diag;    
}


int diagonales(){
    return diagonal1() || diagonal2();
}

// returns 1 if game is over
int estado_juego(){
    return filas() || columnas() || diagonales();
}

int main(int argc, char const *argv[]){
    for (unsigned int i = 0; i < MAX_ELEMS; i++)
        tablero[i] = NEUTRO;
    
    int termino_juego = 0, i;
    for (i = 0; i < MAX_ELEMS && !termino_juego; i++){
        int isFull = 1;
        do{
            hacer_tablero();
            unsigned int col;
            char jugador;
            if (i%2)
                jugador = O;
            else
                jugador = X;
                    
            printf("Turno de %c ", jugador);
            input_jugador("ingrese Columna: ", &col);
            isFull = meter_ficha(col, jugador);
            termino_juego = estado_juego();
        } while (isFull);
    }
    hacer_tablero();
    i++;
    if (i%2 && termino_juego)
        printf(YEL"gano O !!\n"reset);    
    else if (termino_juego)
        printf(CYN"gano X !!\n"reset);    
    else
        printf("Hay Empate !!\n");
    
    printf("\n");
    return 0;
}
