#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MONTH_OFFSET 1;
#define YEAR_OFFSET 1900;

typedef struct User
{
    char *username;
    unsigned short int age;
    struct DocumentNode *document_head;

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
    char *subject;
    char *contents;
} Document;

typedef struct DocumentNode
{
    Document *data;
    struct Document *next;
} DocumentNode;

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
}

int main()
{
    const char *version = "v0.0.0-unreleased";
    system("cls");
    printf("=== WELCOME TO NOTEPAD C verson %s === \n", version);
    Date *current_date_time = get_current_date_time();
    display_current_date_time(current_date_time);

    return 0;
}