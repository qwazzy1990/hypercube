#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#include "String.h"
#include "utilities.h"


 
          /**
            Function to copy the content of a file to a char*
            Input: File Pointer
            Output: Char* with all content for file
          **/
char* readfile(FILE* fp)
{
    if(fp == NULL)return NULL;
    rewind(fp);
    char* theFile = (char*)calloc(2, sizeof(char));
    if(theFile == NULL)return NULL;
    int mem_size = 2;
    int count = 0;
    char c;
    while(!feof(fp)){
      c = fgetc(fp);
      if(feof(fp) != 0)break;

      theFile[count] = c;
      theFile[count + 1] = '\0';
      count++;
      mem_size++;
      theFile = (char*)realloc(theFile, sizeof(char)*mem_size);
      if(theFile == NULL)return NULL;
    }
    theFile[count] = '\0';

    return theFile;
}



            /**
                Parses a string into an array of strings based on delimitr(s)
                Input: String to be parsed and delimiters
                Output: Array of strings delimited by delimiter
            **/
char** stringsplit(char* s, char* delims)
{
     int j = 0;

     //errorcheck
     if(badstring(s))return NULL;

     //errorcheck
     if(badstring(delims))return NULL;
     //while
     while(isdelim(s[j], delims))
        j++;
     //endwhile

     //parameter and varaible setup
     int mem_size = 1;
     int row = 0;
     int col = 0;
     char c = 0;
     char p = 0;
     char** tokens = (char**)calloc(mem_size, sizeof(char*));
     if(tokens == NULL)return NULL;
     tokens[row] = createvoidstring();
     //for
     for(int i = j; i < strlen(s); i++){
         //if
         if(i == 0){
             c = s[i];
             p = c;
         }//endif
         c = s[i];
         //if
         if(isdelim(c, delims) && isdelim(p, delims)){
             p = c;
             continue;
         }//endif
         //if
         if((isdelim(c, delims))&& (!isdelim(p, delims))){
             p = c;
             continue;
         }//endif
         //if
         if((!isdelim(c, delims))&&(isdelim(p, delims))){
             tokens[row][col] = '\0';
             row++;
             col = 0;
             mem_size++;
             tokens = (char**)realloc(tokens, sizeof(char*)*mem_size);
             if(tokens == NULL)return NULL;
             tokens[row] = createvoidstring();
             tokens[row][col] = c;
             col++;
         }//endif
         //if
         if(!isdelim(c, delims) && !isdelim(p, delims)){
             tokens[row][col] = c;
             col++;
         }//endif
         p = c;
     }//endfor
   mem_size++;
   row++;
   tokens = (char**)realloc(tokens, sizeof(char*)*mem_size);
   if(tokens == NULL)return NULL;
   tokens[row] = NULL;
  return tokens;
}//end Function


bool isdelim(char c, char* delims)
{
    if(delims == NULL)return false;
    if(strlen(delims) <= 0)return false;
    for(int i = 0; i < strlen(delims); i++){
         if(c == delims[i])return true;
    }
    return false;
}










                      /********CONSTRUCTORS*************/

/**
    Output: null-terminated String of DEFAULT_SIZE
**/
char* createvoidstring(void)
{
     char* s = (char*)calloc(50000, sizeof(char));
     if(s == NULL)return NULL;
     for(int i = 0; i < DEFAULT_SIZE; i++)
      s[i] = '\0';
     return s;
}

/**
    Input: string
    Output: new null-terminated string of size = len of s
    or NULL if input is invalid
**/
char* createstring(char* s)
{
    if(badstring(s))return NULL;
    int len = strlen(s);
    char* newString = (char*)calloc(len, sizeof(char));
    if(newString == NULL)return NULL;
    for(int i = 0; i < len; i++)
      s[i] = '\0';
    return newString;
}


/**
   Input: size of string to be created
   Output: Null-terminated string = to size
**/
char* createnstring(unsigned int size)
{
    assert(size > 0);
    char* s = (char*)calloc(size, sizeof(char));
    if(s == NULL)return NULL;
    for(int i = 0; i < size; i++)
        s[i] = '\0';
    return s;
}





/**
    Constructors for string arrays
**/


/**
     Preconditions: N/A
     Postconditions: Newly allocated string matrix of DEFAULT_SIZE by DEFAULT_SIZE
     String array terminated with NULL
**/
char** createvoidstringarray(void)
{
    int i = 0;
    char** s = (char**)calloc(DEFAULT_SIZE+1, sizeof(char*));
    if(s==NULL)return NULL;
    for(i = 0; i < DEFAULT_SIZE; i++){
      s[i] = createvoidstring();
    }
    s[i]=NULL;
    return s;
}




                  /********DESTROYERS*************/

void destroystring_real(char** s)
{
    assert(s != NULL);
    if((*s) == NULL)return;
   
    if(stringlen(*s)<=0)return;
    free(*s);
    *s = NULL;
}


/**
   Input: String
   Output: N/A
   Function to free a string array

**/

void destroystringarray_real(char*** s)
{
    if(s == NULL){
      return;
    }
    if(*s == NULL){
      return;
    }
    int i = 0;
    while((*s)[i] != NULL){
        destroystring((*s)[i]);
	i++;
    }
    free(*s);
    *s = NULL;
}





                            /***********CLONERS**********/


char* stringcopy(char* source)
{
   if(badstring(source))return NULL;
   int len = stringlen(source) + 1;
   char* clone = createnstring(len);
   int i = 0;
   for(i = 0; i < len-1; i++)
      clone[i] = source[i];

    clone[i] = '\0';
    return clone;
}

char* stringncopy(char* source, int n)
{
    if(badstring(source))return NULL;
    if(strlen(source) < n)return NULL;
    char* clone = createnstring(n+1);
    int i = 0;
    for(i = 0; i < n; i++)
      clone[i] = source[i];
    clone[i] = '\0';
    return clone;
}


char** stringarraycopy(char** source)
{
    if(source == NULL)return NULL;
    if(badstring(source[0]))return NULL;
    int count = 0;
    int mem_size = 1;
    char** clone = (char**)calloc(mem_size, sizeof(char*));
    if(clone == NULL)return NULL;
    while(source[count] != NULL){
      clone[count] = stringcopy(source[count]);
      mem_size++;
      clone = (char**)realloc(clone, sizeof(char*)*mem_size);
      if(clone == NULL)return NULL;
      count++;
    }
    clone[count] = NULL;
    return clone;
}






char* stringsegmentcopy(char* s, unsigned int start, unsigned int end)
{
    if(badstring(s))return NULL;
    if(start <= 0){
      start = 1;
    }
    if(end > strlen(s)){
      end = strlen(s);
    }
    if(start > end)return NULL;
    int mem_size = (end - start)+2;
    char* clone = createnstring(mem_size+1);
    if(clone == NULL)return NULL;
    int count = start-1;
    int i = 0;
    for(i = 0; i < mem_size-1; i++){
        clone[i] = s[count];
        count++;
    }
    clone[i] = '\0';
    return clone;
}



char** stringarraysegmentcopy(char** s, unsigned int start, unsigned int end)
{
      //error checking
      char** clone = stringarraycopy(s);
      if(clone == NULL)return NULL;

     if(s == NULL)return NULL;
     if(start <= 0){
       start = 1;
     }
     int i = 0;
     while(s[i] != NULL){
       i++;
     }
     if(i == 0){
       return NULL;
     }
     if(end > i){
       end = i;
     }
     if(start > end)return NULL;

     int mem_size = 1;
     char** copy = (char**)calloc(mem_size, sizeof(char*));
     int count = start-1;
     int j = 0;
     for(j = 0; j <= end-start; j++){
        copy[j] = stringcopy(clone[count]);
        count++;
        mem_size++;
        copy = (char**)realloc(copy, mem_size*sizeof(char*));
     }
     copy[j] = NULL;

     //remember to free clone
     destroystringarray(clone);
     return copy;
}




                      /********MUTATORS*********************/

char* stringcat(char* dest, char* source)
{
    assert(badstring(source)==false);
    if(badstring(dest)){
	      dest = stringcopy(source);
	       assert(badstring(dest)==false);
	       return dest;
    }
    char* clone = (char*)calloc(stringlen(dest), sizeof(*clone));
    int j = 0;
    while(dest[j] != '\0'){
        if(dest[j]=='\0')break;
      clone[j] = dest[j];
      j++;
    }
    destroystring(dest);
    int count = 0;
    int reallocSize= j + stringlen(source) +2;
    count = j;
    clone = (char*)realloc(clone, reallocSize*sizeof(char));
   
    for(int i = 0; i < strlen(source); i++){
        clone[count] = source[i];
        count++;
    }
   clone[count] = '\0';
    return clone;
}



char* reversestring(char* s)
{
    assert(badstring(s)==false);
     if(badstring(s))return NULL;
     int len = stringlen(s);
     int n = len-1;
     int i = 0;
     char* inverse = createnstring(len+1);
     for( i = 0; i <= len-1; i++){
       inverse[i] = s[n];
       n--;
     }
     inverse[i] = '\0';
     destroystring(s);
     return inverse;
}

char* tostring(Primitive type, void* data)
{
    assert((type == INT) || (type == FLOAT));
    assert(data != NULL);
    if(type != INT && type != FLOAT)return NULL;
    if(data == NULL)return NULL;
    char* s = createvoidstring();
    char* s2 = NULL;
    //if
    if(type == INT){
        int* d = (int*)data;
        int n = *d;
        //if
        if(n == 0){
           s[0] = 48;
           
           return s;
        }
        else if(n > 0){
          int r = 0;
          int i = 0;
          while(n != 0){
            r = n%10;
            n = n/10;
            char c = r+48;
            s[i] = c;
            i++;
          }
          s2 = reversestring(s);
          n = *d;
        }//endelseif
        //else
        else{
          int r = 0;
          int i = 0;
          n = n*(-1);
          //while
          while(n != 0){
            r = n%10;
            n = n/10;
            char c = r+48;
            s[i] = c;
            i++;
          }//endwhile
          s = stringcat(s, "-");
          s2 = reversestring(s);
          n = *d;

        }//endelse
    }//endif


    //if
    if(type == FLOAT){
      double r = 0;
      int n = 0;
      int count = 0;
      double* fp = (double*)data;
      double f = *fp;
      //if
      if(f == 0){
        s[0] = 48;
        s2 = reversestring(s);
        return s2;
      }//endif

      //if
      if(f > 0){
        //while
        long k = 0;
        while(f > k){
          f = f*10;
          k = f;
          count++;
        }//endwhile
        n = f;
        int i = 0;
        //while
        while(n != 0){
            //if
            if(count != 0){
              r = n%10;
              n = n/10;
              char c = r+48;
              s[i] = c;
              i++;
            }//endif
            //else
            else{
               char c = '.';
               s[i] = c;
               i++;
            }
            count--;
        }//endwhile

        s2 = reversestring(s);

      }//endif

      //if
      if(f < 0){

        f = f*(-1);
        long k = 0;
        //while
        while(f > k){
          f = f*10;
          k = f;
          count++;
        }//endwhile
        n = f;
        int i = 0;
        //while
        while(n != 0){
            //if
            if(count != 0){
              r = n%10;
              n = n/10;
              char c = r+48;
              s[i] = c;
              i++;
            }//endif
            //else
            else{
               char c = '.';
               s[i] = c;
               i++;
            }//endelse
            count--;
        }//endwhile
        s = stringcat(s, "-");
        s2 = reversestring(s);

      }//endif
      n = *fp;

    }//endif
    return s2;
}


int stringtoint(char* s)
{
    assert(badstring(s) == false);
    int value = 0;
    int i = 0;
    while(s[i] != '\0'){
      value = value + (int)s[i];
      i++;
    }
    return value;
}







                      /*************PRINTERS************/


char* printstringarray(char** s)
{
    if(s == NULL)return NULL;
    int i = 0;
    while(s[i] != NULL){
      i++;
    }
    if(i == 0){
       return NULL;
    }
    char* printer = NULL;
    i = 0;
    while(s[i] != NULL){
      printer = stringcat(printer, s[i]);

      printer = stringcat(printer, "\n");
      i++;
    }
    return printer;
}






                            /********VALIDATORS***********/
/**
      Input: String
      Output: True if string is  NUll or Empty
              else true
**/
bool badstring(char*s)
{
     if(s==NULL)return true;
     if(strlen(s) <= 0)return true;
     return false;
}


                          /*****************Accessors*****************/
int stringlen(char* s)
{
    if(s == NULL)return -1;

    int i = 0;
    while(s[i] != '\0'){
      i++;
    }
    return i;
}

char getch(char* s, int n)
{
    if(badstring(s))return -1;
    if(n < 1 || n > stringlen(s))return -1;
    char c = s[n-1];
    return c;
}




