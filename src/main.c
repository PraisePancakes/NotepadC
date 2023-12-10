#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MONTH_OFFSET 1;
#define YEAR_OFFSET 1900;

typedef struct User
{
    char *username;
    unsigned short int age;
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

int main()
{
    printf("HELLO WORLD 1");
    Date *current_date_time = get_current_date_time();

    printf("%d", current_date_time->current_date->tm_year);
    return 0;
}