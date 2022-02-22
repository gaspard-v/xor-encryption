#ifndef TERMINAL_COLOR_H
#define TERMINAL_COLOR_H
#if defined(__linux__) //Linux host
    #define DEFAULT_COLOR 0
    #define BRIGHTER_COLOR 1
    #define UNDERLINE_TEXT 4
    #define FLASHING_TEXT 5
    #define BLACK_FOREGROUND 30
    #define RED_FOREGROUND 31
    #define GREEN_FOREGROUND 32
    #define YELLOW_FOREGROUND 33
    #define BLUE_FOREGROUND 34
    #define PURPLE_FOREGROUND 35
    #define CYAN_FOREGROUND 36
    #define WHITE_FOREGROUND 37
    #define BLACK_BACKGROUND 40
    #define RED_BACKGROUND 41
    #define GREEN_BACKGROUND 42
    #define YELLOW_BACKGROUND 43
    #define BLUE_BACKGROUND 44
    #define PURPLE_BACKGROUND 45
    #define CYAN_BACKGROUND 46
    #define WHITE_BACKGROUND 47

    #define set_colors(...) _set_colors(sizeof((int[]){__VA_ARGS__})/sizeof(int), __VA_ARGS__)
    int _set_colors(int n, ...);

#elif _WIN32 //Windows host
    #include <windows.h>
    #define DEFAULT_COLOR 0
    #define BRIGHTER_COLOR FOREGROUND_INTENSITY	
    #define UNDERLINE_TEXT COMMON_LVB_UNDERSCORE
    #define FLASHING_TEXT -1
    #define BLACK_FOREGROUND -1
    #define RED_FOREGROUND FOREGROUND_RED
    #define GREEN_FOREGROUND FOREGROUND_GREEN
    #define YELLOW_FOREGROUND FOREGROUND_RED | FOREGROUND_GREEN
    #define BLUE_FOREGROUND FOREGROUND_BLUE
    #define PURPLE_FOREGROUND FOREGROUND_BLUE | FOREGROUND_RED
    #define CYAN_FOREGROUND FOREGROUND_BLUE | FOREGROUND_GREEN
    #define WHITE_FOREGROUND FOREGROUND_RED	| FOREGROUND_BLUE | FOREGROUND_GREEN
    #define BLACK_BACKGROUND -1
    #define RED_BACKGROUND BACKGROUND_RED
    #define GREEN_BACKGROUND BACKGROUND_GREEN
    #define YELLOW_BACKGROUND BACKGROUND_RED | BACKGROUND_GREEN
    #define BLUE_BACKGROUND BACKGROUND_BLUE
    #define PURPLE_BACKGROUND BACKGROUND_BLUE | BACKGROUND_RED
    #define CYAN_BACKGROUND BACKGROUND_BLUE | BACKGROUND_GREEN
    #define WHITE_BACKGROUND BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED

    #define set_colors(...) _set_colors(sizeof((int[]){__VA_ARGS__})/sizeof(int), __VA_ARGS__)
    int _set_colors(int n, ...);

#else //unknow host
    #define set_colors(...)
#endif

#endif