#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define stoves 10

int stove[stoves] = {100,100,100,100,100,100,100,100,100,100};
int sucess = 0;

pthread_mutex_t m[stoves];
pthread_mutex_t check;

void* consumption(void *arg){

int boo = 0;
int boo2 = 0;
int need;

   for(int i = 0; i<stoves; i++)
   {
    if(pthread_mutex_trylock(&m[i]) == 0){
    need = rand() % 30;
    if(stove[i] - need < 0){
    //   printf("No gas %i\n", i);

    pthread_mutex_unlock(&m[i]);
    
    }else{
        usleep(50000);
        stove[i] -= need;
        printf("coocked %i\n", i);
        sucess++; 
        boo = 1;
        pthread_mutex_unlock(&m[i]);
        break; 
    }
    }else if(i == stoves - 1){
           i=0;
    }
   }

//check for any gas left
if(boo == 0){
    pthread_mutex_lock(&check);
    for(int i = 0; i<stoves; i++){
        if(stove[i]>need){
            stove[i] -= 40;
            sucess++;
            boo2 = 1;
        }
    }
    pthread_mutex_unlock(&check);
    if(boo2 == 1)
        printf("Coocked \n");
    else
        printf("empty\n");
}

    return NULL;
}


int main(void){


    int quant = 0;
    
    printf("How many cookers do we have? \n");
    scanf("%i", &quant);
    
    pthread_t t[quant];

    for(int i = 0; i<stoves; i++)
    pthread_mutex_init(&m[i], NULL);

for(int i=0; i<quant; i++)
    {
        if(pthread_create(t+i, NULL, &consumption, NULL) != 0)
            return 1;
    }

for(int i=0; i<quant; i++)
    {
        if(pthread_join(*(t+i), NULL) != 0)
            return 1;
    }
    for(int i = 0; i<stoves; i++)
    pthread_mutex_destroy(&m[i]);

printf("%i\n", sucess);

    if(quant - sucess > 0){
        printf("Coockers who couldn't cook are: %i \n", quant - sucess);
    }else{
        printf("Everyone coocked successfully %i\n", quant - sucess);
    }
}