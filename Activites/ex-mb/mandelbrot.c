/*
 * Dominic He and David Vo
 * April 2014
 * Runs a server that sends portions of the Mandelbrot set
 *
 * Uses code created by Tim Lambert on 02/04/12 to serve a BMP.
 * Containing code created by Richard Buckland on 28/01/11.
 * Copyright 2012 Licensed under Creative Commons BY-NC-SA 3.0
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


#define PI 3.14159265
#define BMP_WIDTH 512
#define BMP_HEIGHT 512
#define BYTES_PER_PIXEL 3
#define MAX_SQUARE_DIST 4
#define MAX_STEPS 256

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 15432
#define NUMBER_OF_PAGES_TO_SERVE 2048

typedef unsigned char byte;
typedef struct _color {
    byte red;
    byte green;
    byte blue;
} color;
typedef struct _complex {
    double real;
    double imag;
} complex;

unsigned char stepsToRed(int steps);
unsigned char stepsToBlue(int steps);
unsigned char stepsToGreen(int steps);
int escapeSteps(double x, double y);

static int waitForConnection(int serverSocket);
static int makeServerSocket(int portno);
static void serveIndex(int socket);
static void serveBMP(
    int socket,
    double xCenter, double yCenter,
    int zoom
);
static double modulusSquared(complex z);
static complex square(complex z);
static complex add(complex a, complex b);
double power(int base, int exponent);

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
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
        printf("*** So far served %d pages ***\n", numberServed);
        char address[256];
        int connectionSocket = waitForConnection(serverSocket);
        double x, y;
        int zoom;

        // read the first line of the request sent by the browser
        int bytesRead = recv (connectionSocket, request, sizeof(request) - 1, 0);
        assert (bytesRead >= 0);

        // XXX this entire code assumes a GET request
        // print request address to the console 
        printf(" *** Received http request ***\n");
        sscanf(request, "GET %s HTTP/", address);
        printf("address: %s\n", address);

        // check whether the client requested the index
        if (strcmp(address, "/") == 0) {
            // client requested index, serve the index HTML
            printf(" *** Sending index HTML ***\n");
            serveIndex(connectionSocket);
        } else {
            // client is requesting something else
            // assume the client wants a BMP tile
            sscanf(address, "/tile_x%lf_y%lf_z%d.bmp", &x, &y, &zoom);
            printf("x = %lf\n", x);
            printf("y = %lf\n", y);
            printf("z = %d\n", zoom);

            // serve the requested BMP tile
            printf(" *** Sending BMP ***\n");
            serveBMP(connectionSocket, x, y, zoom);
        }

        // close the connection after sending the page
        close(connectionSocket);

        numberServed++;
    }
 
    // close the server connection after we are done- keep aust beautiful
    puts("** shutting down the server **");
    close (serverSocket);
 
#ifdef _WIN32
    WSACleanup();
#endif
    return EXIT_SUCCESS;
}

static void serveIndex(int socket) {
    // the entire HTTP response
    char *response =
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: text/html, charset=utf-8\r\n"
        "\r\n"
        "<!DOCTYPE html>"
        "<html>"
        "<head>"
        "<script src=\"//almondbread.cse.unsw.edu.au/tiles.js\"></script>"
        "</head>"
        "<body></body>"
        "</html>";

    send(socket, response, strlen(response), 0);
}

static void serveBMP(
    int socket,
    double xCenter, double yCenter,
    int zoom
) {
    // HTTP response headers
    char *headers =
        "HTTP/1.0 200 OK\r\n"
        "Content-Type: image/bmp\r\n"
        "\r\n";

    // the BMP header (first 54 bytes)
    byte bmpHeader[] = {
        0x42, 0x4d, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
        0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x13, 0x0b,
        0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // BMP color table with 512 x 512 pixels, 3 bytes per pixel
    byte bmpColorTable[BMP_WIDTH * BMP_HEIGHT * BYTES_PER_PIXEL];

    double pixelDist = power(2, -zoom);
    int xPixel = 0, yPixel = 0;
    double xCoord, yCoord;
    int steps;

    // Start with yCoord at lowest coordinate
    yCoord = yCenter - BMP_HEIGHT / 2 * pixelDist + pixelDist / 2;
    while (yPixel < BMP_HEIGHT) {
        xPixel = 0;
        // Start with xCoord at leftmost coordinate
        xCoord = xCenter - BMP_WIDTH / 2 * pixelDist + pixelDist / 2;

        while (xPixel < BMP_WIDTH) {
            steps = escapeSteps(xCoord, yCoord);
            color pixel;
            pixel.red = stepsToRed(steps);
            pixel.green = stepsToGreen(steps);
            pixel.blue = stepsToBlue(steps);

            // send bytes to BMP color table
            int bmpPxOffset =
                BYTES_PER_PIXEL * (yPixel * BMP_HEIGHT + xPixel);

            bmpColorTable[bmpPxOffset    ] = pixel.blue;
            bmpColorTable[bmpPxOffset + 1] = pixel.green;
            bmpColorTable[bmpPxOffset + 2] = pixel.red;

            // Move x to the right
            xCoord += pixelDist;
            xPixel++;
        }

        // Move y up
        yCoord += pixelDist;
        yPixel++;
    }

    // Send over bitmap
    send(socket, headers, strlen(headers), 0);
    send(socket, bmpHeader, sizeof(bmpHeader), 0);
    send(socket, bmpColorTable, sizeof(bmpColorTable), 0);
}

// start the server listening on the specified port number
static int makeServerSocket(int portNumber) {
 
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

static int waitForConnection(int serverSocket) {
    // listen for a connection
    const int serverMaxBacklog = 10;
    listen(serverSocket, serverMaxBacklog);

    // accept the connection
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof clientAddress;
    int connectionSocket = accept(
        serverSocket,
        (struct sockaddr *) &clientAddress,
        &clientLen
    );

    // check for error on accept
    assert(connectionSocket >= 0);

    return connectionSocket;
}

int escapeSteps(double x, double y) {
    complex coord = {x, y};
    complex z = {0, 0};
    int step = 0;

    while (modulusSquared(z) < MAX_SQUARE_DIST && step < MAX_STEPS) {
        z = add(square(z), coord);
        step++;
    }

    return step;
}

static double modulusSquared(complex z) {
    double x = z.real;
    double y = z.imag;

    return x * x + y * y;
}

static complex square(complex z) {
    complex result;
    double x = z.real;
    double y = z.imag;

    result.real = x * x - y * y;
    result.imag = 2 * x * y;

    return result;
}

static complex add(complex a, complex b) {
    complex result;

    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;

    return result;
}


double power(int base, int exponent) {
    int i = 0;
    double result = 1;
    while (i < exponent) {
        result *= base;
        ++i;
    }
    return result;
}
