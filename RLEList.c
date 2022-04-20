#include "RLEList.h"
#include <stdlib.h>
#include <stdio.h>

#define INITIALIZED_CHAR '\0'

struct RLEList_t{
    char letter;
    int letterNum;
    struct RLEList_t* next;
} ;

RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if (!ptr)
        return NULL;
    ///check Allocation
    ptr->letter = INITIALIZED_CHAR;
    ptr->letterNum = 0;
    ptr->next = NULL;
        return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    if (list == NULL || value == '\0')
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
   RLEList tmp = list;
   while (tmp->next)
   {
       tmp = tmp->next;
   }
    if (tmp->letter == value)
    {
        tmp->letterNum = tmp->letterNum + 1;
    }
    else if (tmp->letter != value && tmp->letter != INITIALIZED_CHAR)
    {
        tmp->next = RLEListCreate();
        if (tmp->next == NULL)
            return RLE_LIST_OUT_OF_MEMORY;
        tmp = tmp->next;
        tmp->letter = value;
        tmp->letterNum = 1;
            return RLE_LIST_SUCCESS;
    }
    else 
    {
        list->letter = value;
        list->letterNum = 1;
            return RLE_LIST_SUCCESS;
    }
    return RLE_LIST_SUCCESS; //TODO
}

int RLEListSize(RLEList list)
{
    if(list == NULL)
    {
        return -1;
    }
    RLEList tmp = list;
    
    int counter = 0; 
    while(tmp)
    {
        counter += tmp->letterNum;
        tmp = tmp->next;
    }
    return counter;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (index > (RLEListSize(list) - 1) || index < 0)
    {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    else if ((index == 0) && (list->letterNum == 1))
    {
        list = list->next;
    }
    RLEList tmp = list;
    RLEList previousList = list;
    int sum = tmp->letterNum;
    while(sum < index)
    {
        previousList = tmp;
        tmp = tmp->next;
        sum += tmp->letterNum;
    }
    if(tmp->letterNum == 1)
    {
        RLEList toDelete=tmp;
        previousList = tmp->next;
        free(toDelete);
    }
    else
    {
        tmp->letterNum = tmp->letterNum - 1;
    }
    tmp = previousList;
    return 	RLE_LIST_SUCCESS;
}

/**
*   RLEListGet: Returns the character found at a specified index in an RLE list.
*
* @param list - The RLE list to retrieve the character from.
* @param index - The index at which the character to be retrieved is found.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	LIST_SUCCESS the character found at index has been retrieved successfully.
* @return
* 	0 if result is not RLE_LIST_SUCCESS.
* 	The character found at given index in case of success.   
*/
char RLEListGet(RLEList list, int index, RLEListResult *result) //TODO: fix if return isn't SUCCESS return 0
{
     if (index > (RLEListSize(list) - 1) || index < 0)
    {
        *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    else if (list == NULL)
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList tmp = list;
    int sum = tmp->letterNum;
    while(sum < index)
    {
        tmp = tmp->next;
        sum += tmp->letterNum;
    }
    *result = RLE_LIST_SUCCESS;
     return tmp->letter;
}


//TODO: repeat these two functions we were very tired when we wwrote them
RLEListResult RLEListMap(RLEList list, MapFunction map_function)
{
    RLEList tmp = list; //TODO:נראה קל מידי 
    if((list==NULL) && (map_function==NULL))
    {
        return RLE_LIST_NULL_ARGUMENT;
    }
    while(tmp)
    {
        tmp->letter = map_function(tmp->letter);
        tmp=tmp->next;
    }
    return RLE_LIST_SUCCESS;
}
/**
*   RLEListExportToString: Returns the characters found in an RLE list as a string.
*
* @param list - The RLE list to be exported as a string. //TODO: what to do if result is null itself
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	LIST_SUCCESS the RLE list has been successfuly exported as a string.
* @return
* 	NULL if result is not RLE_LIST_SUCCESS.
* 	The string that corresponds to the received RLE list.
*/
char* RLEListExportToString(RLEList list, RLEListResult* result)//TODO לשחרר הקצאה דינאמית במקום אחר
{
    if (list == NULL)
    {
        *result = RLE_LIST_NULL_ARGUMENT;
        return *result;
    }
    int nodes_counter = 0;
    RLEList tmp = list;
    RLEList stringData = list;
    while(tmp)
    {
        tmp=tmp->next;
        nodes_counter++;
    }
    nodes_counter=3*nodes_counter+1;
    char *s = malloc(sizeof(char)*nodes_counter);
    for(int i=0; i<nodes_counter; i=i+3)
    {
        if (i == (nodes_counter - 1))
            s[i] = '\0';

        else
        {
            s[i]=stringData->letter;
            s[i+1]=stringData->letterNum;
            if (stringData->next != NULL)
            {
                s[i+2] = '\n';
            }
            stringData = stringData->next;
        }
    }

    return s;
}






