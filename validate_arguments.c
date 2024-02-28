#include "inverted_index.h"

// Function to validate and store filenames in a linked list
int validate_n_store_filenames(const int argc, char *filenames[], file_node_t **head)
{
    for (int i = 1; i < argc; i++)
    {
        // Check the validity of the file and handle different cases
        int file_valid = IsFileValid(filenames[i]);
        if (file_valid == NOT_PRESENT)
        {
            printf("File <%s> is not present\n", filenames[i]);
        }
        else if (file_valid == FILE_EMPTY)
        {
            printf("File <%s> is empty\n", filenames[i]);
        }
        else if (file_valid == NOT_EXTENSION)
        {
            printf("File <%s> is not a .txt file\n", filenames[i]);
        }
        else
        {
            printf("Inside loop, file %s\n", filenames[i]);
            // Store the filename in the linked list
            store_filename_to_list(filenames[i], head);
        }
    }
    return SUCCESS;
}

// Function to check the validity of a file
int IsFileValid(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        return NOT_PRESENT; // File is not present
    }

    // Check if the file has a .txt extension
    if (strcmp(strstr(filename, "."), ".txt") != 0)
    {
        return NOT_EXTENSION; // File is not a .txt file
    }

    fseek(fp, 0, SEEK_END);
    int f_tell = ftell(fp);

    // Check if the file is empty
    if (f_tell == 0)
    {
        return FILE_EMPTY; // File is empty
    }

    fclose(fp);
    return SUCCESS; // File is valid
}

// Function to store a filename in the linked list
int store_filename_to_list(char *f_name, file_node_t **head)
{
    file_node_t *new = (file_node_t *)malloc(sizeof(file_node_t));
    if (new == NULL)
    {
        printf("Failed to create a new node\n");
        return FAILURE;
    }

    strcpy(new->f_name, f_name);
    new->link = NULL;

    // If the linked list is empty, make the new node the head
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    file_node_t *temp = *head;

    // Traverse the linked list to check for duplicate filenames
    while (temp->link != NULL)
    {
        if (strcmp(temp->f_name, f_name) == 0)
        {
            printf("File name %s is already present\n", f_name);
            return FAILURE;
        }
        temp = temp->link;
    }

    // Check the last node in the linked list
    if (strcmp(temp->f_name, f_name) == 0)
    {
        printf("File name %s is already present\n", f_name);
        return FAILURE;
    }

    // Add the new node to the end of the linked list
    temp->link = new;
    return SUCCESS;
}
