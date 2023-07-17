#include <iostream>
#include <list>
#include <ncurses.h>
#include <unistd.h>
using namespace std;

typedef struct _Coords {
    int x;
    int y;
    bool operator==(_Coords const& other) const {
        return (x == other.x) && (y == other.y);
    };
} Coords;

typedef struct _Ball {
    Coords pos;
    Coords dir;
    char const* body;
} Ball;

int randomDir() {
    bool b = rand() > (RAND_MAX / 2);
    return b ? 1 : -1;
};

Coords generateCoords(int height, int width) {
    int headx;
    int heady;

    headx = rand() % (width - 2) + 1;
    heady = rand() % (height - 2) + 1;

    Coords coords = {headx, heady};
    return coords;
};

Ball generateBall(int height, int width, char const* body) {
    Coords initpos = generateCoords(height, width);
    Coords initdir = {randomDir(), randomDir()};
    Ball ball = {initpos, initdir, body};
    return ball;
};

/*
    run:      Game loop.
*/
void run(int N) {
    // get terminal dimensions
    int height;
    int width;
    getmaxyx(stdscr, height, width);

    srand(time(NULL));  // seed rand

    list<Ball> balls;
    for (int i = 0; i < N; i++) {
        Ball ball = generateBall(height, width, "o");
        balls.push_front(ball);
    }

    while (getch() != 'q') {
        for (auto& ball : balls) {
            mvprintw(ball.pos.y, ball.pos.x, ball.body);

            // update ball location
            ball.pos.x += ball.dir.x;
            ball.pos.y += ball.dir.y;

            // bounce ball on boundaries
            if (ball.pos.x == width - 1 || ball.pos.x == 0) {
                ball.dir.x *= -1;
            };
            if (ball.pos.y == height - 1 || ball.pos.y == 0) {
                ball.dir.y *= -1;
            };
        }

        refresh();
        usleep(100000);
        clear();
    }
}

/*
    main:     Mostly ncurses handling.
*/
int main() {
    cout << endl;
    cout << "How many balls?" << endl;
    int N = 0;
    while (N == 0) {
        cin >> N;
    }
    usleep(500000);
    cout << endl;
    usleep(500000);
    cout << "Running with " << N << " balls." << endl;
    usleep(500000);
    cout << endl;
    usleep(500000);
    cout << endl;

    // start up ncurses
    initscr();
    nodelay(stdscr, TRUE);  // don't wait for \n for getch to parse input
    cbreak();               // switch off input buffering
    curs_set(FALSE);        // don't place a cursor on the screen
    noecho();               // don't display input

    run(N);

    // close ncurses
    endwin();
    return 0;
}