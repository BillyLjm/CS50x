/*
 * @file: initials.c
 * @author: Billy.Ljm
 * @date: 18 June 2015
 * @brief: Program that converts full name to initials
 *
 * Program is case-insensitive but
 * name must contain only spaces b/w words
 * e.g.
 *  >> ./initials
 *  >> adam'O-Brien JohnDoe
 *  >> AJ
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void){
	// Get name
	string s  = GetString();

	// Output initials
	for(int i = 0, len = strlen(s); i < len; i++){
		if(isspace(s[i-1]) || i == 0)
			printf("%c", toupper(s[i]));
	}

	//end
	printf("\n");
	free(s);
	return 0;
}
