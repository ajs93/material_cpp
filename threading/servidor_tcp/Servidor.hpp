#ifndef __SERVIDOR_HPP__
#define __SERVIDOR_HPP__

#include <ManejadorCliente.hpp>

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <atomic>
#include <list>
#include <thread>

class Servidor {
public:
  using Socket = int;

  Servidor(unsigned int port = DEFAULT_SERVER_PORT);

  ~Servidor();

private:
  static constexpr unsigned int DEFAULT_SERVER_PORT{15001};

  static constexpr int SERVER_BACKLOG_SIZE{10};

  const unsigned int __port;

  Socket __server_fd;

  std::atomic<bool> __run;

  std::thread __loop_thread;

  sockaddr_in __server_address;

  std::list<ManejadorCliente> __clientes;

  void __initSocket();

  void __loop();
};

#endif // __SERVIDOR_HPP__