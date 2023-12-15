#include "document.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gui.h"
#define BUFFER_SIZE 256
#define MAX_FILE_PATH 260

struct tm *get_current_date_time()
{
    time_t t = time(NULL);
    struct tm *new_date = malloc(sizeof(struct tm));
    new_date = localtime(&t);
    new_date->tm_mon = new_date->tm_mon + MONTH_OFFSET;
    new_date->tm_year = new_date->tm_year + YEAR_OFFSET;

    return new_date;
}

void save_document(const char *full_path_to_document, Document *document)
{

    FILE *fp = fopen(full_path_to_document, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR :: file | %s returned NULL for writing note", full_path_to_document);
        fclose(fp);
        return;
    }

    // Write title
    size_t title_length = strlen(document->title) + 1;
    fwrite(&title_length, sizeof(size_t), 1, fp);
    fwrite(document->title, sizeof(char), title_length, fp);

    // Write contents
    size_t contents_length = strlen(document->contents) + 1;
    fwrite(&contents_length, sizeof(size_t), 1, fp);
    fwrite(document->contents, sizeof(char), contents_length, fp);

    // Write created_at and updated_at
    fwrite(document->created_at, sizeof(struct tm), 1, fp);
    fwrite(document->updated_at, sizeof(struct tm), 1, fp);

    fclose(fp);
}

Document *create_document(struct tm *current_date_time, User *user)
{
    fflush(stdin);
    Document *new_document = malloc(sizeof(Document));

    style_printf("Enter the subject of this document : ", BRIGHT_WHITE);
    char input_buff[BUFFER_SIZE];
    char *p_input_buff = fgets(input_buff, BUFFER_SIZE, stdin);
    strtok(p_input_buff, "\n");

    new_document->title = malloc(strlen(p_input_buff) + 1);
    strcpy(new_document->title, p_input_buff);

    user->note_titles = realloc(user->note_titles, (user->note_length + 1) * sizeof(char *));
    user->note_titles[user->note_length] = malloc(strlen(new_document->title) + 1);
    strcpy(user->note_titles[user->note_length], new_document->title);

    style_printf("\n\n :: TYPE AWAY :: \n\n", BRIGHT_WHITE);
    style_printf("================================================================\n", LIGHT_GREEN);
    char contents_buff[BUFFER_SIZE];
    char *p_contents_buff = fgets(contents_buff, BUFFER_SIZE, stdin);
    strtok(p_contents_buff, "\n");

    new_document->contents = malloc(strlen(p_contents_buff) + 1);
    strcpy(new_document->contents, p_contents_buff);

    new_document->created_at = current_date_time;
    new_document->updated_at = current_date_time;

    return new_document;
};

Document *load_document(const char *full_path_to_doc)
{
    FILE *fp = fopen(full_path_to_doc, "rb");
    if (fp == NULL)
    {
        style_printf("ERROR :: file | %s returned NULL for reading note", LIGHT_RED, full_path_to_doc);
        fclose(fp);
        return NULL;
    }

    Document *loaded_document = malloc(sizeof(Document));

    size_t title_length;
    fread(&title_length, sizeof(size_t), 1, fp);
    loaded_document->title = malloc(title_length);
    fread(loaded_document->title, sizeof(char), title_length, fp);

    size_t contents_length;
    fread(&contents_length, sizeof(size_t), 1, fp);
    loaded_document->contents = malloc(contents_length);
    fread(loaded_document->contents, sizeof(char), contents_length, fp);

    loaded_document->created_at = malloc(sizeof(struct tm));
    fread(loaded_document->created_at, sizeof(struct tm), 1, fp);
    loaded_document->updated_at = malloc(sizeof(struct tm));
    fread(loaded_document->updated_at, sizeof(struct tm), 1, fp);

    fclose(fp);

    return loaded_document;
}

char *doc_full_path_string(const char *docs_base_dir, char *doc_title)
{
    char title[strlen(doc_title) + 1];
    strcpy(title, doc_title);

    strcat(title, ".bin");

    char *full_path = malloc(MAX_FILE_PATH);
    strcpy(full_path, docs_base_dir);
    strcat(full_path, title);

    return full_path;
}

void free_document(Document *loaded_document)
{
    free(loaded_document->contents);
    free(loaded_document->title);
    free(loaded_document->created_at);
    free(loaded_document->updated_at);
    free(loaded_document);
};