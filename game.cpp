#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "menu.h"

using namespace std;

//Define game window size
int gameWindowSizeY = 20;
int gameWindowSizeX = 60;

//The Player class keeps track of the player's name, score, and remaining lives
class Player {
public:
    //Player name
    string name;
    //Player score
    int score;
    //Player lives
    int lives;

    //Initialize player
    void init(string name, int score, int lives) {
        this -> name = name;
        this -> score = score;
        this -> lives = lives;
    }
};

//The Brick class represents an individual brick and keeps track of its position and whether it has been destroyed
class Brick {
public:
    //Brick art
    string sprite = "#";
    //Brick position
    int x, y;
    //Destroyed status of brick
    bool isDestroyed;

    //Initialize individual brick
    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }
};

//The Level class represents a level of the game and is responsible for creating and drawing the bricks
class Level {
public:
    int rows = 3;
    int cols = 55;
    //2D array to store map of bricks
    Brick bricks[3][55];
    
    //Initialize level
    void init() {
        for(int y = 0; y < rows; y++) {
            for(int x = 0; x < cols; x++) {
                Brick brick;
                brick.init(y + 2, x + 2);
                bricks[y][x] = brick;
            }
        }
    }

    void draw(WINDOW* window)  {
        //check if bricks are destroyed and print bricks that aren't
        for(int y = 0; y < rows; y++) {
            for(int x = 0; x < cols; x++) {
                if(!bricks[y][x].isDestroyed)
                    mvwprintw(window, bricks[y][x].y, bricks[y][x].x, bricks[y][x].sprite.c_str());
            }
        }
    }
};

//The Paddle class represents the player's paddle and is responsible for moving it left and right based on user input
class Paddle {
public:
    //Paddle art
    string sprite = "======"; 
    //Paddle position
    int x, y;

    //Initialize paddle
    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

    //Update paddle position according to player input
    void update(int input) {
        switch(input) {
            case KEY_LEFT:
                if(x > 2) {
                    x -= 2;
                }
                break;
            case KEY_RIGHT:
                if(x < gameWindowSizeX - 7) {
                    x += 2;
                }
                break;
            default:
                break;
        }
    }

    //Draw paddle in the game window
    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite.c_str());
    }

    //Erase paddle from the game window
    void erase(WINDOW* window) {
        mvwprintw(window, y, x, "      ");
    }
};

//The Ball class is responsible for handling the ball
class Ball {
public:
    //Ball art
    string sprite = "o";
    //Ball position
    int x, y;
    //Ball velocity
    int dx, dy;
    
    //Initialize ball
    Ball(int y, int x, int dy, int dx) {
        this -> y = y;
        this -> x = x;
        this -> dy = dy;
        this -> dx = dx;
    }

    //Draw ball in the game window
    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite.c_str());
    }

    //Erase ball from the game window
    void erase(WINDOW* window) {
        mvwprintw(window, y, x, " "); 
    }
};

//The game function runs the main game - it accepts the player name as a parameter and passes it to the player class
int game(string playerName) {

    //Randomize seed
    srand(time(nullptr)); 

    //Create a window to show player info
    WINDOW* infoWindow = newwin(3, 60, 0, 0);
    //Draw a box around the info window
    box(infoWindow, 0, 0);
    //Refresh the info window initially
    wrefresh(infoWindow);

    //Create a window for the game
    WINDOW* gameWindow = newwin(gameWindowSizeY, gameWindowSizeX, 3, 0); 
    //Draw a box around the game window
    box(gameWindow, 0, 0); 
    //Refresh the game window initially
    wrefresh(gameWindow); 
    
    //Create a window to show controls
    WINDOW* commandsWindow = newwin(3, 60, 23, 0);
    //Draw a box around the command window
    box(commandsWindow, 0, 0);
    //Print instructions
    mvwprintw(commandsWindow, 1, 1, "[<][>]:Move Paddle                                [Q]:Quit");
    //Refresh command window initially
    wrefresh(commandsWindow);    

    //Initialize the player, level, ball and paddle
    Player player;
    player.init(playerName, 0, 3);

    Level level;
    level.init();

    Ball *ball = new Ball(13, 30, -1, rand() % 3 - 1);

    Paddle paddle;
    paddle.init(17, 1);

    //Draw all the components and refresh the game window initially
    level.draw(gameWindow);
    ball->draw(gameWindow);
    paddle.draw(gameWindow);
    wrefresh(gameWindow);

    //Flags to handle losing a life and player death
    bool restart = false;
    bool died = false;

    //Game loop
    while(true) {
        //Randomize seed
        srand(time(nullptr)); 

        //Get player input
        int input = getch();

        //Quit if user presses 'Q'
        if(input == 'q' || input == 'Q') {
            break;
        }

        //If player dies, exit loop and show Game Over screen
        if(player.lives == 0) {
            died = true;
            break;
        }
        
        //Initialize new ball on losing a life
        if(restart) {
            Ball *ball = new Ball(13, 30, -1, rand() % 3 - 1);
            restart = false;
        }

        //Clears ball from last position to not leave a trail
        ball -> erase(gameWindow);
        //Handle ball collision with walls
        if(ball -> x <= 1 || ball -> x >= gameWindowSizeX - 2) {
            ball -> dx = -ball -> dx;
        }
        //Handle ball collision with roof
        if(ball -> y <= 1) {
            ball -> dy = -ball -> dy;
        }
        //Handle ball falling through
        if(ball -> y >= gameWindowSizeY - 2) {
            //Delete the current ball
            delete ball;
            //Player loses a life
            player.lives -= 1;

            //Wait for user to press Enter before continuing the game
            wattron(gameWindow, A_BOLD);
            wattron(gameWindow, A_REVERSE);
            mvwprintw(gameWindow, 10, 18, "PRESS ENTER TO CONTINUE");
            wattroff(gameWindow, A_BOLD);
            wattroff(gameWindow, A_REVERSE);
            wrefresh(gameWindow);
            while(getch() != '\n') 
            {

            }
            mvwprintw(gameWindow, 10, 18, "                       ");
            restart = true;
            continue;
        }
        //Handle collision with paddle
        if(ball -> y == paddle.y - 1 && ball -> x >= paddle.x - 1 && ball -> x < paddle.x + 6) { /*account for condition when ball hits at an angle*/
            ball -> dy = -ball -> dy;
            ball -> dx = max(-1, min(1, ball -> dx + (rand() % 3 - 1)));
        }

        //Handle collision with bricks
        for(int q = 0; q < 3; q++) {
            for(int p = 0; p < gameWindowSizeX - 5; p++) {
                if(ball -> x == level.bricks[q][p].x && ball -> y == level.bricks[q][p].y)
                    if(!level.bricks[q][p].isDestroyed) {
                        ball -> dy = -ball -> dy;
                        level.bricks[q][p].isDestroyed = true;
                        //Update player score
                        player.score += 10;
                    }
            }
        }
        //Update ball position
        ball -> x += ball -> dx;
        ball -> y += ball -> dy;
        ball -> draw(gameWindow);

        //Update paddle position
        paddle.erase(gameWindow);
        paddle.update(input);
        paddle.draw(gameWindow);

        //Update player info
        string playerInfo = "Score:" + to_string(player.score) + "                                       " + "Lives:" + to_string(player.lives);
        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());
        wrefresh(infoWindow);

        //Refresh game window
        level.draw(gameWindow);
        wrefresh(gameWindow);

        //Clear buffered input from previous frame
        flushinp(); 
        //Sleep for 100000 microseconds before updating
        usleep(100000);
    }

    if(died) gameOver(player.name, player.score);
    else mainmenu();

    return 0;
}