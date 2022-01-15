#include <servidor.h>
#include <cliente.h>

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#define   PUERTO_SERVIDOR         (15001)
#define   SERVER_BACKLOG_SIZE     (10)

// Variable privadas al modulo
static int __run = 1;

static int __server_fd;

static struct sockaddr_in __server_address;

static pthread_t __server_loop_thread;
static int __server_created = 0;

static int __cantidad_clientes_conectados = 0;

// Funciones privadas al modulo

static void *__loop_servidor(void *argumentos);

static int __inicializar_socket(void);

int iniciar_servidor(void) {
  if (-1 == __inicializar_socket()) {
    return -1;
  }

  int res = pthread_create(&__server_loop_thread, NULL, __loop_servidor, NULL);

  if (0 != res) {
    perror("Error creando servidor");
    return -1;
  }

  __server_created = 1;

  return 0;
}

void detener_servidor(void) {
  if (__server_created) {
    __run = 0;
    int res = pthread_join(__server_loop_thread, NULL);

    if (0 != res) {
      perror("Error deteniendo el servidor");
    }
  }
}

static int __inicializar_socket(void) {
  __server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (-1 == __server_fd) {
    perror(NULL);
    return -1;
  }

  struct timeval receive_timeout;
  receive_timeout.tv_sec = 1;
  receive_timeout.tv_usec = 0;

  if (-1 == setsockopt(__server_fd, SOL_SOCKET, SO_RCVTIMEO, (void*)&receive_timeout, sizeof(receive_timeout))) {
    perror(NULL);
    return -1;
  }

  int reuse = 1;

  if (-1 == setsockopt(__server_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse, sizeof(reuse))) {
    perror(NULL);
    return -1;
  }
  
  __server_address.sin_family = AF_INET;
  __server_address.sin_addr.s_addr = INADDR_ANY;
  __server_address.sin_port = htons(PUERTO_SERVIDOR);

  socklen_t server_address_length = sizeof(__server_address);

  if (-1 == bind(__server_fd, (const struct sockaddr*)&__server_address, server_address_length)) {
    perror(NULL);
    return -1;
  }

  if (-1 == listen(__server_fd, SERVER_BACKLOG_SIZE)) {
    perror(NULL);
    return -1;
  }
}

static void *__loop_servidor(void *argumentos) {
  printf("Servidor TCP inicializado en: %s:%d\n", inet_ntoa(__server_address.sin_addr), PUERTO_SERVIDOR);

  while (__run) {
    struct sockaddr direccion_cliente;
    socklen_t largo_direccion;
    int nuevo_cliente = accept(__server_fd, &direccion_cliente, &largo_direccion);

    if (-1 == nuevo_cliente && errno != EAGAIN) {
      printf("Error aceptando nuevo cliente: %s\n", strerror(errno));
      __run = 0;
    } else if (0 < nuevo_cliente) {
      if (0 > crear_cliente(nuevo_cliente, &direccion_cliente, largo_direccion)) {
        printf("Error creando cliente.\n");
      }
    }
  }
}