#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "DynamicString.h"
#include "utilities.h"
#include "HashMap.h"
#include "hypercube1.0.h"


int main(int argc, char* argv[])
{
    fprintf(stdout, "%s", "Please enter an odd number\n");
    int userInput = 0;
    scanf("%d", &userInput);
    int n = userInput;
    int k = n/2;
    generate_hamiltonian_paths(n, k);
}