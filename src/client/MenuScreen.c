#include <ncurses.h>
#include <stdlib.h>





#include <ncurses.h>
#include <string.h>
#include "data.h"

#define CMD_HEIGHT 5
#define CMD_SIZE 256

WINDOW *gameWin;
WINDOW *cmdWin;

char command[CMD_SIZE];
char lastCommand[CMD_SIZE];
int commandPos = 0;
char commandRES[30];

int initScreen(){
    return 0;
}

int displayMenu()
{
    int height;
    int width;

    // Start ncurses
    initscr();

    start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);

    cbreak();
    noecho();

    // Show cursor
    curs_set(1);

    // Get terminal dimensions
    getmaxyx(stdscr, height, width);

    // Create windows
    gameWin = newwin(
        height - CMD_HEIGHT,
        width,
        0,
        0
    );

    cmdWin = newwin(
        CMD_HEIGHT,
        width,
        height - CMD_HEIGHT,
        0
    );

    
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    
    box(cmdWin, 0, 0);

    
    mvwprintw(gameWin, 0, 0, "      .          ,                   .                   \n _ ._ |*._  _   -+- _ ._.._ _ *._  _.|   _  _.._ _  _  __\n(_)[ )||[ )(/,   | (/,[  [ | )|[ )(_]|  (_](_][ | )(/,_) \n                                        ._|              \n");

    
    mvwprintw(cmdWin, 1, 1, "OTG$ ");

    // Put cursor after OTG$
    wmove(cmdWin, 1, 6);

    
    wrefresh(gameWin);
    wrefresh(cmdWin);

    return 0;
}


void cmdDisplay()
{
    
    werase(cmdWin);
    box(cmdWin, 0, 0);

    mvwprintw(cmdWin, CMD_HEIGHT - 4, 1, "OTG$ %s", lastCommand);

    if (strlen(lastCommand) > 0) {
        mvwprintw(cmdWin, CMD_HEIGHT - 3, 1, "%s", commandRES);
    }

    
    mvwprintw(cmdWin, CMD_HEIGHT - 2, 1, "OTG$ %s", command);

    
    wmove(cmdWin, CMD_HEIGHT - 2, 6 + commandPos);

    
    touchwin(gameWin); 
    wrefresh(gameWin); 
    wrefresh(cmdWin);
}


void handleCommandInput(int key)
{
    
    if (key == ERR)
        return;


    // Enter
    if (key == '\n' || key == KEY_ENTER)
    {
        commandRES[0] = '\0';
        command[commandPos] = '\0';
        strcpy(lastCommand, command);
        char **toks = tokens(command);


    if (toks != NULL)
    {
        char* ptr = commandRES;
        cmd(toks, &ptr);


        

        for (int i = 0; toks[i] != NULL; i++)
            free(toks[i]);

        free(toks);
    }
        

        

        if (strcmp(command, "exit") == 0)
        {
            //
        }

        commandPos = 0;
        command[0] = '\0';
    }


    // Backspace
    else if (key == KEY_BACKSPACE ||
             key == 127 ||
             key == 8)
    {
        if (commandPos > 0)
        {
            commandPos--;

            command[commandPos] = '\0';
        }
    }


    // Normal printable character
    else if (key >= 32 && key <= 126)
    {
        if (commandPos < CMD_SIZE - 1)
        {
            command[commandPos] = key;

            commandPos++;

            command[commandPos] = '\0';
        }
    }


    // Redraw command line
    cmdDisplay(command);
    
}












/*
int displayMenu()
{

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_RED,     COLOR_BLACK);
    init_pair(2, COLOR_GREEN,   COLOR_BLACK);
    init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4, COLOR_BLUE,    COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN,    COLOR_BLACK);
    init_pair(7, COLOR_WHITE,   COLOR_BLACK);



    clear();
    //too big?
    //mvprintw(0, 0, "              .__  .__                  __                       .__              .__                                         \n  ____   ____ |  | |__| ____   ____   _/  |_  ___________  _____ |__| ____ _____  |  |      _________    _____   ____   ______\n /  _ \\ /    \\|  | |  |/    \\_/ __ \\  \\   __\\/ __ \\_  __ \\/     \\|  |/    \\\\__  \\ |  |     / ___\\__  \\  /     \\_/ __ \\ /  ___/\n(  <_> )   |  \\  |_|  |   |  \\  ___/   |  | \\  ___/|  | \\/  Y Y  \\  |   |  \\/ __ \\|  |__  / /_/  > __ \\|  Y Y  \\  ___/ \\___ \\ \n \\____/|___|  /____/__|___|  /\\___  >  |__|  \\___  >__|  |__|_|  /__|___|  (____  /____/  \\___  (____  /__|_|  /\\___  >____  >\n            \\/             \\/     \\/             \\/            \\/        \\/     \\/       /_____/     \\/      \\/     \\/     \\/ \n");
    mvprintw(0, 0, "      .          ,                   .                   \n _ ._ |*._  _   -+- _ ._.._ _ *._  _.|   _  _.._ _  _  __\n(_)[ )||[ )(/,   | (/,[  [ | )|[ )(_]|  (_](_][ | )(/,_) \n                                        ._|              \n");

    refresh();
    return 0;
}*/

//int cmdDisplay(){
//    mvprintw(10, 0, "OTG$ ");
//}