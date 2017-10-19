//Compilación por consola: gcc p2_2.c -o p2_2
//Configuración en eclipse: botón derecho sobre el proyecto -> Properties -> C/C++ Build -> Settins -> Cross GCC Linker -> Libraries -> Añadir pthread

//Añadir la librería de utilización de señales
#include <signal.h>
//Añadir la librería de utilización de pthreads
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void HiloSigInt (int *num_capturas) {
	//Crear un conjunto de señales
        sigset_t set;
        int s;
	//Inicializar el conjunto de señales a vacío
        sigemptyset(&set);
	//Añadir SIGINT al conjunto de señales
        sigaddset(&set, SIGINT);
	//Añadir el conjunto de señales al conjunto de señales bloqueadas
        pthread_sigmask(SIG_BLOCK, &set, NULL);
	//Mientras no se capturen *num_capturas señales
        int cap=0;
              while(cap < *num_capturas){
		//Esperar por el conjunto de señales (solamente contiene SIGINT)
                 if (sigwait(&set, &s) != 0)
		       pthread_exit((void *) -1);
                 
                 printf("recibido SIGINT\n");
              
		//Incrementar las capturas
                cap++;
              }
}

int main (int argc, char *argv[]) {
	if (argc!=2) {
		printf("Error en la ejecución. El formato correcto es p2_2 num_capturas\n");
		return 0;
	}
	int num_capturas=atoi(argv[1]);
	//Crear un conjunto de señales
        sigset_t set;
	//Inicializar el conjunto de señales a vacío
        sigemptyset(&set);
	//Añadir SIGINT al conjunto de señales
        sigaddset(&set, SIGINT);
	//Añadir el conjunto de señales al conjunto de señales bloqueadas
        pthread_sigmask(SIG_BLOCK, &set, NULL);
	//Crear un identificador de hilo de tipo pthread_t
        pthread_t h;
	//Crear un hilo con la función HiloSigInt y el número de capturas por las que se desea esperar
        pthread_create(&h,NULL,(void *)HiloSigInt,&num_capturas);
	//Esperar el hilo
        pthread_join(h,NULL);
}
