#include "gui.h"
#include <stdio.h>

void style_printf(const char *format, WORD text_color, ...)
{
    SetConsoleTextAttribute(hc, text_color | FOREGROUND_INTENSITY);

    va_list args;
    va_start(args, text_color);
    vprintf(format, args);
    va_end(args);

    SetConsoleTextAttribute(hc, DEFAULT);
}

unsigned short int get_menu_option()
{
    unsigned short int option = 0;
    style_printf(":::: MENU ::::\n", LIGHT_YELLOW);
    style_printf("1 : Add a note \n2 : View a note \n3 : Edit a note \n", BRIGHT_WHITE);
    style_printf("4 : Quit \n", LIGHT_RED);
    style_printf("Enter : ", LIGHT_BLUE);
    scanf("%hu", &option);
    return option;
};

void display_document(Document *loaded_document)
{
    style_printf("Subject : %s\n", BRIGHT_WHITE, loaded_document->title);
    style_printf("Created at : %d/%d/%d\n", BRIGHT_WHITE, loaded_document->created_at->tm_mon, loaded_document->created_at->tm_mday, loaded_document->created_at->tm_year);
    style_printf(":: CONTENTS ::\n====================================================\n", LIGHT_GREEN);
    style_printf("%s\n", BRIGHT_WHITE, loaded_document->contents);
};

void display_current_date_time(struct tm *current_date_time)
{
    style_printf("CURRENT DATE : %02d/%02d/%02d \n", BRIGHT_WHITE, current_date_time->tm_mon, current_date_time->tm_mday, current_date_time->tm_year);
    style_printf("CURRENT TIME : %02d:%02d:%02d %s \n", BRIGHT_WHITE, current_date_time->tm_hour > 12 ? current_date_time->tm_hour - 12 : current_date_time->tm_hour, current_date_time->tm_min, current_date_time->tm_sec, current_date_time->tm_hour > 12 ? "PM" : "AM");
};
