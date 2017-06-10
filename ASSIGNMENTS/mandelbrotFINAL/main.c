/* 
 * main.c
 * Jarrod Li
 * 12 April 2017
 * prints the mandelbrot fractal set 
 * in .bmp, serves the image to a web browser
 * compiling with GCC:
 *          gcc main.c -o main -lws2_32
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
//#include "pixelcolour.h"
//#include "mandelbrot.h"

// MB Defintions
#define TRUE 1
#define FALSE 0
#define MAX 256
#define HEIGHT 512
#define WIDTH 512
#define ZOOM 5
#define BYTES_PER_PIXEL 3
// Server Definitions
#define SIMPLE_SERVER_VERSION 2.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7191
// after serving this many pages the server will halt
#define NUMBER_OF_PAGES_TO_SERVE 10

typedef struct _colour {
    int blue;
    int green; 
    int red;
} colour;

typedef struct _complex {
    double real;
    double imag;
} complex;

// Server Function Prototypes
void processRequest(int socket, char *request);
void serveBMP (int socket);
void writeBMPHeader (int socket);
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
// MB Function Prototypes
void generateBMP (unsigned char bmpData[],
                    double centreX, double centreY, int zoom);
int escapeSteps (double x, double y);
int inSet (double x, double y);
double square (complex z);
complex sum (complex a, complex b);
complex product (complex a, complex b);
double power (int base, int exponent);
// External .h Prototypes
int escapeSteps (double x, double y);
unsigned char stepsToRed (int steps);
unsigned char stepsToBlue (int steps);
unsigned char stepsToGreen (int steps);

/* > ------------------- HOW THIS WILL WORKS ------------------- <
 *
 *      1. starts a windows server using winsock2
 *      2. calls processrequest() 
 *              a. writes a BMP header
 *              b. writes the body through calling
 *                 flag()
 *      3. flag() writes a colour value dependant on pixelcolor.c
 *         to an array 
 *      4. calls inset() which determines whether a point is 
 *         in the mandelbrot set
 *      5. calls escapesteps() which determines how many steps a point
 *         takes to escape 
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
        serveBMP (connectionSocket);
 
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

void serveBMP (int socket) {
    int xcentre = 1;
    int ycentre = 1;
    char* message;
   
    // first send the http response header
   
    // (if you write stings one after another like this on separate
    // lines the c compiler kindly joins them togther for you into
    // one long string)
    message = "HTTP/1.0 200 OK\r\n"
                "Content-Type: image/bmp\r\n"
                "\r\n";
    printf ("about to send=> %s\n", message);
    send (socket, message, strlen (message), 0);
   
    // bmp header - 54 BYTES
    unsigned char bmpHeader[] = {
        0x42, 0x4D, 0x36, 0x00, 0x0C, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
        0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x13, 0x0B,
        0x00, 0x00, 0x13, 0x0B, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
    };

    // write the header to the socket
    send (socket, bmpHeader, strlen(bmpHeader), 0);
    
    // write the body to the socket
    int size = HEIGHT * WIDTH * BYTES_PER_PIXEL;
    unsigned char bmpData[size];
    
    generateBMP(bmpData, xcentre, ycentre, ZOOM);
    send (socket, bmpData, sizeof(bmpData), 0);
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

// ------------------- BMP FUNCTIONS -------------------

void generateBMP(unsigned char bmpData[],
                         double centreX, double centreY, int zoom) {
    int drawingX;
    int drawingY;

    // The index of the desired row
    int bitmapRow;
    // The index of the desired column
    int bitmapColumn;

    double scaledX, scaledY;
    double scale;

    int iterations;

    scale = 1 / power(2, zoom);

    drawingY = 0;
    while (drawingY < BITMAP_HEIGHT) {
        drawingX = 0;
        while (drawingX < BITMAP_WIDTH) {
            // centering
            scaledX = centreX -(BITMAP_WIDTH / 2) * scale;
            scaledY = centreY -(BITMAP_HEIGHT / 2) * scale;

            // calculate current point
            scaledX += drawingX * scale;
            scaledY += drawingY * scale;

            bitmapRow = drawingY *
                            (BITMAP_WIDTH * BITMAP_BYTES_PER_PIXEL);
            bitmapColumn = drawingX * BITMAP_BYTES_PER_PIXEL;
            iterations = escapeSteps(scaledX, scaledY);
            bmpData[bitmapRow + bitmapColumn] = stepsToBlue(iterations);
            bmpData[bitmapRow + bitmapColumn + 1] = stepsToGreen(iterations);;
            bmpData[bitmapRow + bitmapColumn + 2] = stepsToRed(iterations);;

            drawingX++;
        }
        drawingY++;
    }
}

/*void generateBMP(unsigned char bmpData[],
                         double centreX, double centreY, int zoom) {
    int currentCharacterPosition = 0;
    int xpoint, ypoint;
    double sxpoint, sypoint, scale;

    int distance = 1 / power(2, ZOOM);

    // lowest y coordinate
    sypoint = ypoint - HEIGHT / 2 * distance + distance / 2;
    while (ypoint < HEIGHT) {
        // left most x coordinate
        sxpoint = xpoint - WIDTH / 2 * distance + distance / 2;
        while (xpoint < WIDTH) {
            int steps = escapeSteps(xpoint, ypoint);
            // determine colour
            colour pixel;
            pixel.red = stepsToRed(steps);
            pixel.blue = stepsToBlue(steps);
            pixel.green = stepsToGreen(steps);
            int offset = BYTES_PER_PIXEL * (ypoint * HEIGHT + xpoint);
            // write colours to data array
            bmpData[offset] = pixel.blue;
            bmpData[offset + 1] = pixel.green;
            bmpData[offset + 2] = pixel.red;

            xpoint += distance;
            ++xpoint;
        }
        ypoint += distance;
        ++ypoint;
    }
}*/

// ------------------- HEADER FUNCTIONS -------------------
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

unsigned char stepsToRed (int steps) {

    int valueRed;
    if (steps < 20) {
        valueRed = 0x00;
    } else {
        valueRed = 0xcc;
    }
    if (steps % 3 == 0 ) {
        valueRed = 0xff;
    }
    
    return valueRed;
}
unsigned char stepsToGreen (int steps) {

    int valueGreen;
    if (steps > 200 && steps < 256 ) {
        valueGreen = 0xFF * steps / MAX * 2;
    } else if (steps >= MAX) {
        valueGreen = 0x55;
    } else if (steps < 100) {
        valueGreen = 0xFF * steps / 30;
    } else {
        valueGreen = 0xff;
    }
    if (steps % 3 == 0 ) {
        valueGreen = 0xff * 23 * steps / MAX;
    }
    
    return valueGreen;      
}

unsigned char stepsToBlue (int steps) {

    int valueBlue;
    if (steps > 200 && steps < 256 ) {
        valueBlue = 0xFF * steps / MAX * 2;
    } else if (steps >= MAX) {
        valueBlue = 0x22;
    } else {
        valueBlue = 0xaa;
    }
    if (steps % 3 == 0 ) {
        valueBlue = 0x00;
    }
    
    return valueBlue;
}
