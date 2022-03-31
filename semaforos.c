#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <pthreads.h>

#define CONTAR_ATE 100000
#define MAX_THREADS 4

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// variável i é meu contador global.
long long i = 0;

void* comecar_contagem(void* arg) {
  //loop infinito com for, semelhante a while(true).
  for(;;) {

    // esta funçao tranca o recurso de software utilizado para a thread.
    pthread_mutex_lock(&mutex);

    if(i >= CONTAR_ATE) {
      // se i for maior ou igual ao numero que quero chegar, destrava o recurso
      // e chama o return para terminar a funçao...
      pthread_mutex_unlock(&mutex);
      return NULL;
    }

    // enquanto a condiçao acima nao for atendida, incremento meu contador enquanto minha thread
    // usufrui do recurso...
    i = i + 1;

    // e destravo o meu recurso para a próxima thread.
    pthread_mutex_unlock(&mutex);
    printf("i = %lld\n", i);
  }
}

int main(void) {
  int i = 0;

  // crio multiplas threads (array) usando memory allocation passando o tamanho da pthread_t
  // multiplicando com o define de MAX_THREADS que sao quatro
  pthread_t* grupo_de_threads = malloc(sizeof(pthread_t) * MAX_THREADS);


  // starto todas as threads
  for(i = 0; i < MAX_THREADS; i++) {
    pthread_create(&grupo_de_threads[i], NULL, comecar_contagem, NULL);
  }

  // esperar por todas as threads terminarem
  for(i = 0; i < MAX_THREADS; i++) {
    pthread_join(grupo_de_threads[i], NULL);
  }

  return 0;
}
