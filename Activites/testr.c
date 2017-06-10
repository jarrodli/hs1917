#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *reverse(char *message);
int main (int argc, char *argv[]){

	char message[] = "hello";
	reverse(message);
	printf("%s\n", message);

}

char *reverse(char *message){
	char input = *message;
	int length = strlen(input);
	int last_pos = length-1;
	for(int i = 0; i < length/2; i++)
	{
	    char tmp = input[i];
	    input[i] = input[last_pos - i];
	    input[last_pos - i] = tmp;
	}

	
	return input;
}