
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "hypercube.h"
#include <stdbool.h>
#include <assert.h>
#include "..//..//String/include/String.h"



void swap_char(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

char* next_binary_string(char* s)
{
    char* nextString = stringcopy(s);
    printf("Seed is %s\n", nextString);
    int start = 0;
    int leftMost1 = 0;
    int rightMost0 = 0;
    int end = stringlen(nextString) - 1;
    int i = end;
    int j = 0;
    int k = 0;
    while(nextString[i] != '1'){
        if(i == 0)break;
        i--;
    }
    start = i;
    for(j = start; j>=0; j--){
        if(s[j] == '0')
            break;
    }
    rightMost0 = j;
    nextString[rightMost0] = '1';
    leftMost1 = rightMost0 +1;
    nextString[leftMost1] = '0';
    int count = 0;
    for(k = end; k > leftMost1; k--){
        if(nextString[k] == '0'){
            nextString[k] = '1';
            count++;
        }
    }
    for(int i = 1; i <= count; i++){
        nextString[leftMost1+i] = '0';
    }

   /* unsigned long m = n_choose_k(n, k);
    printf("m is %ld\n", m);
    unsigned long size = 2*(m+1);
    CubeVertecies c = (CubeVertecies)calloc(size, sizeof(CubeVertex));
    char* sd = stringcopy(seed->string);
    create_combinations(m, 0, sd, c);
    destroystring(sd);
    //arr[m] = last index in array
    CubeVertecies combinations = (CubeVertecies)calloc((m+1), sizeof(CubeVertex));
    for(int i = 0; i < (m); i++){
        char* s = print_vertex(c[i]);
        printf("%s\n", s);        
    }
    combinations[m] = NULL;
    return combinations;*/
    printf("Next String is %s\n", nextString);
    return nextString;

}






unsigned long n_choose_k(int n, int k)
{
    unsigned long denominator = 1;
    unsigned long numerator = 1;
    unsigned long nChooseK = 1;
    unsigned long inGroup = n-k;
    unsigned long outGroup = n-inGroup;
    for(int i = n; i >=1; i--)
        numerator = numerator*i;
    
    for(int i = inGroup; i >= 1; i--)
        denominator = denominator*i;
    for(int i = outGroup; i >= 1; i--)
        denominator = denominator*i;
    
    nChooseK = numerator/denominator;
    return nChooseK;

}


                    /****CONSTRUCTORS****/

CubeVertex generate_seed(int n, int k)
{
    assert(n >= k);
    CubeVertex seed = (CubeVertex)calloc(1, sizeof(*seed));
    assert(seed != NULL);
    seed->string = createvoidstring();
    assert(seed->string != NULL);
    if(n == k){
        for(int i = 0; i < n; i++)
            seed->string[i] = '1';
    }else{
        int x = n - k;
        for(int i = 0; i < x; i++)
            seed->string[i] = '0';
        for(int i = x; i < n; i++)
            seed->string[i] = '1';
    }
    seed->len = n;
    seed->kOnes = k;
    seed->visited = false;
    seed->deadEnd = false;
    seed->seed = true;
    seed->numberOfNeighbors = k+1;
    seed->neighbors = (CubeVertecies)calloc((k+2), sizeof(CubeVertex));
    assert(seed->neighbors != NULL);
    for(int i = 0; i < k+2; i++){
        seed->neighbors[i] = NULL;
    }
    return seed;
}


CubeVertex new_vertex(char* s)
{
    assert(badstring(s)==false);
    CubeVertex newVertex = (CubeVertex)calloc(1, sizeof(*newVertex));
    assert(newVertex != NULL);
    newVertex->string = stringcopy(s);
    newVertex->kOnes = 0;
    for(int i = 0; i < stringlen(s); i++)
        if(s[i] == '1')
            newVertex->kOnes += 1;

    newVertex->len = stringlen(s);
    newVertex->visited = false;
    newVertex->deadEnd = false;
    newVertex->numberOfNeighbors = stringlen(s);
    newVertex->seed = false;

    newVertex->neighbors = (CubeVertecies)calloc(newVertex->numberOfNeighbors+1, sizeof(CubeVertex));
    for(int i = 0; i <= newVertex->numberOfNeighbors; i++){
        newVertex->neighbors[i] = NULL;
    }

    return newVertex; 
}

CubeVertecies generate_vertecies(int n, int k)
{
     
     char* seed = stringcopy("00111");
     char* nextOne = NULL;
    for(int i = 0; i < 20; i++){
     if(i == 0){
        nextOne = next_binary_string(seed);
     }else{
         nextOne = next_binary_string(nextOne);
     }
     printf("NEXT ONE %s\n", nextOne);
    }
     destroystring(seed);
     return NULL;
}







                                           /***********PRINTERS*******/
char* print_vertex(CubeVertex v)
{
    assert(v != NULL);
    char* printer = NULL;
    assert(badstring(v->string)==false);
    printer = stringcopy("String Value: ");
    char* s1 = stringcopy(v->string);
    printer = stringcat(printer, s1);
    destroystring(s1);
    printer = stringcat(printer, "Neighbors: ");
    int i = 0;
    while(v->neighbors[i] != NULL){
        printer = stringcat(printer, v->neighbors[i]->string);
        printer = stringcat(printer, " ");
        i++;
    }
    if(v->deadEnd == true){
        printer = stringcat(printer, " DEAD END");
    }
    if(v->seed == true){
        printer = stringcat(printer, " SEED");
    }
    if(v->visited == true){
        printer = stringcat(printer, " Visitied");
    }else{
       printer =  stringcat(printer, " Not Visited");
    }
    return printer;

}



                                                    /**********DESTROYERS**********/

void destroy_vertex_real(CubeVertex* d)
{
    assert(d != NULL);
    if(*d == NULL)return;
    destroystring((*d)->string);
    //FIX ME LATER
    int i = 0;
    while((*d)->neighbors[i] != NULL){
        free((*d)->neighbors[i]);
    }
    free((*d)->neighbors);
    free(*d);
    *d = NULL;

}