/**
 * @file: helpers.h
 * @author: Billy.Ljm
 * @date: 19 June 2015
 * @brief: Binary Search & Bubble Sort
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
 * @brief: Bubble sort in ascending order
 *
 * @param n: size of `values`
 * @param [in] values: array to sort
 * @param [out] values: sorted array
 */
void sort(int values[], int n);
