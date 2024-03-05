README.TXT

PROJECT: PACMAN
PROGRAMMING LANGUAGE: C++
IDE: MICROSOFT VISUAL STUDIO (C++)

ABOUT PROJECT CREATORS 

21L-5691 Abdurrehman Haroon (BS-DS 2A)
21L-6269 Eesha Tariq (BS-DS 2A)

*** ENJOY! ***


ABOUT GAME:

1. Pacman is an 80s Japanese arcade game where the player takes the form of a 
character called 'Pacman' (a yellow circle) who needs to escape from the ghosts
and eat pellets for points.

2. In our cat-shaped map Pacman, each blue line represents an obstacle, where
our Pacman (yellow 'O') cannot go. Each ghost is represented by its signature
color (eg. orange for Clyde) and its initial (eg. 'C' for Clyde). Every white
dot represents a pellet our Pacman is supposed to eat in order to gain +10 
points. Every small white square represents an energizer which, upon consumption,
makes the Pacman temporarily invulnerable to the ghosts, and lets it consume it
for an additional +100 points. Each energizer eaten grants Pacman +30 points.

3. Pacman is given three lives in the beginning of the game. If Pacman collides
with any of our three ghosts without consuming the energizer, or after the
energizer has lost its effects, Pacman will reset its position and lose a life.
After losing all three lives, the game ends and the final score is displayed.

4. If Pacman consumes all the pellets and even a single life remains by the end,
the player wins the game and is shown their final score.


GHOST MECHANICS:

1. CLYDE (orange, C): random ghost

2. BLINKY (red, B): direct approach AI ghost 1

Weakness: energizer


HOW TO PLAY:

1. Use W to move up, A to move left, D to move right and S to move down.

2. Avoid getting caught by the ghosts.

3. Make sure to wisely use the energizers!

4. The tunnel in the middle of the map lets you teleport to the other end
(use the bottom left/top right).


SCORING:

1. Each pellet gains you 5 points.

2. Each energizer gains you 30 points.

3. Each ghost eaten gains you 100 points.