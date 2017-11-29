
//Añadir la librería de utilización de señales
#include <signal.h>
//Añadir la librería de utilización de pthreads
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include "funciones_time.h"


typedef struct{
  int recibidas;
  int esperadas;
}seniales_t;

void HiloSigInt (seniales_t *seniales) {
	//Crear un conjunto de señales
        sigset_t set,set1;
        int s;
	//Inicializar el conjunto de señales a vacío
        sigemptyset(&set);
	//Añadir SIGINT al conjunto de señales
        sigaddset(&set, SIGINT);
	//Añadir el conjunto de señales al conjunto de señales bloqueadas
        pthread_sigmask(SIG_BLOCK, &set, NULL);
        
        
        //igual pero insertando SIGRTMIN
        sigemptyset(&set1);
        sigaddset(&set1, SIGRTMIN);
        pthread_sigmask(SIG_BLOCK, &set1, NULL);
        
        //quitar SIGRTMIN del conjunto
	sigdelset(&set, SIGRTMIN);
        
	//Mientras no se capturen *num_capturas señales
              while(seniales->recibidas < seniales->esperadas){
		//Esperar por el conjunto de señales (solamente contiene SIGINT)
                 if (sigwait(&set, &s) != 0)
		       pthread_exit((void *) -1);
                 
                 printf("recibido SIGINT\n");
              
		//Incrementar las capturas
                seniales->recibidas++;
              }
}


void HiloPeriodicoConRetardos(seniales_t *seniales) {
    
    sigset_t set,set1;
    //Añadir SIGINT y SIGRTMIN al conjunto de señales
    sigaddset(&set, SIGINT);
    sigaddset(&set1, SIGRTMIN);
    //Añadir el conjunto de señales al conjunto de señales bloqueadas
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_sigmask(SIG_BLOCK, &set1, NULL);
    
    struct timespec hora_actual,periodo,siguiente;
    struct tm *hora;
    
    clock_gettime(CLOCK_MONOTONIC, &hora_actual);
    periodo.tv_sec = 5;
    periodo.tv_nsec = 0;
    //Calcular el siguiente instante como la suma de la hora actual y el periodo de repetición
    SumaTimeSpec(&siguiente,hora_actual,periodo);
    
    while(seniales->recibidas < seniales->esperadas){
        
    clock_gettime(CLOCK_MONOTONIC, &hora_actual);
    hora = localtime(&hora_actual.tv_sec);
     
    printf("Hora CLOCK_MONOTONIC: \n");
    printf("%d/%d/%d ", hora->tm_mday, hora->tm_mon,(hora->tm_year + 1900));
    printf("%d:%d:%d.%ld \n", hora->tm_hour,hora->tm_min,hora->tm_sec,hora_actual.tv_nsec/1000000);
    
    
    clock_gettime(CLOCK_REALTIME, &hora_actual);
    hora = localtime(&hora_actual.tv_sec);
    printf("Hora CLOCK_REALTIME: \n");
    printf("%d/%d/%d ", hora->tm_mday, hora->tm_mon,(hora->tm_year + 1900));
    printf("%d:%d:%d.%ld \n", hora->tm_hour,hora->tm_min,hora->tm_sec,hora_actual.tv_nsec/1000000);
    
    
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &hora_actual);
    hora = localtime(&hora_actual.tv_sec);
    printf("Hora CLOCK_THREAD_CPUTIME_ID: \n");
    printf("%d/%d/%d ", hora->tm_mday, hora->tm_mon,(hora->tm_year + 1900));
    printf("%d:%d:%d.%ld \n", hora->tm_hour,hora->tm_min,hora->tm_sec,hora_actual.tv_nsec/1000000);
    
    
    int i;
    for(i=0;i<100000000;i++){
     clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME,&siguiente,NULL);  
     SumaTimeSpec(&siguiente, siguiente, periodo);
    }
    
  }
    
}



void HiloPeriodicoConTemporizador(seniales_t *seniales){
    
    sigset_t set,set1;
    //Añadir SIGINT y SIGRTMIN al conjunto de señales
    sigaddset(&set, SIGINT);
    sigaddset(&set1, SIGRTMIN);
    //Añadir el conjunto de señales al conjunto de señales bloqueadas
    pthread_sigmask(SIG_BLOCK, &set, NULL);
    pthread_sigmask(SIG_BLOCK, &set1, NULL);
    //Quitar SIGINT del conjunto de señales. Esto es necesario ya que, aunque bloqueamos las dos señales, solamente esperamos por SIGRTMIN
    sigdelset(&set, SIGINT);
    
    timer_t id_timer;
    struct sigevent evento;
    evento.sigev_notify=SIGEV_SIGNAL;
    evento.sigev_signo=SIGRTMIN;
    
    
    //Definir una variable datos_temporizador de tipo struct itimerspec
    struct itimerspec datos_temporizador;
    //Leer la hora actual de CLOCK_MONOTONIC y almacenarla en el campo it_value de datos_temporizador
    clock_gettime(CLOCK_MONOTONIC, &datos_temporizador.it_value);
    
    datos_temporizador.it_value.tv_sec=datos_temporizador.it_value.tv_sec+2;
    //Establecer el campo it_interval de datos_temporizador a 2 segundos
    datos_temporizador.it_interval.tv_sec=2;
    
    timer_create(CLOCK_MONOTONIC, &evento, &id_timer);
    
    timer_settime(id_timer, TIMER_ABSTIME,&datos_temporizador,NULL);

    int a;
    while(seniales->recibidas < seniales->esperadas){
        printf("Numero de señales recibidas: %d \n", seniales->recibidas);
        sigwait(&set1, &a);
        //seniales->recibidas++;
    }
}



int main (int argc, char *argv[]) {
	if (argc!=2) {
		printf("Error en la ejecución. El formato correcto es p2_2 num_capturas\n");
		return 0;
	}
	
	seniales_t seniales;
	seniales.esperadas= atoi(argv[1]);
	seniales.recibidas=0;
	//Crear un conjunto de señales
        sigset_t set,set2;
	//Inicializar el conjunto de señales a vacío
        sigemptyset(&set);
	//Añadir SIGINT al conjunto de señales
        sigaddset(&set, SIGINT);
        //Añadir SIGRTMIN al conjunto de señales
        sigemptyset(&set2);
        sigaddset(&set2, SIGRTMIN);
	//Añadir el conjunto de señales al conjunto de señales bloqueadas
        pthread_sigmask(SIG_BLOCK, &set, NULL);
        pthread_sigmask(SIG_BLOCK, &set2, NULL);
	//Crear un identificador de hilo de tipo pthread_t
        pthread_t h,i,j;
	//Crear un hilo con la función HiloSigInt y el parámetro seniales
        pthread_create(&h,NULL,(void *)HiloSigInt,&seniales);
        pthread_create(&i,NULL,(void *)HiloPeriodicoConRetardos,&seniales);
        pthread_create(&i,NULL,(void *)HiloPeriodicoConTemporizador,&seniales);
	//Esperar el hilo
        pthread_join(h,NULL);
        pthread_join(i,NULL);
        pthread_join(j,NULL);
}