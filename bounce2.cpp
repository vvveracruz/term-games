#include <ncurses.h>
#include <unistd.h>

#include <iostream>
using namespace std;

/*
    run:      Game loop.
*/
void run() {
    // get terminal dimensions
    int height;
    int width;
    getmaxyx(stdscr, height, width);

    // initialise ball
    int ballx;
    int bally;

    srand(time(NULL));  // seed rand
    ballx = rand() % (width - 2) + 1;
    bally = rand() % (height - 2) + 1;

    // initialise dir
    int dirx = 1;
    int diry = 1;

    // define color pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);


    // initialise colours
    int color_pair;
    color_pair = rand() % 7 + 1;

    while (getch() == ERR) {
        attron(COLOR_PAIR(color_pair));
        mvprintw(bally, ballx, "o");
        attroff(COLOR_PAIR(color_pair));

        // update ball location
        ballx += dirx;
        bally += diry;

        // bounce ball on boundaries
        if (ballx == width - 1 || ballx == 0) {
            dirx *= -1;
            color_pair = rand() % 4 + 1;
        };
        if (bally == height - 1 || bally == 0) {
            diry *= -1;
            color_pair = rand() % 4 + 1;
        };

        refresh();
        usleep(100000);
        clear();
    }
}

/*
    main:     Mostly ncurses handling.
*/
int main() {
    // start up ncurses
    initscr();
    nodelay(stdscr, TRUE);  // don't wait for \n for getch to parse input
    cbreak();               // switch off input buffering
    curs_set(FALSE);        // don't place a cursor on the screen
    start_color();

    run();

    // close ncurses
    endwin();
    return 0;
}