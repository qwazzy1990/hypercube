#ifndef _UTILITIES_
#define _UTILITIES_



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define clear(myarg) clear_real((void*)&myarg); myarg = NULL


/** DEBUGGING AND PRINTING MACRO**/
#define DEBUGPRINT true
#define P if(DEBUGPRINT)printf



/***CONSTRUCTORS***/
#define new(type, myarg, size) type* myarg = calloc(size, sizeof(*myarg))

#define new_object(type, myarg, size) type myarg = calloc(size, sizeof(*myarg))

/***MEMORY ALLOCATERS***/
#define mem_alloc(myarg, size) myarg = calloc(size, sizeof(*myarg))

#define resize(myarg, size) myarg = realloc(myarg, 1000);

							/******DESTROYERS FOR SINGLE AND DOUBLE POINTERS TO ANY DATA****/


/**ITERATORS**** Do not use a variable 'x' in block of code when using iterator. Will cause unpredicted beghavior**/
#define foreach(index, number) for(int x=index; x<number; x++)

#define forall(number) for(int x = 0; x < number; x++)

#define doublefor(number) for(int x = 0; x < number-1; x++)\
								for(int y = x+1; y<number; y++)

//MACRO TO GET THE SIZE OF THE DATA THAT A POINTER IS POINTING TO
#define SIZE(x) sizeof(*x)




/***SIZES OF PRIMITIVES***/
#define CHAR_SIZE 1
#define INT_SIZE 4
#define FLOAT_SIZE 8
#define PTR_SIZE 8
#define LONG_SIZE 8
#define DOUBLE_SIZE 8


				

/***typedefs for pointers to primitives with exception of char* which can be found in String.h***/

typedef int* Int;
typedef long* Long;
typedef float* Float;
typedef double* Double;
typedef void* AnyData;
typedef bool* Bool;




enum type {INT, CHAR, BOOL, DOUBLE, LONG, FLOAT, UNSIGNED_INT};
typedef enum type Primitive;


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



							/********TESTING CLONE FUNCTION POINTER******/

/**
 * If a function returns a non void* then a function pointer to a function that returns a void* cannot be assigned the address of the function
 * that returns a non void* Likewise if the parameter to a function pointer is a void* a function that has a parameter of a non void* 
 * cannot be assigned to a variable of type void*(*foo)(void*)
 * **/
int* test_clone(void* a);



						/**************MEMORY ALLOCATERS*********/

void resize_real(AnyData* a, int size);


						/*********DESTROYERS*******/


void clear_real(AnyData d);


				/******DUMMY FUNCTIONS: DEFAULT TYPE IS int* ****/

int dummy_compare(const void* a, const void* b);

char* dummy_print(AnyData p);

void dummy_delete(AnyData d);




#endif
