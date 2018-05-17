#include <string.h>
#include <stdlib.h>
#include "hypercube.h"
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "..//..//String/include/String.h"
#include "..//..//utilities/include/utilities.h"

bool debug1 = false;
bool debug2 = true;
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
    
  }
  return 0;
}
