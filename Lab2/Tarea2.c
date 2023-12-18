#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include "estructuras.h"

int main(){
    struct pieza *aux = NULL; //servirá para apoyarnos al momento de remover las piezas del jugadorActual.
    struct tablero *jugadorActual = NULL; //Hay que asignar esta variable al jugador que le toque.
    int turno, turnoAux = 0; //servirá para pasar al siguiente jugador.
    int index;
    int noGanan = 1; //Es 1 mientras nadie haya ganado.
    int noPiezas = 1;
    int pos;//es 0 si es a la izq. 1 si es a la der.
    int quienParte = 0;
    
    int contador = 0, i = 0, j = 0;
    iteraciones_crear_pieza(i, j, contador);

    jugador1 = nuevo();
    jugador2 = nuevo();
    jugador3 = nuevo();
    jugador4 = nuevo();

    i = 0;

    //Mano jugador1
    printf("Tu mano inicial es:\n");
    while(i < 7){
        agregarPieza(jugador1, &piezas[arreglo_orden[i]]);
        mostrarTusPiezas(&piezas[arreglo_orden[i]]);
        i++;
    }
    printf("\n");

    //Mano jugador2

    while(i < 14){
        agregarPieza(jugador2, &piezas[arreglo_orden[i]]);
        i++;
    }

    //Mano jugador3

    while(i < 21){
        agregarPieza(jugador3, &piezas[arreglo_orden[i]]);
        i++;
    }

    //Mano jugador4

    while(i < 28){
        agregarPieza(jugador4, &piezas[arreglo_orden[i]]);
        i++;
    }

    
    turno = rand() %4;

    printf("Comienza el jugador %i\n\n", turno);

    // turno = 0;//esta sección del código habría que cambiarlo si queremos seguir estrictamente las reglas.
    index = -1;
    switch(turno){
        case(0):
            jugadorActual = jugador1;
            break;
        case(1):
            jugadorActual = jugador2;
            break;
        case(2):
            jugadorActual = jugador3;
            break;
        case(3):
            jugadorActual = jugador4;
            break;
    }

    int suma = 0;

    for(int i = 0; i<jugadorActual->cuenta; i++){
        if(suma < (jugadorActual->piezas[i]->valores[0] + jugadorActual->piezas[i]->valores[1] ) ){
            suma = jugadorActual->piezas[i]->valores[0] + jugadorActual->piezas[i]->valores[1];
            index = i;
        }
    }

    aux = quitarPieza(jugadorActual, index);
    mostrarPieza(aux);

    //Agrego la pieza de mayor puntaje del jugador incial al tablero.
    mesaActual = nuevo();
    agregarPieza(mesaActual, aux);
    printf("Tablero Actual\n");
    mostrarTablero(mesaActual);
    printf("\n");

    //Se empieza a jugar.
    int buscar;
    while(noGanan == 1){
        if(turnoAux == 4){
            printf("---------Todos pasaron---------\n");
            printf("Contando puntos...\n\n");
            noGanan = 0;

            int puntos1 = contarPuntos(jugador1);
            int puntos2 = contarPuntos(jugador2);
            int puntos3 = contarPuntos(jugador3);
            int puntos4 = contarPuntos(jugador4);

            printf("Jugador 1\n");
            mostrarTablero(jugador1);
            printf("Puntos: %i\n\n", puntos1);
            printf("Jugador 2\n");
            mostrarTablero(jugador2);
            printf("Puntos: %i\n\n", puntos2);
            printf("Jugador 3\n");
            mostrarTablero(jugador3);
            printf("Puntos: %i\n\n", puntos3);
            printf("Jugador 4\n");
            mostrarTablero(jugador4);
            printf("Puntos: %i\n\n", puntos4);

            int menor;
            int ganador;

            if(puntos1 < puntos2){
                menor = puntos1;
                ganador = 1;
            }
            else{
                menor = puntos2;
                ganador = 2;
            }

            if(menor > puntos3){
                menor = puntos3;
                ganador = 3;
            }
            else if(menor > puntos4){
                menor = puntos4;
                ganador = 4;
            }

            switch(ganador){
                case 1: printf("Gana el jugador 1\n");
                    break;
                case 2: printf("Gana el jugador 2\n");
                    break;
                case 3: printf("Gana el jugador 3\n");
                    break;
                case 4: printf("Gana el jugador 4\n");
                    break;
            }
            
        }
        else{
            turno++;
            printf("Turno del jugador %i\n", (turno%4) + 1);
            if(turno%4==0){
                jugadorActual = jugador1;

                if(quienParte == 1){
                    turnoAux = 0;
                }

            }
            else if(turno%4==1){
                jugadorActual = jugador2;

                if(quienParte == 2){
                    turnoAux = 0;
                }

            }
            else if(turno%4==2){
                jugadorActual = jugador3;

                if(quienParte == 3){
                    turnoAux = 0;
                }

            }
            else if(turno%4==3){
                jugadorActual = jugador4;

                if(quienParte == 4){
                    turnoAux = 0;
                }

            }

            if(turno%4==0){

                aux = consultarValor(mesaActual);//Recordar que esto verifica el primer valor de la primera pieza y el último valor de la última pieza.
                index = buscarValor(jugadorActual, aux->valores[0]);//buscar en el extremo izquierdo.

                if(index == -1){
                    noPiezas = 1;
                    index = buscarValor(jugadorActual, aux->valores[1]);//buscar en el extremo derecho.

                    if(index == -1){
                        noPiezas = 1;
                    }
                    else{
                        buscar = aux->valores[1];
                        noPiezas = 0;
                        pos = 1;//a la derecha.
                    }

                }
                else{
                    buscar = aux->valores[0];
                    noPiezas = 0;
                    pos = 0;//a la izquierda.
                }

                printf("Tablero Actual\n");
                mostrarTablero(mesaActual);
                printf("\nTu mano actual: \n");
                mostrarTablero(jugador1);

                if(noPiezas == 1){
                    turnoAux++;
                    printf("Pasaste turno automáticamente por no tener piezas jugables.\n");
                    printf("\n");
                }

                else{
                    int valida = 0;
                    while(valida == 0){

                        printf("Indique que pieza VÁlIDA desea jugar de su mano partiendo de 0, de izquierda a derecha...\n");
                        scanf("%i", &index);

                        struct pieza *pieza_aux = jugadorActual->piezas[index];
                        for(int i = 0; i < 2; i++){
                            if(pieza_aux->valores[i] == mesaActual->primer->valores[0]){
                                valida = 1;
                            }
                            else if(pieza_aux->valores[i] == mesaActual->ultimo->valores[1]){
                                valida = 1;
                            }
                        }
                        if(valida == 0){
                            printf("Pieza escogida inválida.\n \n");

                            printf("\nTu mano actual: \n");
                            mostrarTablero(jugador1);
                        }
                    }

                    aux = quitarPieza(jugadorActual, index);

                    if(pos == 0){
                        if(mesaActual->primer->valores[0] != aux->valores[1]){
                            darVuelta(aux);
                        }
                    }
                    else{
                        if(mesaActual->ultimo->valores[1] != aux->valores[0]){
                            darVuelta(aux);
                        }
                    }

                    printf("--------- Has jugado la pieza: [%i|%i] ---------\n", aux->valores[0], aux->valores[1]);
                    agregarEsquinas(mesaActual, aux, pos);
                    printf("Tablero Actual\n");
                    mostrarTablero(mesaActual);
                    printf("\n");

                    if(jugadorActual->cuenta == 0){
                        noGanan = 0;
                        printf("Ganaste la partida!\n");
                    }
                }

            }
            else{

                aux = consultarValor(mesaActual);//Recordar que esto verifica el primer valor de la primera pieza y el último valor de la última pieza.
                index = buscarValor(jugadorActual, aux->valores[0]);//buscar en el extremo izquierdo.

                if(index == -1){
                    noPiezas = 1;
                    index = buscarValor(jugadorActual, aux->valores[1]);//buscar en el extremo derecho.

                    if(index == -1){
                        noPiezas = 1;
                    }
                    else{
                        buscar = aux->valores[1];
                        noPiezas = 0;
                        pos = 1;//a la derecha.
                    }

                }
                else{
                    buscar = aux->valores[0];
                    noPiezas = 0;
                    pos = 0;//a la izquierda.
                }

                if(noPiezas == 1){
                    turnoAux++;
                    printf("Jugador %i pasa el turno\n", (turno%4) + 1);
                    printf("\n");
                }
                else{
                    aux = quitarPieza(jugadorActual, index);

                    if(pos == 0){
                        if(mesaActual->primer->valores[0] != aux->valores[1]){
                            darVuelta(aux);
                        }
                    }
                    else{
                        if(mesaActual->ultimo->valores[1] != aux->valores[0]){
                            darVuelta(aux);
                        }
                    }
                    mostrarPieza(aux);
                    agregarEsquinas(mesaActual, aux, pos);
                    printf("Tablero Actual\n");
                    mostrarTablero(mesaActual);
                    printf("\n");

                    if(jugadorActual->cuenta == 0){
                        noGanan = 0;
                        printf("Ganó el jugador %i\n", (turno%4) + 1);
                    }
                }
            }
        }
    }

    return 0;
}