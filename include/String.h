#ifndef _STRING_
#define _STRING_

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




      

          /**
              Converts a file to a string
          **/
char* readfile(FILE* fp);





                        /**PARSING FUNCTIONS********/

/**
    Input: String and delimiters
    Output: Array of strings parsed from  original string based on delimiter(s)
**/
char** stringsplit(char* s, char* delims);
/**
    Helper function to check if a character is a delimiter
**/
bool isdelim(char c, char* delims);



                  /****CONSTRUCTORS**********/
/**
      Input: void
      Output: Memory allocated for a char*
      size = max_size
**/

char* createvoidstring(void);


/**
      Input: String
      Output: new string = to size of s
**/

char* createstring(char* s);


/**
    Input: size
    Output: null-terminated string = to size
**/
char* createnstring(unsigned int size);



/**
    Constructors for string arrays
**/


/**
    creates a null terminated string matrix of DEFAULT_SIZE by DEFAULT_SIZE
    Terminates matrix with NULL
**/
char** createvoidstringarray( void );









                      /***********DESTROYERS****************/

/**
    Input: String
    Output: freed string
**/

void destroystring_real(char** s);

/**
   Input: Stringarray
   Output: N/A
   Postconditions: String array is freed
**/
void destroystringarray_real(char*** s);






                    /***************CLONERS********************/
/**
   Function to copy a string to another
   Preconditions: Source must exist and contain content
   Postconditions:  Source is unchanged
   Input: source string
   Output: newstring with content of source
**/
char* stringcopy(char* source);

char* stringncopy(char* source, int n);

/**
    Function to copy the contents of one string array to another
    Preconditions: Source must exist and contain content
    Postconditions: Source is unchanged, copy of source is returned
**/
char** stringarraycopy(char** s);



    /**
      Function to copy a segment of a string to another from start to end.
      The copy includes both the start and end character
      Preconditions: Source must exist and contain content. The end must be >= to
      the start. The start must be > 0. The end will be reduced to length of source if
      > than length of source.
      Postconditions: Source is unchanged, copy of segment of source is returned
    **/
char* stringsegmentcopy(char* s, unsigned int start, unsigned int end);


        /**
            Function to copy a segment of a string array to another string array.
            Copies every string in the segment and copies the entirety of every string
            Pre-conditions: Source must exist and contain content. The end must be >= to
            the start. Every index within the bound must contain a valid string.  End
            will be reduced to the end of the array if it goes out of bounds
            The start must be > 0.
            Post conditions: Source is unchanged, copy of segment of source is returned
        **/
char** stringarraysegmentcopy(char** s, unsigned int start, unsigned int end);




                      /***************MUTATORS****************/

/**
  Function to concatenate one string to the end of another
  Preconditions: Neither Source nor Dest can be NULL
                 source must be null terminated

   Postconditions: Source is unchanged. Destination is modified with source appended
**/
char* stringcat(char* dest, char* source);


/**
    Function to convert data in memory to a string
    Preconditions: The data must be numeric, i.e. floating point or integer
    Postconditions: A string containing the data is returned
**/
char* tostring(Primitive type, void* data);


/**
    Function to reverse the order of a string
    Preconditions: String muest not be empty or null
    Postconditions: New string in reverse order. s is freed
**/
char* reversestring(char* s);



                        /*************PRINT FUNCTIONS**************/

  /**
    Function to convert a string array to a string.
    Preconditions: String array must exist and be non-empty
    Postconidtions: a string returned concatenated with all the strings of
    the stringarray. string array remains unchanged.
  **/
char* printstringarray(char** s);


                        /**************VALIDATORS**********/
/**
    Checks if a pointer is NULL or Empty
      Returns true if NULL or Empty
      else false
**/
bool badstring(char* s);

                      /**Checks if a string is static
                         Returns true if static else false**/
bool isstatic(char* s);





                                    /*****ACCESSORS*****/


        /**
         * Gets the length of a string.
         * Preconditions: String must exist
         * Postconditions: String remains unchanged and length of string excluding null terminator is returned
         * */
int stringlen(char* s);


        /**
         * Gets the nth characters in string s
         * Preconditions: String must exist and be non empty. n must be >= 1 and <= string length
         * Postconidtions: The nth character in string s is returned. 
         * */
char getch(char* s, int n);


int stringtoint(char* s);

int stringlen(char* s);
#endif
