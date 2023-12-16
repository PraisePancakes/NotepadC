#include <stdio.h>
#include <stdlib.h>
#include "document.h"
#include "user.h"
#include "gui.h"
#include <windows.h>

/*
    !!to build and run : mkdir build, cmake -> exec
   :: TO-DO ::
   1 : IF NOT FIRST TIME CREATING, STAMP UPDATED DATE INTO FILE;
   2 : REFACTOR
*/

int main()
{
    hc = GetStdHandle(STD_OUTPUT_HANDLE);

    const char *version = "v0.0.5-alpha";
    const char *user_filepath = ".././save/User/user.bin";
    const char *documents_base_directory = ".././save/Docs/";
    const unsigned short int MENU_EXIT = 4;
    unsigned short int menu_option = 0;

    User *user = load_user(user_filepath);
    if (user == NULL)
    {
        user = get_user();
    }
    else
    {
        style_printf("WELCOME BACK %s", LIGHT_GREEN, user->username);
    }

    getch();

    while (menu_option != MENU_EXIT)
    {
        system("cls");
        fflush(stdin);
        style_printf("=== WELCOME TO NOTEPAD C verson %s === \n", LIGHT_AQUA, version);
        struct tm *current_date_time = get_current_date_time();
        display_current_date_time(current_date_time);
        menu_option = get_menu_option();
        switch (menu_option)
        {
        case 1:
            system("cls");
            style_printf(":: CREATE A NOTE :: \n", BRIGHT_WHITE);
            display_current_date_time(current_date_time);
            Document *new_document = create_document(current_date_time, user);
            char *full_path_to_doc = doc_full_path_string(documents_base_directory, new_document->title);
            save_document(full_path_to_doc, new_document);
            user->note_length++;
            free(new_document);
            free(full_path_to_doc);
            getch();
            break;
        case 2:
            system("cls");
            style_printf(":: CHOOSE A NOTE TO VIEW ::\n", BRIGHT_WHITE);
            if (user->note_length == 0)
            {
                style_printf(":: YOU CURRENTLY HAVE %d NOTES ::\n", LIGHT_RED, user->note_length);
                getch();
                break;
            }

            style_printf(":: YOU CURRENTLY HAVE %d NOTES ::\n", LIGHT_BLUE, user->note_length);
            for (int i = 0; i < user->note_length; i++)
            {
                style_printf("%d : %s\n", BRIGHT_WHITE, i, user->note_titles[i]);
            }

            int option = 0;
            style_printf("Enter : ", BRIGHT_WHITE);
            scanf("%d", &option);
            char *full_path_to_load_doc = doc_full_path_string(documents_base_directory, user->note_titles[option]);
            Document *loaded_document = load_document(full_path_to_load_doc);
            if (loaded_document == NULL)
            {
                free(loaded_document);
                style_printf("ERROR :: file | failed to open file for reading", LIGHT_RED);
                getch();
                break;
            }
            system("cls");
            display_document(loaded_document);
            free_document(loaded_document);
            free(full_path_to_load_doc);

            getch();
            break;
        case 3:
            system("cls");
            style_printf(":: CHOOSE A NOTE TO DELETE :: \n", BRIGHT_WHITE);
            if (user->note_length == 0)
            {
                style_printf(":: YOU CURRENTLY HAVE %d NOTES ::\n", LIGHT_RED, user->note_length);
                getch();
                break;
            }

            style_printf(":: YOU CURRENTLY HAVE %d NOTES ::\n", LIGHT_BLUE, user->note_length);
            for (int i = 0; i < user->note_length; i++)
            {
                style_printf("%d : %s\n", BRIGHT_WHITE, i, user->note_titles[i]);
            }
            option = 0;
            style_printf("Enter : ", BRIGHT_WHITE);
            scanf("%d", &option);
            char *full_path_to_delete_document = doc_full_path_string(documents_base_directory, user->note_titles[option]);

            if (delete_document(user, option, full_path_to_delete_document) == 0)
            {
                style_printf(":: DOCUMENT REMOVED SUCCESSFULLY ::", LIGHT_GREEN);
                getch();
                break;
            }
            else
            {
                style_printf("ERROR :: file | failed to be removed ", LIGHT_RED);
            };

            getch();
            break;
        case 4:
            save_user(user_filepath, user);
            free_user(user);
            style_printf(":: NOTEPAD C PROCESS TERMINATED SUCCESSFULLY ::", LIGHT_GREEN);
            break;
        default:
        {
            style_printf("ERROR :: invalid menu option try again ", LIGHT_RED);
            getch();
            break;
        }
        }
    }

    return 0;
}
