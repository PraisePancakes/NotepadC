#ifndef GUI_H
#define GUI_H
#include "document.h"
#include <time.h>
#include <windows.h>

enum Colors
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    AQUA = 3,
    RED = 4,
    PURPLE = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 0xA,  // 0xA ≡ 10
    LIGHT_AQUA = 0xB,   // 0xB ≡ 11
    LIGHT_RED = 0xC,    // 0xC ≡ 12
    LIGHT_PURPLE = 0xD, // 0xD ≡ 13
    LIGHT_YELLOW = 0xE, // 0xE ≡ 14
    BRIGHT_WHITE = 0xF, // 0xF ≡ 15
    DEFAULT = 0x07
};

HANDLE hc;

unsigned short int get_menu_option();
void style_printf(const char *format, WORD text_color, ...);
void display_document(Document *loaded_document);
void display_current_date_time(struct tm *current_date_time);

#endif