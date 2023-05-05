#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "menu.h"

using namespace std;


int gameWindowSizeY = 20;
int gameWindowSizeX = 60;


class Player {
public:
    string name;
    int score;
    int lives;

    void init(string name, int score, int lives) {
        this -> name = name;
        this -> score = score;
        this -> lives = lives;
    }
};

class Brick {
public:
    string sprite = "#";
    int x, y;

    bool isDestroyed;

    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }
};

class Level {
public:
    int rows = 3;
    int cols = 55;
    Brick bricks[3][55];
    
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

class Paddle {
public:
    string sprite = "======"; 
    int x, y;

    void init(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

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

    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite.c_str());
    }

    void erase(WINDOW* window) {
        mvwprintw(window, y, x, "      ");
    }
};

class Ball {
public:
    string sprite = "o";
    int x, y;
    int dx, dy;
    
    Ball(int y, int x, int dy, int dx) {
        this -> y = y;
        this -> x = x;
        this -> dy = dy;
        this -> dx = dx;
    }

    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite.c_str());
    }

    void erase(WINDOW* window) {
        mvwprintw(window, y, x, " "); 
    }
};


int game(string playerName) {

    refresh();

    //Randomize seed
    srand(time(nullptr)); 

    WINDOW* infoWindow = newwin(3, 60, 0, 0);
    box(infoWindow, 0, 0);
    wrefresh(infoWindow);

    //Create a window for the game <rows, cols, y, x>
    WINDOW* gameWindow = newwin(gameWindowSizeY, gameWindowSizeX, 3, 0); 
    //Draw a box <window, char for y, char for x> - look at wborder()
    box(gameWindow, 0, 0); 
    //Refresh the window
    wrefresh(gameWindow); 
    
    WINDOW* commandsWindow = newwin(3, 60, 23, 0);
    box(commandsWindow, 0, 0);
    mvwprintw(commandsWindow, 1, 1, "[<][>]:Move Paddle                                [Q]:Quit");
    wrefresh(commandsWindow);    

    //Initiliaze
    Player player;
    player.init(playerName, 0, 3);

    Level level;
    level.init();

    Ball *ball = new Ball(13, 30, -1, rand() % 3 - 1);

    Paddle paddle;
    paddle.init(17, 1);

    //First draw
    level.draw(gameWindow);
    ball->draw(gameWindow);
    paddle.draw(gameWindow);
    wrefresh(gameWindow);

    bool restart = false;

    //Game loop
    while(true) {
        srand(time(nullptr)); 

        int input = getch();

        //Quit if user presses 'Q'
        if(input == 'q' || input == 'Q')
            break;

        if(player.lives == 0) {
            getch();
            break;
        }

        if(restart) {
            restart = false;
            Ball *ball = new Ball(13, 30, -1, rand() % 3 - 1);
        }

        //Clears ball from last position to not leave a trail
        ball -> erase(gameWindow);
        if(ball -> x <= 1 || ball -> x >= gameWindowSizeX - 2) {
            ball -> dx = -ball -> dx;
        }
        if(ball -> y <= 1) {
            ball -> dy = -ball -> dy;
        }
        if(ball -> y >= gameWindowSizeY - 2) {
            delete ball;
            player.lives -= 1;

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

        if(ball -> y == paddle.y - 1 && ball -> x >= paddle.x - 1 && ball -> x < paddle.x + 6) { /*account for slanted angles*/
            ball -> dy = -ball -> dy;
            ball -> dx = max(-1, min(1, ball -> dx + (rand() % 3 - 1)));
        }

        for(int q = 0; q < 3; q++) {
            for(int p = 0; p < gameWindowSizeX - 5; p++) {
                if(ball -> x == level.bricks[q][p].x && ball -> y == level.bricks[q][p].y)
                    if(!level.bricks[q][p].isDestroyed) {
                        ball -> dy = -ball -> dy;
                        level.bricks[q][p].isDestroyed = true;
                        player.score += 10;
                    }
            }
        }
        ball -> x += ball -> dx;
        ball -> y += ball -> dy;
        ball -> draw(gameWindow);

        paddle.erase(gameWindow);
        paddle.update(input);
        paddle.draw(gameWindow);

        string playerInfo = "Score:" + to_string(player.score) + "                                       " + "Lives:" + to_string(player.lives);
        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());
        wrefresh(infoWindow);

        level.draw(gameWindow);
        wrefresh(gameWindow);

        //Clear buffered input from previous frame
        flushinp(); 
        //Sleep for 100000 microseconds before updating
        usleep(100000);
    }

    gameOver(player.name, player.score);

    return 0;
}