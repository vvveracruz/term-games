import curses
from random import randint
from time import sleep

head_char = 'O'
body_char = 'o'
food_char = '*'

def generate_coords(maxx, maxy):
    '''Generates a random coordinate pair.'''
    return randint(0, maxx - 1), randint(0, maxy -1 )

def run(stdscr):
    '''Main function for the game.'''
    maxx, maxy = stdscr.getmaxyx() # get terminal size

    while True:
        headx, heady = generate_coords(maxx, maxy) # generate head coords
        stdscr.addch(headx, heady, head_char) # draw head
        stdscr.refresh()
        sleep(1)

def main():
    '''Handles curses initialization and cleanup.'''
    stdscr = curses.initscr()
    stdscr.keypad(True) # enable keypad mode
    curses.curs_set(False) # hide cursor
    run(stdscr)

    # cleanup
    curses.nocbreak()
    stdscr.keypad(False)
    curses.echo()
    curses.endwin()

main()