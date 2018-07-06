#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "utilities.h"

void swap(void* a, void* b, SwapFunc s)
{
     s(a, b);
}

void swapInts(void* a, void* b)
{
    int temp = 0;
    int* first = (int*)(a);
    int* second = (int*)(b);
    temp = (*first);
    (*first) = (*second);
    (*second) = temp;

}



int compare(void* a, void* b, CompareFunc c)
{
  return c(a, b);
}


bool sameobject(void* a, void* b)
{
    if(a == b)return true;
    return false;
}




void remove_hard_return(char* s)
{
    assert(s != NULL);
    assert(strlen(s)>0);
    if(s[strlen(s)]=='\n')
        s[strlen(s)] = '\0';
}

int* test_clone(void* a)
{
    int* f = (int*)a;
   int* clone = (int*)calloc(1, sizeof(int));
    *clone = *f;
   return clone;
}



                        /******MEMORY ALLOCATERS*****/

void resize_real(AnyData* a, int size)
{
     size += 1000;
    *a = realloc(*a, size);
}

                        /******DESTROYERS****/

void clear_real(AnyData d)
{
    assert(d != NULL);
    void** delete = (void**)d;
    *delete = *((void**)(d));
    if(*delete == NULL){
        return;
    }
    free(*delete);
    *((void**)d) = NULL;
}

  /*********Dummy Functions****/

char* dummy_print(AnyData p){
     char* printer = calloc(100, sizeof(char));
     int* temp = (int*)p;
     sprintf(printer, "%d", *temp);
     printer = strcat(printer, "\n");
     return printer;
}

int dummy_compare(const void* a, const void* b)
{
    if(a == NULL)return -2;
    if(b == NULL)return -2;
    int* first = (int*)a;
    int* second = (int*)b;
    if(*first == *second)return 0;
    else if(*first < *second)return -1;
    else return 1;
}

void dummy_delete(AnyData d){
    clear(d);
}