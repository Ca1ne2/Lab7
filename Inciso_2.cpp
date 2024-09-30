//Programacion MicroProcesadores 
//Lab 7 
//Jorge Palacios 231385 
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // Para la función sleep
#include <stdlib.h>  // Para la función exit

#define MAX_BOLSAS 400
#define CAPACIDAD_SILO 5

int cafe_silo = 0;
int cafe_bodega = 0;

pthread_mutex_t mutex_silo;
pthread_cond_t cond_empacadora;

void* tostadora1(void* arg) {
    while (cafe_bodega < MAX_BOLSAS) {
        sleep(1);
        pthread_mutex_lock(&mutex_silo);
        
        if (cafe_bodega >= MAX_BOLSAS) {
            pthread_mutex_unlock(&mutex_silo);
            break;
        }
        
        cafe_silo++;
        printf("Tostadora 1 produjo: 1 lb de café tostada\n");
        
        pthread_cond_signal(&cond_empacadora);
        pthread_mutex_unlock(&mutex_silo);
    }
    pthread_exit(NULL);
}

void* tostadora2(void* arg) {
    while (cafe_bodega < MAX_BOLSAS) {
        sleep(1);
        pthread_mutex_lock(&mutex_silo);
        
        if (cafe_bodega >= MAX_BOLSAS) {
            pthread_mutex_unlock(&mutex_silo);
            break;
        }
        
        cafe_silo++;
        printf("Tostadora 2 produjo: 1 lb de café tostada\n");
        
        pthread_cond_signal(&cond_empacadora);
        pthread_mutex_unlock(&mutex_silo);
    }
    pthread_exit(NULL);
}

void* empacadora(void* arg) {
    while (cafe_bodega < MAX_BOLSAS) {
        pthread_mutex_lock(&mutex_silo);
        
        // Esperar hasta que haya 5 libras en el silo para empacar
        while (cafe_silo < CAPACIDAD_SILO && cafe_bodega < MAX_BOLSAS) {
            pthread_cond_wait(&cond_empacadora, &mutex_silo);
        }
        
        // Empacar café
        if (cafe_bodega < MAX_BOLSAS) {
            cafe_silo--;
            cafe_bodega++;
            printf("Empacadora produjo: 1 bolsa de 1 lb de café\n");
            printf("Lbs de café en bodega: %d\n", cafe_bodega);
            printf("Lbs de café en silo: %d\n", cafe_silo);
        }
        
        pthread_mutex_unlock(&mutex_silo);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_tostadora1, thread_tostadora2, thread_empacadora;
    
    // Inicializar el mutex y la condición
    pthread_mutex_init(&mutex_silo, NULL);
    pthread_cond_init(&cond_empacadora, NULL);
    
    // Crear los hilos
    pthread_create(&thread_tostadora1, NULL, tostadora1, NULL);
    pthread_create(&thread_tostadora2, NULL, tostadora2, NULL);
    pthread_create(&thread_empacadora, NULL, empacadora, NULL);
    
    // Esperar a que los hilos terminen
    pthread_join(thread_tostadora1, NULL);
    pthread_join(thread_tostadora2, NULL);
    pthread_join(thread_empacadora, NULL);
    
    // Destruir el mutex y la condición
    pthread_mutex_destroy(&mutex_silo);
    pthread_cond_destroy(&cond_empacadora);
    
    printf("Lbs de café en bodega: %d\n", cafe_bodega);
    printf("Lbs de café en silo: %d\n", cafe_silo);
    printf("Producción completada.\n");
    
    return 0;
}
