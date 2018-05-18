
#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "HashMap.h"
#include "utilities.h"
#include <assert.h>
#include <math.h>







                                            /*****ENCAPSULATED FUNCTIONS AND VARIABLES NOT DIRECTLY 
                                                   AVAILABLE TO API USERS*********/

 unsigned long hash(HashMap map, char* key)
{
    /****FIX ME: COME UP WITH A BETTER HASHING ALGORITHM****/
    /*unsigned long hash = 0;
    int n = stringtoint(key);
    if(n < map->tableSize){
        hash = map->tableSize % n;
        return hash;
    }
    else{
        hash = n % map->tableSize;
        return hash;
    }*/
    unsigned long hash = 0;
     int power = 0;
     for(int i = (stringlen(key) -1); i >= 0; i--){
     	if(key[i] == '1'){
	        power = (stringlen(key) -1) - i;
    	    hash += pow(2.0, power);
	    }
     }
     return hash;
    
}


static Node new_empty_node(void)
{
    Node newNode = (Node)calloc(1, sizeof(HashElement));
    newNode->data = NULL;
    newNode->key = NULL;
    newNode->inUse = 0;
    return newNode;
}

static ErrorCode destroy_node_real(Node* n)
{
    if(n == NULL){
        return DNE;
    }
    if(*n == NULL){
        return DNE;
    }
    
    destroystring((*n)->key);
    free(*n);
    *n = NULL;
    return OK;
}

unsigned long get_data_index(HashMap map, char* key)
{
    assert(map != NULL);
    assert(map->table != NULL);
    assert(badstring(key) == false);
    unsigned long index = hash(map, key);
    assert(index < map->tableSize);
    unsigned long start = index;
    if(map->table[index]->key == NULL)return -1;
    if(strncmp(key, map->table[index]->key, strlen(key+1))==0)return index;

    assert(map->table[index]!=NULL);
    assert(map->table[index]->key != NULL);
    assert(map->table[index]->data != NULL);

    //while
    while(strncmp(key, map->table[index]->key, strlen(key)+1)!=0){
        index++;
        //if
        if(index == (map->tableSize)){
            index = 0;
        }//enidif

        //if
        if(index == start){
            return -1;
        }//endif
        Node temp = map->table[index];
        if(temp->inUse == 1){
            if(strncmp(key, temp->key, strlen(key+1))==0)
                return index;
        }else{
            continue;
        }

    }//endwhile
    return index;
}



static unsigned long table_size[] = {
    
     7, 13, 31, 61, 127, 251, 509, 1021, 2039, 4093, 8191,
     16381, 32749, 65521, 131071, 
     
     262143, 524287, 1048575, 2097151, 4194303, 8388607,
     16777211, 33554431, 67108863, 134217727, 268435455,
     536870911, 1073741823, 2147483647  
};





                        /*****
                         * Following Code is Open source API code for HashMap.h
                         * ***Comments on the functionality of the functions can be found 
                         * ***in HashMap.h
                         * ********/



                                    /***CONSTRUCTORS*****/






HashMap new_hashmap(print_func p, delete_func d, unsigned int sizeOfTable)
{
    int max = sizeof(table_size)/sizeof(table_size[0]);
    int index = 0;
    assert(sizeOfTable >= 1);
    if(p == NULL)return NULL;
    if(d == NULL)return NULL;
    HashMap map = (HashMap)calloc(1, sizeof(Map));
    assert(map != NULL);
    if(sizeOfTable >= max){
        index = max-1;
        map->table = (Nodes)calloc(table_size[index], sizeof(Node));
    }else{
        index = sizeOfTable-1;
        map->table = (Nodes)calloc(table_size[index], sizeof(Node));
    }
    assert(map->table != NULL);
    for(int i = 0; i < table_size[index]; i++){
        map->table[i] = new_empty_node();
    }
    map->size = 0;
    map->tableSize = table_size[index];
    map->printData = p;
    map->deleteData = d;
    return map;
}


Node new_node(char* k, AnyData d)
{
    Node newNode = (Node)calloc(1, sizeof(HashElement));
    newNode->key = stringcopy(k);
    newNode->data = d;
    newNode->inUse = 1;
    return newNode;
}



                             /****ACCESSORS****/

ErrorCode get_hashmap(HashMap map, char* key, AnyData* value){
    assert(map != NULL);
    assert(badstring(key) == false);
    assert(value != NULL);
    ErrorCode status;
    unsigned long index = get_data_index(map, key);
    if(index == -1){
        status = DNF;
        return status;
    }
    *value = map->table[index]->data;
    if(*value == NULL)return DNE;
    AnyData t = *value;
    char* s = map->printData(t);
    printf("%s\n", s);
    destroystring(s);
    status = OK;
    return status;
}

unsigned long current_size_hashmap(HashMap map)
{
    if(map == NULL)return -1;
    unsigned long size = map->size;
    return size;
}
                        
unsigned long table_size_hashmap(HashMap map)
{
    if(map == NULL)return -1;
    unsigned long tableSize = map->tableSize;
    return tableSize;
}


                            /*********SETTERS***********/

ErrorCode put_hashmap(HashMap map, char* key, AnyData value)
{
    assert(map != NULL);
    if(badstring(key))return DNE;
    if(value == NULL)return DNE;
    if(map->size >= map->tableSize)return FULL;
    unsigned long index = hash(map, key);
    assert(index < map->tableSize);
    ErrorCode status;
    status = iterate_hashmap(map, &index);
    if(status == OOM){
        return status;
    }
    Node temp = (Node)map->table[index];
    destroy_node(temp);
   Node newNode = new_node(key, value);
    map->table[index] = newNode;
    map->size++;
    return status;

}





                            /************DESTROYERS************/
ErrorCode remove_from_hashmap(HashMap map, char* key)
{
    assert(map != NULL);
    assert(badstring(key) == false);
    unsigned long index = get_data_index(map, key);
    if(index == -1)return DNE;
    map->deleteData(map->table[index]->data);
    map->table[index]->data = NULL;
    map->table[index]->inUse = 0;
    destroystring(map->table[index]->key); 
    return OK;

}

ErrorCode destroy_hashmap_real(HashMap* map)
{

    ErrorCode code;
    HashMap m = *map;
    for(int i = 0; i < (m)->tableSize; i++){
        Node temp = (m)->table[i];
        if(temp->inUse == 0){
            destroy_node((*map)->table[i]);
        }
        else{
            m->deleteData((*map)->table[i]->data);
            destroy_node((*map)->table[i]);
        }
    }
    (*map)->tableSize = 0;
    (*map)->size = 0;
    free((*map)->table);
    (*map)->table = NULL;
    free(*map);
    *map = NULL;
    code = OK;
    return code;
}



                                /***************ITERATORS**************/

ErrorCode iterate_hashmap(HashMap map, unsigned long* start)
{
    Iterator itr;
    unsigned long index = *start;
    itr.current = (Node)map->table[index];
    Node temp = (Node)itr.current;
    unsigned long beginning = index;
    while(temp->inUse != 0){
        (index)++;
        if(index >= map->tableSize){
            index = 0;
        }
        if(index == beginning)return OOM;
        itr.current = (Node)map->table[index];
        temp = (Node)itr.current;
    }
    return OK;
}




                            /******************PRINTERS*************/
char* map_to_string(HashMap map)
{
     assert(map != NULL);
     assert(map->table != NULL);
     Iterator itr;
     itr.current = NULL;
     char* printer = NULL;
     for(int i = 0; i < map->tableSize; i++)
     {
         itr.current = map->table[i];
         Node n = (Node)itr.current;
         if(n->inUse == 1){
            char* k = stringcopy("KEY: VALUE: ");
            printer = stringcat(printer, k);
            char* temp = map->printData(n->data);
            printer = stringcat(printer, temp);
            printer = stringcat(printer, "\n\n");
            destroystring(temp);
            destroystring(k);
         }
     } 
     return printer;

}

void print_error_code(ErrorCode code)
{
	if(code == OK)
		printf("Status OK\n");
	if(code == OOM)
		printf("Status Out of Memory\n");
	if(code == DNF)
		printf("Status Data not found\n");
	if(code == DNE)
		printf("Status Data does not exist\n");
	if(code == FULL)
		printf("Status Table Full\n");
}