#ifndef __CLIENTE_HPP__
#define __CLIENTE_HPP__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int crear_cliente(int socket_cliente, struct sockaddr *direccion_cliente, socklen_t largo_direccion);

#endif // __CLIENTE_HPP__