/**
 * @file: dictionary.h
 * @author: Billy.Ljm
 * @date: 29 June 2015
 * @brief: functions to check for word in a dictionary
 *
 * Dictionary is converted to a hash table which uses a murmur hash
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include <stdint.h>

#define LENGTH 45 // maximum length for a word
#define HASHSEED 0 // seed for murmur hash
#define HASHSIZE 0xFFFF // size of hash table

/**
 * @brief: singly linked list of strings
 */
struct node;

/**
 * @brief: murmur hash
 * @param key: string to be hashed
 * @param length: length of key string
 * @param seed: seed for hash function
 *
 * copied from https://en.wikipedia.org/wiki/MurmurHash
 */
uint32_t murmur3_32(const char *key, uint32_t len, uint32_t seed);

/**
 * @brief: check if word is in dictionary
 * @param word: word to look for dictionary
 * @return: true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * @brief: loads dictionary into memory.
 * @param dictionary: file name of dictionary
 * @return: true if successful, else false.
 */
bool load(const char* dictionary);

/**
 * @brief: counts number of words in dictionary
 * @return: number of words if dictionary loaded or 0 if not loaded.
 */
unsigned int size(void);

/**
 * @brief: unloads dictionary from memory
 * @return: true if successful, else false.
 */
bool unload(void);

#endif // DICTIONARY_H
