#include "inverted_index.h"

int search_DB(main_node_t **main_head, char *word)
{
    int key;

    // Determine the index key based on the first character of the word
    if (word[0] >= 65 && word[0] <= 90)
    {
        key = word[0] % 65;
    }
    else if (word[0] >= 97 && word[0] <= 122)
    {
        key = word[0] % 97;
    }
    else
    {
        key = 26; // If the first character is not a letter
    }

    // Check if the main node at the computed key is NULL
    if (main_head[key] == NULL)
    {
        return FAILURE; // Return failure if the main node is NULL
    }

    main_node_t *mtemp = main_head[key];
    printf("\n");

    // Traverse the linked list at the computed key to find the word
    while (mtemp != NULL)
    {
        if (strcmp(mtemp->word, word) == 0)
        {
            printf("The word %s found at index %d\n", word, key);
            printf("The word details are:\n");
            //printf("INDEX NO: %d\n", key);
            printf("The word %s present in %d file.\n", mtemp->word,mtemp->f_count);
            //printf("FILE COUNT IS: %d\n", mtemp->f_count);

            sub_node_t *stemp = mtemp->sub_link;

            // Traverse the sub-nodes and display details
            while (stemp != NULL)
            {
                printf("In %s for %d times.\n",stemp->f_name,stemp->w_count);
                //printf("FILE NAME IS: %s\n", stemp->f_name);
                stemp = stemp->sub_node_link;
            }

            printf("\n");
            return SUCCESS; // Return success if the word is found and details are displayed
        }
        mtemp = mtemp->link; // Move to the next main node in the linked list
    }

    return FAILURE; // Return failure if the word is not found in the database
}
