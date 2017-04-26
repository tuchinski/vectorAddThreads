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

void *vecAdd(void * Param){

}

// Input vectors
    float *a;
    float *b;
    // Output vector
    float *c;
 
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
        a[i] = sinf(i)*sinf(i);
        b[i] = cosf(i)*cosf(i);
    }
    
    /* threads here!!!! */
    pthread_t vetThread[num_threads];
    Param vetParam[num_threads];
    //vetThread = (pthread_t*) malloc(sizeof(pthread_t)*num_threads);
    //vetParam = (Param*) malloc(sizeof(param) * num_threads);
    
    int k = n/num_threads;// tamanho do vetor/numero de threads(serve para saber em quanstas partes o vetor será separado)
    int qtdeIteracoes; //conta quantas vezes foi iterado o for
    for(i=0;i<n;i+=k){
    	vetParam[qtdeIteracoes].val1 = i;
    	vetParam[qtdeIteracoes].val2 = i+(k-1);
    	if(qtdeIteracoes+1 == num_threads){
    		vetParam[qtdeIteracoes].val2 = n%num_threads;
    		break;
    	}
    	qtdeIteracoes++;
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

