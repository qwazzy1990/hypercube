#include <stdio.h>
#include <stdlib.h>
#include "DynamicString.h"
#include "utilities.h"
#include "StringBitPosition.h"
 


static int _____get_bit_position(StringBitPosition sbp, String s, int n)
{
    //printf("%s\n", s);
    char bit = sbp->bit;
    int count = 0;
    forall(n){
        if(s[x] == bit){
            count++;
        }
    }
    return count;
}

BitPathPairs new_bit_path_pairs(int n)
{
    new_object(BitPathPairs, bitPathPairs, 1);
    bitPathPairs->bitNumber = n;
    bitPathPairs->pathNumbers = new_linkedlist(dummy_print, dummy_delete, dummy_compare);
    bitPathPairs->numberOfPaths = 0;
    return bitPathPairs;
}


StringBitPositions new_string_bit_positions(int n)
{
    //printf("Here\n");

    new_object(StringBitPositions, newSbp, n);
    //printf("N is %d\n", n);
    int numBitPosn = (n/2)+2;
    forall(n){
        newSbp[x] = calloc(1, sizeof(stringBitPosition));
        newSbp[x]->binaryString = NULL;
        newSbp[x]->stringNumber = x+1;
        newSbp[x]->bitPathPairs = new_linkedlist(print_bit_path_pairs, destroy_bit_path_pairs, dummy_compare);
        if(x%2 == 0){
            newSbp[x]->bit = '0';
        }else{
            newSbp[x]->bit = '1';
        }
    }

    forall(n){
        for(int i = 0; i < numBitPosn; i++){
            BitPathPairs temp = new_bit_path_pairs(i+1);
            insert_back(newSbp[x]->bitPathPairs, temp);
            //printf("temp after inserting back %d\n", temp->bitNumber);
            //String ss = print_bit_path_pairs(temp);
            //printf("SS is %s\n", ss);
            //clear(ss);
        }
    }
    return newSbp;

}


StringBitContainer new_string_bit_container(int n, PrintFunc p, DeleteFunc d, CompareFunc c)
{
   // printf("Here1\n");
    new_object(StringBitContainer, stringBitContainer, 1);

   
    stringBitContainer->size = n;

    stringBitContainer->stringBitPositions = new_string_bit_positions(n);
    stringBitContainer->printData = p;
    stringBitContainer->deleteData = d;
    stringBitContainer->compareData = c;
    return stringBitContainer;
}





/****SETTERS****/
void add_string_bit_pair(StringBitContainer c, Strings s, int n)
{
    forall(c->size){
        printf("x is %d\n", x);

        char ch = s[x][strlen(s[x])-1];
        //printf("char is %c\n", ch);
        new_object(String, ss, 2);
        ss[0] = ch;
        int temp = atoi(ss);
        free(ss);
        String tempString = stringsegmentcopy(s[x], 1, temp);
        StringBitPosition sbp = c->stringBitPositions[x];
        sbp->binaryString = stringcopy(s[x]);
        int bitPosition = _____get_bit_position(sbp, tempString, temp);
        clear(tempString);
        ListNode tempHead = sbp->bitPathPairs->head;
        forall(sbp->bitPathPairs->length){
            BitPathPairs temp = tempHead->data;
            if(temp->bitNumber == bitPosition){
                temp->numberOfPaths++;
                add_path_number(temp->pathNumbers, n);
                //printf("Number of paths is %d\n", temp->numberOfPaths);
                break;
            }
            tempHead = tempHead->next;
        }
        //printf("Bit position is %d\n", bitPosition);
        
    }
}

void add_path_number(LinkedList pathNumbers, int n)
{
    new_object(Int, k, 1);
    *k = n;
    insert_back(pathNumbers, k);
}

/***END SETTERS***/



/****PRINTERS****/
String print_bit_path_pairs(AnyData bbp)
{
    
        BitPathPairs bb = (BitPathPairs)bbp;
        new_object(String, printer, 999);
        new_object(String, tempOne, 1000);
        sprintf(tempOne, "                                                 %d", (bb->bitNumber));
        printer = stringcat(printer, tempOne);
        clear(tempOne);
        new_object(String, tempTwo, 100);
        sprintf(tempTwo, "            %d", (bb->numberOfPaths));
        //printer = stringcat(printer, "  Number Of Paths: ");
        printer = stringcat(printer, tempTwo);
        //String pathNumbers = list_to_string(bb->pathNumbers);
       // printer = stringcat(printer, pathNumbers);
        printer = stringcat(printer, "\n");
        clear(tempTwo);
        //clear(pathNumbers);

       return printer;
}

String print_string_bit_positions(AnyData sbp)
{
    StringBitPosition temp = (StringBitPosition)sbp;

    new_object(String, printer, 999);
    int* index = indecies_of_char(temp->binaryString, ' ');
    String binString = stringsegmentcopy(temp->binaryString, 1, (index[0]+1));
    clear(index);
    printer = stringcat(printer, binString);
    clear(binString);
    printer = stringcat(printer, "          ");
    new_object(String, stringNumber, 9999);
    sprintf(stringNumber, "%d", temp->stringNumber);
    printer = stringcat(printer, stringNumber);
    new_object(String, bit, 2);
    bit[0] = temp->bit;
    printer = stringcat(printer, "                ");
    printer = stringcat(printer, bit);
    clear(bit);
    //printer = stringcat(printer, "                             ");
    String bbp = list_to_string(temp->bitPathPairs);
    String bbpTwo = stringsegmentcopy(bbp, 2, stringlen(bbp));
    printer = stringcat(printer, bbpTwo);
    printer = stringcat(printer, "\n\n");
    clear(bbp);
    clear(bbpTwo);
    clear(stringNumber);
    return printer;

}

String print_string_bit_container(StringBitContainer c)
{
   
    new_object(String, printer, 10000);
    int memSize = 1000;
    printer = strcat(printer, "|Binary String:| |String Number:| |Bit:| |Bit Positions:| |Number of Paths:|\n\n\0");
    forall(c->size){
        memSize += 1000;
        String temp = print_string_bit_positions(c->stringBitPositions[x]);
        printer = realloc(printer, memSize);
        printer = strncat(printer, temp, strlen(temp)+1);
        //printf("%s\n", temp);
        free(temp);
    }
    return printer;
}

/***END PRINTERS***/
/****DESTROYERS*****/

void destroy_string_bit_position(AnyData sbp)
{
    StringBitPosition temp = (StringBitPosition)sbp;
    String s = temp->binaryString;
    clear(s);
    destroy_list(temp->bitPathPairs);
    clear(temp);
}

void destroy_bit_path_pairs(AnyData bbp)
{
    BitPathPairs temp = (BitPathPairs)bbp;
    destroy_list(temp->pathNumbers);
    clear(temp);
}

void destroy_string_bit_container(AnyData sbc)
{
    StringBitContainer temp = (StringBitContainer)sbc;
    forall(temp->size){
        destroy_string_bit_position(temp->stringBitPositions[x]);
    }
    clear(temp->stringBitPositions);
    clear(temp);
}

/****END DESTROYERS****/