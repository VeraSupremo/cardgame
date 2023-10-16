# cardgame
# proyecto unidad 1 algoritmo y estructura de datos
 
 ## introduccion:
   el proyecto busca poder implementar de buena manera las listas, pilas y colas para reforzar esto se creo un juego de cartas en el cual podremos combatir, recorrer lista y eliminar    elementos de estas.
   ### El codigo fue realizado en el programa dev c++ en su version portable 5.11 y su compilador tiene la version de TDM-GCC 4.9.2 64-bits
   ### tambien el codigo utilizo librerias como: stdio.h, windows.h, time.h, stdlib.h y math.h
   ### link de la presentacion en youtube:[video presentacion](https://youtu.be/FGp8O3DVwnE)
   ### tenga la version de controlador que permita inicicializar variables dentro de un for

   ### Para la instalacion siga los pasos del ejecutable por favor.

### breve resumen del programa;
 el usuario al empezar el programa debe decidir en el menu si desea agregar una carta, iniciar la partida, ver las reglas o el historial y por ultimo salir
 el menu solo tomara numeros para ingresar, siempre que esten dentro del rango solicitado

 en la opcion de crear una carta se dan los valores maximos que no se dbeen sobrepasar por el usuario en el juego, sino su vida ataque o defensa seran sumados y divididos para que de esta forma no excedan el limite

 despues de crear la carta el usuario vuelve al menu para elegir la opcion de volver a crear y las demas opciones
 en la seccion de nueva partida las cartas se revuelven y se le entregan 15 a el usuario 1 y 2
 de estas 15 solo pueden elegir 3 en un inicio, despues deberan elegir una carta para dejar al frente de la batalla
 y se dara la opcion de sacar una carta o atacar
 si al atacar eliminas la vida de la carta esta se eliminara y el que pierda esta carta se le quitara una vida

si se elige la opcion numero 5 que es salir 
se libera la memoria y se cierra el juego 
