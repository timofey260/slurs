# Slurs

Slurs is simple reimagination of [curses](https://en.wikipedia.org/wiki/Ncurses).

## Why?

The main problem of curses is that it only works out-of-the-box
with UNIX like operating systems(Windows users required to install additional libraries).

The second problem is uniqueness of every terminal.
Some features of terminal can be used and some don't(like custom colors).

Slurs solves both of these by using GUI instead of TUI(though that makes some terminal features non-accessible
it also gives us more control over stuff on screen). All of Slurs's functions are guaranteed to work on Slurs

## How?

Slurs uses [raylib](https://raylib.com) to render the interface.
All characters you see on screen is a single shader that renders all characters at the same time.