//incluir la librería para usar threads
#include <pthread.h>
#include <stdio.h>

#define TAMANIO 10

typedef struct {
	int buf[TAMANIO];
	int cuenta, primero, ultimo, btam;
	//Definir el mutex

	//Definir las variables de condición lleno y vacio
        pthread_mutex_t mutex;
	pthread_cond_t lleno;
	pthread_cond_t vacio;

} limited_buffer_t;

int limited_buffer_create  (limited_buffer_t *buffer, int buff_size);
void limited_buffer_destroy (limited_buffer_t  *buffer);
void limited_buffer_put (limited_buffer_t  *buffer, int  elem);
void limited_buffer_get (limited_buffer_t  *buffer, int *elem);
