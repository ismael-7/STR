#include "buffer_acotado.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define REPETICIONES 50 //50
#define NUM_HILOS 5

void hilo_productor(limited_buffer_t *b) {
	//Llamar REPETICIONES veces a limited_buffer_put mostrando un mensaje con el número que se introducirá
   int i;
   for(i=0;i<REPETICIONES;i++){
       limited_buffer_put(b,i);
   }

}

void hilo_consumidor(limited_buffer_t *b) {
	//Llamar REPETICIONES veces a limited_buffer_get mostrando un mensaje con el número leído
    int x;
    int i;
    for(i=0;i<REPETICIONES;i++){
       limited_buffer_get(b,&x);
   }
}


int main (void) {
	//Definir una variable limited_buffer_t
        limited_buffer_t buffer;
	//Inicializar el buffer (si hay error, mostrar un mensaje y terminar)
        limited_buffer_create(&buffer,3);
	//Crear dos vectores idP e idC de tipo pthread_t y de tamaño NUM_HILOS para almacenar los identificadores de los productores y de los consumidores
        pthread_t idC[NUM_HILOS], idP[NUM_HILOS];

        //Lanzar los NUM_HILOS productores y consumidores
                 
        int i;
        for(i=0;i<NUM_HILOS;i++){
          pthread_create(&idP[i],NULL,(void *)hilo_productor,(void *)&buffer);
          pthread_create(&idC[i],NULL,(void *)hilo_consumidor,(void *)&buffer);
        }
         
	//Esperar a que terminen todos los productores y los consumidores

	for (int i = 0; i < NUM_HILOS; i++){
		pthread_join(idP[i],NULL);
		pthread_join(idC[i],NULL);
	}
	//Destruir el buffer
        limited_buffer_destroy(&buffer);
	return 0;
}
