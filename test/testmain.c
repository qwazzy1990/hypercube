#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "String.h"
#include "utilities.h"
#include "HashMap.h"
#include "hypercube1.0.h"


bool debug1 = false;
bool debug2 = false;
bool debug3  = false;
bool debug4 = true;

unsigned long hashes[100] = {-1};

void delete_vertex(AnyData v)
{
   CubeVertex v1 = (CubeVertex)(v);
   destroystring(v1->string);
   free(v1->neighbors);
   free(v1);
   v1 = NULL;

}
int main(int argc, char* argv[])
{
  
  if(debug1){
    /*CubeVertex v1 = generate_seed(5, 2);
    char* printer = print_vertex(v1);
    printf("printer is %s\n", printer);
    destroystring(printer);
    destroy_vertex(v1);*/
    CubeVertecies v =  generate_vertecies(3, 1);
    int i = 0;
    while(v[i] != NULL){
      char* s = print_vertex(v[i]);
      printf("here %s\n", s);
    }
  }
  if(debug2){
    CubeVertecies v = generate_vertecies(5, 3);
    for(int i = 0; i < 10; i++){
      char* printer = print_vertex(v[i]);
      printf("vertex |%d| %s\n", i, printer);
      destroystring(printer);
    }
  }


  if(debug3){
      HashMap map = new_hashmap(print_vertex, delete_vertex, 7);
      
      CubeVertecies k = generate_vertecies(5, 2);
      CubeVertecies l = generate_vertecies(5, 3);
      ErrorCode mapStatus = 0;
    
      for(int i = 0; i < 10; i++)
      {
         mapStatus = put_hashmap(map, k[i]->string, k[i]);
         print_error_code(mapStatus);
      }
      for(int i = 0; i < 10; i++){
        mapStatus = put_hashmap(map, l[i]->string, l[i]);
        print_error_code(mapStatus);
      }
      int count = 0;
      for(int i = 0; i < 20; i++){
        if(i < 10){
          hashes[i] = hash(map, k[i]->string);
          printf("%ld ", hashes[i]);
        }
        else{ 
          hashes[i] = hash(map, l[count]->string);
          printf("%ld", hashes[i]);
          count++;
        }
      }
      free(k);
      free(l);
      printf("\n");
      destroy_hashmap(map);

  }
  if(debug4){
    char** neighbors = generate_neighbors("00101");
    int i = 0;
    while(neighbors[i] != NULL){
      printf("%s\n", neighbors[i]);
      destroystring(neighbors[i]);
      i++;
    }
    destroystringarray(neighbors);
    
  }
  
  return 0;
}
