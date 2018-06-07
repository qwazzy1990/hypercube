#ifndef _string_
#define _string_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "utilities.h"

#define DEFAULT_SIZE 10000





/**
  MOST USEFUL THING EVER!!
  THE PREPROCESSOR WILL REPLACE destroystring(myarg) with destroystring_real(&myarg)
**/
#define destroystring(myarg) destroystring_real(&myarg)

#define destroystringarray(myarg) destroystringarray_real(&myarg)




typedef char* String;
typedef String* Strings;
      

          /**
              Converts a file to a string
          **/
String readfile(FILE* fp);





                        /**PARSING FUNCTIONS********/

/**
    Input: string and delimiters
    Output: Array of strings parsed from  original string based on delimiter(s)
**/
Strings stringsplit(String s, String delims);
/**
    Helper function to check if a character is a delimiter
**/
bool isdelim(char c, String delims);



                  /****CONSTRUCTORS**********/
/**
      Input: void
      Output: Memory allocated for a string
      size = max_size
**/

String createvoidstring(void);


/**
      Input: string
      Output: new string = to size of s
**/

String createstring(String s);


/**
    Input: size
    Output: null-terminated string = to size
**/
String createnstring(unsigned int size);



/**
    Constructors for string arrays
**/


/**
    creates a null terminated string matrix of DEFAULT_SIZE by DEFAULT_SIZE
    Terminates matrix with NULL
**/
Strings createvoidstringarray( void );









                      /***********DESTROYERS****************/

/**
    Input: string
    Output: freed string
**/

void destroystring_real(Strings s);

/**
   Input: stringarray
   Output: N/A
   Postconditions: string array is freed
**/
void destroystringarray_real(Strings* s);

int remove_from_stringarray(Strings a, String s);






                    /***************CLONERS********************/
/**
   Function to copy a string to another
   Preconditions: Source must exist and contain content
   Postconditions:  Source is unchanged
   Input: source string
   Output: newstring with content of source
**/
String stringcopy(String source);

String stringncopy(String source, int n);

/**
    Function to copy the contents of one string array to another
    Preconditions: Source must exist and contain content
    Postconditions: Source is unchanged, copy of source is returned
**/
Strings stringarraycopy(Strings s);



    /**
      Function to copy a segment of a string to another from start to end.
      The copy includes both the start and end character
      Preconditions: Source must exist and contain content. The end must be >= to
      the start. The start must be > 0. The end will be reduced to length of source if
      > than length of source.
      Postconditions: Source is unchanged, copy of segment of source is returned
    **/
String stringsegmentcopy(String s, unsigned int start, unsigned int end);


        /**
            Function to copy a segment of a string array to another string array.
            Copies every string in the segment and copies the entirety of every string
            Pre-conditions: Source must exist and contain content. The end must be >= to
            the start. Every index within the bound must contain a valid string.  End
            will be reduced to the end of the array if it goes out of bounds
            The start must be > 0.
            Post conditions: Source is unchanged, copy of segment of source is returned
        **/
Strings stringarraysegmentcopy(Strings s, unsigned int start, unsigned int end);




                      /***************MUTATORS****************/

/**
  Function to concatenate one string to the end of another
  Preconditions: Neither Source nor Dest can be NULL
                 source must be null terminated

   Postconditions: Source is unchanged. Destination is modified with source appended
**/
String stringcat(String dest, String source);


/**
    Function to convert data in memory to a string
    Preconditions: The data must be numeric, i.e. floating point or integer
    Postconditions: A string containing the data is returned
**/
String tostring(Primitive type, void* data);


/**
    Function to reverse the order of a string
    Preconditions: string muest not be empty or null
    Postconditions: New string in reverse order. s is freed
**/
String reversestring(String s);

int add_to_stringarray(Strings a, String s);

void replace_in_string(String s, char c, int index);

                        /*************PRINT FUNCTIONS**************/

  /**
    Function to convert a string array to a string.
    Preconditions: string array must exist and be non-empty
    Postconidtions: a string returned concatenated with all the strings of
    the stringarray. string array remains unchanged.
  **/
String printstringarray(Strings s);


                        /**************VALIDATORS**********/
/**
    Checks if a pointer is NULL or Empty
      Returns true if NULL or Empty
      else false
**/
bool badstring(String s);

                      /**Checks if a string is static
                         Returns true if static else false**/
bool isstatic(String s);





                                    /*****ACCESSORS*****/


        /**
         * Gets the length of a string.
         * Preconditions: string must exist
         * Postconditions: string remains unchanged and length of string excluding null terminator is returned
         * */
int stringlen(String s);


        /**
         * Returns the indecies of all occurrencs of c in s.
         * Returns a dynamic array of all indecies of c in s terminated with a value of -1. Or  if no occurences of c in s then returns 
         * array with value of -1.
         * Preconidtions: s must exist. c must be a valid character
         * Postconditions: s and c remain unchanged. 
         * */
int* indecies_of_char(String s, char c);


        /**
         * returns a dynamic array of all indecies of occurrences of string s in string array terminated with a value of -1/
         * Or if no occrences of s in a then returns an array with value of -1.
         * Preconditions: a must exist and be non empty. s must exist and be nonempty
         * Postconditions: a and s remain unchanged.
         * 
         * */
int* indecies_of_string(Strings a, String s);


        /**
         * Gets the nth characters in string s
         * Preconditions: string must exist and be non empty. n must be >= 1 and <= string length
         * Postconidtions: The nth character in string s is returned. 
         * */
char getch(String s, int n);


int stringtoint(String s);

#endif
