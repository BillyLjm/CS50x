/**
 * @file: helpers.h
 * @author: Billy.Ljm
 * @date: 20 June 2015
 * @brief: Binary Search & Counting Sort
 */

#include <cs50.h>

/**
 * @brief: Binary Search
 *
 * @param value: value to search for
 * @param values: array to search in
 * @param n: size of `values`
 * @return: 1 if `value` found, 0 otherwise.
 */
bool search(int value, int values[], int n);

/**
 * @brief: Destructive counting sort
 * @param n: size of 'n'
 * @param [in] values: array to be sorted
 * @param [out] values: sorted array
 *
 * Max & min keys is defined in function.
 * This is solely because of assigment requirements.
 */
void sort(int values[], int n);
