#include <Servidor.hpp>

#include <arpa/inet.h>
#include <string.h>

#include <iostream>

Servidor::Servidor(unsigned int port) :
  __port{port},
  __run{true} {
  __initSocket();
  __loop_thread = std::thread(&Servidor::__loop, this);
}

Servidor::~Servidor() {
  __run = false;
  __loop_thread.join();
}

void Servidor::__initSocket() {
  __server_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (-1 == __server_fd) {
    throw std::runtime_error(strerror(errno));
  }

  timeval receive_timeout;
  receive_timeout.tv_sec = 1;
  receive_timeout.tv_usec = 0;

  if (-1 == setsockopt(__server_fd, SOL_SOCKET, SO_RCVTIMEO, (void*)&receive_timeout, sizeof(receive_timeout))) {
    throw std::runtime_error(strerror(errno));
  }

  int reuse = 1;

  if (-1 == setsockopt(__server_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&reuse, sizeof(reuse))) {
    throw std::runtime_error(strerror(errno));
  }
  
  __server_address.sin_family = AF_INET;
  __server_address.sin_addr.s_addr = INADDR_ANY;
  __server_address.sin_port = htons(__port);

  socklen_t server_address_length = sizeof(__server_address);

  if (-1 == bind(__server_fd, (const sockaddr*)&__server_address, server_address_length)) {
    throw std::runtime_error(strerror(errno));
  }

  if (-1 == listen(__server_fd, SERVER_BACKLOG_SIZE)) {
    throw std::runtime_error(strerror(errno));
  }
}

void Servidor::__loop() {
  std::cout << "Servidor TCP inicializado en: " <<
               inet_ntoa(__server_address.sin_addr) << ":" << __port << std::endl;

  while (__run.load()) {
    sockaddr direccion_cliente;
    socklen_t largo_direccion;
    Socket nuevo_cliente = accept(__server_fd, &direccion_cliente, &largo_direccion);

    if (-1 == nuevo_cliente && errno != EAGAIN) {
      std::cerr << "Error aceptando nuevo cliente: " << strerror(errno) << std::endl;
      __run = false;
    } else if (0 < nuevo_cliente) {
      __clientes.emplace_back(nuevo_cliente, direccion_cliente, largo_direccion);
    }
  }

  std::cout << "Cerrando conexiones con todos los clientes..." << std::endl;
}