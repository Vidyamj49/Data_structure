#ifndef inverted_index
#define inverted_index

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//macro defination for the return values and constants
#define SUCCESS 0
#define FAILURE -1
#define NOT_PRESENT -2
#define FILE_EMPTY -3
#define NOT_EXTENSION -4


//macro defination for the maximum length and size of the hashtable
#define NAMELENGTH 50
#define size 27


/* Structure defination for the main node*/
typedef struct main_node
{
    char word[NAMELENGTH];
    struct sub_node* sub_link;
    struct main_node* link;
    int f_count;
}main_node_t;


/*Structure defination for the sub node*/
typedef struct sub_node
{
    char f_name[NAMELENGTH];
    int w_count;
    struct sub_node *sub_node_link;
}sub_node_t;


/*Structure defination for the linked list*/
typedef struct file_node
{
    char f_name[NAMELENGTH];
    struct file_node* link;
}file_node_t;


//Validate functions
int validate_n_store_filenames( const int argc,char *argv[],file_node_t **head);
int IsFileValid(char *filename);
int store_filename_to_list(char *f_name, file_node_t **head);


//create hashtable functions
int create_DB(main_node_t **main_head, file_node_t *file_head);
void read_datafile(main_node_t **main_head,char *f_name);
int insert_at_last_main(main_node_t **main_head,char buffer[],char *f_name);


//Display database functions
int display_DB(main_node_t **main_head);


//Search database functions
int search_DB(main_node_t **main_head,char word[]);


//Save database functions
int save_DB(main_node_t **head, char *fname);


//Update database functions
int update_DB(file_node_t **file_head, main_node_t **main_head, char *saved_fname);
int update_main_head(main_node_t **main_head,main_node_t *new, int key );
int update_sub_node(main_node_t *new, sub_node_t *new_sub);

#endif
