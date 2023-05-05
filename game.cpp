#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Paddle {
public:
    const char* sprite = "======"; 
    int length;
    int x, y;

    Paddle(int y, int x) {
        this -> y = y;
        this -> x = x;
    }

    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite);
    }
};

class Ball {
public:
    const char* sprite = "o";
    int x, y;
    int dx, dy;
    
    Ball(int y, int x, int dy, int dx) {
        this -> y = y;
        this -> x = x;
        this -> dy = dy;
        this -> dx = dx;
    }

    void update() {

    }

    void draw(WINDOW* window) {
        mvwprintw(window, y, x, sprite);
    }
};

class Brick {
public:
    const char* sprite = "#";
    int x, y;

    bool isDestroyed;

    Brick() {
        this -> y = 0;
        this -> x = 0;
    }

    Brick(int y, int x) {
        this -> y = y;
        this -> x = x;
    }
};
 
class Level {
public:
    Brick bricks[3][55];
    
    Level() {
        for(int y = 0; y < 3; y++) {
            for(int x = 0; x < 55; x++) {
                Brick brick(y + 2, x + 2);
                bricks[y][x] = brick;
            }
        }
    }

    void draw(WINDOW* window)  {
        //check if bricks are destroyed and print bricks that aren't
        for(int y = 0; y < 3; y++) {
            for(int x = 0; x < 55; x++) {
                if(!bricks[y][x].isDestroyed)
                    mvwprintw(window, bricks[y][x].y, bricks[y][x].x, bricks[y][x].sprite);
            }
        }
    }
};


class Player {
public:
    const char* name;
    int score;
    int lives;
};

/*
class Player {
public:
    const char* name;
    int score;
    int lives;
};

class Game {
public:

    void update() {

    }

    void draw() {

    }
};

*/

int lives;
int score;

int game() {

    //Randomize seed
    srand(time(nullptr)); 

    int gameWindowSizeY = 20;
    int gameWindowSizeX = 60;

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

    Player player;
    player.score = 0;
    player.lives = 3;

    Ball ball(13, 10, -1, rand() % 3 - 1);
    Paddle paddle(17, 1);
    Level level;

    level.draw(gameWindow);
    ball.draw(gameWindow);
    paddle.draw(gameWindow);
    wrefresh(gameWindow);

    while(true) {
        srand(time(nullptr)); 

        int input = getch();

        //Quit if user presses 'Q'
        if(input == 'q' || input == 'Q')
            break;

        //Clears ball from last position to not leave a trail
        mvwprintw(gameWindow, ball.y, ball.x, " "); 
        if(ball.x <= 1 || ball.x >= gameWindowSizeX - 2) {
            ball.dx = -ball.dx;
        }
        if(ball.y <= 1) {
            ball.dy = -ball.dy;
        }
        if(ball.y >= gameWindowSizeY - 2) {
            ball.dx = ball.dy = 0;
            player.lives -= 1;
            ball.y = 15;
            ball.x = 30;
        }
        if(ball.y == paddle.y - 1 && ball.x >= paddle.x - 1 && ball.x < paddle.x + 6) { /*account for slanted angles*/
            ball.dy = -ball.dy;
            ball.dx = max(-1, min(1, ball.dx + (rand() % 3 - 1)));
        }

        for(int q = 0; q < 3; q++) {
            for(int p = 0; p < gameWindowSizeX - 5; p++) {
                if(ball.x == level.bricks[q][p].x && ball.y == level.bricks[q][p].y)
                    if(!level.bricks[q][p].isDestroyed) {
                        ball.dy = -ball.dy;
                        level.bricks[q][p].isDestroyed = true;
                        player.score += 10;
                    }
            }
        }

        ball.x += ball.dx;
        ball.y += ball.dy;
        mvwprintw(gameWindow, ball.y, ball.x, ball.sprite);

        switch(input) {
            case KEY_LEFT:
                if(paddle.x > 2) {
                    mvwprintw(gameWindow, paddle.y, paddle.x, "      ");
                    paddle.x -= 2;
                    mvwprintw(gameWindow, paddle.y, paddle.x, paddle.sprite);
                }
                break;
            case KEY_RIGHT:
                if(paddle.x < gameWindowSizeX - 7) {
                    mvwprintw(gameWindow, paddle.y, paddle.x, "      ");
                    paddle.x += 2;
                    mvwprintw(gameWindow, paddle.y, paddle.x, paddle.sprite);
                }
                break;
            default:
                break;
        }
        
        string score = "Score:" + to_string(player.score);
        string lives = "Lives:" + to_string(player.lives);
        string playerInfo = lives + "                                       " + score;

        mvwprintw(infoWindow, 1, 1, playerInfo.c_str());
        wrefresh(infoWindow);

        level.draw(gameWindow);
        wrefresh(gameWindow);

        //Clear buffered input from previous frame
        flushinp(); 
        //Sleep for 100000 microseconds before updating
        usleep(100000);
    }

    //Clear terminal settings
    endwin(); 

    return 0;
}