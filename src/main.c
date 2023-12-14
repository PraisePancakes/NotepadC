#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#define MONTH_OFFSET 1
#define YEAR_OFFSET 1900
#define BUFFER_SIZE 256

typedef struct User
{
    char *username;
    char **note_titles;
    int note_length;

} User;

typedef struct Date
{
    struct tm *current_date;
    struct tm *current_time;
} Date;

typedef struct Document
{
    User *author;
    Date *created_at;
    Date *updated_at;
    char *title;
    char *contents;
} Document;

/*
   :: TO-DO ::
   1 : ALLOW USER TO TYPE CONTENTS OF FILE INTO COMMAND LINE
        i. get user info
   2 : CREATE A TXT FILE
   3 : COPY COMMAND LINE CONTENTS INTO TXT FILE
   4 : STAMP CREATED DATE INTO FILE
   5 : IF NOT FIRST TIME CREATING, STAMP UPDATED DATE INTO FILE;
   6 : SAVE TXT FILE
   7 : IMPLEMENT CONSOLE COLOR HANDLE THROUGH WINDOWS HEADER


*/

Date *get_current_date_time();
void display_current_date_time(Date *current_date_time);
unsigned short int get_menu_option();

User *get_user()
{
    User *new_user = malloc(sizeof(User));

    char input[BUFFER_SIZE];
    printf("Enter your username : ");
    char *p_input = fgets(input, BUFFER_SIZE, stdin);
    strtok(p_input, "\n");

    new_user->username = malloc(strlen(p_input) + 1);
    strcpy(new_user->username, p_input);

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

    fclose(fp);
}

User *load_user(const char *filepath)
{
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR :: user | %s returned NULL for reading user \n", filepath);
        fclose(fp);
        return NULL;
    }

    User *user = malloc(sizeof(User));

    // Read the username length and then the username
    size_t username_length;
    if (fread(&username_length, sizeof(size_t), 1, fp) != 1)
    {
        fclose(fp);
        free(user);
        return NULL;
    }

    user->username = malloc(username_length);
    if (fread(user->username, sizeof(char), username_length, fp) != username_length)
    {
        fclose(fp);
        free(user->username);
        free(user);
        return NULL;
    }

    // Read the rest of the User struct excluding the username
    if (fread(&(user->note_length), sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        free(user->username);
        free(user);
        return NULL;
    }

    fclose(fp);
    return user;
}

void save_document(const char *filepath, Document *document)
{
    document->title = strcat(document->title, ".bin");
    printf("title : %s \n", document->title);
    filepath = strcat(filepath, document->title);
    printf("filepath : %s \n", filepath);
    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "ERROR :: file | %s returned NULL for writing note", filepath);
        fclose(fp);
        return;
    }

    fclose(fp);
}

Document* create_document() {
    Document* new_document = malloc(sizeof(Document));
};

int main()
{
    const char *version = "v0.0.0-unreleased";
    const char *user_filepath = ".././save/User/user.bin";
    const char *documents_filepath = ".././save/Docs/";
    const unsigned short int MENU_EXIT = 4;
    unsigned short int menu_option = 0;

    User *user = load_user(user_filepath);
    if (user == NULL)
    {
        user = get_user();
    }
    else
    {
        printf("WELCOME BACK %s", user->username);
    }

    getch();

    while (menu_option != MENU_EXIT)
    {
        system("cls");
        fflush(stdin);
        printf("=== WELCOME TO NOTEPAD C verson %s === \n", version);
        Date *current_date_time = get_current_date_time();
        display_current_date_time(current_date_time);
        menu_option = get_menu_option();
        switch (menu_option)
        {
        case 1:
            printf(":: CREATE A NOTE :: \n");
            Document *new_document = create_document();
            save_document(documents_filepath, new_document);
            user->note_length++;
            free(new_document);
            getch();
            break;
        case 2:
            system("cls");
            printf(":: VIEW ALL NOTES ::\n");
            if (user->note_length == 0)
            {
                printf("You currently have %d notes", user->note_length);
                getch();
                break;
            }
            getch();
            break;
        case 3:
            getch();
            break;
        case 4:
            save_user(user_filepath, user);
            printf(":: NOTEPAD C PROCESS TERMINATED SUCCESSFULLY ::");
            break;
        default:
        {
            printf("ERROR :: invalid menu option try again ");
            getch();
            break;
        }
        }
    }

    return 0;
}

Date *get_current_date_time()
{
    time_t t = time(NULL);
    Date *new_date = malloc(sizeof(struct tm) * 2);
    new_date->current_date = localtime(&t);
    new_date->current_time = localtime(&t);
    new_date->current_date->tm_mon = new_date->current_date->tm_mon + MONTH_OFFSET;
    new_date->current_date->tm_year = new_date->current_date->tm_year + YEAR_OFFSET;

    return new_date;
}

void display_current_date_time(Date *current_date_time)
{
    printf("CURRENT DATE : %02d/%02d/%02d \n", current_date_time->current_date->tm_mon, current_date_time->current_date->tm_mday, current_date_time->current_date->tm_year);
    printf("CURRENT TIME : %02d:%02d:%02d %s \n", current_date_time->current_time->tm_hour > 12 ? current_date_time->current_time->tm_hour - 12 : current_date_time->current_time->tm_hour, current_date_time->current_time->tm_min, current_date_time->current_time->tm_sec, current_date_time->current_time->tm_hour > 12 ? "PM" : "AM");
};

unsigned short int get_menu_option()
{
    unsigned short int option = 0;
    printf(":::: MENU ::::\n");
    printf("1 : Add a note \n");
    printf("2 : View a note \n");
    printf("3 : Edit a note \n");
    printf("4 : Quit \n");
    printf("Enter : ");
    scanf("%hu", &option);
    return option;
};