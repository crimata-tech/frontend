/*
** Crimata Technologies - 2020
**
** Package Handler: Landon Clark
**
**
** This file seeks to define quality-of-life functionality for client-side
** networking. This implementation allows us to hold our client socket
** information while abstracting away any handling of the socket data itself.
**
** The functions are as follows:
**
**   *********************FUNCTIONS SEMANTICS*************************
**
**   1. @connect_socket ( host name, port number ) : This method allows us to
**   initiate our client side socket with only an IP and port, thus abstracting
**   the tedious and largely uniform aspects of the TCP socket away.
**
**   2. socket_send ( message, message length ) : This method allows us the
**   ability to send a message across our pre-established socket needing only
**   the message itself.
**
**   3. send_package ( package, package length ) : This method wraps up audio
**   data as an audio package and sends it across the pre-established socket.
**
**   4. @@socket_recv ( message, message length ) : This method places 'message
**   length' adjacent bytes of data received from the socket in the memory
**   held by message.
**
**   5. recv_package ( package, package length ) : This method parses a received
**   message to determine what type of message was sent, returns that value and
**   stores the length of the data in the 'message length' variable and the
**   actual data in ['message length' * sizeof('message type')] adjacent bytes
**   starting at 'package'. The data returned in 'package' should be handled
**   depending on the return value of this method as an audio message does not
**   contain 'char' data while a text message does.
**
**   6. close_socket () : This method handles the closing of our pre-established
**   socket.
**
**
**   @ - This needs to be done before any other method - there are no
**   protections on doing the others first, but they will not work as expected.
**
**   @@ - Should be essentially a helper function as (4) handles packages which
**   will likely be how we receive data from our sockets anyways.
 */


/*  LIBRARIES  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//strlen
#include <sys/socket.h>
#include <arpa/inet.h>	//inet_addr
#include <unistd.h>

/*  HEADER FILE  */
#include "package_handler.h"

/*  ERROR macro to return if problems occur  */
#define ERROR -1

/*  Packages will either be audio or text, an enum exposes this pretty well  */
enum _package_type {
AUDIO,
TEXT,
};


/*  This value will hold our socket information statically, allowing it to live
 *  outside of this files lifetime which may be essential  */
static int socket_desc;


/*  Predefined header length as determined by Crimata Backend  */
size_t HEADER_LENGTH = 20;


int min_int (int a, int b) {
	return (a < b) ? a : b;
}

/*  Boilerplate socket connection function  */
int connect_socket ( char *server_ip , int port ) {

	struct sockaddr_in server;

	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == ERROR)
	{
		printf("Could not create socket");
		return ERROR;
	}
		
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_family = AF_INET;
	server.sin_port = htons( port );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("connect error");
		return ERROR;
	}
	
	puts("Connected\n");

	return 0;
}



/*  Boilerplate message sending function  */
int socket_send ( char *message, int len ) {

	if (send(socket_desc , message , len , 0) < 0)
	{
		puts("Send failed");
		return ERROR;
	}

	return 0;
}


int send_package ( char *data, int mes_len, int type ) {
	
	char header[HEADER_LENGTH];
	char len[12];

	switch(type) {
		case 0:
			strcpy(header, "aud-");
			break;

		case 1:
			strcpy(header, "txt-");
			break;

		case 2:
			strcpy(header, "con-");
			break;
	}

	sprintf(len, "%d", mes_len);

	// makes eg. "aud-1532"
	strcat(header, len);

	sprintf(header, "%-20s", header);

	// sending header and data separately
	if ( socket_send(header, HEADER_LENGTH) < 0 ) {
		puts("failed to send package header");
		return ERROR;
	}

	if ( socket_send(data, mes_len) < 0) {
		puts("failed to send package data");
		return ERROR;
	}

	return 0;

}


/*  Boilerplate message receiving function  */
int socket_recv ( char *response, int resp_len ) {

	int bytes_left = resp_len;
	int bytes_read = 0;

	int _read = 0;

	while (bytes_left > 0) {
		_read = recv(socket_desc, &(response[bytes_read]), bytes_left, 0);
		bytes_read += _read;
		bytes_left -= _read;
	}

	return 0;
}



/*  Boilerplate package parsing function  */
int recv_package ( char **data, int *mes_len ) {

	char header[HEADER_LENGTH+1];
	char *mes_type;

	if ( socket_recv(header, HEADER_LENGTH) < 0 ) {
		puts("receiving packet failed");
		return ERROR;
	}

	mes_type = strtok(header, "-");
	*mes_len = atoi((const char *) strtok(NULL, "\0"));

	*data = realloc(*data, (*mes_len+1)*sizeof(char));

	if ( socket_recv(*data, *mes_len) < 0 ) {
		puts("failed to receive data from package");
		return ERROR;
	}

	if ( strcmp(mes_type, "aud") == 0 ) {
		return AUDIO;
	}

	if ( strcmp(mes_type, "txt") == 0 ) {
		return TEXT;
	}

	puts("could not find package type");
	return ERROR;

}



/*  Boilerplate socket closing function  */
int close_socket () {
	if (close(socket_desc) < 0) {
		return ERROR;
	}
	return 0;
}
