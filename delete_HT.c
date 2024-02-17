#include"hash.h"

int destroy_HT(hash_t *arr, int size)
{
    hash_t *temp;
    hash_t *temp1;
    for(int i=0;i<size;i++)
    {
        if(arr[i].value == -1)
        {
            continue;
        }
        if(arr[i].value != -1)
        {
            temp = arr[i].link;
            arr[i].value = -1;
            arr[i].link = NULL;
           
        }
        while(temp != NULL)
        {
            temp1 = temp->link;
            free(temp);
            temp =temp1;
        }
        
    }
    return SUCCESS;
}
