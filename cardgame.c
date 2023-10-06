//nombre: Martin vera, Rut:21586190-2, seccion:A, fecha: 30/09/2023//
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<math.h>
//se pueden usar variables globales usadas con define para no perderse
#define maxd_cartas = 15
#define cartas_juego = 3
#define UenJuego = 5
struct jugador{
	char nombre[200];
	int vida[4]; //un array para la vida? vida[0] = 1, vida[1] = 1 y asi? -n
	
	
};
struct cartas{
	char nombre[200];
	char clase[200];
	int ataque;
	int vida;
	int defensa;
	struct cartas*siguiente;
}CARTA;
struct historial{
	//el historial debe ser una cola ya que se muestran por orden
};


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
void nuevacarta(){
	//la funcion crear debe validar en base a los datos cargados en el analisis
	//en esta parte se relaciona con lo comentado en analisis, ya que a la hora de crear la carta
	//el usuario debe de respetar los limites max y min  x ej  si la vida tiene 90 y el limite es 70 la vida baja a 70
	
	
}
void juego(){
	int turno;
	
}
void analisis(struct cartas*personajes){
//	struct cartas personajes [75];
	FILE*fichero;
	fichero= fopen("cardgametest.txt","r");
	//verificador si el archivo presenta eerror o no 
	if(fichero == NULL){
		perror("fallo abrir el archivo");
		
		return 1;
	}
	while(feof(fichero)==0){
	
		fscanf(fichero ,%s,%s,%d,%d,%d, personajes->nombre,personajes->clase,personajes->ataque, personajes-> vida, personajes-> defensa)	
		
	}
//
	

	//debe haber un valor maximo para cada variable de vida, ataque y defensa 
	// de esta forma cuando se esten cargando se pueden ir guardando en una variable
	
	
}
void revolver(){
	
}
void atacar(){
	
}

int main(){
	int menu;
	
    //orden de las cartas                   Name,Type,vida,Ataque,DeFensa
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	//menu de inicio para empezar
	sleep(1);
	printf("CARGANDO JUEGO");
	sleep(1);
	printf("..");
	sleep(1);
	printf("..");
	sleep(1);
	printf("..");
	sleep(1);
	printf("............\nJUEGO CARGADO EXITOSAMENTE\n\n\n");
	printf("BIENVENIDO A THE CLASH OF THE GUARDIANS\n");
	sleep(1);
	printf("__________________________________________\n");
	printf("......opcion 1:   CREAR CARTA PROPIA.....\n");
	printf("......opcion 2:     NUEVA PARTIDA   .....\n");
	printf("......opcion 3:   HISTORIAL DEL JUEGO....\n");
	printf("......opcion 4:         REGLAS      .....\n");
	printf("......opcion 5:    SALIR DEL JUEGO  .....\n");
	printf("_________________________________________\n");
	sleep(1);
	printf("Que opcion desea elegir:");
	scanf("%d",&menu);
	switch(menu){
		case 1:
		
		break;
		
		case 2:
			
		break;
			
		case 3:
			
		break;
		
		case 4:
			
		break;
		
		
		
		case 5:
			
		default: break;
	}
	
	return 0;
}
