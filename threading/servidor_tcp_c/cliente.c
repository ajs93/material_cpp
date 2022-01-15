#include <cliente.h>
#include <contador_seguro.h>

#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define   RECV_BUFFER_SIZE          (128)
#define   SEND_BUFFER_SIZE          (128)

typedef struct {
  int socket;
  struct sockaddr direccion;
  socklen_t largo_direccion;
} argumentos_cliente_t;

static void *__loop_cliente(void *args);

static void __printEvento(const struct sockaddr *addr, const char *evento);

static void __analizarErrorRecibiendo(const struct sockaddr *addr, int error, int *run);

int crear_cliente(int socket_cliente, struct sockaddr *direccion_cliente, socklen_t largo_direccion) {
  argumentos_cliente_t *args = (argumentos_cliente_t*) malloc(sizeof(argumentos_cliente_t));
  
  if (NULL == args) {
    return -1;
  }

  args->socket = socket_cliente;
  args->largo_direccion = largo_direccion;
  memcpy(&args->direccion, direccion_cliente, sizeof (struct sockaddr));

  pthread_t nuevo_cliente;
  int res = pthread_create(&nuevo_cliente, NULL, __loop_cliente, args);

  if (0 != res) {
    perror("Error creando thread del cliente");
    free(args);
    return -1;
  }

  pthread_detach(nuevo_cliente);

  return 0;
}

static void *__loop_cliente(void *args) {
  argumentos_cliente_t *argumentos = (argumentos_cliente_t*)args;
  
  int __sock = argumentos->socket;
  socklen_t __largo = argumentos->largo_direccion;
  struct sockaddr __addr;

  int __run = 1;

  memcpy(&__addr, &argumentos->direccion, sizeof(struct sockaddr));

  free(args);

  char buffer[RECV_BUFFER_SIZE];

  __printEvento(&__addr, "Nueva conexion");

  do {
    ssize_t res = recv(__sock, buffer, RECV_BUFFER_SIZE, 0);

    if (-1 == res) {
      __analizarErrorRecibiendo(&__addr, errno, &__run);
    } else if (0 < res) {
      char respuesta[SEND_BUFFER_SIZE];
      ssize_t largo_respuesta;
      long int num = strtol(buffer, NULL, 10);

      if (errno != 0 && num == 0) {
        __printEvento(&__addr, "Parseo fallido");
        strcpy(respuesta, "Parseo fallido");
        largo_respuesta = strlen(respuesta);
      } else {
        int nuevo_valor_contador;
        incrementar_contador_seguro(num);
        obtener_contador_seguro(&nuevo_valor_contador);
        sprintf(respuesta, "%d", nuevo_valor_contador);
        largo_respuesta = strlen(respuesta);
      }

      send(__sock, respuesta, largo_respuesta, 0);
    } else {
      __run = 0;
      __printEvento(&__addr, "Conexion cerrada");
    }
  } while(__run);

  __printEvento(&__addr, "Conexion finalizada");
}

static void __printEvento(const struct sockaddr *addr, const char *evento) {
  struct sockaddr_in *aux_addr = (struct sockaddr_in*)addr;
  printf("(%s) - %s\n", inet_ntoa(aux_addr->sin_addr), evento);
}

static void __analizarErrorRecibiendo(const struct sockaddr *addr, int error, int *run) {
  if (EAGAIN != error) {
    char buffer_error[256];
    *run = 0;
    sprintf(buffer_error, "Error recibiendo: %s", strerror(error));
    __printEvento(addr, buffer_error);
  }
}