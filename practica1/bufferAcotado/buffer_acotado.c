#include "buffer_acotado.h"

int limited_buffer_create  (limited_buffer_t *buffer, int buff_size) {
	//Si buff_size > TAMANIO devolver falso
    	if(buff_size > TAMANIO){
            printf("error al inicializar el buffer");
		return 0;
        }
	//Inicializar los contadores
        buffer->cuenta = 0; 
	buffer->primero = 0;
	buffer->ultimo = 0;
        buffer->btam = buff_size;
	//Inicializar el mutex
        pthread_mutex_init(&buffer->mutex,NULL);
	//Inicializar las variables de condición
        pthread_cond_init(&buffer->lleno, NULL);
	pthread_cond_init(&buffer->vacio, NULL);
	//Devolver verdadero
        printf("buffer inicializado");
        return 1;
}

void limited_buffer_destroy (limited_buffer_t  *buffer) {
	//Destruir mutex
        pthread_mutex_destroy(&buffer->mutex);
	//Destruir las variables de condición
        pthread_cond_destroy(&buffer->lleno);
        pthread_cond_destroy(&buffer->vacio);
}

void limited_buffer_put (limited_buffer_t  *buffer, int  elem) {
	//Acceder a la región crítica a través del mutex
        pthread_mutex_lock(&buffer->mutex);
	//Mientras el buffer esté lleno, bloquearse en la variable de condición lleno
        while(buffer->cuenta >= buffer->btam)
            pthread_cond_wait(&buffer->lleno, &buffer->mutex);
	//Añadir elem en el buffer y actualizar cuenta y último
        buffer->buf[buffer->ultimo] = elem;
	buffer->ultimo++;
	buffer->cuenta++;
        
        printf("Se ha insertado el elemento: %d\n",elem);
        
         if(buffer->ultimo == TAMANIO)
              buffer->ultimo=0;
         
	//Liberar el mutex
        pthread_mutex_unlock(&buffer->mutex);
	//Hacer un signal en la variable de condición vacio
        pthread_cond_signal(&buffer->vacio);

}

void limited_buffer_get (limited_buffer_t  *buffer, int *elem) {
	//Acceder a la región crítica a través del mutex
        pthread_mutex_lock(&buffer->mutex);
	//Mientras el buffer esté vacío, bloquearse en la variable de condición vacio
        while(buffer->cuenta == 0)
            pthread_cond_wait(&buffer->vacio, &buffer->mutex);
	//Guardar en *elem el primer elemento del buffer y actualizar cuenta y primero
        
        *elem = buffer->buf[buffer->primero];
	buffer->primero++;
	buffer->cuenta--;
        
        printf("Se ha extraido el elemento: %d\n",*elem);
        
        
        if(buffer->primero == TAMANIO)
              buffer->primero=0;
        
	//Liberar el mutex
        pthread_mutex_unlock(&buffer->mutex);
	//Hacer un signal en la variable de condición lleno
         pthread_cond_signal(&buffer->lleno);
}
