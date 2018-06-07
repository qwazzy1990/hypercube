#ifndef _HASH_MAP_
#define _HASH_MAP_

#include <stdbool.h>
#include "..//..//..//utilities/include/utilities.h"
#include "..//..//..//String/include/String.h"
#include <stdio.h>
#include <stdlib.h>





//ErrorCode codes for OK,  out of memory, full hash map and data not found
enum e{OK, OOM, FULL, DNF, DNE};
typedef enum e ErrorCode;

#define destroy_node(myarg) destroy_node_real(&myarg)
#define destroy_hashmap(myarg) destroy_hashmap_real(&myarg)

/**
 *struct to contain key
 *and data
 *
 **/
struct he{
    AnyData data;
    char* key;
    int inUse;
};typedef struct he HashElement;


/**
 *giving names to pointers of hashelement. Pointer to hash element is a Node
 *and pointers to pointers of hashelemnts. Pointer to a Node is Nodes. Used to create table
 * **/
typedef HashElement* Node;
typedef Node* Nodes;




/**
 * A HashMap containing the maximum table size
 * and the current size of the table
 * Also contains the data in the table
 * **/

struct hm{

   Nodes table;
   int tableSize;
   int size;
   PrintFunc printData;
   DeleteFunc deleteData;

};typedef struct hm Map;

/**
 *Giving name to a pointer to the map
 *Will only be using pointer to map
 * **/
typedef Map* HashMap;




		/**
		 * Function to create a Node for the HashMap
		 * The key must be valid and the data must be valid
		 * **/
Node new_node(char* k, AnyData d);


	/**
	 *Function to create a HashMap
	 *The HashMap is empty with exception to its size, 
	 print function and delete function
	 * **/
HashMap new_hashmap(PrintFunc p, DeleteFunc d, unsigned int table_size);


	/**
	 *Function to iterate through a HashMap.
	 *Will return 1 of 4 ErrorCode codes.
	 * **/
ErrorCode iterate_hashmap(HashMap map, unsigned long* start);


	/**
	 * Function to find a value in a HashMap
	 * Will return either OK or DNF if data not found
	 * Preconidtions: map must exist, the key must exist and the address of the value must exist
	 * Postconditions: dereferenced value = value in HashMap corresponding to key
	 * **/
ErrorCode get_hashmap(HashMap map, char* key, AnyData* value);



    /**
	 *Gets size to current size of HashMap
	 *Returns -1 if map does not exist
	 * **/
unsigned long current_size_hashmap(HashMap map);

unsigned long table_size_hashmap(HashMap map);

unsigned long hash(HashMap map, char* key);


	/**
	 * Function to put data in the hash map
	 * Returns OK or OOM
	 * **/
ErrorCode put_hashmap(HashMap map, char* key, AnyData value);




	/**
	 *Function to remove data from the map.
	 * Returns OK or DNF
	 * **/
ErrorCode remove_from_hashmap(HashMap map, char* key);

ErrorCode destroy_hashmap_real(HashMap* map);


							/**************PRINTERS******************/
	
			/**
			 * Function to return a string of all the data in the map
			 * For readability
			 * **/
char* map_to_string(HashMap map);

void print_error_code(ErrorCode code);


#endif
