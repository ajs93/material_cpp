#include <servidor.h>
#include <contador_seguro.h>

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static int __run = 1;

static void sigint_handler(int sig) {
  __run = 0;
}

int main(void) {
  struct sigaction new_handler = {{0}}, old_handler = {{0}};
  new_handler.sa_handler = sigint_handler;
  if (sigaction(SIGINT, &new_handler, &old_handler) == -1) {
    perror("Error en sigaction");
    return -1;
  }
  
  if (0 != inicializar_contador_seguro()) {
    return -1;
  }

  if (0 != iniciar_servidor()) {
    deinicializar_contador_seguro();
    return -1;
  }

  while (__run) {
    sleep(1);
  }

  detener_servidor();
  deinicializar_contador_seguro();

  return 0;
}