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
typedef struct cartas{
	char nombre[200];
	char clase[200];
//	int clase;
	int ataque;
	int vida;
	int defensa;
	struct cartas*siguiente;
}CARTA;
typedef struct historial{
	//el historial debe ser una cola ya que se muestran por orden
}HISTORIAL;


void reglas(){
	printf("________________________________________________________________________________________\n");
	printf("Cada jugador recibe un lote de 15 cartas, entregadas luego de revolver, de las cuales\n");
	sleep(1);
    printf(" debe seleccionar tres cartas para comenzar el juego las cuales quedan en su mano.\n");
    sleep(1);
    printf("Las 12 cartas restantes corresponden a un monto, que debe devolver y dejarlo al costado.\n");
    sleep(1);
    printf("Cada jugador parte con 5 puntos de vida. Los puntos de vida solo se restan cuando\n");
    sleep(1);
	printf("uno de los guardianes (las cartas) es derrotado.\n");
    printf("En cada turno los jugadores sacan una carta y ademas pueden:\n");
    printf("Seleccionar una carta y dejarla en el campo de batalla.\n");
    printf("Atacar a un oponente con una de las cartas que se encuentra en el campo de batalla.\n");
	printf("________________________________________________________________________________________\n");
}

void juego(){
	int turno;
	
}
// aca personajes es la lista de cartas
//lee el archivo de texto y añade carta a la lista
void analisis( CARTA **MAZO, int vidmin,int vidmax,int atamin,int atamax,int defmin,int defmax){
//	struct cartas personajes [75];
	char limite[MaximoLinea];
	int contador;
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

        char *nombre = strtok(limite, ",");
        strcpy(newStruct->nombre, nombre);                //para copiar texto
        
        
        //newStruct->clase = atoi(strtok(NULL, ","));
		char *clase = strtok(NULL, ",");
        strcpy(newStruct->clase, clase);
      
        newStruct->ataque = atoi(strtok(NULL, ","));      //atoi es  para valores enteros
        newStruct->vida = atoi(strtok(NULL, ","));
        newStruct->defensa = atoi(strtok(NULL, ","));

        newStruct->siguiente = NULL;

		printf("\n\n%s \n%s \n %d \n%d \n %d\n",newStruct->nombre,newStruct->clase,newStruct->ataque, newStruct-> vida, newStruct-> defensa);
        //                  Se añade el Struct creado a la lista existente.
       //  agregarcartas(lista, newStruct); // función para agregar elementos a la lista
       if(newStruct->vida < vidmin){
       	vidmin= newStruct->vida;
	   }
	   if(newStruct->vida > vidmax){
       	vidmax= newStruct->vida;
	   }
	   if(newStruct->ataque < atamin){
       	atamin= newStruct->ataque;
	   }
	   if(newStruct->ataque > atamax){
       	atamax= newStruct->ataque;
	   }
	   if(newStruct->defensa< defmin){
	   	defmin= newStruct->defensa;
	   }
	   if(newStruct->defensa> defmax){
	   	defmax= newStruct->defensa;
	   }
       
    }
    fclose(fichero);

	
/*	while(!feof(fichero)){
		fgets(temp,500,fichero);
		contador++;
		//par que vuelva al inicio la posicion y seguir trwabajando usammos rewind
	}
	rewind(fichero);
	for(int i= 0; !feof(fichero); i++){
		fscanf(fichero %s,%s,%d,%d,%d, personajes->nombre,personajes->clase,personajes->ataque, personajes-> vida, personajes-> defensa):	
		
	}
	
	
	while(feof(fichero)==0){
	
		fscanf(fichero ,%s,%s,%d,%d,%d, personajes->nombre,personajes->clase,personajes->ataque, personajes-> vida, personajes-> defensa):	
		
	}
*/
	

	//debe haber un valor maximo para cada variable de vida, ataque y defensa 
	// de esta forma cuando se esten cargando se pueden ir guardando en una variable
	
	
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
CARTA *crearcarta(char *nombre, char *clase, int ataque, int vida, int defensa){
	//la funcion crear debe validar en base a los datos cargados en el analisis
	//en esta parte se relaciona con lo comentado en analisis, ya que a la hora de crear la carta
	//el usuario debe de respetar los limites max y min  x ej  si la vida tiene 90 y el limite es 70 la vida baja a 70
	CARTA *NUEVACARTA = (CARTA *)malloc(sizeof(CARTA));
    strcpy(NUEVACARTA->nombre, nombre);
    strcpy(NUEVACARTA->clase, clase);
  //  NUEVACARTA->clase = clase;
    NUEVACARTA->ataque = ataque;
    NUEVACARTA->vida = vida;
    NUEVACARTA->defensa = defensa;
    NUEVACARTA->siguiente = NULL;
    return NUEVACARTA;
	
}
void revolver(){
	
}
void atacar(){
	
}

int main(){
	int menu;
	char *nombreNC;
	char * claseNC;
	int ataqueNC;
	int vidaNC;
	int defensaNC;
	int wh1= 0;
	int vidmin=0,vidmax=0,atamin=0,atamax=0,defmin=0,defmax=0; //todo estos valores se tomaran del archivo
	
    //orden de las cartas                   Name,Type,vida,Ataque,DeFensa
    CARTA *MAZO= NULL; //mazo es el head
    CARTA *NUEVACARTA;
	analisis(&MAZO,vidmin,vidmax,atamin,atamax,defmin,defmax);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//menu de inicio para empezar
	sleep(1);
	printf("\nCARGANDO JUEGO");
	sleep(1);
	printf("..");
	sleep(1);
	printf("..");
	sleep(1);
	printf("..");
	sleep(2);
	printf("............\nJUEGO CARGADO EXITOSAMENTE\n\n\n");
	printf("BIENVENIDO A THE CLASH OF THE GUARDIANS\n");
	sleep(2);
	printf("__________________________________________\n");
	printf("......opcion 1:   CREAR CARTA PROPIA.....\n");
	printf("......opcion 2:     NUEVA PARTIDA   .....\n");
	printf("......opcion 3:   HISTORIAL DEL JUEGO....\n");
	printf("......opcion 4:         REGLAS      .....\n");
	printf("......opcion 5:    SALIR DEL JUEGO  .....\n");
	printf("_________________________________________\n");
	sleep(1);

	while(wh1==0){
		printf("Que opcion desea elegir:");
		scanf("%d",&menu);
	
		switch(menu){
			case 1:                                          //aca se crearan y agregaran nuevas cartas
			
				printf("\n INGRESE SOLO LO SOLICITADO\n el orden de ingresos son \nNOMBRE\n CLASE\nATAQUE\nVIDA\nDEFENSA\n ");
				printf("ingrese el nombre(SOLO LETRAS NO NUMEROS) :");
				scanf("%s",nombreNC);
				printf("%s",nombreNC);

				printf("\n ahora ingrese la clase de la carta SOLO LETRAS NO NUMEROS\n");
				scanf("%s",claseNC);	
				printf("\n %s",claseNC);

				printf("\n ingrese ahora el ataque NO LETRAS SOLO NUMEROS\n EL ATAQUE MAXIMO ES DE %d  ",atamax);
				scanf("%d",&ataqueNC);
				printf("\n %d",ataqueNC);
				if(ataqueNC < atamin || ataqueNC>atamax){
					ataqueNC = atamin;                   //redactar en readme: si ingresas un valor fuera de rango se pone de forma automatica el valor menor del archivo de texto
				}
				printf("\n ingrese ahora  la vida NO LETRAS SOLO NUMEROS\n LA VIDA MAXIMA ES DE %d  ",vidmax);
				scanf("%d",&vidaNC);
				printf("\n %d",vidaNC);
				if(vidaNC < vidmin || vidaNC> vidmax){
					vidaNC = vidmin;
				}
				printf("\n ingrese ahora la defensa NO LETRAS SOLO NUMEROS\n LA DEFENSA MAXIMA ES DE %d  ",defmax);
				scanf("%d",&defensaNC);
				printf("\n %d",defensaNC);
				if(defensaNC < defmin || defensaNC>defmax){
					defensaNC = defmin;
				}
				
				NUEVACARTA = crearcarta( nombreNC, claseNC, ataqueNC, vidaNC, defensaNC);
				agregarcartas(&MAZO, NUEVACARTA);
				printf("%s,%s,%d,%d,%d",nombreNC, claseNC, ataqueNC, vidaNC, defensaNC);
					
				
			
			break;
			
			case 2:
				
			break;
				
			case 3:
				
			break;
			
			case 4:
				reglas();
			break;
			
			
			
			case 5:
				wh1= 1;
			default: wh1= 1;  break;
		}
	}
	return 0;
}
