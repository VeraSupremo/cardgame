//nombre: Martin vera, Rut:21586190-2, seccion:A, fecha: 30/09/2023//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
//se pueden usar variables globales usadas con define para no perderse
#define maxd_cartas  15
#define cartas_juego  3
#define UenJuego  5
#define MaximoLinea  459
typedef struct jugador{
	char nombre[200];
	int vida[4]; //un array para la vida? vida[0] = 1, vida[1] = 1 y asi? -n
	
	
}JUGADOR;
typedef struct CARTA{
	char nombre[200];
	char clase[200];
	int idnt;
	int ataque;
	int vida;
	int defensa;
	struct CARTA*siguiente;
}CARTA;

typedef struct historial{
	//el historial debe ser una cola ya que se muestran por orden
}HISTORIAL;


void reglas(){
	printf("________________________________________________________________________________________\n");
	printf("Cada jugador recibe un lote de 15 cartas, entregadas luego de revolver, de las cuales\n");
	Sleep(1000);
    printf(" debe seleccionar tres cartas para comenzar el juego las cuales quedan en su mano.\n");
    Sleep(1000);
    printf("Las 12 cartas restantes corresponden a un monto, que debe devolver y dejarlo al costado.\n");
    Sleep(1000);
    printf("Cada jugador parte con 5 puntos de vida. Los puntos de vida solo se restan cuando\n");
    Sleep(1000);
	printf("uno de los guardianes (las cartas) es derrotado.\n");
    printf("En cada turno los jugadores sacan una carta y ademas pueden:\n");
    printf("Seleccionar una carta y dejarla en el campo de batalla.\n");
    printf("Atacar a un oponente con una de las cartas que se encuentra en el campo de batalla.\n");
	printf("________________________________________________________________________________________\n");
}



void agregarcartas( CARTA **MAZO, CARTA *NUEVACARTA) {
    if (*MAZO == NULL) {
        *MAZO = NUEVACARTA;
    } else {
        CARTA *current = *MAZO;
        while (current->siguiente != NULL) {
            current = current->siguiente;
        }
        current->siguiente = NUEVACARTA;
    }

}

// aca personajes es la lista de cartas
//lee el archivo de texto y añade carta a la lista
void analisis( CARTA **MAZO, int *vidmin,int *vidmax,int *atamin,int *atamax,int *defmin,int *defmax, int cont){
	char limite[MaximoLinea];
	//int contador;
	FILE*fichero;
	fichero= fopen("cardgametest.txt","r");
	//verificador si el archivo presenta eerror o no 
	if(fichero == NULL){
		perror("fallo abrir el archivo");
		
		return ;
	}
	
	while(fgets(limite, MaximoLinea, fichero)){
//                                                        malloc reserva el espacio en la memoria
        CARTA *newStruct= (CARTA *)malloc(sizeof(CARTA));
		
        strcpy(newStruct->nombre, strtok(limite, ","));                //para copiar texto
        
        
        strcpy(newStruct->clase, strtok(NULL, ","));
      
        newStruct->ataque = atoi(strtok(NULL, ","));      //atoi es  para valores enteros
        newStruct->vida = atoi(strtok(NULL, ","));
        newStruct->defensa = atoi(strtok(NULL, ","));
		cont ++;
		newStruct->idnt = cont;
        newStruct->siguiente = NULL;
		
        //                  Se añade el Struct creado a la lista existente.
       //  agregarcartas(lista, newStruct); // función para agregar elementos a la lista
       agregarcartas(MAZO, newStruct);
	   if(newStruct->vida < *vidmin){
       		*vidmin= newStruct->vida;
	   }
	   if(newStruct->vida > *vidmax){
       		*vidmax= newStruct->vida;
	   }
	   if(newStruct->ataque < *atamin){
   	    	*atamin= newStruct->ataque;
	   }
	   if(newStruct->ataque > *atamax){
   	    	*atamax= newStruct->ataque;
	   }
	   if(newStruct->defensa< *defmin){
		   	*defmin= newStruct->defensa;
	   }
	   if(newStruct->defensa> *defmax){
		   	*defmax= newStruct->defensa;
	   }
       
  		printf("\n\n%s \n%s \n %d \n%d \n %d\n %d\n",newStruct->nombre,newStruct->clase,newStruct->ataque, newStruct-> vida, newStruct-> defensa,newStruct->idnt);

    }
    
    fclose(fichero);
    printf("\n\nmaximo ataque: %d  maximo vida: %d  maxima defensa: %d\n\n",*atamax, *vidmax,*defmax);


	//debe haber un valor maximo para cada variable de vida, ataque y defensa 
	// de esta forma cuando se esten cargando se pueden ir guardando en una variable
	
	
}

CARTA* crearcarta(char *nombre, char *clase, int ataque, int vida, int defensa){
	//la funcion crear debe validar en base a los datos cargados en el analisis
	//en esta parte se relaciona con lo comentado en analisis, ya que a la hora de crear la carta
	//el usuario debe de respetar los limites max y min  x ej  si la vida tiene 90 y el limite es 70 la vida baja a 70
	CARTA *NUEVACARTA = (CARTA *)malloc(sizeof(CARTA));
	if(NUEVACARTA != NULL){
	   	strcpy(NUEVACARTA->nombre, nombre);
	  	strcpy(NUEVACARTA->clase, clase);
	  	NUEVACARTA->ataque = ataque;
		NUEVACARTA->vida = vida;
	    NUEVACARTA->defensa = defensa;
	    NUEVACARTA->idnt ++;
	    NUEVACARTA->siguiente = NULL;
	}

    
    return NUEVACARTA;
	
}

 
 void revolver(CARTA**MAZO, CARTA **MAZOREV) {
    CARTA* current = *MAZO;
    int cont = 0;
    
    // Contar el número de elementos en la lista
    while (current != NULL) {
        cont++;
        current = current->siguiente;
    }
    
    // Crear un arreglo temporal para almacenar los nodos
    CARTA* arr[cont];
    current = *MAZO;
    int i = 0;

    // Copiar los nodos en el arreglo
    while (current != NULL) {
        arr[i] = current;
        current = current->siguiente;
        i++;
    }

    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Revolver el arreglo de nodos
    for (i = cont - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        CARTA* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // Reconstruir la lista enlazada con el arreglo revuelto
    *MAZOREV = arr[0];
    current = *MAZOREV;
    for (i = 1; i < cont; i++) {
        current->siguiente = arr[i];
        current = current->siguiente;
    }
    current->siguiente = NULL;
}
 
 void mostrarcartas(){
 	
 }
 void juego(CARTA **MAZO){
	int player1[15];
	int player2[15];
	
	
}
void atacar(){
	
}

void imprimirLista(CARTA **MAZO){
	CARTA *current = *MAZO;
	int contador = 0;
	
	while(current != NULL){
		contador++;
		printf("%d) Nombre: %s    Clase: %s   ataque: %d   vida: %d   defensa: %d\n\n", contador, current->nombre,current->clase,current->ataque,current->vida,current->defensa);
		current = current->siguiente;
	}
}

int main(){
	int menu;
	char nombreNC[100];
	char claseNC[100];
	int ataqueNC;
	int vidaNC;
	int defensaNC;
	int wh1= 0;
	int cont= 0;
	int vidmin=0,vidmax=0,atamin=0,atamax=0,defmin=0,defmax=0; //todo estos valores se tomaran del archivo
	
    //orden de las cartas                   Name,Type,vida,Ataque,DeFensa
    CARTA *MAZO= NULL; //mazo es el head
    CARTA *MAZOREV = NULL;
    CARTA *NUEVACARTA;
	analisis(&MAZO,&vidmin,&vidmax,&atamin,&atamax,&defmin,&defmax,cont);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//menu de inicio para empezar
	Sleep(1000);
	printf("\nCARGANDO JUEGO");
	Sleep(1000);
	printf("..");
	Sleep(1000);
	printf("..");
	Sleep(1000);
	printf("..");
	Sleep(2000);
	printf("............\nJUEGO CARGADO EXITOSAMENTE\n\n\n");
	printf("BIENVENIDO A THE CLASH OF THE GUARDIANS\n");
	Sleep(2000);
	printf("__________________________________________\n");
	printf("......opcion 1:   CREAR CARTA PROPIA.....\n");
	printf("......opcion 2:     NUEVA PARTIDA   .....\n");
	printf("......opcion 3:   HISTORIAL DEL JUEGO....\n");
	printf("......opcion 4:         REGLAS      .....\n");
	printf("......opcion 5:    SALIR DEL JUEGO  .....\n");
	printf("_________________________________________\n");
	Sleep(1000);

	while(wh1==0){
		printf("Que opcion desea elegir:");
		scanf("%d",&menu);
	
		switch(menu){
			case 1:                                          //aca se crearan y agregaran nuevas cartas
			
				printf("\n INGRESE SOLO LO SOLICITADO\n el orden de ingresos son \n    NOMBRE\n    CLASE\n    ATAQUE\n    VIDA\n    DEFENSA\n ");
				printf("ingrese el nombre(SOLO LETRAS NO NUMEROS) :");
				scanf("%s",&nombreNC);

				printf("\n ahora ingrese la clase de la carta SOLO LETRAS NO NUMEROS\n");
				scanf("%s",&claseNC);
				
		        printf("\n\n ataque maximo: %d  vida maxima: %d   defensa maxima: %d\n\n",atamax, vidmax,defmax);


				printf("\n ingrese ahora el ataque NO LETRAS SOLO NUMEROS\n EL ATAQUE MAXIMO ES DE %d  ",atamax);
				scanf("%d",&ataqueNC);
				if(ataqueNC < atamin || ataqueNC>atamax){
					ataqueNC = atamin+atamax/2;                   //redactar en readme: si ingresas un valor fuera de rango se pone de forma automatica el valor menor del archivo de texto
				}
				printf("\n ingrese ahora  la vida NO LETRAS SOLO NUMEROS\n LA VIDA MAXIMA ES DE %d  ",vidmax);
				scanf("%d",&vidaNC);
				if(vidaNC < vidmin || vidaNC> vidmax){
					vidaNC = vidmin+vidmax/2;
				}
				printf("\n ingrese ahora la defensa NO LETRAS SOLO NUMEROS\n LA DEFENSA MAXIMA ES DE %d  ",defmax);
				scanf("%d",&defensaNC);
				if(defensaNC < defmin || defensaNC>defmax){
					defensaNC = defmin+defmax/2;
				}
				
				NUEVACARTA = crearcarta( nombreNC, claseNC, ataqueNC, vidaNC, defensaNC);
				agregarcartas(&MAZO, NUEVACARTA);
				
				printf("tu carta es:\n   %s \n   %s\n   %d\n   %d\n   %d\n  ",nombreNC, claseNC, ataqueNC, vidaNC, defensaNC);
					
				
			
			break;
			
			case 2:
				imprimirLista(&MAZO);
				Sleep(3000);
				printf("\n\n\n\n\n\n\n\n");
				system("cls");
				revolver(&MAZO, &MAZOREV);
				imprimirLista(&MAZOREV);
				
				//asignar 15 cartas al jugador B)
				
					
				break;
				
			case 3:
				
			break;
			
			case 4:
				reglas();
			break;
			
			
			
			case 5:
			//memory);
				wh1= 1;
			default: wh1= 1;  break;
		}
	}
	return 0;
}
