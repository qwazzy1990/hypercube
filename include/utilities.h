#ifndef _UTILITIES_
#define _UTILITIES_



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>



#define mem_alloc(myarg, size) myarg = calloc(size, sizeof(*myarg))
#define resize(myarg, size) myarg = realloc(myarg, sizeof(*myarg)*size)
#define for_each(index, number) for(int index=0; index<number; index++)



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
typedef void (*SwapFunc)(AnyData a, AnyData b);
typedef int (*CompareFunc)(AnyData a, AnyData b);
typedef char* (*PrintFunc)(AnyData data);
typedef void (*DeleteFunc)(AnyData data);
typedef void* (*CloneFunc)(AnyData data);
		/**
		 *Typedef for void*
		 * **/


		/**
		 * Swapping functions
		 * **/
void swap(AnyData a, AnyData b, SwapFunc s);

void swapInts(AnyData a, AnyData b);

void swapChars(AnyData a, AnyData b);

void swapDoubles(AnyData a, AnyData b);




		/**
		 * Comparing Functions
		 * **/

int compare(AnyData a, AnyData b, CompareFunc c);





										/*******MISCECLLANIOUS FUNCTIONS*******/
void remove_hard_return(char* s);


bool sameobject(AnyData a, AnyData b);

#endif
