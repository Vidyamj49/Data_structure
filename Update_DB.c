
#include "inverted_index.h"

int update_DB(file_node_t **file_head, main_node_t **main_head, char *saved_fname)
{
    FILE *fp = fopen(saved_fname, "r");

    if (fp == NULL)
        return FAILURE; // Return failure if file opening fails

    // Read data from the saved file and update the database
    while (1)
    {
        char str[200];
        fscanf(fp, " %s", str);
        if (feof(fp))
            break;

        char *tok = strtok(str, ";");
        int key = atoi(tok + 1);

        main_node_t *new = (main_node_t *)malloc(sizeof(main_node_t));

        if (new == NULL)
            return FAILURE; // Return failure if memory allocation fails

        new->link = NULL;
        new->sub_link = NULL;

        tok = strtok(NULL, ";");
        strcpy(new->word, tok);

        tok = strtok(NULL, ";");
        int fcount = atoi(tok);
        new->f_count = fcount;

        // Update the main node in the hash table
        update_main_head(main_head, new, key);

        for (int i = 0; i < fcount; i++)
        {
            sub_node_t *new_sub = (sub_node_t *)malloc(sizeof(sub_node_t));

            if (new_sub == NULL)
                return FAILURE; // Return failure if memory allocation fails

            new_sub->sub_node_link = NULL;

            tok = strtok(NULL, ";");
            strcpy(new_sub->f_name, tok);

            tok = strtok(NULL, ";");
            int w_count = atoi(tok);
            new_sub->w_count = w_count;

            // Update the sub-node in the main node
            update_sub_node(new, new_sub);
        }
    }

    fclose(fp); // Close the file
    return SUCCESS; // Return success if the update is successful
}

int update_main_head(main_node_t **main_head, main_node_t *new, int key)
{
    if (main_head[key] == NULL)
    {
        main_head[key] = new;
    }
    else
    {
        main_node_t *temp = main_head[key];

        while (temp->link)
        {
            temp = temp->link;
        }
        temp->link = new;
    }

    return SUCCESS;
}


int update_sub_node(main_node_t *new, sub_node_t *new_sub)
{
    if (new->sub_link == NULL)
    {
        new->sub_link = new_sub;
    }
    else
    {
        sub_node_t *temp_sub = new->sub_link;

        while (temp_sub->sub_node_link)
        {
            temp_sub = temp_sub->sub_node_link;
        }

        temp_sub->sub_node_link = new_sub;
    }

    return SUCCESS;
}
