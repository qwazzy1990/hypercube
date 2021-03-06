#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "DynamicString.h"
#include "utilities.h"
#include "HashMap.h"
#include "hypercube1.0.h"
#include "StringBitPosition.h"


bool debug1 = false;
bool debug2 = false;
bool debug3  = false;
bool debug4 = false;
bool debug5 = false;
bool debug6 = false;
bool debug7 = false;
bool debug9 = false;
bool debug10 = true;

//github why
//plase
void delete_vertex(AnyData v)
{
   CubeVertex v1 = (CubeVertex)(v);
   destroystring(v1->string);
   free(v1->neighbors);
   free(v1);
   v1 = NULL;

}
int main(int argc, String argv[])
{
  
  if(debug1){
    /*CubeVertex v1 = generate_seed(5, 2);
    String printer = print_vertex(v1);
    printf("printer is %s\n", printer);
    destroystring(printer);
    destroy_vertex(v1);*/
    CubeVertecies v =  generate_vertecies(3, 1);
    int i = 0;
    while(v[i] != NULL){
      String s = print_vertex(v[i]);
      printf("vertex %s\n", s);
      delete_vertex(v[i]);
      destroystring(s);
      i++;
    }
    free(v);
  }
  if(debug2){
    CubeVertecies v = generate_vertecies(5, 3);
    for(int i = 0; i < 10; i++){
      String printer = print_vertex(v[i]);
      printf("vertex |%d| %s\n", i, printer);
      destroystring(printer);
    }
  }


  if(debug3){
      HashMap map = new_hashmap(print_vertex, delete_vertex, 7);
      
      CubeVertecies k = generate_vertecies(5, 2);
      CubeVertecies l = generate_vertecies(5, 3);
      ErrorCode mapStatus = 0;
    
      foreach(x, 10)
      {
         mapStatus = put_hashmap(map, k[x]->string, k[x]);
         print_error_code(mapStatus);
      }
      foreach(x, 10){
        mapStatus = put_hashmap(map, l[x]->string, l[x]);
        print_error_code(mapStatus);
      }
      printf("\n");
      CubeVertex temp = map->table[hash(map, "00111")]->data;
      temp->seed = false;
      String seed = stringcopy("00011");
      back_track(map, seed, 1, '0', 20);
      //free(k);
      //free(l);
      destroystring(seed);
      destroy_hashmap(map);
      free(k);
      free(l);

  }
  if(debug4){
    Strings neighbors = generate_neighbors("00101");
    int i = 0;
    while(neighbors[i] != NULL){
      printf("%s\n", neighbors[i]);
      destroystring(neighbors[i]);
      i++;
    }
    destroystringarray(neighbors);
    
  }
  if(debug5){
    
    //generate_hamiltonian_paths(5, 2);
    String temp = stringcopy("0100111");
    //String temp2 = stringcopy("00101");
    //temp = one_dyk_word(temp);
    //printf("%s\n", temp);
    //destroystring(temp);
    Strings cycle = cyclic_decomposition(temp);
    //Strings cycle2 = cyclic_decomposition(temp2);
    String printer = printstringarray(cycle);
    printer = stringcat(printer, "Cyclic Decomposition using Dyk Word\n");
    //printer = reversestring(printer);
    //String printer2 = printstringarray(cycle2);
    //printer = stringcat(printer, printer2);
    //destroystring(printer2);
    printf("%s\n", printer);

    destroystring(temp);
    //destroystring(temp2);
    //destroystringarray(cycle2);
    destroystringarray(cycle);
    destroystring(printer);
    
  }
  if(debug6){
    
    generate_hamiltonian_paths(7, 3);
  }
  if(debug7){
    Strings k = test_7();
    destroystringarray(k);
  }
  if(debug9){
     test_9();
  }
  if(debug10){
    StringBitContainer sbc = new_string_bit_container(5, dummy_print, dummy_delete, dummy_compare);

    new_object(Strings, path, 6);
    path[0] = stringcopy("0101010 3");
    path[1] = stringcopy("0111010 4");
    path[2] = stringcopy("0110010 1");
    path[3] = stringcopy("1110010 6");
    path[4] = stringcopy("1110000 4");
    path[5] = NULL;
    //printf("%s\n", path[4]);

    add_string_bit_pair(sbc, path, 1);
    String printer = print_string_bit_container(sbc);
    printf("%s\n", printer);
    clear(printer);
    /*ListNode tempNode = sbc->stringBitPositions[0]->bitPathPairs->head;
    BitPathPairs bbp = tempNode->data;
    printf("CHECK CHECK %d\n", bbp->bitNumber);
    //print_bit_path_pairs(sbc->stringBitPositions[0]->bitPathPairs);*/
    destroy_string_bit_container(sbc);
    destroystringarray(path);
  }
  return 0;
}
