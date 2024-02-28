#include "inverted_index.h"

// Function to create the inverted index database
int create_DB(main_node_t **main_head, file_node_t *file_head)
{
    while (file_head)
    {
        read_datafile(main_head, file_head->f_name);
        file_head = file_head->link;
    }
}

// Function to read data from a file and update the inverted index database
void read_datafile(main_node_t **main_head, char *f_name)
{
    FILE *fp = fopen(f_name, "r");

    char buffer[50];

    while (fscanf(fp, "%s", buffer) != EOF)
    {
        if (insert_at_last_main(main_head, buffer, f_name) == FAILURE)
        {
            printf("ERROR: Data insertion failed\n");
        }
    }
    fclose(fp);
}

// Function to insert a word into the inverted index database
int insert_at_last_main(main_node_t **main_head, char buffer[], char *f_name)
{
    int index;

    // Calculate index based on the first character of the word
    if (buffer[0] >= 65 && buffer[0] <= 90)
    {
        index = buffer[0] % 65;
    }
    else if (buffer[0] >= 97 && buffer[0] <= 122)
    {
        index = buffer[0] % 97;
    }
    else
    {
        index = 26; // If the first character is not a letter
    }

    // Allocate memory for the main_node
    main_node_t *main_link = (main_node_t *)malloc(sizeof(main_node_t));
    if (main_link == NULL)
    {
        return FAILURE;
    }

    // Initialize main_node fields
    strcpy(main_link->word, buffer);
    main_link->link = NULL;
    main_link->f_count = 1;
    main_link->sub_link = NULL;

    // Allocate memory for sub_node
    sub_node_t *s_link = (sub_node_t *)malloc(sizeof(sub_node_t));
    if (s_link == NULL)
    {
        return FAILURE;
    }

    // Initialize sub_node fields
    s_link->w_count = 1;
    strcpy(s_link->f_name, f_name);
    s_link->sub_node_link = NULL;
    main_link->sub_link = s_link;

    // If the main_head[index] is NULL, update it with main_link
    if (main_head[index] == NULL)
    {
        main_head[index] = main_link;
        return SUCCESS;
    }
    // If main_head[index] is not NULL and the word is the same
    else
    {
        main_node_t *m_temp = main_head[index];

        while (m_temp != NULL)
        {
            // If the word is found in the main_node
            if (strcmp(m_temp->word, buffer) == 0)
            {
                sub_node_t *s_temp = m_temp->sub_link;

                // Search for the file name in sub-nodes
                while (s_temp->sub_node_link != NULL)
                {
                    // If the file name is found, increment word count and return
                    if (strcmp(s_temp->f_name, f_name) == 0)
                    {
                        s_temp->w_count++;
                        return SUCCESS;
                    }
                    s_temp = s_temp->sub_node_link;
                }

                // Check the last sub-node
                if (strcmp(s_temp->f_name, f_name) == 0)
                {
                    s_temp->w_count++;
                    return SUCCESS;
                }

                // If the file name is not found in the sub-nodes, add a new sub-node
                sub_node_t *new_sub = (sub_node_t *)malloc(sizeof(sub_node_t));
                if (new_sub == NULL)
                {
                    return FAILURE;
                }

                // Initialize new sub-node fields
                strcpy(new_sub->f_name, f_name);
                new_sub->w_count = 1;
                new_sub->sub_node_link = NULL;

                s_temp->sub_node_link = new_sub;
                m_temp->f_count++;
                return SUCCESS;
            }

            // If the word is not found in the current main_node
            if (m_temp->link == NULL)
            {
                break;
            }

            m_temp = m_temp->link;
        }

        // If the word is not found in any existing main_node, add a new main_node
        m_temp->link = main_link;
        return SUCCESS;
    }
}

