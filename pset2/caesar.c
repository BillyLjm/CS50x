/*
 * @file: caesar.c
 * @author: Billy.Ljm
 * @date: 18 June 2015
 * @brief: Caesar cipher program
 *
 * Non-negative integer key must be given as argument
 * After which, enter the plain text
 * e.g.
 * 	>> ./caesar 6
 * 	>> the quick brown fox
 *  >> znk waoiq hxuct lud
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, char** argv){
	int key; // numerical key
	string plaintxt; // plain text input

	// check if key was passed in
	if(argc != 2 || !isdigit(*argv[1])){
		printf("Please provide a single non-negative integer key\n");
		return 1;
	}
	
	// check if key was numerical
	for(int i = 0, len = strlen(argv[1]); i < len; i++){
	    if(!isdigit(argv[1][i])){
	        printf("Please provide a single non-negative integer key\n");
		    return 1;
	    }
	}
	key = atoi(argv[1]);

	// get plaintext
	plaintxt = GetString();

	// Caesar cipher
	for(int i = 0, len = strlen(plaintxt); i < len; i++){
		if(islower(plaintxt[i]))
			printf("%c", (char)(((int)plaintxt[i] - 97 + key) % 26 + 97));
		else if(isupper(plaintxt[i]))
			printf("%c", (char)(((int)plaintxt[i] - 65 + key) % 26 + 65));
		else
			printf("%c", plaintxt[i]);
	}

	// end
	printf("\n");
	free(plaintxt);
	return 0;
}
