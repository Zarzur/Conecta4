#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

#define COL_LENGTH 3
#define ROW_LENGTH 3
#define MAX_ELEM COL_LENGTH*ROW_LENGTH
#define X 'X'
#define O 'O'
#define NEUTRO 'n'

char tablero[MAX_ELEM];

void input_jugador(char * prompt, int *variable){
    do{
        printf("%s", prompt);
        scanf("%d",variable);
        if (!(*variable >= 1 && *variable <= MAX_ELEM))
            printf(RED"NO VALIDO\n"reset);    
    } while (!(*variable >= 1 && *variable <= MAX_ELEM));
}

int filas(){
    int en_fila3 = 0;
    for (int i = 0; i < ROW_LENGTH && !en_fila3; i++){
        if (tablero[i*ROW_LENGTH] != NEUTRO)
            en_fila3 = 1;
        else
            en_fila3 = 0;      
        
        for (int j = 1; j < COL_LENGTH; j++){
            int pos = i*ROW_LENGTH+j;
            en_fila3 = en_fila3 && (tablero[pos] == tablero[pos-1]);      
        }
    }
    return en_fila3; 
}

int columnas(){
    int enColumna3 = 0; // false
    for (int i = 0; i < COL_LENGTH && !enColumna3; i++){
        if (tablero[i] != NEUTRO)
            enColumna3 = 1;
        else
            enColumna3 = 0; 
        for (int j = 1; j < ROW_LENGTH; j++){
            int pos = i+j*COL_LENGTH;
            enColumna3 = enColumna3 && (tablero[pos] == tablero[pos-ROW_LENGTH]);      
        }
    }
    return enColumna3; 
}

int diagonales(){
    int diag1  = 0, diag2 = 0;
    if (tablero[0] != NEUTRO)
        /*diagonal 1 ( \ ) */ 
        diag1 = tablero[0] == tablero[4] && tablero[4] == tablero[8];

    if (tablero[2] != NEUTRO)
        /*diagonal 2 ( / ) */ 
        diag2 = tablero[2] == tablero[4] && tablero[4] == tablero[6];
       
    return diag1 || diag2;     
}

// true solo si hay por lo menos una configuracion ganadora
int termino_juego(){
    return filas() || columnas() || diagonales();
}

// Dibuja el tablero
void hacer_tablero(){
    system("clear");
    printf(RED"TA" GRN"TE"BLU"TI\n"reset);
    printf("-------------\n");        
    for (int i = 0; i < COL_LENGTH; i++){
        printf("|");
        for (int j = 0; j < ROW_LENGTH; j++){
            if (tablero[i*COL_LENGTH+j] == X)
                printf(" "CYN"%c"reset" |", tablero[i*COL_LENGTH+j]);
            else if (tablero[i*COL_LENGTH+j] == O)
                printf(" "YEL"%c"reset" |", tablero[i*COL_LENGTH+j]);                        
            else
                printf(" "MAG"%d"reset" |", i*COL_LENGTH+j+1);
        }
        printf("\n-------------\n");        
    }
    printf("\n");
}

// imprime quien gano el juego o si hubo empate
void estado_juego_final(int jugador){
    hacer_tablero();
    if (termino_juego())
        printf(RED"gano el jugador %d !!\n\n"reset, jugador);    
    else
        printf("Empate\n\n");
}

int jugar(int jugador){
    int col, fila,casilla, jugada_valida = 0;
    
    while (!jugada_valida){   
        hacer_tablero();
        printf("Jugador "BGRN"%d"reset", ingrese que casilla va jugar\n", jugador+1);
        input_jugador("casilla: ", &casilla);
        if(!(tablero[casilla-1] == X || tablero[casilla-1] == O)){
            tablero[casilla-1] = (jugador == 0) ? X : O;
            jugada_valida = 1;
        }
    }
    return termino_juego();
}

void tateti(){
    int i;
    for (i = 0; i < MAX_ELEM && !jugar(i%2); i++);

    estado_juego_final((i%2)+1);
}

int main(int argc, char const *argv[]){
    for (int i = 0; i < MAX_ELEM; i++)
            tablero[i] = NEUTRO;
    
    tateti();
    
    return 0;
}
