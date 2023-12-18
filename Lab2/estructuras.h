struct pieza{
    int valores[2];//pieza tiene 2 valores
};

struct pieza *piezas = NULL;

struct pieza *crearPieza(int a, int b){//Crea un struct con los valores de las piezas.
    struct pieza *nueva = calloc(sizeof(struct pieza), 1);
    nueva->valores[0] = a;
    nueva->valores[1] = b;
    return nueva;
    
};

int arreglo_orden[28]; //Creo arreglo estático para luego almacenar los valores ya revueltos.

void revolver_piezas(){//Se revuelven las piezas.
    int random, i = 0;
    int no_repes[28];
    memset(&no_repes, 0, sizeof(int)*28);//inicializa el arreglo en 0.
    srand(time(NULL));

    while(i<28){
        random = rand() % 28;

        if(no_repes[random] == 0){
            arreglo_orden[i] = random;
            no_repes[random] = 1;//seteo en 1 para que no vuelva a entrar el mismo valor.
            i++;
        }
    }
}

void iteraciones_crear_pieza(int i, int j, int contador){//Función que itera entre 0 y 6 para crear las combinaciones de las piezas.
    struct pieza *temp;
    while (i <= 6){
        j = 0;//Se necesita reiniciar para crear todas las piezas bien.
        while(j <= i){
            piezas = realloc(piezas, (contador+1)*sizeof(struct pieza));
            temp = crearPieza(i, j);
            memcpy(&piezas[contador], temp, sizeof(struct pieza));
            free(temp);
            contador++;
            j++;
        }
        i++;
    }
    revolver_piezas();
    i = 0;
    while(i < contador){
        i++;
    }
}

struct tablero{ //Servirá como estructura para los jugadores y el tablero.
    struct pieza **piezas; //Para que no se repitan los valores en mesa. Es una lista de fichas, en donde las fichas tienes sus valores.
    struct pieza *primer; //Acceso a la primera pieza del tablero.
    struct pieza *ultimo; //Acceso a la última pieza del tablero.
    int cuenta; //Cuenta cuantas piezas hay en mesa para así poder asignar más fácil.
};

//Se crean variables a usar.
struct tablero *mesa = NULL;
struct tablero *jugador1 = NULL;
struct tablero *jugador2 = NULL;
struct tablero *jugador3 = NULL;
struct tablero *jugador4 = NULL;
struct tablero *mesaActual = NULL;

struct tablero *nuevo(){//Se usa para asignarle a los jugadores sus futuros espacios de la mano.
    struct tablero *temporal = NULL;
    temporal = calloc(1, sizeof(struct tablero));//Lo que hace es inicializar todo en 0 al tiro.
    return temporal;
};

void agregarPieza(struct tablero *mesa, struct pieza *p){//Agrega pieza al tablero.
    if(mesa){//Si la mesa es válida.
        if(p){//Si la pieza es válida.
            mesa->piezas = realloc(mesa->piezas, sizeof(struct pieza*) * mesa ->cuenta+1);//Asigna espacio para una pieza.
            mesa->piezas[mesa->cuenta] = p;
            mesa->cuenta++;
            mesa->primer = mesa->piezas[0];
            mesa->ultimo = mesa->piezas[mesa->cuenta-1];
        }
    }
}

struct pieza *quitarPieza (struct tablero *mesa, int posicion){//Quita pieza de la mano del jugador correspondiente.
    int i = posicion; //Iterador.
    struct pieza *temporal = NULL;
    temporal = mesa->piezas[posicion];

    while(i < mesa->cuenta-1){//Reacomoda las piezas en sus índices al nuevo.
        mesa->piezas[i] = mesa->piezas[i+1];
        i++;
    }

    mesa->piezas[i] = NULL; //Pieza del jugador ya se jugó, por lo que debe desaparecer de él.
    mesa->piezas = realloc(mesa->piezas, sizeof(struct pieza *) * (mesa->cuenta-1));//Al jugar una pieza, se debe reasignar el espacio.
    mesa->cuenta--;

    if(mesa->cuenta > 0){
        mesa->primer = mesa->piezas[0];
        mesa->ultimo = mesa->piezas[mesa->cuenta-1];
    }

    return temporal;
}

void mostrarPieza(struct pieza *p){//Muestra la pieza en cuestión.
    printf("Se jugó la ficha: [%i|%i]\n", p->valores[0], p->valores[1]);
}
void mostrarTusPiezas(struct pieza *p){//Se usa para mostrar las piezas del jugador controlado en un iterador del main.
    printf("[%i|%i]\n", p->valores[0], p->valores[1]);
}

void mostrarTablero(struct tablero *t){//Muestra el tablero o la mano del jugador según se convenga.
    for(int i = 0; i < t->cuenta; i++){
        printf("[%i|%i]",t->piezas[i]->valores[0], t->piezas[i]->valores[1]);
    }
    printf("\n");
}

int buscarValor(struct tablero *mesa, int valor){//Sirve para ver si hay en mesa (y que sea válido) un valor X de interés para poder jugar.
    int x = -1;//Indica que el valor X no está.
    struct pieza *actual = NULL;
    int y = 0;// Si es 0 el valor no se encontró. Si es 1 el valor se encontró.
    int count = 0;

    while(y == 0 && count < mesa->cuenta){
        actual = mesa->piezas[count];
        if(actual->valores[0] == valor || actual->valores[1] == valor){
            x = count;
            y = 1;
        }
        count++;
    }
    return x;//si retorna un valor distinto de -1 es porque lo encontró.
}

int valorEspejo(struct tablero *mesa, int valor){//Se usa para buscar entre los jugadores la pieza [6|6].
    int x = -1;//Si es -1 indica que el valor X no está ([6|6] siempre estará en alguna mano inicialmente).
    struct pieza *actual = NULL;
    int y = 0;
    int count = 0;

    while(y == 0 && count < mesa->cuenta){
        actual = mesa->piezas[count];
        if(actual->valores[0] == valor && actual->valores[1] == valor){
            x = count;
            y = 1;
        }
        count++;
    }
    return x;
}

void darVuelta(struct pieza *p){//Se usa para voltear la pieza en caso de que las condicionales del main lo indiquen.
    int ayuda = p->valores[1];

    p->valores[1] = p->valores[0];
    p->valores[0] = ayuda;
}

struct pieza *consultarValor(struct tablero *mesa){//Este struct ve los valores de los extremos del tablero.
    struct pieza *p = malloc(sizeof(struct pieza));
    p->valores[0] = mesa->primer->valores[0];
    p->valores[1] = mesa->ultimo->valores[1];
    return p;
}

void agregarEsquinas(struct tablero *mesa, struct pieza *p, int pos){//Agrega pieza a jugar al extremo correspondiente del tablero.
    if(mesa){
        if(p){
            mesa->piezas = realloc(mesa->piezas, sizeof(struct pieza *)*(mesa->cuenta+1));//se debe crear espacio para otra ficha.
            
            if(pos==0){//a la izquierda
                int x = mesa->cuenta;
                while(x > 0){
                    mesa->piezas[x] = mesa->piezas[x-1];
                    x--;
                }
                mesa->piezas[0] = p;
            }
            else{//a la derecha
                mesa->piezas[mesa->cuenta] = p;
            }

            mesa->cuenta++;
            mesa->primer = mesa->piezas[0];
            mesa->ultimo = mesa->piezas[mesa->cuenta-1];
        }
    }
    else{
        printf("Error en la pieza agregada(?)\n");
    }
}

int contarPuntos(struct tablero *jugador){//En caso de empate se usa para contar los puntos de los jugadores.
    int suma = 0;

    for(int i = 0; i<jugador->cuenta; i++){
        suma = suma + jugador->piezas[i]->valores[0] + jugador->piezas[i]->valores[1];
    }
    
    return suma;
}