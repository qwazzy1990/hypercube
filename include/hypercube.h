

#ifndef _HYPERCUBE_
#define _HYPERCUBE_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "..//..//String/include/String.h"
#include "..//..//utilities/include/utilities.h"


#define destroy_vertex(myarg) destroy_vertex_real(&myarg)

enum vs{OK, DEAD_END, SEED, DNE, DNF};
typedef enum vs VertexStatus;

struct hc{
    char* string;
    struct hc** neighbors;
    bool visited;
	bool seed;
	bool deadEnd;
	int len;
	int kOnes;
	int numberOfNeighbors;
};typedef struct hc VertexElement;


typedef VertexElement* CubeVertex;
typedef CubeVertex* CubeVertecies;



							/**********CONSTRUCTORS***********/

	/**
	 *Function to generate a seed to create the permutations
	 *Input: The dimensions of the hyper cube vertex. N = length of binary string representing vertex = 
	 * dimensions of the Cube. K = Number of 1s in binary string
	 **/
CubeVertex generate_seed(int n, int k);



		/**
		 * Function to generate all HyperCube Vertecies of length N with exactly K 1s in them
		 * */
CubeVertecies generate_vertecies(int n, int k);

CubeVertex new_vertex(char* s);





							/***********SETTERS*************/

							/**
							 * Fucntion to set the neighbors of a CubeVertex
							 * */
VertexStatus set_neighbors(CubeVertex v);





							
							/*****PRINTERS*********/
char* print_vertex(CubeVertex v);



						/***********DESTROYERS*************/

void destroy_vertex_real(CubeVertex* d);
#endif

