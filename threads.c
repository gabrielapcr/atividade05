#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int qnt_threads = 0;
int **headquarters;
int line;
int some = 0;
int cont = 0;
void * soma(void * arg);
int main (void ){
    int i, j;
    printf("digite o valor da matriz :");
    scanf("%d", &line);
    qnt_threads = line;
    
    headquarters  = malloc(line  * sizeof(int*));
    for ( i = 0; i < line; i++)
    {
        headquarters[i]= malloc(line  * sizeof(int*));
    }
    for ( i = 0; i < line; i++)
    {
        for ( j = 0; j < line; j++)
        {
            scanf("%d", &headquarters[i][j]);
        }
        
    }
    pthread_t  threads[qnt_threads];

        for( i = 0 ; i < line ; i ++ ){
            for ( j = 0 ; j < line ; j ++ )
            {
                if (pthread_create(&threads[i], NULL,soma,NULL))
                    {
                    printf("erro na criacao de threads %d",i);
                    }
            }   
            cont ++;  
        }
    
    printf("%d \n",some);
    return 0;
}
void * soma(void * arg){
    int i ,j;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < line; i++)
    {   for ( j = 0; j < line; j++)
        { 
            if (i == cont)
                some += *(*(headquarters +i) + j);
            
        }

    }
    pthread_mutex_unlock(&mutex);
    return arg;
}
