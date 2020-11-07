/**
 * @file: helpers.c
 * @author: Billy.Ljm
 * @date: 20 June 2015
 * @brief: Binary Search & Counting Sort
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
 * @brief: Destructive counting sort
 * @param n: size of 'n'
 * @param [in] values: array to be sorted
 * @param [out] values: sorted array
 *
 * Max & min keys is defined in function.
 * This is solely because of assigment requirements.
 */
void sort(int values[], int n)
{
	// rage of keys
	int minkey = 0;
	int maxkey = 65536;

	// counting sort
	int sorted[n];
	int count[maxkey - minkey];
	int total = 0;
	int oldTotal;
	for(int i = 0; i < n; i++) // make histogram, copy `values` & make values zero-based
		count[values[i] - minkey]++;
	for(int i = 0, range = maxkey - minkey; i < range; i++){ // count how many are smaller
		oldTotal = total;
		total += count[i];
		count[i] = oldTotal;
	}
	for(int i = 0; i < n; i++){
		sorted[count[values[i] - minkey]] = values[i];
		count[values[i] - minkey]++; // to increment values for repeat values
	}

	// copy output into values
	for(int i = 0; i < n; i++)
		values[i] = sorted[i];

	return;
}
