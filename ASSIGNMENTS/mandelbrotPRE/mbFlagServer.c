
/* 
 * mbFlagServer.c
 * Jarrod Li
 * 12 April 2017
 * prints the mandelbrotset with '*'
 * serves the image to a web browser
 * compiling with GCC:
 *		gcc -Wall -Werror -O1 -o mbflagserver mbflagserver.c -lws2_32
 */

#include <stdio.h>
#include <stdlib.h>
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

// MB Defintions
#define TRUE 1
#define FALSE 0
#define MAX 256
#define HEIGHT 100
#define WIDTH 125
#define ZOOM 5

// Server Definitions
#define SIMPLE_SERVER_VERSION 2.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7191
// after serving this many pages the server will halt
#define NUMBER_OF_PAGES_TO_SERVE 10 

typedef struct _complex {
	double real;
	double imag;
} complex;

// Server Function Prototypes
void processRequest(int socket, char *request);
void writeBMPHeader (int socket);
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
// MB Function Prototypes
void flag (char *dest);
int escapeSteps (double x, double y);
int inSet (double x, double y);
double square (complex z);
complex sum (complex a, complex b);
complex product (complex a, complex b);
double power (int base, int exponent);

/* > -------------------------- HOW THIS WORKS -------------------------- <
 *
 * 		1. starts a windows server using winsock2
 * 		2. calls processrequest() 
 *				a. writes the html header
 *				b. writes the body through calling
 *		  		   flag()
 *				c. writes the html footer
 * 		3. flag() writes either a * or a ' ' 
 * 	  	   to an array 
 * 		4. calls inset() which determines whether a point is 
 *    	   in the mandelbrot set
 * 		5. calls escapesteps() which determines how many steps a point
 *    	   takes to escape 
 */


int main (int argc, char* argv[]) {

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup((2 << 8) + 2, &wsaData);
#endif

	puts("************************************");
    printf("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
    puts("Serving poetry since 2011");
 
    int serverSocket = makeServerSocket(DEFAULT_PORT);
    printf("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    puts("************************************");
 
    char request[REQUEST_BUFFER_SIZE];
    int numberServed = 0;
    while ( numberServed < NUMBER_OF_PAGES_TO_SERVE) {
        printf("*** So far served %d pages ***\n", numberServed);
 
        int connectionSocket = waitForConnection(serverSocket);
        // wait for a request to be sent from a web browser, open a new
        // connection for this conversation
 
        // read the first line of the request sent by the browser
        int bytesRead = recv (connectionSocket, request, sizeof(request) - 1, 0);
        assert (bytesRead >= 0);
        // were we able to read any data from the connection?
 
        // print entire request to the console
        printf (" *** Received http request ***\n %s\n", request);
 
        //send the browser a simple html page using http
        puts (" *** Sending http response ***");
        processRequest (connectionSocket, request);
 
        // close the connection after sending the page- keep aust beautiful
        close (connectionSocket);
        ++numberServed;
    }
 
    // close the server connection after we are done- keep aust beautiful
    puts("** shutting down the server **");
    close (serverSocket);
 
#ifdef _WIN32
    WSACleanup();
#endif
 
    return EXIT_SUCCESS;
}
 
// ------------------- SERVER FUNCTIONS -------------------

void processRequest(int socket, char *request) {

    const char* htmlBefore =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<!DOCTYPE html>\n"
        "<html>\n"
        " <title>Current Short Message</title>\n"
        " <body><pre>";

   	/* breakdown of the maths here ->
	 * WIDTH x 2 because we use two '*' for 
	 * because of spacing issues
	 * we add one to account for new lines
	 * x HEIGHT and add one for terminating /0
	 */
        
    char mandelbrotDrawing[((WIDTH * 2 + 1) * HEIGHT) + 1];
    flag(mandelbrotDrawing);

    const char* htmlAfter =     
        "</pre></body>\n"
        "</html>\n";

    printf("sending the header");
    send (socket, htmlBefore, strlen(htmlBefore), 0);
    printf("sending the drawing");
    send (socket, mandelbrotDrawing, strlen(mandelbrotDrawing), 0);
    printf("sending the footer");
    send (socket, htmlAfter, strlen(htmlAfter), 0);
}

// start the server listening on the specified port number
int makeServerSocket(int portNumber) {
 
    // create socket
    int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    assert (serverSocket >= 0);
    // error opening socket
 
    // bind socket to listening port
    struct sockaddr_in serverAddress;
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons (portNumber);
 
    // let the server start immediately after a previous shutdown
    int optionValue = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char *)&optionValue, sizeof(int));
 
    int bindSuccess = bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
 
    assert (bindSuccess >= 0);
    // if this assert fails wait a short while to let the operating
    // system clear the port before trying again
 
    return serverSocket;
}
 
// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection(int serverSocket) {
 
    // listen for a connection
    const int serverMaxBacklog = 10;
    listen(serverSocket, serverMaxBacklog);
 
    // accept the connection
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof(clientAddress);
    int connectionSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    assert(connectionSocket >= 0);
    // error on accept
 
    return connectionSocket;
}

// ------------------- FLAG FUNCTIONS -------------------

void flag (char *dest) {
	int currentCharacterPosition = 0;
	int xpoint, ypoint;
	double sxpoint, sypoint, scale;

	scale = 1 / power(2, ZOOM);
	ypoint = 0;
	while (ypoint < HEIGHT) {
		xpoint = 0;
		while (xpoint < WIDTH) {
			// center
			sxpoint = -( WIDTH / 2 ) * scale;
			sypoint = -( WIDTH / 2 ) * scale;

			// current point
			sxpoint += xpoint * scale;
			sypoint += ypoint * scale;
			if (inSet(sxpoint, sypoint) == TRUE) {
				dest[currentCharacterPosition++] = '*';
                dest[currentCharacterPosition++] = '*';
			} else {
				dest[currentCharacterPosition++] = ' ';
                dest[currentCharacterPosition++] = ' ';
			}
			++xpoint;
		}
		dest[currentCharacterPosition++] = '\n';
		++ypoint;
	}
	dest[currentCharacterPosition++] = '\0';
}

// determines whether a point is in the mandelbrot set
int inSet (double x, double y) {
	int result;

	if (escapeSteps(x, y) == MAX) {
		result = TRUE;
	} else {
		result = FALSE;
	}

	return result;
}

// ------------------- ESCAPE FUNCTIONS -------------------

// determines how many steps until the point escapes the
// mandelbrot set
int escapeSteps (double x, double y) {
    int steps = 0;
    complex z = { 0, 0 };
    complex c = { x, y };
    
    // loop to find when z escapes
    while (steps < MAX && square(z) < 4) {
        z = sum (product (z, z), c);
        ++steps;
    }
    
    return steps;
}

double square (complex z) {
    return z.real * z.real + z.imag * z.imag;
}

// adds two complex numbers
complex sum (complex a, complex b) {
    return (complex) {
        a.real + b.real,
        a.imag + b.imag
    };
}

// multiplys two complex numbers
complex product (complex a, complex b) {
    return (complex) {
        a.real * b.real - a.imag * b.imag,
        a.real * b.imag + a.imag * b.real
    };
}
double power (int base, int exponent) {
	int i = 0;
	double result = 1;
	while (i < exponent) {
		result *= base;
		++i;
	}
	return result;
}

