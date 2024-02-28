#include "inverted_index.h"

int display_DB(main_node_t **main_head)
{
    int flag = 1; // Flag to check if all main nodes are null
    printf("INDEX\tWORD\t\tFILE_COUNT\tFILE_NAME\tWORD_COUNT\n");
    for (int i = 0; i <= 26; i++)
    {
        if (main_head[i] == NULL)
        {
            continue; // Skip empty main nodes
        }

        flag = 0; // Set flag to indicate non-empty database
        main_node_t *temp = main_head[i];
        printf("\n");

        //printf("INDEX\tWORD\t\tFILE_COUNT\tFILE_NAME\tWORD_COUNT\n");
        while (temp)
        {
            printf("\n");
            printf("%d\t", i);
            printf("%s\t\t", temp->word);
            printf("%d\t\t", temp->f_count);
            sub_node_t *sub_temp = temp->sub_link;

            while (sub_temp)
            {
                printf("%s\t\t", sub_temp->f_name);
                printf("%d\t", sub_temp->w_count);
                printf("\t\t");
                sub_temp = sub_temp->sub_node_link;
            }
            printf("\n");
            temp = temp->link;
        }
    }

    if (flag) // If all main nodes are null, return that the database is empty
        return FAILURE;

    return SUCCESS; // Return success if the display is successful
}
