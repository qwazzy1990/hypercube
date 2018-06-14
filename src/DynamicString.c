#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

#include "DynamicString.h"



 
          /**
            Function to copy the content of a file to a String
            Input: File Pointer
            Output: Char* with all content for file
          **/
String readfile(FILE* fp)
{
    if(fp == NULL)return NULL;
    rewind(fp);
    String theFile = (String)calloc(2, sizeof(char));
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
      theFile = (String)realloc(theFile, sizeof(char)*mem_size);
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
Strings stringsplit(String s, String delims)
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
     Strings tokens = (Strings)calloc(mem_size, sizeof(String));
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
             tokens = (Strings)realloc(tokens, sizeof(String)*mem_size);
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
   tokens = (Strings)realloc(tokens, sizeof(String)*mem_size);
   if(tokens == NULL)return NULL;
   tokens[row] = NULL;
  return tokens;
}//end Function


bool isdelim(char c, String delims)
{
    if(delims == NULL)return false;
    if(strlen(delims) <= 0)return false;
    for(int i = 0; i < strlen(delims); i++){
         if(c == delims[i])return true;
    }
    return false;
}





                    /*****MEMORY ALLOCATING FUNCTIONS*****/
String string_alloc(int size)
{
    assert(size > 0);
    String newString = (String)calloc((size+5), sizeof(char));
    return newString; 
}

void resize_string_real(String* s, int* size)
{
    assert(s != NULL);
    assert(*s != NULL);
    assert(*size > 0);
    *size += stringlen(*s)+1;
    *s = (String)realloc(*s, *size);
}

Strings strings_alloc(int size)
{
    assert(size > 0);
    Strings s = (Strings)calloc((size+5), sizeof(char*));
    return s;
}

Strings resize_strings(Strings s, int size)
{
    assert(s != NULL);
    assert(size > 0);
    s = (Strings)realloc(s, sizeof(char*)*(size+5));
    return s;
}


                      /********CONSTRUCTORS*************/

/**
    Output: null-terminated String of DEFAULT_SIZE
**/
String createvoidstring(void)
{
     String s = (String)calloc(50000, sizeof(char));
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
String createstring(String s)
{
    if(badstring(s))return NULL;
    int len = strlen(s);
    String newString = (String)calloc(len, sizeof(char));
    if(newString == NULL)return NULL;
    for(int i = 0; i < len; i++)
      s[i] = '\0';
    return newString;
}


/**
   Input: size of string to be created
   Output: Null-terminated string = to size
**/
String createnstring(unsigned int size)
{
    assert(size > 0);
    new_object(String, s, size);
    if(s == NULL)return NULL;
    for_all(size)
        s[x] = '\0';
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
Strings createvoidstringarray(void)
{
    int i = 0;
    new_object(Strings, s, 1000+1);
    if(s==NULL)return NULL;
    for(i = 0; i < 1000; i++){
       new_object(String, t, 1000);
       s[i] = t;
    }
    s[i]=NULL;
    return s;
}




                  /********DESTROYERS*************/

void destroystring_real(Strings s)
{
    assert(s != NULL);
    if((*s) == NULL){
        return;
    }
    String temp = (String)(*s);
    if(stringlen(temp)<=0)return;
    free(*s);
    *s = NULL;
}


/**
   Input: String
   Output: N/A
   Function to free a string array

**/

void destroystringarray_real(Strings* s)
{
    if(s == NULL){
      return;
    }
    if(*s == NULL){
      return;
    }
    int i = 0;
    Strings temp = (Strings)(*s);
    while(temp[i] != NULL){
        destroystring(temp[i]);
	i++;
    }
    free(*s);
    *s = NULL;
}

int remove_from_stringarray(Strings a, String s){
    int i = 0;
    while(a[i] != NULL){
        if(strncmp(a[i], s, strlen(s)+1)==0){
            destroystring(a[i]);
            break;
        }
        i++;
    }
    int count = i+1;
    int prev = i;
    while(a[count]!=NULL){
        a[prev] = stringcopy(a[count]);
        destroystring(a[count]);
        count++;
        prev++;
    }
    return i;
}






                            /***********CLONERS**********/


String stringcopy(String source)
{
   if(badstring(source))return NULL;
   int len = stringlen(source) + 1;
   String clone = createnstring(len);
   int i = 0;
   for(i = 0; i < len-1; i++)
      clone[i] = source[i];

    clone[i] = '\0';
    return clone;
}

String stringncopy(String source, int n)
{
    if(badstring(source))return NULL;
    if(strlen(source) < n)return NULL;
    String clone = createnstring(n+1);
    int i = 0;
    for(i = 0; i < n; i++)
      clone[i] = source[i];
    clone[i] = '\0';
    return clone;
}


Strings stringarraycopy(Strings source)
{
    if(source == NULL)return NULL;
    if(badstring(source[0]))return NULL;
    int count = 0;
    int mem_size = 1;
    Strings clone = (Strings)calloc(mem_size, sizeof(String));
    if(clone == NULL)return NULL;
    while(source[count] != NULL){
      clone[count] = stringcopy(source[count]);
      mem_size++;
      clone = (Strings)realloc(clone, sizeof(String)*mem_size);
      if(clone == NULL)return NULL;
      count++;
    }
    clone[count] = NULL;
    return clone;
}






String stringsegmentcopy(String s, unsigned int start, unsigned int end)
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
    String clone = createnstring(mem_size+1);
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



Strings stringarraysegmentcopy(Strings s, unsigned int start, unsigned int end)
{
      //error checking
      Strings clone = stringarraycopy(s);
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
     Strings copy = (Strings)calloc(mem_size, sizeof(String));
     int count = start-1;
     int j = 0;
     for(j = 0; j <= end-start; j++){
        copy[j] = stringcopy(clone[count]);
        count++;
        mem_size++;
        copy = (Strings)realloc(copy, mem_size*sizeof(String));
     }
     copy[j] = NULL;

     //remember to free clone
     destroystringarray(clone);
     return copy;
}




                      /********MUTATORS*********************/



/**********FIX ME:********/
String stringcat(String s, int n, ...)
{
    va_list list;
    va_start(list, n);
    String c = NULL;
    String temp = NULL;
    int memSize = 0;
    int end = 0;
    if(s == NULL){
        for_all(n){
            temp = va_arg(list, char*);
            memSize += stringlen(temp)+1;
            if(x == 0){
                c = stringcopy(temp);
            }else{
                resize_string(c, memSize);
                PR("Debug %s\n", c);
                end = stringlen(c);
                for_each(x, stringlen(temp)+1){
                    c[end] = temp[x];
                    end++;
                }
                c[end] = '\0';
                PR("c is %s\n", c);
            }
        }
        va_end(list);
        if(c == NULL)PR("What the fuck\n");
        return c;
    }
    else{
        c = stringcopy(s);
        memSize = stringlen(c)+1;
        end = stringlen(c);
        for_all(n){
            temp = va_arg(list, char*);
            memSize = stringlen(temp)+1;
            resize_string(c, memSize);
            end = stringlen(c);
            for_each(0, stringlen(temp)+1){
                c[end] = temp[x];
                end++;
            }
            c[end] = '\0';
        }
        va_end(list);
        destroystring(s);
        return c;
    }
}



String reversestring(String s)
{
    assert(badstring(s)==false);
     if(badstring(s))return NULL;
     int len = stringlen(s);
     int n = len-1;
     int i = 0;
     String inverse = createnstring(len+1);
     for( i = 0; i <= len-1; i++){
       inverse[i] = s[n];
       n--;
     }
     inverse[i] = '\0';
     return inverse;
}

String to_lower(String s)
{
    assert(s != NULL);
    String temp = stringcopy(s);
    for_each(x, stringlen(temp)){
        if(temp[x] >= 65 && temp[x] <= 90){
            char c = temp[x];
            int t = (int)c;
            t = t+32;
            c = (char)t;
            temp[x] = c;
        }
    }
    String lowerCase = stringcopy(temp);
    destroystring(temp);
    return lowerCase;
}

String to_upper(String s)
{
    assert(s != NULL);
    String temp = stringcopy(s);
    for_each(x, stringlen(temp)){
        if(temp[x] >= 97 && temp[x] <= 122){
            char c = temp[x];
            int t = (int)c;
            t = t-32;
            c = (char)t;
            temp[x] = c;
        }
    }
    String upperCase = stringcopy(temp);
    destroystring(temp);
    return upperCase;
}

int add_to_stringarray(Strings a, String s)
{
    int i = 0;
    while(a[i] != NULL){
        i++;
    }
    a[i] = stringcopy(s);
    a[i+1] = NULL;
    return i;
}

String tostring(Primitive type, void* data)
{
    assert((type == INT) || (type == FLOAT));
    assert(data != NULL);
    if(type != INT && type != FLOAT)return NULL;
    if(data == NULL)return NULL;
    String s = createvoidstring();
    String s2 = NULL;
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
          s = stringcat(s, 1, "-");
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
        s = stringcat(s, 1, "-");
        s2 = reversestring(s);

      }//endif
      n = *fp;

    }//endif
    return s2;
}


int stringtoint(String s)
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



void replace_in_string(String s, char c, int index)
{
    s[index] = c;
}




                      /*************PRINTERS************/


String printstringarray(Strings s)
{
    if(s == NULL)return NULL;
    int i = 0;
    while(s[i] != NULL){
      i++;
    }
    if(i == 0){
       return NULL;
    }
    String printer = NULL;
    i = 0;
    while(s[i] != NULL){
      printer = stringcat(printer, 1, s[i]);

      printer = stringcat(printer, 1, "\n");
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
bool badstring(String s)
{
     if(s==NULL)return true;
     if(strlen(s) <= 0)return true;
     return false;
}

bool is_upper_real(char c)
{
    int x = (int)c;
    if(x >= 65 && x <=90){
        return true;
    }return false;
}

EqualStringStatus strequal(String s1, String s2, CaseSensitivity c)
{
    assert(s1 != NULL);
    assert(s2 != NULL);
    if(c == CASE_SENSITIVE){
        EqualStringStatus equivelenceStatus = NULL;
        mem_alloc(equivelenceStatus, 1);
        equivelenceStatus->lengthDifferential = stringlen(s1) - stringlen(s2);
        if(equivelenceStatus->lengthDifferential > 0){
            equivelenceStatus->message = stringcopy("First string is longer than second string");
            equivelenceStatus->equal = false;
            return equivelenceStatus;
        }//endif

        if(equivelenceStatus->lengthDifferential < 0){
            equivelenceStatus->message = stringcopy("Second string is longer than first string");
            equivelenceStatus->equal = false;
            return equivelenceStatus;
        }//endif

        equivelenceStatus->lengthDifferential = 0; 

        for_each(x, stringlen(s1)){
            if(s1[x] != s2[x]){
                equivelenceStatus->message = stringcopy("Strings differ: Check index to see at which index they differ");
                equivelenceStatus->equal = false;
                equivelenceStatus->index = x;
                return equivelenceStatus;
            }
        }//endfor
        equivelenceStatus->message = stringcopy("Strings are equal");
        equivelenceStatus->equal = true;
        equivelenceStatus->index = -1;
        return equivelenceStatus;
    }//endif

    else{
        EqualStringStatus equivelenceStatus = NULL;
        mem_alloc(equivelenceStatus, 1);
        equivelenceStatus->lengthDifferential = stringlen(s1) - stringlen(s2);
        if(equivelenceStatus->lengthDifferential > 0){
            equivelenceStatus->index = -2;
            equivelenceStatus->message = stringcopy("First string is longer than second string");
            equivelenceStatus->equal = false;
            return equivelenceStatus;
        }//endif
        if(equivelenceStatus->lengthDifferential < 0){
            equivelenceStatus->index = -2;
            equivelenceStatus->message = stringcopy("Second string is longer than first string");
            equivelenceStatus->equal = false;
            return equivelenceStatus;
        }//endif
        equivelenceStatus->lengthDifferential = 0; 
        char* temp1 = stringcopy(s1);
        char* temp2 = stringcopy(s2);
        for_each(x, stringlen(temp1)){
            char c = temp1[x];
            char c2 = temp2[x];
            if(IS_UPPER(c)){
                c = c+32;
            }
            if(IS_UPPER(c2)){
                c2 = c2+32;
            }
            replace_in_string(temp1, c, x);
            replace_in_string(temp2, c2, x);
        }//endfor
        for_each(x, stringlen(temp1)){
            if(temp1[x] != temp2[x]){
                equivelenceStatus->message = stringcopy("Strings differ: Check index to see at which index they differ");
                equivelenceStatus->equal = false;
                equivelenceStatus->index = x;
                PR("%s %s\n", temp1, temp2);
                destroystring(temp1);
                destroystring(temp2);
                return equivelenceStatus;
            }
        }//endfor
        equivelenceStatus->message = stringcopy("Strings are equal");
        equivelenceStatus->equal = true;
        equivelenceStatus->index = -1;
        destroystring(temp1);
        destroystring(temp2);
        return equivelenceStatus;
    }//endelse
}


                          /*****************Accessors*****************/
int stringlen(String s)
{
    if(s == NULL)return -1;

    int i = 0;
    while(s[i] != '\0'){
      i++;
    }
    return i;
}

char getch(String s, int n)
{
    if(badstring(s))return -1;
    if(n < 1 || n > stringlen(s))return -1;
    char c = s[n-1];
    return c;
}



int* indecies_of_char(String s, char c)
{
    assert(badstring(s)==false);
    int* indecies = NULL;
    int mem_size = sizeof(int);
    int i = 0;
    int count = 0;
    while(s[i] != '\0'){
        if(s[i] == c){
            count++;
            indecies = (int*)realloc(indecies, mem_size*count);
            indecies[count-1] = i;
        }
        i++;
    }
    count++;
    indecies = realloc(indecies, mem_size*count);
    indecies[count-1] = -1;
    return indecies;
}


int* indecies_of_string(Strings a, String s)
{

    assert(badstring(s)==false);
    assert(a != NULL);
    int* indecies = NULL;
    int mem_size = sizeof(int);
    int i = 0;
    int count = 0;
    while(a[i] != NULL){
        if(strncmp(a[i], s, strlen(s)+1)==0){
            count++;
            indecies = (int*)realloc(indecies, mem_size*count);
            indecies[count-1] = i;
        }
        i++;
    }
    count++;
    indecies = realloc(indecies, mem_size*count);
    indecies[count-1] = -1;
    return indecies;

}


/****FIX ME: CREATE A FUNCTION TO GET THE STATUS OF A STRING****/
