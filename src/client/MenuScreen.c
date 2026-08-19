#include <ncurses.h>


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
}