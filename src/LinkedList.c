#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "LinkedList.h"

/*****STATIC FUNCTIONS: NOT AVAILABLE TO USER***/

void _____destroy_____node_____real(ListNode *node)
{
    clear(node);
    //PL("%p\n", node);
}

ListNode _____newListNode(AnyData d)
{
    new_object(ListNode, newNode, 1);
    newNode->data = d;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}

/*****CONSTRUCTORS*****/

LinkedList new_linkedlist(PrintFunc p, DeleteFunc d, CompareFunc c)
{
    new_object(LinkedList, newList, 1);
    newList->printData = p;
    newList->deleteData = d;
    newList->compareData = c;
    newList->length = 0;
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}


ListNode new_list_node(AnyData d)
{
    new_object(ListNode, newNode, 1);
    newNode->data = d;
    newNode->next = NULL;
    newNode->previous = NULL;
    return newNode;
}



LinkedListIterator new_iterator(LinkedList l)
{
    LinkedListIterator itr;
    itr.current = l->head;
    return itr;
}

AnyData next_element(LinkedListIterator itr)
{
    AnyData temp = itr.current->data;
    itr.current = itr.current->next;
    return temp;
}

/*******ACCESSORS******/

AnyData get_from_front(LinkedList l)
{
    if (l == NULL)
        return NULL;
    if (l->head == NULL)
        return NULL;
    if (l->head->data == NULL)
        return NULL;
    return l->head->data;
}

AnyData get_from_back(LinkedList l)
{
    if (l == NULL)
        return NULL;
    if (l->tail == NULL)
        return NULL;
    if (l->tail->data == NULL)
        return NULL;
    return l->tail->data;
}

int get_length(LinkedList l)
{
    if (l == NULL)
        return -1;
    else
        return l->length;
}

AnyData find_data_list(LinkedList l, AnyData d)
{
    if (l == NULL)
        return NULL;
    if(d == NULL)return NULL;

    LinkedListIterator itr = new_iterator(l);
    while (itr.current != NULL)
    {
        if (l->compareData(itr.current->data, d) == 0)
        {
            return itr.current->data;
        }
        itr.current = itr.current->next;
    }
    return NULL;
}

/*********SETTERS******/

ListErrorCode insert_front(LinkedList l, AnyData d)
{
    if (l == NULL)
    {
        return DNE_LIST;
    }
    if (d == NULL)
    {
        return DNE_LIST;
    }
    if (l->head == NULL && l->tail == NULL)
    {
        new_object(ListNode, newNode, 1);
        if(newNode == NULL)return MEM_ERR_LIST;
        newNode->data = d;
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->previous = NULL;
        l->head = newNode;
        l->tail = newNode;
        l->head->next = l->tail;
        l->head->previous = NULL;
        l->tail->previous = l->head;
        l->tail->next = NULL;
        l->length++;

        return OK_LIST;
    }
    else
    {
        new_object(ListNode, newNode, 1);
        if(newNode == NULL)return MEM_ERR_LIST;
        newNode->data = d;
        newNode->previous = NULL;
        newNode->next = l->head;

        l->head->previous = newNode;
        l->head = newNode;
        l->length++;
        return OK_LIST;
    }

}

ListErrorCode insert_back(LinkedList l, AnyData d)
{
    if (l == NULL)
    {
        return DNE_LIST;
    }
    if (d == NULL)
    {
        return DNE_LIST;
    }
    if (l->tail == NULL && l->head == NULL)
    {
        new_object(ListNode, newNode, 1);
        if(newNode == NULL)
        {
            return MEM_ERR_LIST;
        }
        newNode->data = d;
        newNode->previous = NULL;
        newNode->next = NULL;
        l->tail = newNode;
        l->head = newNode;
        l->head->next = l->tail;
        l->head->previous = NULL;
        l->tail->previous = l->head;
        l->tail->next = NULL;
        l->length++;
        
        return OK_LIST;
    }
    else
    {
        new_object(ListNode, newNode, 1);
        if(newNode == NULL)return MEM_ERR_LIST;

        newNode->data = d;
        newNode->next = NULL;
        newNode->previous = l->tail;
        l->tail->next = newNode;
        l->tail = newNode;
        l->length++;

        return OK_LIST;
    }

}


ListErrorCode insert_sorted(LinkedList l, AnyData d)
{
    if (l == NULL)
    {
        return DNE_LIST;
    }
    if (d == NULL)
    {
        return DNE_LIST;
    }
    if(l->length < 0){
        return DNE_LIST;
    }
    ListNode newNode = new_list_node(d);
    if(newNode == NULL){
        clear(newNode);
        return MEM_ERR_LIST;
    }

    //if
    if (l->length == 0)
    {
        newNode->previous = NULL;
        newNode->next = NULL;
        l->tail = newNode;
        l->head = newNode;
        l->head->next = l->tail;
        l->head->previous = NULL;
        l->tail->previous = l->head;
        l->tail->next = NULL;
    }//end if & return

    //else if
    else if(l->length == 1){
       if (l->compareData(d, l->head->data) < 0){
		    newNode->next = l->head;
            newNode->previous = NULL;
            l->head->previous = NULL;
            l->head = newNode;
	    }
        else if (l->compareData(d, l->tail->data) > 0){
		    newNode->next = NULL;
            newNode->previous = l->tail;
            l->tail->next = newNode;
            l->tail = newNode;
	    }
        else{
            clear(newNode);
            return DUPLICATE_VALUE_LIST;
        }
    }//end elseif

    //else
    else{
        PL("Adding third\n");
        int currStatus = 0;
        LinkedListIterator itr = new_iterator(l);
        //while
        while(itr.current != NULL){
            currStatus = l->compareData(newNode->data, itr.current->data);
            //if
            if(currStatus < 0){
                //if
                if(sameobject(itr.current, l->head)){
                    newNode->previous = NULL;
                    newNode->next = l->head;
                    l->head->previous = newNode;
                    l->head = newNode;
                    break;
                }//end if
                //else if
                else if(sameobject(itr.current, l->tail)){
                    printf("At tail adding third\n");
                    newNode->next = l->tail;
                    newNode->previous = l->tail->previous;
                    l->tail->previous->next = newNode;
                    l->tail->previous = newNode;
                    break;
                }//end else if

                //else
                else{
                    newNode->next = itr.current;
                    newNode->previous = itr.current->previous;
                    itr.current->previous->next = newNode;
                    itr.current->previous = newNode;
                    break;

                }//end else
            }//endif


            itr.current = itr.current->next;

            if(itr.current == NULL){
                printf("Adding at tail\n");
                //insert at back
                newNode->next = NULL;
                newNode->previous = l->tail;
                l->tail->next = newNode;
                l->tail = newNode;
                break;

            }//end if

        }//end while


    }//end else


    l->length++;
    return OK_LIST;
}//end func





/*******MUTATORS*****/

String list_to_string(LinkedList l)
{
    if(l == NULL)PL("Waht the fucsacsaca\n");
    LinkedListIterator itr = new_iterator(l);
    new_object(String, str, 999);
    strcpy(str, "");

    while(itr.current != NULL)
    {
        PL("Looping\n");
        void *tempData = itr.current->data;
        char *currDescr = l->printData(tempData);
        int newLen = strlen(str) + 50 + strlen(currDescr);
        str = (char *)realloc(str, newLen);
        strcat(str, "\n");
        strcat(str, currDescr);

        free(currDescr);
        itr.current = itr.current->next;
    }

    return str;
}


AnyData list_to_array(LinkedList l)
{
    if(l == NULL)return NULL;
    if(l->length <= 0)return NULL;
    new_object(void**, listAsArray, l->length+1);
    LinkedListIterator itr = new_iterator(l);
    int endOfArray;
    forall(l->length){
        endOfArray = x+1;
        listAsArray[x] = itr.current->data;
        if(listAsArray[x]==NULL){
            return NULL;
        }
        itr.current = itr.current->next;
    }
    listAsArray[endOfArray] = NULL;
    return (void*)listAsArray;

}

/****END MUTATORS*****/

/******DESTROYERS*****/


ListErrorCode destroy_object_list(LinkedList l, AnyData d)
{
    if(l == NULL)return DNE_LIST;
    if(d == NULL)return DNE_LIST;
    if(l->length == 0)return DNE_LIST;
    if(contains_list(l, d)==false)return DNF_LIST;
    //if
    if(l->length == 1){
        l->deleteData(l->head->data);
        clear(l->head);
    }//endif

    //else
    else{
        LinkedListIterator itr = new_iterator(l);
        //while
        while(itr.current != NULL){
            //if
            if(l->compareData(itr.current->data, d)==0){
                if(sameobject(itr.current, l->head)){
                    ListNode newHead = l->head->next;
                    newHead->previous = NULL;
                    l->deleteData(itr.current->data);
                    clear(l->head);
                    l->head = newHead;
                    break;
                }//end if

                //else if
                else if(sameobject(itr.current, l->tail)){
                    ListNode newTail = l->tail->previous;
                    newTail->next = NULL;
                    l->deleteData(itr.current->data);
                    clear(l->tail);
                    l->tail = newTail;
                    break;
                }//end elseif

                else{
                    itr.current->previous->next = itr.current->next;
                    itr.current->next->previous = itr.current->previous;
                    l->deleteData(itr.current->data);
                    clear(itr.current);
                    break;
                }//end else

            }//endif

            itr.current = itr.current->next;
        }//endwhile

    }//end else

    l->length--;
    return OK_LIST;

}//end func



ListErrorCode destroy_list_real(LinkedList* l){

    if(l == NULL)return DNE_LIST;
    LinkedList tempList = *l;
    if(tempList == NULL){
        return DNE_LIST;
    }
    if(tempList->length <= 0){
        clear(tempList);
        *l = NULL;
        return OK_LIST;
    }
    else{
        LinkedListIterator itr = new_iterator(tempList);
        //while
        while(itr.current != NULL){
            tempList->deleteData(itr.current->data);
            itr.current = itr.current->next;
        }//end while
        itr.current = tempList->head;
        while(itr.current != NULL){
            ListNode nextNode = itr.current->next;
            clear(itr.current);
            itr.current = nextNode;
        }

    }//end else
    clear(tempList);
    *l = NULL;
    return OK_LIST;
}


/*****VALIDATORS******/

bool contains_list(LinkedList l, AnyData d)
{
    if(l == NULL)return false;
    if(d == NULL)return false;
    if(l->length == 0)return false;
    LinkedListIterator itr = new_iterator(l);
    while(itr.current != NULL){
        if(l->compareData(itr.current->data, d)==0){
            return true;
        }
        itr.current = itr.current->next;
    }
    return false;
}
