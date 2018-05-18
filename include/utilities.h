#ifndef _UTILITIES_
#define _UTILITIES_



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

enum type {INT, CHAR, BOOL, DOUBLE, LONG, FLOAT, UNSIGNED_INT};
typedef enum type Primitive;


typedef void* AnyData;

struct i{
	AnyData current;
    int position;    
};typedef struct i Iterator;

		/**
		 *Typedefs for function pointers for standard functions
		   pointer to swap function, compare function, print function and delete function
		 *
		 * **/
typedef void (*swap_func)(AnyData a, AnyData b);
typedef int (*compare_func)(AnyData a, AnyData b);
typedef char* (*print_func)(AnyData data);
typedef void (*delete_func)(AnyData data);
		/**
		 *Typedef for void*
		 * **/


		/**
		 * Swapping functions
		 * **/
void swap(AnyData a, AnyData b, swap_func s);

void swapInts(AnyData a, AnyData b);

void swapChars(AnyData a, AnyData b);

void swapDoubles(AnyData a, AnyData b);




		/**
		 * Comparing Functions
		 * **/

int compare(AnyData a, AnyData b, compare_func c);





										/*******MISCECLLANIOUS FUNCTIONS*******/
void remove_hard_return(char* s);


bool sameobject(AnyData a, AnyData b);

#endif
