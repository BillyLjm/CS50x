0. Pneumono­ultra­microscopic­silico­volcano­coniosis means silicosis.  
1. `getrusage` returns resource usage measures.  
2. `struct rusage` has 16 member
3. `before` and `after` are passed by reference to `calculate` to save time and memory resources as the 2 structs would not have to be copied.  
4. In the `for` loop of `main`, the program reads characters in one by one. The program checks that the characters are either alphabetical or a apostrophe. 
If it passes the check, the character is saved in a word buffer. This continues until a non-alphabetical character (such as \n) is read. Afterwhich, the word 
is null-terminated and spell-checked. If during this process a digit or an excessively long word is read, the entire line is scrapped.  
5. `fscanf` is vulnerable to buffer overflow. Additionally, we are already checking if each character is alphabetical and thus `fgetc` is likely to be more efficient too.  
6. The parameters for `check` and `load` are only meant to be read from. Declaring them as `const` makes the program throw errors and alert us if they are wrongly written to.  
7. For the spell-checker, I used mumur has to create a hash table of singly-linked lists.   
8. My first correct implementation of spell-check took about 0.15s on `austinpowers.txt`.  
9. To reduce run times, I tried different hash table sizes until I got one which was approximately optimal.  
10. A bottleneck I wasn't able to solve was the hash did not perfectly evenly distribute the hash keys for the dictionary, leading to the need for linked lists and increased traversal time.  
