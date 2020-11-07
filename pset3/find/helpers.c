/**
 * @file: helpers.c
 * @author: Billy.Ljm
 * @date: 19 June 2015
 * @brief: Binary Search & Bubble Sort
 */

#include <cs50.h>
#include "helpers.h"

/**
 * @brief: Binary Search
 *
 * @param value: value to search for
 * @param values: array to search in
 * @param n: size of `values`
 * @return: 1 if `value` found, 0 otherwise.
 */
bool search(int value, int values[], int n)
{
	int min, max, mid; // ranges of binary search

	// verify array size
	if(n < 1)
		return false;

	// initialise min & max
	min = 0;
	max = n;

	// binary search
	while(true){
		// most of the search
		if(max - min > 1){
			mid = (min + max) / 2;
			if(value == values[mid])
				return 1;
			else if(value < values[mid])
				max = mid;
			else
				min = mid;
		}

		// if only last 2 values left
		else if(max - min == 1){
			if(value == values[max] || value == values[min])
				return true;
			else
				return false;
		}
	}
}

/**
 * @brief: Bubble sort in ascending order
 *
 * @param n: size of `values`
 * @param [in] values: array to sort
 * @param [out] values: sorted array
 */
void sort(int values[], int n)
{
	bool sorted = false; // boolean of whether `values` is sorted
	int buffer; // temporarily store values for swaps

	// bubble sort
	while(!sorted){
		sorted = true;
		for(int i = 1; i < n; i++){
			if(values[i - 1] > values[i]){
				buffer = values[i];
				values[i] = values[i - 1];
				values[i - 1] = buffer;
				sorted = false;
			}
		}
	}

	// end
	return;
}
