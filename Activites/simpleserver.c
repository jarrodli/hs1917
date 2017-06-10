/*
 *  simpleServer.c
 *  1917 lab 4
 *
 *  Richard Buckland 28/01/11, 30/3/14.
 *  Licensed under Creative Commons SA-BY-NC 3.0, share freely.
 *
 *	Caringbah High School's Poetry Server
 *	Modified by Stanley Su with a bit of help from Jarrod Li
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #define close closesocket
#else
    #include <netinet/in.h>
    #include <unistd.h>
#endif

int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void serveHTML (int socket);

#define SIMPLE_SERVER_VERSION 2.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7191
#define NUMBER_OF_PAGES_TO_SERVE 10
// after serving this many pages the server will halt

int main (int argc, char* argv[]) {

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup((2 << 8) + 2, &wsaData);
#endif

	printf ("************************************\n");
	printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
	printf ("Serving poetry since 2011\n");
	printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
	printf ("************************************\n");

	int serverSocket = makeServerSocket(DEFAULT_PORT);
	char request[REQUEST_BUFFER_SIZE];
	int numberServed = 0;
	while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
		printf ("*** So far served %d pages ***\n", numberServed);

		// STEP 1. wait for a request to be sent from a web browser,
		// then open a new connection for this conversation
		int connectionSocket = waitForConnection(serverSocket);

		// STEP 2. read the first line of the request
		int bytesRead = recv (connectionSocket, request, sizeof(request) - 1, 0);
		assert (bytesRead >= 0);
		// check that we were able to read some data from the connection

		// echo entire request to the console for debugging
		printf (" *** Received http request ***\n %s\n", request);

		// STEP 3. send the browser a simple html page using http
		printf (" *** Sending http response ***\n");
		serveHTML (connectionSocket);

		// STEP 4. close the connection after sending the page- keep aust beautiful
		close (connectionSocket);
		++numberServed;
	}

	// close the server connection after we are done- keep aust beautiful
	printf ("** shutting down the server **\n");
	close (serverSocket);

	return EXIT_SUCCESS;
}

void serveHTML(int socket) {
	const char* message =
	"HTTP/1.1 200 OK\r\n"
	"Content-Type: text/html\r\n"
	"\r\n"
	"<!DOCTYPE html>\n"
	"<html>\n"
	"<head><title>simpleserver.c</title>"
	"<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/4.0.0-alpha.6/css/bootstrap.min.css\">"
	"</head>\n"
	"<body>\
	<style>\
	body {\
		background-color: green;\
		color: green;\
		font-size: 14px;\
		text-align: center;\
	}\
	h1 {\
		font-family: Mission Script;\
		font-size: 22px;\
		font-style: oblique;\
		font-weight: bolder;\
	}\
	.centered {\
		position: absolute;\
		left: 50%;\
		top: 50%;\
		-webkit-transform: translate(-50%, -50%);\
		transform: translate(-50%, -50%);\
	}\
	.jumbotron {\
		background-color: white;\
		padding: 20px;\
	}\
	img {\
		display: block;\
		margin: 0 auto;\
		width: 30%;\
	}\
	span {\
		display: block;\
		text-align: right;\
	}\
	</style>\
	<body>\
	<div class=\"centered\">\
	<div class=\"jumbotron\">\
	<img src=\"http://www.caringbah-h.schools.nsw.edu.au/cmsresources/images/chs_crest_green_1355267211561_m.jpg\" alt=\"School Logo\" align=\"middle\">\
	<h1>I Wandered Lonely As A Cloud</h1>\
	<p>Two roads diverged in a yellow wood,<br>\
	And sorry I could not travel both<br>\
	And be one traveler, long I stood<br>\
	And looked down one as far as I could<br>\
	To where it bent in the undergrowth;<br>\
	<br>\
	Then took the other, as just as fair,<br>\
	And having perhaps the better claim,<br>\
	Because it was grassy and wanted wear;<br>\
	Though as for that the passing there<br>\
	Had worn them really about the same,<br>\
	<br>\
	And both that morning equally lay<br>\
	In leaves no step had trodden black.<br>\
	Oh, I kept the first for another day!<br>\
	Yet knowing how way leads on to way,<br>\
	I doubted if I should ever come back.<br>\
	<br>\
	I shall be telling this with a sigh<br>\
	Somewhere ages and ages hence:<br>\
	Two roads diverged in a wood, and I-<br>\
	I took the one less traveled by,<br>\
	And that has made all the difference.</p>\
	<span>- Robert Frost</span>\
	</div>\
	</div>\
	</body>\n"
	"</html>\n";

	// echo the http response to the console for debugging purposes
	printf ("VVVV about to send this via http VVVV\n");
	printf ("^^^^ end of message ^^^^\n");

	// send the http response to the web browser which requested it
	send (socket, message, strlen(message), 0);
}

// start the server listening on the specified port number
int makeServerSocket (int portNumber) {

	// create socket
	int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
	assert (serverSocket >= 0);
	// check there was no error in opening the socket

	// bind the socket to the listening port  (7191 in this case)
	struct sockaddr_in serverAddress;
	serverAddress.sin_family      = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port        = htons (portNumber);

	// tell the server to restart immediately after a previous shutdown
	// even if it looks like the socket is still in use
	// otherwise we might have to wait a little while before rerunning the
	// server once it has stopped
	const int optionValue = 1;
	setsockopt (serverSocket, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof (int));

	int bindSuccess = bind (serverSocket, (struct sockaddr*)&serverAddress, sizeof (serverAddress));

	assert (bindSuccess >= 0);
	// if this assert fails wait a short while to let the operating
	// system clear the port before trying again

	return serverSocket;
}

// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {

	// listen for a connection
	const int serverMaxBacklog = 10;
	listen (serverSocket, serverMaxBacklog);

	// accept the connection
	struct sockaddr_in clientAddress;
	socklen_t clientLen = sizeof (clientAddress);
	int connectionSocket = accept (serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
	assert (connectionSocket >= 0);
	// check for connection error

	return connectionSocket;
}

/*
 this code calls these external networking functions
 try to work out what they do from seeing how they are used,
 then google them for full details.

 recv
 close
 send
 socket
 setsockopt
 bind
 listen
 accept
 */
