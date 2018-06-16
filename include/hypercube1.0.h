

#ifndef _HYPERCUBE_
#define _HYPERCUBE_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DynamicString.h"
#include "utilities.h"
#include "HashMap.h"

#define destroy_vertex(myarg) destroy_vertex_real(&myarg)

#define SEVEN false
#define NINE true

enum vs{DEAD_END, SEED};
typedef enum vs VertexStatus;

struct hc{
    String string;
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

CubeVertex new_vertex(String s);





							/***********SETTERS*************/

							/**
							 * Fucntion to set the neighbors of a CubeVertex
							 * */
Strings generate_neighbors(String v);


							/*********ACCESSORS*********/
unsigned long n_choose_k(int n, int k);




							
							/*****PRINTERS*********/
String print_vertex(AnyData v);

void print_path(void);



						/***********DESTROYERS*************/

void destroy_vertex_real(AnyData* d);

void destroy_vertex_update(AnyData d);


						/**************CLONERS***********/

CubeVertex clone_vertext(CubeVertex v);


						/**********BACK TRACKING ALGORITHM************/
void back_track(HashMap map, String binaryString, int n, char bit, int maxDepth);

void set_bit(Strings s, int n);



						/****************MODULE****************/

void generate_hamiltonian_paths(int n, int k);


						/************MODIFIERS DYK_WORD*************/

String zero_dyk_word(String s);

String one_dyk_word(String s);

Strings cyclic_decomposition(String s);



					/******************TEST FUNCTION FOR N = 7**************/

Strings test_7( void );

				/******TEST FOR N = 9*****/

void back_track_nine(HashMap map, String binaryString, Strings startingSet, char bit, int n, int maxLevel);

Strings test_9( void );

bool is_necklace(String set, String s);

#endif

