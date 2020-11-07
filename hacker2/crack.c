/**
 * @file: crack.c
 * @author: Billy.Ljm
 * @date: 18 June 2015
 * @brief: Program that cracks DES encryption from `crypt.h`
 *
 * Enter the encrypted password as an argument &
 * the crack password will be printed out
 * e.g.
 * 	>> ./crack 50yoN9fp966dU
 * 	>> crimson
 */

#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>

const int MIN_CHAR = 32; // min decimal equivalent of each char to brute force search
const int MAX_CHAR = 127; // max decimal equivalent of each char to brute force search

int dictAtk (char plainPass[9], char* cryptPass, char* salt, char* fileName){
/**
 * @brief: dictionary attack for DES encryption
 *
 * @var plainPass: to save null-terminated plain-text password if found
 * @var cryptpass: encrypted password
 * @var salt: DES salt
 * @var fileName: dictionary file name
 */
	FILE* dict;
	char word[20]; // to extract words from dict

	// open dictionary
	dict = fopen(fileName, "r");
	if(dict == NULL){
		printf("Error opening dictionary at %s\n", fileName);
		return 1;
	}

	// try each word
	while(fgets(word, sizeof(word), dict)){
		// change word to string
		for(int i = 0; i < sizeof(word); i++){
			if(word[i] == '\n')
				word[i] = '\0';
		}

		// if password found, copy & return true
		if(strcmp(crypt(word, salt), cryptPass) == 0){
			strncpy(plainPass, word, 8);
			plainPass[8] = '\0';
			fclose(dict);
			return 1;
		}
	}

	// password not found, return false
	fclose(dict);
	return 0;
}


int bruteRecur(char plainPass[9], char* cryptPass, char* salt, char try[9], int passLen, int pos){
/**
 * @brief: Recursive function for `bruteAtk`
 *
 * @var plainPass: to save null-terminated plain-text password if found
 * @var cryptpass: encrypted password
 * @var salt: DES salt
 * @var try: password guess
 * @var passLen: length of password to try
 * @var pos: position in `try` currently being tried (one-based)
 */
 	// trim try to appropriate length
 	try[passLen] = '\0';

 	// recursively fill up guess &
 	// if password found, return early
	if(pos < passLen){
		for(int i  = MIN_CHAR; i < MAX_CHAR; i++){
			try[pos - 1] = (int)i;
			if(bruteRecur(plainPass, cryptPass, salt, try, passLen, pos + 1))
				return 1;
		}
	}

	// if at end
	else{
		for(int i  = MIN_CHAR; i < MAX_CHAR; i++){
			// complete guess
			try[pos - 1] = (int)i;
			//printf("%s\n", try);
			// check if guess is correct
			if(strcmp(crypt(try, salt), cryptPass) == 0){
				strncpy(plainPass, try, 8);
				plainPass[8] = '\0';
				return 1;
			}
		}
	}

	// can't decrypt password for this pos, return false
	return 0;
}


int bruteAtk (char plainPass[9], char* cryptPass, char* salt){
/**
 * @brief: brute attack for DES encryption
 *
 * @var plainPass: to save null-terminated plain-text password if found
 * @var cryptpass: encrypted password
 * @var salt: DES salt
 *
 * Configure MIN_CHAR & MAX_CHAR to specify search range
 * This actually just configures & call `bruteRecur`
 */
	// guess at the password
	char try[9];
	try[8] = '\0';

	// brute-force
	for(int passLen = 1; passLen < 9; passLen++){
		if(bruteRecur(plainPass, cryptPass, salt, try, passLen, 1))
			return 1;
	}

	// can't decrypt password, return false
	return 0;
}


int main(int argc, char** argv){
	char* cryptPass; // encrypted password
	char plainPass[9]; // plain-text password
	char salt[3]; // EDS salt

	// check encrypted password passed in
	if(argc != 2){
		printf("Please provide a encrypted password as argument\n");
		return 1;
	}
	cryptPass = argv[1];

	// get salt
	strncpy(salt, cryptPass, 2);
	salt[2] = '\0';

	// check salt validity
	if((!isalnum(salt[0]) && salt[0] != '.' && salt[0] != '/') ||
	   (!isalnum(salt[1]) && salt[1] != '.' && salt[1] != '/')){
		printf("Password's salt is invalid\n");
		return 2;
	}

	// crack password
	if(dictAtk(plainPass, cryptPass, salt, "./dict"))
		printf("%s\n", plainPass);
	else if(bruteAtk(plainPass, cryptPass, salt))
		printf("%s\n", plainPass);
	else
		printf("Password could not be decrypted\n");

	return 0;
}
