import curses
from random import randint
from time import sleep

head_char = 'O'
body_char = 'o'
food_char = '*'

def generate_coords(maxx, maxy):
    '''Generates a random coordinate pair.'''
    return randint(0, maxx - 1), randint(0, maxy -1 )

def run(window):
    '''Main function for the game.'''
    maxx, maxy = window.getmaxyx() # get terminal size

    while True:
        window.erase()
        headx, heady = generate_coords(maxx, maxy) # generate head coords
        window.addch(headx, heady, head_char) # draw head

        # main game loop goes here

        window.refresh()
        sleep(1)

def main():
    '''Handles curses initialization and cleanup.'''
    window = curses.initscr()
    window.keypad(True) # enable keypad mode
    curses.curs_set(False) # hide cursor
    
    run(window)

    # cleanup
    curses.nocbreak()
    window.keypad(False)
    curses.endwin()

main()