#include "terminal_color.h"
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#if defined(__linx__)
#define COLOR_PREFIX \x1b[
#define COLOR_SUFFIX m
int _set_colors(int n, ...)
{
    va_list color_list;
    va_start(color_list, n);
    int retour = printf(QUOTE(COLOR_PREFIX));
    for(int i = 0 ;; i++)
    {
        int current = (int)va_arg(color_list, int);
        retour += printf("%d", current);
        if(i == n-1)
            break;
        retour += printf(";");
    }
    retour += printf(QUOTE(COLOR_SUFFIX));
    va_end(color_list);
    return retour;
}
#elif _WIN32
#include <windows.h>
int _set_colors(int n, ...)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    static WORD saved_attributes = 0;
    va_list color_list;
    int retour = 0;
    va_start(color_list, n);
    /* Save current attributes */
    if(!saved_attributes)
    {
        retour += GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
    }
    WORD text_attribute = 0;
    for(int i = 0 ; i < n ; i++)
    {
        WORD current = (WORD)va_arg(color_list, int);
        if((signed short)current == -1)
            continue;
        else if(current == 0)
        {
            text_attribute = saved_attributes;
            break;
        }
        text_attribute |= current;
    }
    retour += SetConsoleTextAttribute(hConsole, text_attribute);
    return retour;
}
#else

#endif