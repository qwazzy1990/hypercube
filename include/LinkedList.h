/*****Author: Patrick Di Salvo
 *    Date: June 23rd 2018
 *    Description: LinkedList API. 
 * 
 * 
 * 
 * ***/

#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DynamicString.h"
#include "utilities.h"

/***Struct Declarations and Definitions***/

/***Struct of type ListNode***/
struct n
{
    AnyData data;
    struct n *next;
    struct n *previous;
};
typedef struct n listnode;

/***typedefs for listnode* and double pointers***/
typedef listnode *ListNode;
typedef ListNode *ListNodes;

/***Struct for type list****/
struct l
{
    struct n *head;
    struct n *tail;

    PrintFunc printData;
    DeleteFunc deleteData;
    CompareFunc compareData;

    //add more function pointers to create object oriented style.
    int length;
};
typedef struct l list;

/***Typedef for list* = List****/
typedef list *LinkedList;

struct itr
{
    ListNode current;
};

typedef struct itr LinkedListIterator;

/*****Enum for ErrorCodes*****/
enum ec
{
    OK_LIST,
    DNF_LIST,
    DNE_LIST,
    MEM_ERR_LIST,
    DUPLICATE_VALUE_LIST,
};
typedef enum ec ListErrorCode;

/***DEBUG MACROS***/

#define LISTDEBUG1 false
#define PL          \
    if (LISTDEBUG1) \
    printf

/****Macros for destroyers: User is expected to use lefthand expression of macro in function Call. For example: destroy_list(myListVar)
 *   Not destroy_list_real(&myListVar)
 * *****/
//#define destroy_object_list(list, var) destroy_object_list_real(&list, myarg)

#define destroy_list(myarg) destroy_list_real(&myarg)

#define destroy_iterator(myarg) destroy_iterator_real(&myarg)

/***FUNCTION REMAINS PRIVATE TO USERS: NUMBER OF UNDERSCORES = 5****
                         *  FUNCTION IS NOT FOUND IN API. ONLY STATIC IN .c extention
                         * */

#define _____destroy_____node(myarg) _____destroy_____node_____real(&myarg)


                        

/*****FUNCTION DECLARATIONS*****/

/*****CONSTRUCTORS****/

/**
 * Function to create a new LinkedList (list*)
 * @param PrintFunction, DeleteFunction, CompareFunction.
 * @return: A List with space allocated for it. List length is set to 0.
 * List head = NULL
 * List tail = NULL
 * */
LinkedList new_linkedlist(PrintFunc p, DeleteFunc d, CompareFunc c);

ListNode new_list_node(AnyData d);

/***ACCESSORS****/

/**
 * Function to return the data at the head of the list.
 * @ return: If list length = 0, then returns NULL. 
 * @ return: If list head is empty then return NULL.
 * @ return: If data exists then returns data
 * @param: LinkedList l. Must not be NULL
 * */
AnyData get_from_front(LinkedList l);

/**
 * Function to return the data fro the tail of the list.
 * @return: If l->length = 0, the return NULL.
 * @return: If l->tail = NULL then return NULL.
 * @return: If l = NULL then return NULL.
 * @return: data at tail of list.
 * @param: LinkedList l.
 * */
AnyData get_from_back(LinkedList l);

/** Function that searches for an element in the LinkedList using the CompareFunc passed to List constructor
 * If an element is found, a pointer to the data of that element is returned
 * Returns NULL if the element is not found.
 *@pre LinkedList exists and is valid.  
 *@post List remains unchanged.
 *@return The data associated with the list element that matches the search criteria.  If element is not found, return NULL.
 *@param list - a LinkedList 
 *@param void* d. Must not be NULL.
 **/

AnyData find_data_list(LinkedList l, AnyData d);
/**
 * Function to get the length of a LinkedList.
 * @param: LinkedList . Must not be NULL.
 * @return: Length of LinkedList.
 * */
int get_length(LinkedList l);

/****SETTERS****/

/**
 * Function to insert data at tail of LinkedList l.
 * Internal creation of ListNode. Data added to Node.
 * Node inserted to list.
 * @param: LinkedList l, void* d.
 * @return: ListErrorCode. If successful insertion returns
 * OK_LIST. Else returns MEM_ERR_LIST
 * */
ListErrorCode insert_back(LinkedList l, AnyData d);

/**
 * Function to insert data at head of LinkedList l.
 * Internal creation of ListNode. Data added to Node.
 * Node inserted to list.
 * @param: LinkedList l, void* d.
 * @return: ListErrorCode. If successful insertion returns
 * OK_LIST. Else returns MEM_ERR_LIST
 * */

ListErrorCode insert_front(LinkedList l, AnyData d);

/**
 * Function to insert data into list in a sorted way.
 * Internal creation of ListNode. Data added to Node.
 * Node inserted to list.
 * Uses the list function pointer for the comparison function 
 * passed into the LinkedList constructor.
 * @param: LinkedList l, void* d.
 * @return: ListErrorCode. If successful insertion returns
 * OK_LIST. Else returns MEM_ERR_LIST
 * */
ListErrorCode insert_sorted(LinkedList l, AnyData d);

/*****MUTATORS****/

/***
 * Function to convert a LinkedList to an array of void**.
 * The function returns a type-casted void** as a void* in order to allow for 
 * Assignment of return value to any pointer. Recommended that the user assigns 
 * Function to a double pointer of any type. Not a single pointer.
 * Function returns a SHALLOW copy of list->node->data. 
 * @param: LinkedList l
 * @Return: an array of void** type-cast as a void* containing the data. The array ends 
 * with a NULL terminator. Or null if error occurs
 * @pre list must exist
 * @pre no nodes in the list can be null
 * @pre no data in any nodes can be null
 * @post: list is unchanged. 
 * @post: array of shallow copies of node->data
 * */
AnyData list_to_array(LinkedList l);

/**Returns a string that contains a string representation of
    the list traversed from  head to tail. Utilize the list's printData function pointer to create the string.
    returned string must be freed by the calling function.
 *@pre List must exist, but does not have to have elements.
 *@param list Pointer to linked list dummy head.
 *@return on success: char * to string representation of list (must be freed after use).  on failure: NULL
 **/
String list_to_string(LinkedList l);

/*****ITERATOR*****/

/**
 * Function to create a LinkedListIterator for a LinkedList.
 * @param: LinkedList l.
 * @return a LinkedListIterator with current element = to l->head.
 * @pre: l must exist and not be NULL
 * @post: l is unchanged. LinkedListIterator is returned pointint to l->head.
 * */
LinkedListIterator new_iterator(LinkedList l);

/**
 * Function to return the next element the LinkedListIterator is pointing to.
 * @param: LinkedListIterator 
 * @return: element that itr is pointing to
 * @pre: itr must exist with itr->current != NULL
 * @post: itr->current is set to itr->current->next
 * */
AnyData next_element(LinkedListIterator itr);

/*****DESTROYERS*****/

/**Wrapper function for delete_object_list_real
 * Removes data from from the list by deleting the dereferenced LinkedList* l, the creating a 
 * new list with the data except the data to be deleted. the newlist is assigned to *LinkedList pointer.
 * deletes the old nodes.
 * Uses comparato function provided to list to find data.
 * changes pointer values of surrounding nodes to maintain list structure.
 * Function call is "destroy_object_list(LinkedList l, AnyData d)"
 * @param LinkedList* l. Void* d.
 * @return OK_LIST if data successfully removed. Else DNF_LIST if data not found
 * @pre: LinkedList l must exist and not be empty
 * @pre: Address of LinkedList l must exist.
 * @pre: d != NULL
 * 
 * */
ListErrorCode destroy_object_list(LinkedList l, AnyData d);

/** Clears the contents linked list, freeing all memory asspociated with these contents.
* uses the supplied function pointer to release allocated memory for the data
*@pre 'List' type must exist and be used in order to keep track of the linked list.
*@param list pointer to the List-type dummy node
**/
ListErrorCode destroy_list_real(LinkedList *l);



/****VALIDATORS*****/

/**
 * Function to check if a LinkedList l contains Data d.
 * Uses comparator function passed to list constructor.
 * @Returns true if l contains d
 * @Returns false if l = NULL, d = NULL or if data is not found.
 * @param l, d
 * @Pre-conditions: l must exist, d must exist
 * @Post-conditions: l is unchaged, d is unchanged.
 * 
 * */
bool contains_list(LinkedList l, AnyData d);
#endif
