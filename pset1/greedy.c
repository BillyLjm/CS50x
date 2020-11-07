/*
 * @file: greedy.c
 * @author: Billy.Ljm
 * @date: 15 June 2015
 * @brief: Program that calculates least number of coins to make up an amount
 *
 * For example, 35c is made up of a 25c and a 10c.
 * Thus, the program will print "2" as the minimum number of coins
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
	float dollars; // user input in dollars
	int cents; // user input in cents
	int change[4] = {25,10,5,1}; // change values in cents
	int changeSize = 4; // size of `change[]` above
	int numCoins = 0; // min number of coins to make up dollars`

	// Get valid user input
	printf("O hai! ");
	do{
		printf("How much change is owed?\n");
		dollars = GetFloat();
	} while(dollars < 0);

	// Convert to cents to prevent rounding errors
	cents = round(dollars * 100);

	// Greedy algorithm
	for(int i = 0; i < changeSize; i++){
		while(cents >= change[i]){
			cents -= change[i];
			numCoins +=1;
		}
	}

	// Output
	printf("%d\n", numCoins);
	return 0;
}
