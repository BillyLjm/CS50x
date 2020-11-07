/*
 * @file: vigenere.c
 * @author: Billy.Ljm
 * @date: 18 June 2015
 * @brief: Vigenere cipher program
 *
 * Alphabetical key must be given as argument
 * After which, enter the plain text
 * e.g.
 * 	>> ./vigenere foo
 * 	>> the quick brown fox
 *  >> yvs einqy pftkb tcc
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, char** argv){
	string keyphrase; // key phrase passed in
	int keylen; // length of key phrase
	//int[] key  // key phrase converted to numbers
	string plaintxt; // plain text input

	// check if key was passed in
	if(argc != 2){
		printf("Please provide a single alphabetical key\n");
		return 1;
	}

	// check if key is alphabetical
	keyphrase = argv[1];
	keylen = strlen(keyphrase);
	for(int i = 0; i < keylen; i++){
		if(!isalpha(keyphrase[i])){
			printf("Please provide a single alphabetical key\n");
			return 1;
		}
	}

	// get numeric version of key
	int key[keylen];
	for(int i = 0; i < keylen; i++){
		if(islower(keyphrase[i]))
			key[i] = ((int)keyphrase[i]) - 97;
		else
			key[i] = ((int)keyphrase[i]) - 65;
	}

	// get plain text
	plaintxt = GetString();

	// Vigenere cipher
	for(int i = 0, keycount = 0, len = strlen(plaintxt); i < len; i++){
		if(islower(plaintxt[i])){
			printf("%c", (char)(((int)plaintxt[i] - 97 + key[keycount % keylen]) % 26 + 97));
			keycount++;
		}
		else if(isupper(plaintxt[i])){
			printf("%c", (char)(((int)plaintxt[i] - 65 + key[keycount % keylen]) % 26 + 65));
			keycount++;
		}
		else
			printf("%c", plaintxt[i]);
	}

	// end
	printf("\n");
	free(plaintxt);
	return 0;
}
