#include "user.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gui.h"

#define BUFFER_SIZE 256

User *get_user()
{
    User *new_user = malloc(sizeof(User));

    char input[BUFFER_SIZE];
    style_printf("Enter your username : ", LIGHT_YELLOW);
    char *p_input = fgets(input, BUFFER_SIZE, stdin);
    strtok(p_input, "\n");

    new_user->username = malloc(strlen(p_input) + 1);
    strcpy(new_user->username, p_input);
    style_printf("Welcome ", LIGHT_GREEN, new_user->username);
    style_printf("%s", LIGHT_BLUE, new_user->username);
    style_printf(", press any key to begin...", LIGHT_GREEN, new_user->username);
    new_user->note_titles = NULL;
    new_user->note_length = 0;

    return new_user;
};

void save_user(const char *filepath, User *user)
{
    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR :: user | %s returned NULL for writing user \n", filepath);
        fclose(fp);
        return;
    }

    size_t username_length = strlen(user->username) + 1;
    fwrite(&username_length, sizeof(size_t), 1, fp);
    fwrite(user->username, sizeof(char), username_length, fp);

    fwrite(&(user->note_length), sizeof(int), 1, fp);

    for (int i = 0; i < user->note_length; i++)
    {
        size_t title_length = strlen(user->note_titles[i]) + 1;
        fwrite(&title_length, sizeof(size_t), 1, fp);
        fwrite(user->note_titles[i], sizeof(char), title_length, fp);
    }

    fclose(fp);
}

User *load_user(const char *filepath)
{
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        fclose(fp);
        return NULL;
    }

    User *user = malloc(sizeof(User));

    size_t username_length;
    if (fread(&username_length, sizeof(size_t), 1, fp) != 1)
    {
        fclose(fp);
        free(user);
        return NULL;
    };

    user->username = malloc(username_length);
    if (fread(user->username, sizeof(char), username_length, fp) != username_length)
    {
        fclose(fp);
        free(user->username);
        free(user);
        return NULL;
    };

    if (fread(&(user->note_length), sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        free(user->username);
        free(user);
        return NULL;
    };

    user->note_titles = malloc(user->note_length * sizeof(char *));
    for (int i = 0; i < user->note_length; i++)
    {
        size_t title_length;
        if (fread(&title_length, sizeof(size_t), 1, fp) != 1)
        {
            fclose(fp);
            free(user->username);
            free(user->note_titles);
            free(user);
            return NULL;
        }

        user->note_titles[i] = malloc(title_length);
        if (fread(user->note_titles[i], sizeof(char), title_length, fp) != title_length)
        {
            fclose(fp);
            free(user->username);
            free(user->note_titles[i]);
            free(user->note_titles);
            free(user);
            return NULL;
        }
    }

    fclose(fp);
    return user;
}

void free_user(User *user)
{
    free(user->username);
    for (int i = 0; i < user->note_length; i++)
    {
        free(user->note_titles[i]);
    }
    free(user->note_titles);
    free(user);
};
