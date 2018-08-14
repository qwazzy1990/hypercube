#ifndef _STRING_BIT_POSN_
#define _STRING_BIT_POSN_

#include <stdio.h>
#include <stdlib.h>
#include "DynamicString.h"
#include "utilities.h"
#include "LinkedList.h"

/***STRUCT DEFINITIONS***/


struct bpp 
{
    int bitNumber;
    LinkedList pathNumbers;
    int numberOfPaths;
};
typedef struct bpp BitPathPair;
typedef BitPathPair* BitPathPairs;

struct sbp 
{
    String binaryString;
	int stringNumber;
	LinkedList bitPathPairs;
    char bit;
};
typedef struct sbp stringBitPosition;
typedef stringBitPosition* StringBitPosition;
typedef StringBitPosition* StringBitPositions;
//typedef StringBitPositions* StringsBitPositions;


struct sbc 
{
    StringBitPositions stringBitPositions;
    int size;
    PrintFunc printData;
    DeleteFunc deleteData;
    CompareFunc compareData;
};
typedef struct sbc stringBitContainer;
typedef stringBitContainer* StringBitContainer;


/***END STRUCT DEFINITIONS***/

/***CONSTRUCTORS***/
BitPathPairs new_bit_path_pairs(int n);

StringBitPositions new_string_bit_positions(int n);

StringBitContainer new_string_bit_container(int n, PrintFunc p, DeleteFunc d, CompareFunc c);


/****END CONSTRUCTORS****/


/****DESTROYERS***/
void destroy_bit_path_pairs(AnyData bbp);
void destroy_string_bit_position(AnyData sbp);
void destroy_string_bit_container(AnyData sbc);

/****END DESTROYERS****/


/******SETTERS*****/

void add_string_bit_pair(StringBitContainer c, Strings s, int n);

void add_path_number(LinkedList pathNumbers, int n);
/****END SETTERS****/


/****PRINTERS****/
String print_string_bit_container(StringBitContainer c);

String print_bit_path_pairs(AnyData bbp);
/***END PRINTERS****/
#endif