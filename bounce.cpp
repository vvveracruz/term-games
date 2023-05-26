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

    while (getch() == ERR) {
        mvprintw(bally, ballx, "o");

        // update ball location
        ballx += dirx;
        bally += diry;

        // bounce ball on boundaries
        if (ballx == width - 1 || ballx == 0) {
          dirx *= -1;
        };
        if (bally == height - 1 || bally == 0) {
          diry *= -1;
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

    run();

    // close ncurses
    endwin();
    return 0;
}