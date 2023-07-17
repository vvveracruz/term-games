#include <iostream>
#include <list>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

#define HEAD "O"
#define BODY "o"
#define FOOD "*"

typedef struct _Coords {
    int x;
    int y;

    bool operator==(_Coords const& other) const {
        return (x == other.x) && (y == other.y);
    }
    _Coords operator*(int scalar) const {
        _Coords result;
        result.x = x * scalar;
        result.y = y * scalar;
        return result;
    }
} Coords;

#define UP    Coords{0, 1};
#define DOWN  Coords{0, -1};
#define LEFT  Coords{-1, 0};
#define RIGHT Coords{1, 0};

typedef struct _Snake {
    Coords head;
    Coords dir;
    list<Coords> body;
} Snake;

Coords generateCoords(int height, int width) {
    int headx;
    int heady;

    headx = rand() % (width - 2) + 1;
    heady = rand() % (height - 2) + 1;

    Coords coords = {headx, heady};
    return coords;
}

Coords changeDir(char c, Snake snake) {
    Coords new_dir = snake.dir;
    switch (c) {
        case 'A': new_dir = DOWN; break;
        case 'B': new_dir = UP; break;
        case 'C': new_dir = RIGHT; break;
        case 'D': new_dir = LEFT; break;
    }
    // don't allow 180deg turns when you have a body (this just kills you)
    if (snake.dir * -1 == new_dir & snake.body.size() > 0) {
        return snake.dir;
    }
    return new_dir;
}

void run() {
    // get terminal dimensions
    int height;
    int width;
    getmaxyx(stdscr, height, width);

    srand(time(NULL));  // seed rand

    Coords food = generateCoords(height, width);

    // init snake
    Coords inithead = generateCoords(height, width);
    Coords initdir = {1, 0};
    list<Coords> initbody;

    Snake snake = {inithead, initdir, initbody};

    // main game loop
    bool dead = false;
    while (!dead) {
        mvprintw(snake.head.y, snake.head.x, HEAD);
        mvprintw(food.y, food.x, FOOD);

        // draw body
        for (auto piece : snake.body) {
            // die if eating body
            if (piece == snake.head ) {
                dead = true;
            }
            mvprintw(piece.y, piece.x, BODY);
        }

        // body follows head
        snake.body.push_front(snake.head);
        snake.body.pop_back();

        // move
        snake.head.x += snake.dir.x;
        snake.head.y += snake.dir.y;

        // die on boundaries
        if (snake.head.x == width - 1 || snake.head.x == 0 ||
            snake.head.y == height - 1 || snake.head.y == 0) {
            dead = true;
        }

        // eat food
        if (snake.head == food) {
            // add one more body piece (at dummy location)
            snake.body.push_back(Coords{-1, -1});
            food = generateCoords(height, width);
        }

        // change direction
        if (getch() == '\033') {  // if the first value is esc
            getch();              // skip the [
            snake.dir = changeDir(getch(), snake);
        }

        refresh();
        usleep(300000);
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
    noecho();               // don't display input

    run();

    // close ncurses
    endwin();

    return 0;
}