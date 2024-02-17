#include"hash.h"

int delete_element(hash_t *arr, int data, int size)
{
    int index = data % size;                     // finding index value
    if(arr[index].value == -1)                   // checking index value -1
    {
        return DATA_NOT_FOUND;
    }
    if(arr[index].value == data && arr[index].link == NULL)       // checking whether data is present at index position 
    {
        arr[index].value = -1;
        return SUCCESS;
    }
    if(arr[index].value == data && arr[index].link != NULL)       // checking whether data present at 1st position and link != null
    {
        hash_t *temp = arr[index].link;
        arr[index].value = temp->value;
        arr[index].link = temp->link;
        free(temp);
        return SUCCESS;
        
    }
    if(arr[index].value != data)                               // if data not found at index position in HT traversing through index
    {
        hash_t *temp = &arr[index];
        hash_t *prev = NULL;
        while(temp != NULL)
        {
            if(temp->value == data)
            {
                if(prev == NULL)
                {
                    
                    arr[index].link = temp->link;
                   
                }
                else
                {
                    prev->link = temp->link;
                }
                free(temp);
                return SUCCESS;
                
            }
            else
            {
                prev = temp;
                temp = temp->link;
                
            }
        }
        return DATA_NOT_FOUND;
    }
}
