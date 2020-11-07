/*
 * @file: credit.c
 * @author: Billy.Ljm
 * @date: 15 June 2015
 * @brief: Program that determines type of credit card from its number
 *
 * Calculates validity according to Luhn's algorithm &
 * the standard formats of credit cards from major companies.
 * Only works for AMEX (American Express), MASTERCARD & VISA.
 */

 #include <stdio.h>
 #include <cs50.h>
 #include <math.h>

 int main (void){
	long long num; // credit card number
	int numLen; // number of digits in `num`
	int numStart; // 2 most significant digits of `num`
	long long digit; // temporarily holds a digit for Luhn's algorithm
	int checksum = 0; // Luhn’s algorithm checksum
	string type; // type of credit card

	// get non-zero user input
	do{
		printf("Number: ");
		num = GetLongLong();
	} while(num < 0);


	// get number length
	if(num >= pow(10,12) && num < pow(10,13))
		numLen = 13;
	else if(num >= pow(10,14) && num < pow(10,15))
		numLen = 15;
	else if(num >= pow(10,15) && num < pow(10,16))
		numLen = 16;
	else{
		printf("INVALID\n");
		return 0;
	}

	// check number legnth & starting 2 digits
	numStart = num / pow(10, numLen - 2);
	if(numLen == 15 && (numStart == 34 || numStart == 37))
		type = "AMEX";
	else if(numLen == 16 && (numStart > 50 && numStart < 56))
		type = "MASTERCARD";
	else if((numLen == 13 || numLen == 16) && (numStart >= 40 && numStart < 50))
		type = "VISA";
	else{
		printf("INVALID\n");
		return 0;
	}

	// Luhn's algorithm
	for(int i = 0; i < numLen; i += 2){
		digit = (num / pow(10, i));
		digit = digit % 10;
		checksum += digit;
	}
	for(int i = 1; i < numLen; i+= 2){
		digit = (num / pow(10, i));
		digit = digit % 10;
		if(digit < 5)
			checksum += 2 * digit;
		else
			checksum += 1 + (2 * digit) % 10;
	}

	// check Luhn's algorithm & end
	if(checksum % 10 == 0)
		printf("%s\n", type);
	else
		printf("INVALID\n");
	return 0;
 }
