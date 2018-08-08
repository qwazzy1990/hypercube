
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "hypercube1.0.h"
#include <stdbool.h>
#include <assert.h>
#include "HashMap.h"
#include "DynamicString.h"
#include "utilities.h"
#include "Color.h"


bool DEBUG1 = false;
bool FBRFLAG = true;

//FILE* FP = NULL;

unsigned long globalCount = 0;

String path[100000] = {NULL};

unsigned long hashes[100] = {-1};

unsigned long finalBitRange = 0;

void swap_char(String a, String b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}


/********STATIC FUNCTIONS AND VARIABLES******/

static String next_binary_string(String s)
{
    String nextString = stringcopy(s);
    int start = 0;
    int leftMost1 = 0;
    int rightMost0 = 0;
    int end = stringlen(nextString) - 1;
    int i = end;
    int j = 0;
    int k = 0;
    while (nextString[i] != '1')
    {
        if (i == 0)
            break;
        i--;
    }
    start = i;
    for (j = start; j >= 0; j--)
    {
        if (s[j] == '0')
            break;
    }
    rightMost0 = j;
    nextString[rightMost0] = '1';
    leftMost1 = rightMost0 + 1;
    nextString[leftMost1] = '0';
    int count = 0;
    for (k = end; k > leftMost1; k--)
    {
        if (nextString[k] == '0')
        {
            nextString[k] = '1';
            count++;
        }
    }
    for (int i = 1; i <= count; i++)
    {
        nextString[leftMost1 + i] = '0';
    }

    return nextString;
}



unsigned long n_choose_k(int n, int k)
{
    unsigned long denominator = 1;
    unsigned long numerator = 1;
    unsigned long nChooseK = 1;
    unsigned long inGroup = n - k;
    unsigned long outGroup = n - inGroup;
    for (int i = n; i >= 1; i--)
        numerator = numerator * i;

    for (int i = inGroup; i >= 1; i--)
        denominator = denominator * i;
    for (int i = outGroup; i >= 1; i--)
        denominator = denominator * i;

    nChooseK = numerator / denominator;
    return nChooseK;
}


static long number_of_starting_strings(int n, int k){
    unsigned long numerator = 2*(n_choose_k(n, k));
    unsigned long denominator = n;
    long result = numerator/denominator;
    return result;
}

static long mid_bit_plus_one(int n){
    int d = n/2;
    d++;
    return d;
}

static unsigned long final_bit_range(int n)
{
    unsigned long result = 0;
    if(FBRFLAG == true){
        int numerator = n-2;
        int k = n/2;
        k--;
        numerator = 2*(n_choose_k(numerator, k));
        int denominator = n-2;
        result = numerator/denominator;
    }
    else{
        if(n == 3){
            return 1;
        }
        result = 2*final_bit_range(n-2);
    }

    return result;
}

static String generate_valid_next_string(String s)
{
    new_object(String, nextString, stringlen(s)+1);
    nextString[strlen(s)] = '\0';
    nextString[strlen(s)-1] = '0';
    int divPoint = strlen(s)/2;
    forall(strlen(s)-1){
        if(x < divPoint){
            nextString[x] = '0';
        }
        else{
            nextString[x] = '1';
        }
    }
    return nextString;
}

/****STATIC FUNCTIONS FOR DYK WORD****/
static bool next_index_dykword(char *s, int index, char bit)
{
    if (DEBUG1)
        printf("IND is %d\n", index);
    int q = 0;
    if (index == stringlen(s) - 1)
    {
        q = 0;
    }
    else
    {
        q = index + 1;
    }
    while (s[q] == '(' || s[q] == ')')
    {
        q++;
        if (q == stringlen(s))
        {
            q = 0;
        }
    }
    if (s[q] == bit)
    {
        return false;
    }
    else
    {
        return true;
    }
}

static int next_bit_dykword(char *s, int index, char bit)
{
    int i = index;
    if (i == strlen(s) - 1)
    {
        i = 0;
    }
    while (s[i] != bit)
    {
        //printf("i is %d\n", i);
        i++;
        if (i == strlen(s))
        {
            i = 0;
        }
    }
    return i;
}
static int dyk_word_0(char *s)
{
    if (DEBUG1)
        printf("Dyk word %s\n", s);
    int count = 0;
    int index = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(' || s[i] == ')')
        {
            count++;
        }
    }
    if (count >= strlen(s) - 1)
    {
        if (DEBUG1)
            printf("%s\n", s);
        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] == '0' || s[i] == '1')
            {
                index = i;
            }
        }
    }
    else
    {
        int t = 0;
        int q = 1;
        bool found = false;
        while (!found)
        {
            if (t == stringlen(s))
            {
                t = 0;
            }
            if (s[t] == '0')
            {
                bool v = next_index_dykword(s, t, '0');
                if (DEBUG1)
                    printf("V is %d\n", v);
                if (v == true)
                {
                    q = next_bit_dykword(s, t, '1');
                    if (DEBUG1)
                        printf("s at q is %c\n", s[q]);
                    if (DEBUG1)
                        printf("q is %d\n", q);
                    replace_in_string(s, '(', t);
                    replace_in_string(s, ')', q);
                    return dyk_word_0(s);
                    break;
                }
            }
            t++;
        }
    }
    return index;
}

static int dyk_word_1(char *s)
{
    if (DEBUG1)
        printf("Dyk word %s\n", s);
    int count = 0;
    int index = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(' || s[i] == ')')
        {
            count++;
        }
    }
    if (count >= strlen(s) - 1)
    {
        if (DEBUG1)
            printf("%s\n", s);
        for (int i = 0; i < strlen(s); i++)
        {
            if (s[i] == '0' || s[i] == '1')
            {
                index = i;
            }
        }
    }
    else
    {
        int t = 0;
        int q = 1;
        bool found = false;
        while (!found)
        {
            if (t == stringlen(s))
            {
                t = 0;
            }
            if (s[t] == '1')
            {
                bool v = next_index_dykword(s, t, '1');
                if (DEBUG1)
                    printf("V is %d\n", v);
                if (v == true)
                {
                    q = next_bit_dykword(s, t, '0');
                    if (DEBUG1)
                        printf("s at q is %c\n", s[q]);
                    if (DEBUG1)
                        printf("q is %d\n", q);
                    replace_in_string(s, '(', t);
                    replace_in_string(s, ')', q);
                    return dyk_word_1(s);
                    break;
                }
            }
            t++;
        }
    }
    return index;
}

static String shift_left_by_one(String s)
{
    String temp1 = NULL;
    String temp2 = NULL;
    temp1 = stringsegmentcopy(s, 2, stringlen(s));
    //P("temp 1 is %s\n", temp1);
    temp2 = stringsegmentcopy(s, 1, 1);
    //P("temp2 %s\n", temp2);
    String conc = stringcat(temp1, temp2);
    //P("Left shift string \n");
    destroystring(temp2);
    return conc;
}

static String inverse_and_reverse(String s)
{
    String temp1 = NULL;
    String temp2 = NULL;
    temp1 = stringcopy(s);
    forall(stringlen(temp1)){
        if(temp1[x] == '0'){
            temp1[x] = '1';
        }else{
            temp1[x] = '0';
        }
    }
    temp2 = reversestring(temp1);
    destroystring(temp1);
    return temp2;
}


/***** FUNCTION: TEST FOR N = 7*****/

Strings test_7(void)
{
    Strings firstTen = NULL;
    mem_alloc(firstTen, 1000);
    add_to_stringarray(firstTen, "0000111");
    add_to_stringarray(firstTen, "0100111");
    add_to_stringarray(firstTen, "0100101");
    add_to_stringarray(firstTen, "0101101");
    add_to_stringarray(firstTen, "0101100");
    add_to_stringarray(firstTen, "0111100");
    add_to_stringarray(firstTen, "0110100");
    add_to_stringarray(firstTen, "0110110");
    add_to_stringarray(firstTen, "0100110");
    add_to_stringarray(firstTen, "0101110");
    for (int count = 10; count < 70; count++)
    {
        firstTen[count] = shift_left_by_one(firstTen[count - 10]);
    }
    for (int x = 0; x < 70; x++)
    {
        if (x == 10)
        {
            printf("\n");
        }
        if (x < 9)
            printf("%s | %d|\n", firstTen[x], (x + 1));
        else
            printf("%s |%d|\n", firstTen[x], (x + 1));
    }
    for (int x = 0; x < 69; x++)
        for (int i = x + 1; i < 70; i++)
        {
            if (strcmp(firstTen[x], firstTen[i]) == 0)
            {
                printf("x is %d i is |%d| string is %s\n", x, i, firstTen[x]);
            }
        }

    return firstTen;
}

/*******TEST 9*******/

Strings test_9(void)
{
    new_object(Strings, SS, 1000);

    /***KNOWN FIRST 11***/
    add_to_stringarray(SS, "000001111");
    add_to_stringarray(SS, "100001111");
    add_to_stringarray(SS, "100001011");
    add_to_stringarray(SS, "110001011");
    add_to_stringarray(SS, "010001011");
    add_to_stringarray(SS, "011001011");
    add_to_stringarray(SS, "001001011");
    add_to_stringarray(SS, "101001011");
    add_to_stringarray(SS, "101000011");
    add_to_stringarray(SS, "101100011");
    add_to_stringarray(SS, "001100011");

    add_to_stringarray(SS, "011100011");
    add_to_stringarray(SS, "011000011");
    add_to_stringarray(SS, "011010011");
    add_to_stringarray(SS, "001010011");
    add_to_stringarray(SS, "101010011");
    add_to_stringarray(SS, "100010011");
    add_to_stringarray(SS, "100110011");
    add_to_stringarray(SS, "100100011");
    add_to_stringarray(SS, "100100111");
    add_to_stringarray(SS, "100100110");

    add_to_stringarray(SS, "101100110");
    add_to_stringarray(SS, "101100010");
    add_to_stringarray(SS, "101110010");
    add_to_stringarray(SS, "101010010");
    add_to_stringarray(SS, "101011010");
    add_to_stringarray(SS, "100011010");
    add_to_stringarray(SS, "100011110");
    foreach (28, 252)
        SS[x] = shift_left_by_one(SS[x - 28]);

    for (int i = 0; i < 251; i++)
    {
        for (int j = i + 1; j < 252; j++)
        {
            if (strcmp(SS[i], SS[j]) == 0)
            {
                printf("Duplicate Strings\n%s %d %s %d\n", SS[i], i, SS[j], j);
            }
        }
    }
    printf("PATH:\n\n");
    forall(252)
    {
        if ((x % 28) == 0)
            printf("\n\n");
        printf("%s |%d|\n", SS[x], (x + 1));
    }
    destroystringarray(SS);
    return NULL;
}

static bool check_necklace(Strings startingSet, String s)
{
    int i = 0;
    int n = stringlen(s);
    int k = n/2;
    int nn = number_of_starting_strings(n, k);
    while (i < nn)
    {
        if (startingSet[i] == NULL)
        {
            i++;
        }
        else
        {
            bool isNecklace = is_necklace(startingSet[i], s);
            if (isNecklace == true)
            {
                //printf("NECKLACES:\n%d %s %s\n\n", i+1, startingSet[i], s);
                return true;
            }
            else
                i++;
        }
    }
    return false;
}
bool is_necklace(String set, String s)
{
    String temp = stringcopy(s);
    forall(stringlen(temp))
    {
        if (strcmp(temp, set) == 0)
        {
            destroystring(temp);
            return true;
        }
        else
        {
            String t1 = stringsegmentcopy(temp, 2, stringlen(temp));
            String t2 = stringsegmentcopy(temp, 1, 1);
            t1 = stringcat(t1, t2);
            destroystring(temp);
            temp = stringcopy(t1);
            destroystring(t1);
            destroystring(t2);
        }
    }
    destroystring(temp);
    return false;
}


void back_track_nine(HashMap map, String binaryString, char bit, int n, int maxLevel)
{
    int i = 0;
   
    if (n > 1){
        if (check_necklace(path, binaryString)){
            return;
        }
    }
    String nextString = NULL;

    if (n == maxLevel)
    {
        int count = 0; 
        while(path[count] != NULL){
            count++;
        }
        if(count != maxLevel-1){
           return;
        }
        Strings neighbors = generate_neighbors(binaryString);
        int i = 0;
        nextString = generate_valid_next_string(binaryString);
        while (neighbors[i] != NULL)
        {
            if (strncmp(neighbors[i], nextString, strlen(nextString)) == 0)
            {
                add_to_stringarray(path, binaryString);
                doublefor(maxLevel)
                {
                    /*if(path[x] == NULL || path[y] == NULL){
                        break;
                    }*/
                    if (strcmp(path[x], path[y]) == 0)
                    {
                        remove_from_stringarray(path, path[x]);
                    }
                }
                String printer = printstringarray(path);
                //freopen("./bin/output.txt", "w", stdout);
                printf("PATH %ld FOUND \n\n", globalCount+1);
                printf("%s\n", printer);
                printf("\n");
                destroystringarray(neighbors);
                destroystring(printer);
                destroystring(nextString);
                for(int i = 0; i < maxLevel-1; i++){
                    for(int j = 0; j < stringlen(binaryString); j++){
                        if(path[i][j] != path[i+1][j]){
                            printf("%d\n", j+1);
                        }
                    }
                }
                printf("\n\n");
                for(int i = 1; i < maxLevel; i++){
                    destroystring(path[i]);
                }
                globalCount++;
                //destroystringarray(path);
                return;
            }
            else{
                i++;
            }
        }
        destroystringarray(neighbors);
        destroystring(nextString);
        /*for(int i = 1; i < maxLevel; i++){
            destroystring(path[i]);
        }*/
        return;
    }
    //else
    else
    {
        nextString = stringcopy(binaryString);
        CubeVertex currentVertex = (CubeVertex)map->table[hash(map, binaryString)]->data;

        //for
        for (i = 0; i < stringlen(binaryString); i++)
        {
            /***TESTING CONDITIONAL HYPTHESIS***/
            //if
            /*if (i == 1 && n > 1){
                continue;
            }//endif*/
            //if
            /*if (i == mid_bit_plus_one(strlen(binaryString))){
                continue;
            }//endif*/

            /***IF YOU WANT TO TEST ANOTHER HYPOTHESIS FOR THE LAST BIT THEN UNCOMMENT LINES 568 TO 573***/
            /*if(n == finalBitRange){
                i = stringlen(binaryString)-1;
            }
            if(n > finalBitRange && i == stringlen(binaryString)-1){
                continue;
            }*/
            //if
            if (binaryString[i] == bit)
            {
                set_bit(&nextString, i);
                CubeVertex temp = (CubeVertex)map->table[hash(map, nextString)]->data;
                if(temp == NULL)printf("Why\n");
                //if
                if (temp->visited == false)
                {
                    currentVertex->visited = true;
                    add_to_stringarray(path, currentVertex->string);
                    //if
                    if (bit == '1')
                    {
                        bit = '0';
                    }//endif

                    //else
                    else
                    {
                        bit = '1';
                    }//endelse

                    back_track_nine(map, nextString, bit, n + 1, maxLevel);

                    //if
                    if (bit == '1')
                    {
                        bit = '0';
                    }//endif

                    //else
                    else
                    {
                        bit = '1';
                    }//end else
                    currentVertex->visited = false;
                    remove_from_stringarray(path, currentVertex->string);
                    set_bit(&nextString, i);
                }//endif

                //else
                else
                {
                    set_bit(&nextString, i);
                    continue;
                }//endelse
            }//if
        }//end for
        //end else

        //if
        if (i == stringlen(binaryString))
        {
            if (DEBUG1)
                printf("DEAD END %s at level %d\n", binaryString, n);
            currentVertex->visited = false;
            currentVertex->deadEnd = true;
            remove_from_stringarray(path, currentVertex->string);
            destroystring(nextString);
        }//endif

        
    }//end else

}//end function

void back_track_two(HashMap map, String binaryString, char bit, int n, int maxLevel)
{
    String nextString = NULL;
    //if
    if(n > 14){
        if(check_necklace(path, binaryString)){
            return;
        }
    }//endif

    int i = 0;

    //if
    if(n == maxLevel){
        add_to_stringarray(path, binaryString);
        //int count = 0;
        //while
        /*while(path[count]!=NULL){
            count++;
        }//endwhile

        //if
        if(count != maxLevel){
            return;
        }//endif*/
        

        Strings printPath = stringarraycopy(path);
        int memSize = (2*maxLevel + 1);
        printPath = realloc(printPath, memSize*sizeof(String));
        int index = memSize -2;
        printPath[memSize-1] = NULL;

        //for
        forall(maxLevel){
            printPath[index] = inverse_and_reverse(printPath[x]);
            index--;
        }//endfor
        String checkOne = stringcopy(printPath[maxLevel-1]);
        String checkTwo = stringcopy(printPath[maxLevel]);
        int cc = 0;
        forall(stringlen(binaryString)){
            if(checkOne[x] != checkTwo[x]){
                cc++;
            }
        }
        destroystring(checkOne);
        destroystring(checkTwo);
        if(cc != 1){
            destroystringarray(printPath);
            destroystring(path[maxLevel - 1]);
            return;
        }


        
        //check necklace class
        doublefor(memSize-1){
            if(is_necklace(printPath[x], printPath[y])){
                //printf("%s and %s are in same necklace class\n\n\n", printPath[x], printPath[y]);
                destroystringarray(printPath);
                destroystring(path[maxLevel - 1]);
                return;
            }
        }//end check


        printf("Path %ld Found:\n", (globalCount+1));
        globalCount++;
        int current = 0;
        int next = 1;
        forall((2*maxLevel)-1){
            for(int k = 0; k < stringlen(binaryString); k++){
                if(printPath[current][k] != printPath[next][k]){
                    int br = k+1;
                    String str = tostring(INT, &br);
                    printPath[current] = realloc(printPath[current], 1000);
                    strcat(printPath[current], " ");
                    strcat(printPath[current], str);
                    clear(str);
                    break;
                }
            }
            current++;
            next++;
        }
        String leftRotation = shift_left_by_one(printPath[0]);
        forall(stringlen(binaryString)){
            if(printPath[current][x] != leftRotation[x]){
                    int br = x+1;
                    String str = tostring(INT, &br);
                    printPath[current] = realloc(printPath[current], 1000);
                    strcat(printPath[current], " ");
                    strcat(printPath[current], str);
                    clear(str);
                    break;

            }
        }
        destroystring(leftRotation);
       
        /*forall(memSize - 1){
            //if(x % 2 == 0 && x > 0)printf("\n");

            printf("%s\n", printPath[x]);
            if(x == ((2*maxLevel)/2)-1){
                printf("---------------------------------\n");
            }
        }*/
        print_path_two(printPath, 2*maxLevel);
        printf("\n");
        destroystringarray(printPath);
        destroystring(path[maxLevel - 1]);
        return;


    }//endif

    //else backtrack
   //else
    else
    {
        nextString = stringcopy(binaryString);
        CubeVertex currentVertex = (CubeVertex)map->table[hash(map, binaryString)]->data;

        //for
        for (i = 0; i < stringlen(binaryString); i++)
        {
            //if
            if (binaryString[i] == bit)
            {
                set_bit(&nextString, i);
                CubeVertex temp = (CubeVertex)map->table[hash(map, nextString)]->data;
                if(temp == NULL)printf("Why\n");
                //if
                if (temp->visited == false)
                {
                    currentVertex->visited = true;
                    add_to_stringarray(path, currentVertex->string);
                    //if
                    if (bit == '1')
                    {
                        bit = '0';
                    }//endif

                    //else
                    else
                    {
                        bit = '1';
                    }//endelse

                    back_track_two(map, nextString, bit, n + 1, maxLevel);

                    //if
                    if (bit == '1')
                    {
                        bit = '0';
                    }//endif

                    //else
                    else
                    {
                        bit = '1';
                    }//end else
                    currentVertex->visited = false;
                    remove_from_stringarray(path, currentVertex->string);
                    set_bit(&nextString, i);
                }//endif

                //else
                else
                {
                    set_bit(&nextString, i);
                    continue;
                }//endelse
            }//if
        }//end for
        //end else

        //if
        if (i == stringlen(binaryString))
        {
    
            currentVertex->visited = false;
            currentVertex->deadEnd = true;
            remove_from_stringarray(path, currentVertex->string);
            destroystring(nextString);
            return;
        }//endif

        
    }//end else

}

/****CONSTRUCTORS****/

CubeVertex generate_seed(int n, int k)
{
    assert(n >= k);
    CubeVertex seed = (CubeVertex)calloc(1, sizeof(*seed));
    assert(seed != NULL);
    seed->string = createvoidstring();
    assert(seed->string != NULL);
    if (n == k)
    {
        for (int i = 0; i < n; i++)
            seed->string[i] = '1';
    }
    else
    {
        int x = n - k;
        for (int i = 0; i < x; i++)
            seed->string[i] = '0';
        for (int i = x; i < n; i++)
            seed->string[i] = '1';
    }
    seed->len = n;
    seed->kOnes = k;
    seed->visited = false;
    seed->deadEnd = false;
    seed->seed = true;
    seed->numberOfNeighbors = k + 1;
    seed->neighbors = (CubeVertecies)calloc((k + 2), sizeof(CubeVertex));
    assert(seed->neighbors != NULL);
    for (int i = 0; i < k + 2; i++)
    {
        seed->neighbors[i] = NULL;
    }
    return seed;
}

CubeVertex new_vertex(String s)
{
    assert(badstring(s) == false);
    CubeVertex newVertex = (CubeVertex)calloc(1, sizeof(*newVertex));
    assert(newVertex != NULL);
    newVertex->string = stringcopy(s);
    newVertex->kOnes = 0;
    for (int i = 0; i < stringlen(s); i++)
        if (s[i] == '1')
            newVertex->kOnes += 1;

    newVertex->len = stringlen(s);
    newVertex->visited = false;
    newVertex->deadEnd = false;
    newVertex->numberOfNeighbors = stringlen(s);
    newVertex->seed = false;

    newVertex->neighbors = (CubeVertecies)calloc(newVertex->numberOfNeighbors + 1, sizeof(CubeVertex));
    for (int i = 0; i <= newVertex->numberOfNeighbors; i++)
    {
        newVertex->neighbors[i] = NULL;
    }

    return newVertex;
}

CubeVertecies generate_vertecies(int n, int k)
{
    CubeVertecies vertecies = (CubeVertecies)calloc((n_choose_k(n, k) + 1), sizeof(*vertecies));
    String nextOne = NULL;
    int i = 0;
    unsigned long numberOfVertecies = n_choose_k(n, k);
    for (i = 0; i < numberOfVertecies; i++)
    {
        if (i == 0)
        {
            vertecies[i] = generate_seed(n, k);
            if (DEBUG1)
                printf("%s\n", vertecies[i]->string);
        }
        else
        {
            String seed = vertecies[i - 1]->string;
            nextOne = next_binary_string(seed);
            vertecies[i] = new_vertex(nextOne);
            if (DEBUG1)
                printf("%s\n", vertecies[i]->string);
            destroystring(nextOne);
        }
    }
    vertecies[i] = NULL;
    return vertecies;
}

/***********PINTERS*******/
String print_vertex(AnyData v)
{
    assert(v != NULL);
    String printer = NULL;
    CubeVertex v1 = (CubeVertex)v;
    assert(badstring(v1->string) == false);
    printer = stringcopy("String Value: ");
    String s1 = stringcopy(v1->string);
    printer = stringcat(printer, s1);
    destroystring(s1);
    printer = stringcat(printer, "Neighbors: ");
    int i = 0;
    while (v1->neighbors[i] != NULL)
    {
        printer = stringcat(printer, v1->neighbors[i]->string);
        printer = stringcat(printer, " ");
        i++;
    }
    if (v1->deadEnd == true)
    {
        printer = stringcat(printer, " DEAD END");
    }
    if (v1->seed == true)
    {
        printer = stringcat(printer, " SEED");
    }
    if (v1->visited == true)
    {
        printer = stringcat(printer, " Visitied");
    }
    else
    {
        printer = stringcat(printer, " Not Visited");
    }
    return printer;
}

void print_path(void)
{
    printf("Here\n");
    int i = 0;
    while (path[i] != NULL)
    {
        printf("VERTEX |%s|\n", path[i]);
        i++;
    }
}

/**********DESTROYERS**********/

void destroy_vertex_real(AnyData *d)
{
    assert(d != NULL);
    if (*d == NULL)
        return;
    CubeVertex d1 = (CubeVertex)(*d);
    destroystring((d1)->string);
    //FIX ME LATER
    int i = 0;
    while ((d1)->neighbors[i] != NULL)
    {
        free((d1)->neighbors[i]);
    }
    free((d1)->neighbors);
    free(*d);
    *d = NULL;
}

void destroy_vertex_update(AnyData d)
{
    if (d == NULL)
        return;
    CubeVertex d1 = (CubeVertex)d;
    destroystring(d1->string);
    free(d1->neighbors);
    free(d1);
    d1 = NULL;
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
    clone->kOnes = v->kOnes;
    clone->numberOfNeighbors = v->numberOfNeighbors;
    clone->neighbors = (CubeVertecies)calloc(v->numberOfNeighbors, sizeof(*(v->neighbors)));
    for (int i = 0; i < v->numberOfNeighbors; i++)
    {
        clone->neighbors[i] = (CubeVertex)calloc(1, sizeof(*(clone->neighbors[i])));
        clone->neighbors[i]->string = stringcopy(v->neighbors[i]->string);
        clone->neighbors[i]->visited = v->neighbors[i]->visited;
        clone->neighbors[i]->seed = v->neighbors[i]->seed;
        clone->neighbors[i]->deadEnd = v->neighbors[i]->deadEnd;
        clone->neighbors[i]->len = v->neighbors[i]->len;
        clone->neighbors[i]->kOnes = v->neighbors[i]->kOnes;
        clone->neighbors[i]->numberOfNeighbors = v->neighbors[i]->numberOfNeighbors;
    }
    return clone;
}

/**************BACK TRACKING ALGORITHM**********/

Strings generate_neighbors(String s)
{
    int numOnes = 0;
    int numZeros = 0;
    for (int i = 0; i < stringlen(s); i++)
    {
        if (s[i] == '1')
        {
            numOnes++;
        }
        else
        {
            numZeros++;
        }
    }
    Strings neighbors = NULL;
    int count = 0;
    String temp = NULL;
    if (numOnes > numZeros)
    {
        neighbors = (Strings)calloc(numOnes + 1, sizeof(String));
        temp = stringcopy(s);
        for (int i = 0; i < stringlen(temp); i++)
        {
            if (temp[i] == '1')
            {
                temp[i] = '0';
                neighbors[count] = stringcopy(temp);
                temp[i] = '1';
                count++;
            }
        }
        neighbors[count] = NULL;
    }
    else
    {
        neighbors = (Strings)calloc(numZeros + 1, sizeof(String));
        temp = stringcopy(s);
        for (int i = 0; i < stringlen(temp); i++)
        {
            if (temp[i] == '0')
            {
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

void back_track(HashMap map, String binaryString, int n, char bit, int maxDepth)
{
    //printf("Binary String %s at level %d\n", binaryString, n);
    String nextString = NULL;
    if (n == maxDepth)
    {
        Strings neighbors = generate_neighbors(binaryString);
        int i = 0;
        while (neighbors[i] != NULL)
        {
            unsigned long h = hash(map, neighbors[i]);
            CubeVertex v = (CubeVertex)map->table[h]->data;
            if (v->seed == true)
            {
                add_to_stringarray(path, binaryString);
                String printer = printstringarray(path);
                printf("PATH: NUMBER %ld\n\n%s", globalCount, printer);
                printf("\n\n");
                destroystring(printer);
                destroystringarray(neighbors);
                globalCount++;
                return;
            }
            i++;
        }
        destroystringarray(neighbors);
    }
    else
    {
        int i = 0;
        nextString = stringcopy(binaryString);
        CubeVertex currentVertex = (CubeVertex)map->table[hash(map, binaryString)]->data;
        //if(currentVertex == NULL)return;
        for (i = 0; i < stringlen(binaryString); i++)
        {
            if (binaryString[i] == bit)
            {
                set_bit(&nextString, i);
                CubeVertex temp = (CubeVertex)map->table[hash(map, nextString)]->data;

                if (temp->visited == false)
                {
                    currentVertex->visited = true;
                    add_to_stringarray(path, currentVertex->string);
                    if (bit == '1')
                    {
                        bit = '0';
                    }
                    else
                    {
                        bit = '1';
                    }
                    back_track(map, nextString, n + 1, bit, maxDepth);

                    if (bit == '1')
                    {
                        bit = '0';
                    }
                    else
                    {
                        bit = '1';
                    }
                    currentVertex->visited = false;
                    remove_from_stringarray(path, currentVertex->string);
                    set_bit(&nextString, i);
                    continue;
                }
                else
                {
                    set_bit(&nextString, i);
                    continue;
                }
            }
        }

        if (i == stringlen(binaryString))
        {
            if (DEBUG1)
                printf("DEAD END %s at level %d\n", binaryString, n);
            currentVertex->visited = false;
            currentVertex->deadEnd = true;
            remove_from_stringarray(path, currentVertex->string);
            destroystring(nextString);
        }
    }
}

void set_bit(String* s, int n)
{
    if ((*s)[n] == '0')
       (*s)[n] = '1';
    else
    {
        (*s)[n] = '0';
    }
}

/*****************MODULE***************/
void generate_hamiltonian_paths(int n, int k)
{
    assert((n % 2) == 1);
    assert(k == (n / 2));
    assert(n > 0);
    HashMap map = new_hashmap(print_vertex, destroy_vertex_update, 13);
    CubeVertecies m = generate_vertecies(n, k);
    CubeVertecies l = generate_vertecies(n, k + 1);
    ErrorCode mapStatus;
    for (int i = 0; i < n_choose_k(n, k); i++)
    {
        mapStatus = put_hashmap(map, m[i]->string, m[i]);
        if (DEBUG1)
            print_error_code(mapStatus);
    }
    for (int i = 0; i < n_choose_k(n, (k + 1)); i++)
    {
        mapStatus = put_hashmap(map, l[i]->string, l[i]);
        if (DEBUG1)
            print_error_code(mapStatus);
    }
    String tempString = stringcopy(l[0]->string);
    if (DEBUG1)
        printf("Temp String is %s\n", tempString);
    CubeVertex tempVertex = (CubeVertex)map->table[hash(map, tempString)]->data;
    tempVertex->seed = false;
    String seed = stringcopy(m[0]->string);
    finalBitRange = final_bit_range(n);
    //printf("Final Bit Range is %ld\n", finalBitRange);

    int maxLevel = number_of_starting_strings(n, k);
    maxLevel = maxLevel/2;
    /*path[0] = stringcopy("00000011111");
    path[1] = stringcopy("01000011111");
    path[2] = stringcopy("01000010111");
    path[3] = stringcopy("11000010111");
    path[4] = stringcopy("11000010011");
    path[5] = stringcopy("11000110011");
    path[6] = stringcopy("11000100011");
    path[7] = stringcopy("11000101011");
    path[8] = stringcopy("01000101011");
    path[9] = stringcopy("01000111011");
    path[10] = stringcopy("01000110011");
    path[11] = stringcopy("01000110111");
    path[12] = stringcopy("00000110111");*/
    clear(seed);
    seed = calloc(n, sizeof(char));
    forall(n){
        if((x%2)==0){
            seed[x] = '0';
        }else{
            seed[x] = '1';
        }
    }
    seed[n] = '\0';

    back_track_two(map, seed, '0', 1, (maxLevel));
    //back_track_nine(map, seed, '0', 1, number_of_starting_strings(n, k));
    destroystring(seed);
    destroystring(tempString);
    clear(m);
    clear(l);
    destroy_hashmap(map);
    /*if(FP != NULL){
        fclose(FP);
    }*/
    
}

/*********************MODIFIERS*************/

String zero_dyk_word(String s)
{
    char *temp = stringcopy(s);
    int index = dyk_word_0(temp);
    if (s[index] == '0')
    {
        s[index] = '1';
    }
    else
    {
        s[index] = '0';
    }
    destroystring(temp);
    return s;
}

String one_dyk_word(String s)
{
    char *temp = stringcopy(s);
    int index = dyk_word_1(temp);
    if (s[index] == '0')
    {
        s[index] = '1';
    }
    else
    {
        s[index] = '0';
    }
    destroystring(temp);
    return s;
}

Strings cyclic_decomposition(String s)
{
    Strings cycle = NULL;
    int i = 0;
    mem_alloc(cycle, 100);
    cycle[i] = stringcopy(s);
    bool mode = false;
    int numOnes = 0;
    int numZeros = 0;
    foreach (x, stringlen(cycle[i]))
    {
        if (s[i] == '1')
        {
            numOnes++;
        }
        else
        {
            numZeros++;
        }
    }
    if (numZeros > numOnes)
    {
        mode = false;
    }
    else
    {
        mode = true;
    }

    if (mode == false)
    {
        int count = 0;
        String temp = stringcopy(cycle[i]);

        do
        {
            if ((count % 2) == 0)
            {
                temp = zero_dyk_word(temp);
                if (strcmp(temp, cycle[0]) == 0)
                {
                    destroystring(temp);
                    return cycle;
                }
                i++;
                add_to_stringarray(cycle, temp);
                count++;
            }
            else
            {
                if (DEBUG1)
                    printf("Before %s\n", temp);
                temp = one_dyk_word(temp);
                if (DEBUG1)
                    printf("After %s\n", temp);
                if (strcmp(temp, cycle[0]) == 0)
                {
                    destroystring(temp);
                    return cycle;
                }
                i++;
                add_to_stringarray(cycle, temp);
                count++;
            }
            if (DEBUG1)
                printf("%s\n", temp);
        } while (strcmp(cycle[0], temp) != 0);
        destroystring(temp);
    }
    return cycle;
}

/****PRINTERS***/

void print_path_two(String path[], int size)
{
    forall(size-1){
        if(x == size/2){
            printf("-------------------\n");
        }
        String printer = stringcopy(path[x]);
        String nextString = stringcopy(path[x+1]);
        for(int i = 0; i < strlen(printer); i++){
            if(printer[i] != nextString[i]){
               // textcolor(2);
                printf(GREEN "%c" COLOR_RESET, printer[i]);
            }
            else{
                printf("%c", printer[i]);
            }
        }
        printf("\n");
    }
    printf("%s\n", path[size-1]);
}