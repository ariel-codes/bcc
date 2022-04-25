#include <pthread.h>
#include <semaphore.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// estrutura que representa um rendez-vous (rv)
typedef struct rv_t {
  sem_t *w_sem; // O semaphore de "encontro"
} rv_t;

// inicialização do rv
void rv_init(rv_t *rv) { sem_init(rv->w_sem, 0, -1); }

// operador de espera no rv
void rv_wait(rv_t *rv) {
  sem_post(rv->w_sem);
  sem_wait(rv->w_sem);
}

void *my_thread(void *rv_arg) {
  rv_t *rv = rv_arg;
  sleep(random() % 10); // processe algo
  rv_wait(rv);
  printf("Eu venho antes\n");
  sleep(random() % 10); // processe algo#2
  rv_wait(rv);
  printf("Eu venho depois\n");
  return 0;
}

int main() {
  rv_t rv;
  pthread_t t1, t2;

  rv_init(&rv);

  pthread_create(&t1, NULL, my_thread, &rv);
  pthread_create(&t2, NULL, my_thread, &rv);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
