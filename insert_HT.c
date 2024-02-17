#include"hash.h"

int insert_HT(hash_t *arr, int element, int size)
{
    int index = element % size;
    if(arr[index].value == -1)
    {
        arr[index].value = element;
        return SUCCESS;
    }
    hash_t *new = malloc(sizeof(hash_t));
    if(new == NULL)
       return FAILURE;
    new->value = element;
    new->link = NULL;
    new->key  = index;
    if(arr[index].link == NULL)
    {
        arr[index].link = new;
        return SUCCESS;
    }
    hash_t *temp = arr[index].link;
    while(temp->link != NULL)
    {
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}
