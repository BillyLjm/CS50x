/*
 * @file: mario.c
 * @author: Billy.Ljm
 * @date: 15 June 2015
 * @brief: Program that prints half-pyramid of desired height
 *
 * A height of 3 will print:
 *   ##
 *  ###
 * ####
 * Height must range from 1 to 23 inclusive
 */

#include <stdio.h>
#include <cs50.h>

int main(void){
	int height; // height of pyramid

	// get valid user input
	do{
		printf("height: ");
		height = GetInt();
	} while(height < 0 || height > 23);

	// output pyramid
	for(int row = 1; row <= height; row++){
		for(int i = 0; i < height - row; i++) // output " "
			printf(" ");
		for(int i = 0; i < row + 1; i++) // output "#"
			printf("#");
		printf("\n"); // next line
	}

	return 0;
}
