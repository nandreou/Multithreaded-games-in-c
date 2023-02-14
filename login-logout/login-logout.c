#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *login(void *args){

sem_wait(&s);

printf("Logged in %i\n", *(int*)args);
int wait = rand() % 10; 

sleep(wait);

sem_post(&s);

printf("Logged out %i\n", *(int*)args);

free(args);

    return NULL;
}

int main (void){

srand(time(NULL));

pthread_t t[10];

sem_init(&s, 0, 5);

for(int i = 0; i<10; i++){
    int *p = malloc(sizeof(int));
    *p = i;
    if(pthread_create(t + i,NULL,&login, p)!=0){
        return 0;
    }
}


for(int i = 0; i<10; i++){
    
    if(pthread_join(*(t + i),NULL)!=0){
        return 0;
    }
}

sem_destroy(&s);

//pthread_exit(0);
}