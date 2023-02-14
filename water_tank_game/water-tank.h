#ifndef th
#define th

int water_tank = 0;
pthread_mutex_t w_mutex;
pthread_cond_t w_cond;

void *fill(void *arg){

    while(water_tank < 40)
    {
    pthread_mutex_lock(&w_mutex);  
   
    water_tank += 15;
    printf("filling water level: %i\n", water_tank);
    
    pthread_mutex_unlock(&w_mutex); 
    pthread_cond_broadcast(&w_cond);

    usleep(0);
    }  

    return NULL;
   
}

void *fill_bucket(void *arg){

   int water_bucket = 0;
    
    pthread_mutex_lock(&w_mutex);

    while(water_tank < 40){
        
    printf("not enought water level: %i\n", water_tank);

    pthread_cond_wait(&w_cond, &w_mutex);
    
    }
    
    water_bucket += 40;
    water_tank -= water_bucket;
    
    printf("what is left of the tank is: %i\n", water_tank);
    pthread_mutex_unlock(&w_mutex);
    
    
    return NULL;
}

#endif
