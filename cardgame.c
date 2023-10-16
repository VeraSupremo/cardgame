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
#define MaximoLinea  450
typedef struct jugador{
	int vida ; //un array para la vida? vida[0] = 1, vida[1] = 1 y asi? -n
	struct CARTA* monton[maxd_cartas]; //recibe las 15 caartas
	struct CARTA* mano[maxd_cartas]; //elige las cartas para jugar
	struct CARTA* mesa[maxd_cartas]; //cartas para atacar o colocar
	
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
void analisis( CARTA **MAZO, int *vidmin,int *vidmax,int *atamin,int *atamax,int *defmin,int *defmax, int cont,int wh1){
	char limite[MaximoLinea];
	int contadormin= 0;
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
       
  	//	printf("\n\n%s \n%s \n %d \n%d \n %d\n %d\n",newStruct->nombre,newStruct->clase,newStruct->ataque, newStruct-> vida, newStruct-> defensa,newStruct->idnt);
		contadormin++;
		
    }
    if(contadormin<=30){
    	perror("no tiene la cantidad necesaria");
    	fclose(fichero);
    	wh1 = 1;
	}
    fclose(fichero);
   // printf("\n\nmaximo ataque: %d  maximo vida: %d  maxima defensa: %d\n\n",*atamax, *vidmax,*defmax);


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
    
    // Crear un arreglo  para almacenar posicion
    CARTA* arr[cont];
    current = *MAZO;
    int i = 0;

    // Copiar en el arreglo
    while (current != NULL) {
        arr[i] = current;
        current = current->siguiente;
        i++;
    }


    // Revolver 
    for (i = cont - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        CARTA* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    // Reconstruir la lista con el arreglo revuelto
    *MAZOREV = arr[0];
    current = *MAZOREV;
    for (i = 1; i < cont; i++) {
        current->siguiente = arr[i];
        current = current->siguiente;
    }
    current->siguiente = NULL;
}
 
 
 void juego(CARTA **MAZOREV,JUGADOR* jugador1, JUGADOR* jugador2){
	CARTA* current = *MAZOREV;
    int contrev = 0;
    int contmax= 30;
    for (int i = 0; i < maxd_cartas; i++) {
        jugador1->monton[i] = NULL;
        jugador2->monton[i] = NULL;
    }
    
      for (int i = 0; i < maxd_cartas; i++) {
        if (*MAZOREV == NULL) {
            printf("No hay más cartas disponibles \n");
            break;
        }

        // Asignar carta a jugador2
        CARTA* carta = *MAZOREV;
        *MAZOREV = (*MAZOREV)->siguiente;
        jugador1->monton[i] = carta;

        if (*MAZOREV == NULL) {
            printf("No hay más cartas disponibles para repartir\n");
            break;
        }

        // Asignar carta a jugador2
        carta = *MAZOREV;
        *MAZOREV = (*MAZOREV)->siguiente;
        jugador2->monton[i] = carta;
        printf("%d  \n",carta->idnt);
        
    }
    
    

}



void elegir(JUGADOR*jugador){
	int elecciones[3];
	printf("Tus cartas en mano:\n");
    for (int i = 0; i < 15; i++) {             //aca se muestra al ususario las cartas del 1 al 15 para que elija una
        if (jugador->monton[i] != NULL) {
            printf("%d) %s\n %s\n", i + 1, jugador->monton[i]->nombre,jugador->monton[i]->clase);
        }   
    }
	for(int i= 1; i<=3;i++){
		int eleccion= 0;
		printf("ELIGE LA CARTA [%d]",i);
		scanf("%d",&eleccion);
		if(eleccion >= 1 &&eleccion <= 15 && jugador->monton[i]!= NULL){
			elecciones[i]=eleccion-1;
			jugador->mano[i]= jugador->monton[elecciones[i]];
			
			//una vez asignado se elimina de la carta de de mano
			printf("tu carta fue: %s\n",jugador->mano[i]->nombre);
			jugador->monton[elecciones[i]]= NULL;
			
		}else{
			printf("\n INGRESE NUMERO VALIDO\n");
			i--;
		}
		
		
	}
		for(int j= 1; j<=3;j++){
			system("cls");
			printf("TUS CARTAS SON\n");
			printf("_________________\n");
			printf("[%s]\n",jugador->mano[j]->nombre);
			printf("[%s]\n",jugador->mano[j]->clase);
			printf("|----------------|\n");
			printf("|                |\n");
			printf("|                |\n");
			printf("|                |\n");
			printf("|________________|\n");
			printf("       [%d]\n",jugador->mano[j]->ataque);
			printf("       [%d]\n",jugador->mano[j]->vida);
			printf("       [%d]\n",jugador->mano[j]->defensa);
			printf("_________________\n");
			Sleep(2000);
			system("cls");
	}
}
void imprimirCjugador2(JUGADOR* jugador){
	printf("\n las cartas de J2 son:\n");
	for(int i= 0; i<=3; i++){
		if(jugador->mano[i]!= NULL){
			printf("___________________________\n [%s]  [%d]\n__________________________\n",jugador->mano[i]->nombre,jugador->mano[i]->vida);			
		}else{
			printf("CARTA VACIA\n");
		}
	}	
}

void imprimirCjugador(JUGADOR* jugador){
	for(int i = 0; i<maxd_cartas; i++){
		if(jugador->monton[i]!= NULL){
			 printf("CARTA [%d]:\n", i + 1);
            printf("Nombre: %s\n", jugador->monton[i]->nombre);
            printf("Clase: %s\n", jugador->monton[i]->clase);
            printf("Ataque: %d\n", jugador->monton[i]->ataque);
            printf("Vida: %d\n", jugador->monton[i]->vida);
            printf("Defensa: %d\n", jugador->monton[i]->defensa);
            printf("\n");
		}
	}
}
void elegirj2(JUGADOR* jugador){
	int eleccion2;
	//int elecciones2[3];
	for(int i= 1; i<=3;i++){
		int eleccion2= 0;
		printf("JUGADOR 2 ELIGIO CARTA [%d]",i);
		eleccion2= rand() % 15;
		printf("%d\n\n\n",eleccion2);
		if(eleccion2 >= 0 &&eleccion2 <= 14 && jugador->monton[eleccion2]!= NULL){
		//	elecciones2[i]=eleccion2;
			
			//jugador->mano[i]= jugador->monton[elecciones2[i]];
			jugador->mano[i]= jugador->monton[eleccion2];

				//una vez asignado se elimina de la carta de de mano
			jugador->monton[eleccion2]= NULL;
		}else{
			printf("\n J2 SE EQUIVOCO XD\n");
			i--;
		}
		
	}
	
	
}

void Ecartamesa(JUGADOR* jugador,int Cpcombate){
    printf("\n necesito que escoja una de sus 3 cartas para mandar combate\n");
    scanf("%d",&Cpcombate);

    while(1){
        if(Cpcombate >= 0 && Cpcombate <= 14 && jugador->mano[Cpcombate] != NULL){
            for(int i = 0; i < 15; i++){
                if (jugador->mesa[i] == NULL){
                    jugador->mesa[i] = jugador->mano[Cpcombate];
                    jugador->mano[Cpcombate] = NULL;
                    break;
                }
            }
            break;
        } else {
            printf("\n INGRESE NUMERO VALIDO\n");
        }
    }
}
void Ecartamesaj2(JUGADOR* jugador){
	int Cpcombate2= rand()%15;
	 while(1){
        if(Cpcombate2 >= 0 && Cpcombate2 <= 14 && jugador->mano[Cpcombate2] != NULL){
            for(int i = 0; i < 15; i++){
                if (jugador->mesa[i] == NULL){
                    jugador->mesa[i] = jugador->mano[Cpcombate2];
                    jugador->mano[Cpcombate2] = NULL;
                    break;
                }
            }
            break;
        } else {
            printf("\n INGRESE NUMERO VALIDO\n");
        }
    }
	
}
void cartaenmesa(JUGADOR* jugador){
	
}
void ataque(JUGADOR* jugador){
	int att=0;
	printf("\nDESEA ATACAR?\n 1= SI \n 0= NO\n");
	if(att==0){
		
	}
	
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
void liberal(CARTA** MAZO,CARTA** MAZOREV){
	CARTA* current= *MAZO;
	while(current != NULL){
		CARTA *siguiente= current->siguiente;
		free(current);
		current= siguiente;
	}
}


int main(){
	srand(time(NULL));
	int menu;
	char nombreNC[100];
	char claseNC[100];
	int ataqueNC,Cpcombate;
	int vidaNC;
	int defensaNC;
	int wh1= 0;
	int whg= 0;
	int whj= 0;
	int whattke= 0;
	int cont= 0;
	int cj2;
	int caj1;
	int atke=0;
	int vidmin=0,vidmax=0,atamin=0,atamax=0,defmin=0,defmax=0; //todo estos valores se tomaran del archivo
	
    //orden de las cartas                   Name,Type,vida,Ataque,DeFensa
    CARTA *MAZO= NULL; //mazo es el head
    CARTA *MAZOREV = NULL;
    CARTA *NUEVACARTA;
    JUGADOR jugador1;
    JUGADOR jugador2;
	analisis(&MAZO,&vidmin,&vidmax,&atamin,&atamax,&defmin,&defmax,cont,wh1);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
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

		printf("Que opcion del menu desea elegir:");
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
				printf("lellendo archivos \n");
				
				Sleep(3000);
				printf("\n\n\n mazo leido \n\n\n\n");
				system("cls");
				revolver(&MAZO, &MAZOREV);
				printf("revolviendo mazo\n");
				Sleep(1000);
				printf("mazo revuelto\n");
				Sleep(1000);
				
				while(whg==0){
					//asignar 15 cartas al jugador B)
					juego(&MAZOREV,&jugador1,&jugador2);
					imprimirCjugador(&jugador1);
					printf("DISPONES DE 10 SEG PARA VER QUE CARTAS TE TOCARON\n ELIGE SABIAMENTE");
					Sleep(9000);               //todo esto asigna las cartas y luego las muestra
					imprimirCjugador(&jugador2);
					system("cls");
					printf("\njugador 1 por favor seleccione 3 cartas para poder jugar\n");
					while(whj==0){                                                           // este while permite elegir las 3 cartas 
						int atkj2;
						int contCj1=0,contCj2=0;
						elegir(&jugador1);
						Sleep(1000);
						elegirj2(&jugador2);
						printf("\n tus 3 cartas estan en la mesa solo puedes ver nombre y vida de J2\n piensa sabiamente tus movimientos\n");
						printf("\ncartas J2\n");
					//	imprimirCjugador2(&jugador2);
						int Cpcombate= 0;
					
						Ecartamesa(&jugador1, Cpcombate);
						Ecartamesaj2(&jugador2);
						while(whattke==0){                           // este while repetira la mecanca de ataque hasta que los 2 jugadores se queden o sin 3 cartas
							printf("\nturno jugador 1\n");
							printf("\nDESEA ATACAR?\n 1= SI \n 0= NO\n");
							scanf("%d",&atke);
							if(atke==0){
								printf("TURNO JUGADOR 2\n");   //turno player2 para atacar esto se decidira con randoms dependiendo de las cartas que tenga en mano
								atkj2= rand ()%1;
								
								if(atke==1){
									//aaca se leeran las cartas en mano y se limitaran los ataque a esas cartas
									int cj2= rand() %3;
									int caj1= rand()%3;
									// Contar el número de elementos en la lista
								  /*  jugador1->enJuego[caj1]->defensa - jugador2->enJuego[cj2]->ataque;
								    if(jugador1->enJuego[caj1]->defensa<=0){
								    	jugador1->enJuego[caj1]->vida - jugador->enJuego[cj2]->ataque;								    	
									}*/
								    	
								}else{
									printf("\n JUGADOR 2 NO ATACO :P\n");
									
								}
							}else {              //aca vendra cuando el ususario quiera atacar
								if(atke>=1){
								/*	int ATJ1cj2= 0;
									int ATJ1caj1= 0;
									printf("\nPOR FAVOR SELECCIONE CUAL DE SUS CARTAS DESEA USAR\n");
									scanf("%d",ATJ1caj1);
									if(ATJ1caj1<=0 || ATJ1caj1>= 3){
										jugador2->enJuego[]->defensa-jugador1->enJuego[ATJ1caj1]->ataque;
										
									}
									
									*/
								}
							}
							
						whattke= 1;	
						}//cerrar este while para que quede el que deja elegir cartas xd
						
					
					whj=1;	
					}
					
				whg=1;	
				}
				
				
				
				
				break;
				
			case 3:
				
			break;
			
			case 4:
				reglas();
			break;
			
			
			
			case 5:
			//liberar memoria aca
				liberal(&MAZO,&MAZOREV);
			
				wh1= 1;
				printf("MUCHAS GRACIAS POR JUGAR ME HUBIESE GUSTADO TRAER MAS COSAS...PIDO PERDON POR ESO ");
			default: wh1= 1;  break;
		}
	}
	return 0;
}
