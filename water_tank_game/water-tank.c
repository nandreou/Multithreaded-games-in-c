#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "./water-tank.h"

int main(void){

    pthread_t t[5];

    pthread_mutex_init(&w_mutex, NULL);
    pthread_cond_init(&w_cond, NULL);

    for(int i = 0; i<5; i++)
    {

        if(i == 4){
            if(pthread_create(t + i, NULL, &fill, NULL) !=0)
                return 1;
        }else{
            
            if(pthread_create(t + i, NULL, &fill_bucket, NULL) !=0)
                return 1;
            
        }
    }

    for(int i = 0; i<5; i++)
    {
        if(pthread_join(t[i], NULL) !=0)
            return 1;
    }
    pthread_mutex_destroy(&w_mutex);
    pthread_cond_destroy(&w_cond);
}

