//
//  main.c
//  memory
//
//  Created by Richard Buckland on 20/11/12.
//

#include <stdio.h>
#include <stdlib.h>

long add (int x, int y);

int main(int argc, const char * argv[]) {

   int x;
   int y;
   long total;

   x = 40;
   y = 2;

   total = add (x, y);

   printf("the sum of %d and %d is %ld\n", x, y, total);

   char c ='a';

   unsigned long ul       = 0;
   unsigned int ui        = 1;
   unsigned long long ull = 2;
   unsigned short us      = 3;

   signed long sl       = 4;
   signed int si        = 5;
   signed long long sll = 6;
   signed short ss      = 7;

   long l       = 8;
   int i        = 9;
   long long ll = 10;
   short s      = 11;

   float f = 3.1;
   double d = 3.14;

   // add them all together just to make use of them so the compiler
   // doesn't grumble that they are unused in the program

   double grandTotal;
   grandTotal =  c +
                 ul + ui + ull + us +
                 sl + si + sll + ss +
                  l +  i +  ll +  s +
                  f + d;

   printf ("all these things added together make %f\n", grandTotal);

   // size and location of types

   printf("A char is                %d bytes\n", sizeof(c));
   printf("Address of 'c' is %p\n", &c);
   printf("A long is                %d bytes\n", sizeof(l));
   printf("Address of 'l' is %p\n", &l);
   printf("An integer is            %d bytes\n", sizeof(i));
   printf("Address of 'i' is %p\n", &i);
   printf("A long long is           %d bytes\n", sizeof(ll));
   printf("Address of 'll' is %p\n", &ll);
   printf("A short is               %d bytes\n", sizeof(s));
   printf("Address of 's' is %p\n", &s);
   printf("A float is               %d bytes\n", sizeof(f));
   printf("Address of 'f' is %p\n", &f);
   printf("A double is              %d bytes\n", sizeof(d));
   printf("Address of 'd' is %p\n", &d);
   printf("An unsigned long is      %d bytes\n", sizeof(ul));
   printf("Address of 'ul' is %p\n", &ul);
   printf("An unsigned integer is   %d bytes\n", sizeof(ui));
   printf("Address of 'ui' is %p\n", &ui);
   printf("An unsigned long long is %d bytes\n", sizeof (ull));
   printf("Address of 'ull' is %p\n", &ull);
   printf("An unsigned short is     %d bytes\n", sizeof(us));
   printf("Address of 'us' is %p\n", &us);
   printf("A signed long is         %d bytes\n", sizeof(sl));
   printf("Address of 'sl' is %p\n", &sl);
   printf("A signed integer is      %d bytes\n", sizeof(si));
   printf("Address of 'si' is %p\n", &si);
   printf("A signed long long is    %d bytes\n", sizeof(sll));
   printf("Address of 'sll' is %p\n", &sll);
   printf("A signed short is        %d bytes\n", sizeof(ss));
   printf("Address of 'ss' is %p\n", &ss);

   // check what happens when variables overflow and underflow

   while (c > 0) {

       c++;

       if (c < 0) {
           printf("%d\n", c);
       }
   }

   while (c < 0) {

       c--;

       if (c > 0) {
           printf("%d\n", c);
       }
   }

   return EXIT_SUCCESS;
}

long add (int x, int y) {
   long answer;
   answer = x + y;

   return answer;
}
