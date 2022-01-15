#include <contador_seguro.h>
#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t __lock;
static int inicializado = 0;

static int __contador = 0;

int inicializar_contador_seguro(void) {
  if (!inicializado) {
    if (0 != pthread_mutex_init(&__lock, NULL)) {
      perror("Error creando mutex");
      return -1;
    }

    inicializado = 1;
  } else {
    printf("Mutex ya inicializado.\n");
    return -1;
  }

  return 0;
}

int incrementar_contador_seguro(int valor) {
  if (inicializado) {
    pthread_mutex_lock(&__lock);
    __contador += valor;
    pthread_mutex_unlock(&__lock);
  } else {
    printf("Mutex no inicializado.\n");
    return -1;
  }

  return 0;
}

int obtener_contador_seguro(int *valor) {
  if (inicializado) {
    pthread_mutex_lock(&__lock);
    *valor = __contador;
    pthread_mutex_unlock(&__lock);
  } else {
    printf("Mutex no inicializado.\n");
    return -1;
  }

  return 0;
}

int deinicializar_contador_seguro(void) {
  if (inicializado) {
    if (0 != pthread_mutex_destroy(&__lock)) {
      perror("Error destruyendo mutex");
      return -1;
    }

    inicializado = 0;
  } else {
    printf("Mutex no inicializado.\n");
    return -1;
  }

  return 0;
}