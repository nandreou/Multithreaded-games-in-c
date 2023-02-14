#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

int roll_table[10];

pthread_mutex_t m;

void *roll(void *arg){

    pthread_mutex_lock(&m);
    int index = *(int*)arg;
 
    roll_table[index] = (rand() % 6) + 1;
    
    printf("index: %i, value:%i \n",index, *(roll_table + index));
    
    free(arg);
    arg=NULL;
    pthread_mutex_unlock(&m);
    
    
    return NULL;
}

int main(void){

srand(time(NULL));

pthread_t t[10]; 

int *p=NULL;
int max = 0;
int pos = 0;
int number_of_games;

scanf("%i", &number_of_games);

while(number_of_games > 0){
pthread_mutex_init(&m, NULL);

for(int i = 0; i<10; i++){
    
    p = malloc(sizeof(int));
    *p = i;

    if(pthread_create(t + i, NULL, &roll, p)!=0)
        return 0;
}

for(int i = 0; i<10; i++){
    if(pthread_join(*(t + i), NULL)!=0)
        return 0;
}

pthread_mutex_destroy(&m);

for(int i = 0; i<10; i++){

    if(max < *(roll_table + i)){
        max = *(roll_table + i);
        pos = i;
    }

}
    printf("\n");

printf("Dice: %i won with: %i\n", pos, max);
printf("\n");

max=0;
number_of_games--;

usleep(50000);
}
return 0;

}