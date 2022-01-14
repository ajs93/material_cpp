#include <ManejadorCliente.hpp>

#include <string.h>

#include <chrono>
#include <iostream>
#include <vector>

ManejadorCliente::ManejadorCliente(Socket sock, const sockaddr &addr, socklen_t addr_len) :
  __run{true} {
  __sock = sock;
  __addr_len = addr_len;
  memcpy(&__address, &addr, sizeof(__address));

  timeval receive_timeout;
  receive_timeout.tv_sec = 1;
  receive_timeout.tv_usec = 0;

  if (-1 == setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (void*)&receive_timeout, sizeof(receive_timeout))) {
    throw std::runtime_error(strerror(errno));
  }

  __loop_thread = std::thread(&ManejadorCliente::__loop, this);
}

ManejadorCliente::~ManejadorCliente() {
  __run = false;
  __loop_thread.join();
}

void ManejadorCliente::__loop() {
  std::vector<uint8_t> buffer(RECV_BUFFER_SIZE);

  sockaddr_in *aux_addr = (sockaddr_in*)&__address;
  __addr_str = std::string(inet_ntoa(aux_addr->sin_addr));

  __printEvento("Nueva conexion");

  do {
    ssize_t res = recv(__sock, (void*)buffer.data(), buffer.size(), 0);

    if (-1 == res) {
      __analizarErrorRecibiendo(errno);
    } else if (0 < res) {
      std::vector<uint8_t> respuesta(res);
      
      auto it = buffer.rbegin();
      while (it != buffer.rend()) {
        respuesta.push_back(*it);
        it++;
      }

      send(__sock, respuesta.data(), respuesta.size(), 0);
    } else {
      __run = false;
      __printEvento("Conexion cerrada");
    }
  } while(__run);

  __printEvento("Conexion finalizada");
}

void ManejadorCliente::__analizarErrorRecibiendo(int error) {
  if (EAGAIN != error) {
    __run = false;
    __printEvento(std::string("Error recibiendo") + strerror(errno));
  }
}

void ManejadorCliente::__printEvento(const std::string &evento) {
  std::cout << '(' << __addr_str << ") - " << evento << std::endl;
}