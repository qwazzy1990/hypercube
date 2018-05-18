
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/hypercube1.0.h"
#include <stdbool.h>
#include <assert.h>
#include "String.h"
//#include "utilities.h"
//#include "HashMap.h"

void swap_char(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

char* next_binary_string(char* s)
{
    char* nextString = stringcopy(s);
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

   
    return nextString;

}



char* previous_neighbor(char* s)
{
    //FIX ME
    int numOnes = 0;
    int numZeros = 0;
    for(int i = 0; i < stringlen(s); i++){
        if(s[i] == '1'){
            numOnes++;
        }else{
            numZeros++;
        }
    }        
    if(numOnes > numZeros){
        //flip rightmost one
    }else{

    }
    return NULL;
}


char* next_neighbor(char* s)
{
    //FIX ME
    int numZeors = 0; 
    int numOnes = 0;
    char* neighbor = stringcopy(s);
    for(int i = 0; i < stringlen(s); i++){
        if(s[i] == '1'){
            numOnes++;
        }else{
            numZeros++;
        }
    }
    if(numZeors > numOnes){
        for(int i = stringlen(neighbor)-1; i >= 0; i--){
            if(neighbor[i] == '0'){
                neighbor[i] = '1';
                return neighbor;
            }
        }
    }
    else{
        //FIX ME
    }

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
     CubeVertecies vertecies = (CubeVertecies)calloc((n_choose_k(n, k)+1), sizeof(*vertecies));
     char* nextOne = NULL;
     int i = 0;
     unsigned long numberOfVertecies = n_choose_k(n, k);
    for( i = 0; i < numberOfVertecies; i++){
        if(i == 0){
            vertecies[i] = generate_seed(n, k);
        }else{
            char* seed = vertecies[i-1]->string;
            nextOne = next_binary_string(seed);
            vertecies[i] = new_vertex(nextOne);
            destroystring(nextOne);
        }
    }
    vertecies[i] = NULL;
     return vertecies;
}







                                           /***********PRINTERS*******/
char* print_vertex(AnyData v)
{
    assert(v != NULL);
    char* printer = NULL;
    CubeVertex v1 = (CubeVertex)v;
    assert(badstring(v1->string)==false);
    printer = stringcopy("String Value: ");
    char* s1 = stringcopy(v1->string);
    printer = stringcat(printer, s1);
    destroystring(s1);
    printer = stringcat(printer, "Neighbors: ");
    int i = 0;
    while(v1->neighbors[i] != NULL){
        printer = stringcat(printer, v1->neighbors[i]->string);
        printer = stringcat(printer, " ");
        i++;
    }
    if(v1->deadEnd == true){
        printer = stringcat(printer, " DEAD END");
    }
    if(v1->seed == true){
        printer = stringcat(printer, " SEED");
    }
    if(v1->visited == true){
        printer = stringcat(printer, " Visitied");
    }else{
       printer =  stringcat(printer, " Not Visited");
    }
    return printer;

}



                                                    /**********DESTROYERS**********/

void destroy_vertex_real(AnyData* d)
{
    assert(d != NULL);
    if(*d == NULL)return;
    CubeVertex d1 = (CubeVertex)(*d);
    destroystring((d1)->string);
    //FIX ME LATER
    int i = 0;
    while((d1)->neighbors[i] != NULL){
        free((d1)->neighbors[i]);
    }
    free((d1)->neighbors);
    free(*d);
    *d = NULL;

}




                                                    /************CLONERS***********/
CubeVertex clone_vertext(CubeVertex v)
{
    CubeVertex clone = (CubeVertex)calloc(1, sizeof(*clone));
    clone->string = stringcopy(v->string);
    clone->visited = v->visited;
    clone->seed = v->seed;
    clone->deadEnd = v->deadEnd;
    clone->len = v->len;
    clone->numberOfNeighbors = v->numberOfNeighbors;
    return clone;
    //FIX ME: FIGURE OUT HOW TO DO THE NEIGHBORS AND SHIT

}



                            /**************BACK TRACKING ALGORITHM**********/

//FIX ME
char** generate_neighbors(char* s)
{
    int numOnes = 0;
    int numZeros = 0;
    for(int i = 0; i < stringlen(s); i++){
        if(s[i] == '1'){
            numOnes++;
        }else{
            numZeros++;
        }
    }
    char** neighbors = NULL;
    int count = 0;
    char* temp = NULL;
    if(numOnes > numZeros){
        neighbors = (char**)calloc(numOnes+1, sizeof(char*));
        temp = stringcopy(s);
        for(int i = 0; i < stringlen(temp); i++){
            if(temp[i]=='1'){
                temp[i] = '0';
                neighbors[count] = stringcopy(temp);
                temp[i] = '1';
                count++;
            }
        }
        neighbors[count] = NULL;
    }else{
        neighbors = (char**)calloc(numZeros+1, sizeof(char*));
        temp = stringcopy(s);
        for(int i = 0; i < stringlen(temp); i++){
            if(temp[i]=='0'){
                temp[i] = '1';
                neighbors[count] = stringcopy(temp);
                temp[i] = '0';
                count++;
            }
        }
        neighbors[count] = NULL;
    }
    destroystring(temp);
    return neighbors;
}


//FIX ME
void back_track(HashMap map, char* key, int currentLevel, int maxDepth)
{
    if(currentLevel == maxDepth){
        char** neighbors = generate_neighbors(key);
        int i = 0;
        while(neighbors[i] != NULL){
            unsigned long h = hash(map, neighbors[i]);
            CubeVertex v = (CubeVertex)map->table[h]->data;
            if(v->seed == true){
                printf("Found path\n");
                return;
            }
            i++;
        }
    }
    else{
        char** neighbors = generate_neighbors(key);
        int i = 0;
        while(neighbors[i] != NULL){
            unsigned long h = hash(map, neighbors[i]);
            CubeVertex v = (CubeVertex)map->table[h]->data;
            if((v->visited == false) && (v->deadEnd == false)){
                CubeVertex temp = (CubeVertex)map->table[h];
                temp->visited = true;
                back_track(map, neighbors[i], currentLevel+1, maxDepth);
                return;
            }
            i++;
        }
        unsigned long h = hash(map, key);
        CubeVertex deadend = (CubeVertex)map->table[h];
        deadend->deadEnd = true;

    }

}