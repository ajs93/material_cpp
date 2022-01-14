#ifndef __MANEJADORCLIENTE_HPP__
#define __MANEJADORCLIENTE_HPP__

#include <arpa/inet.h>

#include <atomic>
#include <thread>

class ManejadorCliente {
public:
  using Socket = int;

  ManejadorCliente(Socket sock, const sockaddr &addr, socklen_t addr_len);

  ~ManejadorCliente();

  bool isRunning() const { return __run.load(); }

private:
  static constexpr unsigned int RECV_BUFFER_SIZE{128};

  std::atomic<bool> __run;

  Socket __sock;

  sockaddr __address;

  socklen_t __addr_len;

  std::thread __loop_thread;

  std::string __addr_str;

  void __loop();

  void __analizarErrorRecibiendo(int error);

  void __printEvento(const std::string &evento);
};

#endif // __MANEJADORCLIENTE_HPP__