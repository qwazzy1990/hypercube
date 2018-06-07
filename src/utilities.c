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
