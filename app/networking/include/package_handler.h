#ifndef NETWORK
#define NETWORK

#include <stdlib.h>

int connect_socket ( char *server_ip , int port );

int socket_send ( char *message, int len );

int send_package ( char *data, int mes_len, int type );

int socket_recv ( char *response, int resp_len );

int recv_package ( char **data, int *mes_len );

int close_socket ();

#endif
