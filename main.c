#include "inverted_index.h"

int main(const int argc, char *argv[])
{
    // Check if command line arguments are provided
    if (argc < 2)
    {
        printf("Error: Please pass the command line argument\n");
        return 0;
    }

    file_node_t *file_head = NULL; // Structure pointer

    // Validate and store filenames in a linked list
    if (validate_n_store_filenames(argc, argv, &file_head) == FAILURE)
    {
        printf("Error: File Validation Failed\n");
        return 0;
    }

    // Create hash table
    main_node_t **main_head = (main_node_t **)malloc(27 * sizeof(main_node_t *));
    for (int i = 0; i < 27; i++)
    {
        main_head[i] = NULL;
    }
    printf("Hash table is created\n");

    int option;
    printf("Select your choice among the following options:\n");
    printf("1. Create Database\n2. Display Database\n3. Search Database\n4. Save database\n5. Update Database\n6. Exit\n");

    char ch = 'y';
    do
    {
        printf("Choose option: ");
        scanf("%d", &option);
        getchar(); // Consume newline character

        switch (option)
        {
        case 1:
            // Create Database
            if (create_DB(main_head, file_head) == FAILURE)
            {
                printf("Failed to create database\n");
            }
            else
            {
                printf("Database created successfully\n");
            }
            break;

        case 2:
            // Display Database
            if (display_DB(main_head) == FAILURE)
            {
                printf("Database is empty\n");
            }
            else
            {
                printf("Database displayed successfully\n");
            }
            break;

        case 3:
            // Search Database
            char word[50];
            printf("Enter the word you want to search: ");
            scanf("%s", word);
            getchar(); // Consume newline character
            if (search_DB(main_head, word) == FAILURE)
            {
                printf("The word entered was not found\n");
            }
            break;

        case 4:
            // Save Database
            char f_name[20];
            printf("Enter the file name: ");
            scanf("%s", f_name);
            getchar(); // Consume newline character
            save_DB(main_head, f_name);
            printf("Database saved successfully\n");
            break;

        case 5:
            // Update Database
            char saved_fname[20];
            printf("Enter the saved file name: ");
            scanf("%s", saved_fname);
            getchar(); // Consume newline character
            if (update_DB(&file_head, main_head, saved_fname) == FAILURE)
            {
                printf("Failed to update database\n");
            }
            else
            {
                printf("Database updated successfully\n");
            }
            break;

        default:
            printf("Choose a correct option\n");
        }

        printf("Do you want to continue?\n");
        printf("y/Y to continue and n/N to discontinue\n");
        scanf("%c", &ch);
        getchar(); // Consume newline character
    } while (ch == 'y' || ch == 'Y');

    return 0;
}



