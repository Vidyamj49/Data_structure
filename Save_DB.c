#include "inverted_index.h"

int save_DB(main_node_t **main_head, char *fname)
{
    char f_name[20];

    // Ensure the file extension is ".txt"
    if (strstr(fname, ".") == NULL)
    {
        strcpy(f_name, fname);
        strcat(f_name, ".txt");
    }
    else if (strcmp(strstr(fname, "."), ".txt") != 0)
    {
        char *p;
        p = strstr(fname, ".");
        strncpy(f_name, fname, p - fname);
        strcat(f_name, ".txt");
    }
    else
    {
        strcpy(f_name, fname);
    }

    // Open the file for writing
    FILE *fp = fopen(f_name, "w");
    if (fp == NULL)
    {
        return FAILURE; // Return failure if file opening fails
    }

    // Iterate through the hash table and write data to the file
    for (int i = 0; i < 27; i++)
    {
        if (main_head[i] == NULL)
        {
            continue; // Skip empty main nodes
        }
        main_node_t *temp = main_head[i];

        while (temp != NULL)
        {
            // Write index, word, and file count to the file
            fprintf(fp, "#%d;", i);
            fprintf(fp, "%s;%d;", temp->word, temp->f_count);
            sub_node_t *sub_temp = temp->sub_link;

            // Write file names and word counts in sub-nodes to the file
            while (sub_temp != NULL)
            {
                fprintf(fp, "%s;%d;#", sub_temp->f_name, sub_temp->w_count);
                sub_temp = sub_temp->sub_node_link;
            }
            fprintf(fp, "\n"); // Move to the next line after writing a main node
            temp = temp->link;
        }
    }

    fclose(fp); // Close the file
    return SUCCESS; // Return success if the save operation is successful
}
