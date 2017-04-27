/* TODO: implement threaded code 
 To be done in class */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <pthread.h>
#include <stdio.h>

#define MAX_THREADS 2048

typedef struct{
    int val1;
    int val2;
}Param;

// Input vectors
    float *a;
    float *b;
    // Output vector
    float *c;
 
void *vecAdd(void * p){
    Param* vetor = (Param*) p;
    float inicio,fim;
    inicio = vetor->val1;
    fim = vetor->val2;

    /*printf("Inicio: %f\n",inicio);
    printf("fim: %f\n",fim);
*/
    for(int i=inicio;i<=fim;i++){
        c[i] = a[i]+b[i];
        //printf(" %f ", a[i]+b[i]);
        //printf("\n\nc[i]%f\n",i,c[i] );
    }

}

int main( int argc, char *argv[] ){
    
    int num_threads, i;
    pthread_t tid[MAX_THREADS];     /* Vetor de Identificadores de threads. */
    pthread_attr_t attr;            /* atributos de thread. */

    if (argc != 3) {
        fprintf(stderr, "Uso:  a.out <numero de threads> <quantidade de elementos>\n");
        exit(0);
    }

    if (atoi(argv[1]) <= 0) {
        fprintf(stderr,"%d deve ser > 0\n", atoi(argv[1]));
        exit(0);
    }

    if (atoi(argv[1]) > MAX_THREADS) {
        fprintf(stderr,"%d must be <= %d\n", atoi(argv[1]), MAX_THREADS);
        exit(0);
    }

    if (atoi(argv[2]) <= 0) {
        fprintf(stderr,"%d deve ser > 0\n", atoi(argv[2]));
        exit(0);
    }
    
    // Size of vectors
    num_threads = atoi(argv[1]);
    printf("The number of threads is %d\n", num_threads);
    
    int n = atoi(argv[2]);
 
    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(float);
 
    // Alocar os vetores.
    a = (float*)malloc(bytes);
    b = (float*)malloc(bytes);
    c = (float*)malloc(bytes);
 
    // Inicializa os vetores.
    for(i=0; i<n; i++) {
        a[i] = i+0.1;
        b[i] = i+10.1;
    }
    
    /* threads here!!!! */
    Param vetParam[num_threads]; 
    int k = n/num_threads;
    int numIteracoes = 0;
    for(i=0;i<n;i+=k){
        vetParam[numIteracoes].val1 = i;
        vetParam[numIteracoes].val2 = (i+(k-1));
        if(numIteracoes+1 == num_threads){
            vetParam[numIteracoes].val2 +=n%num_threads;
            break;
        }
        numIteracoes++;
    }  

    pthread_t vetThread[num_threads];

    for(i=0;i<num_threads;i++){
        printf("\t\t\n%i\n",pthread_create(&vetThread[i],NULL,vecAdd,&vetParam[i]));
    }

    for(i=0;i<num_threads;i++){
        pthread_join(vetThread[i],NULL);
    }


 
    // Show results
    printf("Vetores: \n");
    for(i=0; i<n; i++){
        printf("%g + %g = %g\n", a[i], b[i], c[i]);
    }
 
    printf("fim.\n");
 
    // Release memory
    free(a);
    free(b);
    free(c);
 
    return 0;
}

