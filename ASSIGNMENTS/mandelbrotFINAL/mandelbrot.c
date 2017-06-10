/*
 * mandelbrot.c
 * April 2017
 * Caringbah High School
 * Mirela Jarrod Stan
 * Displays Mandelbrot Set bitmap server
 */
 
 //INCOMPLETE - Just writing out the server outline, prints just a red 
 //512 x 512 bmp for now
 //Current Status: It'll compile and run javascript
 //Use m.sh to compile
 //TO RUN THE SERVER FROM CLOUD 9 USE http://mandelbrot-mdimeglio.c9users.io:8080/ 
 //If you're wondering about all the n's, write() returns the number of bytes
 //written and the compiler is super strict and says that the variable isn't
 //used so I 'used' it and then voided it.
 // - Mirela
 //Also if someone could clean up the identation and stuff thank you I'm sorry
 //it's so messy actually death

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>
#include "mandelbrot.h"
#include "pixelColor.h"

#define TRUE 1
#define FALSE 0

#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0
 
#define SIZE 512

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7191
#define NUMBER_OF_PAGES_TO_SERVE 1000

typedef struct _complex {
   double real;
   double imag;
} complex;

typedef struct _triordinate {
   double x;
   double y;
   int z;
   int valid;
} triordinate;

typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;

//The buffer for the image
static bits8 canvas[BYTES_PER_PIXEL*SIZE*SIZE];

//Triordinate function prototypes
triordinate extract (char *message);
double myAtoD (char *message);
long myAtoL (char *message);

//Escape function prototypes
complex sum (complex a, complex b);
complex product (complex a, complex b);
double modulusSquared(complex z);

//Server prototypes
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void serveBMP (int socket, double x, double y, int z);
void processRequest(int socket, char *request);

void writeBMPHeader (int socket);


//BASIC FLOW OF PROGRAM
//Get request from server
//Proccess that request in processRequest()
//Figures out if it's a short url or not
//If yes, runs the javascript as per activity
//If not, goes to extract
//Gets the coordinate
//Passes the coordinate into serveBMP()
//This is where most of the calculations will happen
//First it writes the header to the socket with writeBMPheader()
//ServeBMP, after doing calculations with escape steps and color and center,
//Passes it to setPixel()
//setPixel() will buffer the rgb into the canvas
//Then after that, the end of serveBMP() writes the whole canvas to the socket
//There's also a clear canvas, to make sure that if some pixels aren't written
//The old canvas isn't poking through the holes (Just an error thing)
//main() -> processRequest() -> extract() -> serveBMP() -> writeBMPheader
//                                                         Calculate from center complex coords for pixels
//                                                         escapeSteps() 
//                                                         pixelcolor stuff 
//                                                         -> setPixel()
//                                                         write canvas to socket 
//                                                         Done!
//Delete this after we're done hahaha

int main (int argc, char *argv[]) {
   int serverPort;
   char *c9port;
   printf ("************************************\n");
   printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
   printf ("Serving bmps since 2012\n");   
   
   c9port = getenv("PORT");
   if (c9port == NULL){
       serverPort = DEFAULT_PORT;
       printf ("Access this server at http://localhost:%d/\n", serverPort);
   }
   else {
       serverPort = atoi(c9port);
       printf ("Access this server at http://mandelbrot-mdimeglio.c9users.io:%d/\n", serverPort);
   }
   int serverSocket = makeServerSocket (serverPort);   

   printf ("************************************\n");
   
   char request[REQUEST_BUFFER_SIZE];
   
   int numberServed = 0;
   while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
      
      printf ("*** So far served %d pages ***\n", numberServed);
      
      int connectionSocket = waitForConnection (serverSocket);
      // wait for a request to be sent from a web browser, open a new
      // connection for this conversation
      
      // read the first line of the request sent by the browser  
      int bytesRead;
      bytesRead = read (connectionSocket, request, (sizeof request)-1);
      assert (bytesRead >= 0); 
      // were we able to read any data from the connection?
            
      // print entire request to the console 
      //printf (" *** Received http request ***\n %s\n", request);
      
      //send the browser a simple html page using http
      printf (" *** Sending http response ***\n");
      processRequest(connectionSocket, request);
      
      // close the connection after sending the page- keep aust beautiful
      close(connectionSocket);
      
      numberServed++;
   } 
   
   // close the server connection after we are done- keep aust beautiful
   printf ("** shutting down the server **\n");
   close (serverSocket);
   
   return EXIT_SUCCESS; 
}




//-------------------------------Server Functions

void processRequest(int socket, char *request) {
    char *message;
    char *p;
    char *q;
    triordinate center;
    int n;
    
    //Breaks up the request of the user into just the important part
    //Example of request: GET / blahblahlbah
    //Coordinate example of request: GET /xyz blahblahblah
    
    p = strstr(request, "GET");
    assert(p);
    p = p + 3;
    p = strstr(p, "/");
    q = strstr(p, " ");
    //Sets the space to be a null character, making a string
    *q = 0;
    
    //If there are no coordinates, run the javascript
    if (strcmp(p, "/") == 0) {
        message = "HTTP/1.0 200 Found\n"
                  "Content-Type: text/html\n"
                  "\n";
        printf ("about to send=> %s\n", message);
        n = write (socket, message, strlen (message));
        
        message = "<!DOCTYPE html>\r\n"
                "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>\r\n"
                "\r\n";
        n = write(socket, message, strlen(message));
        (void) n;
    }
    
    else {
        center = extract(p);
        if (center.valid) {
            serveBMP(socket, center.x, center.y, center.z);
        }
    }
}


void clearCanvas(void) {
    memset(canvas, 0, sizeof canvas);
}

void setPixel(int x, int y, int r, int g, int b){
    int index;
    if (x < SIZE && x >= 0 && y < SIZE && y >= 0) {
        index = (y * SIZE + x) * BYTES_PER_PIXEL;
        canvas[index] = (bits8) b;
        canvas[index + 1] = (bits8) g;
        canvas[index + 2] = (bits8) r;
    }
}

void serveBMP (int socket, double x, double y, int z) {
   char* message;
   int n;
   //The pixel coordinates, rather than the complex plane coordinates 
   int steps;
   
   int pixelx = 0;
   int pixely = 0;
   
   complex position;
   //
   double pixelDistance;
   pixelDistance = pow(2, -z);
   
   printf("x = %f y = %f z = %d\n", x, y, z);
   // first send the http response header
   
   // (if you write strings one after another like this on separate
   // lines the c compiler kindly joins them togther for you into
   // one long string)
    message = "HTTP/1.0 200 OK\r\n"
                "Content-Type: image/bmp\r\n"
                "\r\n";
    printf ("about to send=> %s\n", message);
    n = write (socket, message, strlen (message));
   
    // now send the BMP
   
    //Header
    writeBMPHeader(socket);
    
    //Finds the position of the bottom left pixel
    position.real = x - ((SIZE / 2) * pixelDistance) + (pixelDistance / 2);
    position.imag = y - ((SIZE / 2) * pixelDistance) + (pixelDistance / 2);
    
    //Loops through the whole canvas
    while (pixely < SIZE) {
        pixelx = 0;
            while (pixelx < SIZE) {
                steps = escapeSteps(position.real, position.imag);
                setPixel(pixelx, pixely, stepsToRed(steps), stepsToGreen(steps), stepsToBlue(steps));
                pixelx++;
                position.real += pixelDistance;
            }
        position.imag += pixelDistance;
        //Reset position's x coordinate
        position.real = x - ((SIZE / 2) * pixelDistance) + (pixelDistance / 2); 
        pixely++;
    }
    n = write (socket, canvas, sizeof(canvas));
    //printf("Finished sending bmp\n");
    (void) n;
}

// start the server listening on the specified port number
int makeServerSocket (int portNumber) { 
   
   // create socket
   int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
   assert (serverSocket >= 0);   
   // error opening socket
   
   // bind socket to listening port
   struct sockaddr_in serverAddress;
   memset ((char *) &serverAddress, 0,sizeof (serverAddress));
   
   serverAddress.sin_family      = AF_INET;
   serverAddress.sin_addr.s_addr = INADDR_ANY;
   serverAddress.sin_port        = htons (portNumber);
   
   // let the server start immediately after a previous shutdown
   int optionValue = 1;
   setsockopt (
      serverSocket,
      SOL_SOCKET,
      SO_REUSEADDR,
      &optionValue, 
      sizeof(int)
   );

   int bindSuccess = 
      bind (
         serverSocket, 
         (struct sockaddr *) &serverAddress,
         sizeof (serverAddress)
      );
   
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
   int connectionSocket = 
      accept (
         serverSocket, 
         (struct sockaddr *) &clientAddress, 
         &clientLen
      );
   
   assert (connectionSocket >= 0);
   // error on accept
   
   return (connectionSocket);
}

//------------------------------------BMP functions

void writeBMPHeader (int socket) {
    int n;
   assert(sizeof (bits8) == 1);
   assert(sizeof (bits16) == 2);
   assert(sizeof (bits32) == 4);
 
   bits16 magicNumber = MAGIC_NUMBER;
   n = write (socket, &magicNumber, sizeof magicNumber);
 
   bits32 fileSize = OFFSET + (SIZE * SIZE * BYTES_PER_PIXEL);
   n = write (socket, &fileSize, sizeof fileSize);
 
   bits32 reserved = 0;
   n = write (socket, &reserved, sizeof reserved);
 
   bits32 offset = OFFSET;
   n = write (socket, &offset, sizeof offset);
 
   bits32 dibHeaderSize = DIB_HEADER_SIZE;
   n = write (socket, &dibHeaderSize, sizeof dibHeaderSize);
 
   bits32 width = SIZE;
   n = write (socket, &width, sizeof width);
 
   bits32 height = SIZE;
   n = write (socket, &height, sizeof height);
 
   bits16 planes = NUMBER_PLANES;
   n = write (socket, &planes, sizeof planes);
 
   bits16 bitsPerPixel = BITS_PER_PIXEL;
   n = write (socket, &bitsPerPixel, sizeof bitsPerPixel);
 
   bits32 compression = NO_COMPRESSION;
   n = write (socket, &compression, sizeof compression);
 
   bits32 imageSize = (SIZE * SIZE * BYTES_PER_PIXEL);
   n = write (socket, &imageSize, sizeof imageSize);
 
   bits32 hResolution = PIX_PER_METRE;
   n = write (socket, &hResolution, sizeof hResolution);
 
   bits32 vResolution = PIX_PER_METRE;
   n = write (socket, &vResolution, sizeof vResolution);
 
   bits32 numColors = NUM_COLORS;
   n = write (socket, &numColors, sizeof numColors);
 
   bits32 importantColors = NUM_COLORS;
   n = write (socket, &importantColors, sizeof importantColors);
   
   (void) n;
}



//----------------------------------------Escape functions

int escapeSteps (double x, double y) {
    int numberOfSteps = 0;
    complex z = { 0, 0 };
    complex c = { x, y };
    
    // loop to find when z escapes
    while (numberOfSteps < 256 && modulusSquared(z) < 4) {
        z = sum (product (z, z), c);
        ++numberOfSteps;
    }
    
    return numberOfSteps;
}

double modulusSquared(complex z) {
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



//----------------------------------------------------Parsing functions

triordinate extract (char *message) {
   triordinate result;
   
   char *messageCopy = malloc (strlen (message));
   strcpy (messageCopy, message); // copy for string manipulation
   
   // delimiters
   const char d[5] = "_xy"; // separates x and y values from message
   const char d2[5] = "z."; // separates z value from message
   
   char *token, *tokenx, *tokeny, *tokenz; // storage for each section of string
   
   char x[30];
   char y[30];
   char z[30];
   
   token = strtok (messageCopy, d); // assign token to message
   
   tokenx = strtok (NULL, d); // token equates to x value
   tokeny = strtok (NULL, d); // token equates to y value
   tokenz = strtok (NULL, d2); // token equates to z value
   
   //Testing if we got a valid url/coordinate
   if (token != NULL && tokenx != NULL && tokeny != NULL && tokenz != NULL) {
       result.valid = TRUE;
       
       strcpy (x, tokenx);
        strcpy (y, tokeny);
      strcpy (z, tokenz);        
       
       result.x = myAtoD (x);
        result.y = myAtoD (y);
        result.z = myAtoL (z);
   }
   else {
       result.valid = FALSE;
       result.x = 0;
       result.y = 0;
       result.z = 0;
   }

   return result;
}

double myAtoD (char *message) {
   int decimalPlaces = 0;
   int pastDecimal = FALSE;
   int isNegative = FALSE;
   double result = 0;
   int i = 0;
   
   // checks if number is negative
   if (message[i] == '-') {
      isNegative = TRUE;
      ++i;
   }
   
   while (message[i]) {
      if (pastDecimal) {
         ++decimalPlaces;
      }
      if (message[i] == '.') {
         pastDecimal = TRUE;
      } else {
         result *= 10;
         result += message[i] - '0'; // convert ASCII to decimal value
      }
      ++i;
   }
   
   i = 0;
   while (i < decimalPlaces) {
      result /= 10;
      ++i;
   }

   if (isNegative) {
      result *= -1;
   }
   
   return result;
}

long myAtoL (char *message) {
   int isNegative = FALSE;
   int result = 0;
   int i = 0;
   
   if (message[i] == '-') {
      isNegative = TRUE;
      ++i;
   }
   
   while (message[i]) {
      result *= 10;
      result += message[i] - '0'; // convert ASCII to decimal value
      ++i;
   }
   
   if (isNegative) {
      result *= -1;
   }
   
   return result;
}


