#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"
#include "game.h"

using namespace std;

int mainmenu();
int inputName();
int instructions1();
int instructions2();
int instructions3();
int instructions4();
int highscore();
int credits();

int mainmenu()
{
    refresh();

    WINDOW* menuWindow = newwin(26, 60, 0, 0); //main menu window initialization (rows,cols,y,x)
    box(menuWindow, 0, 0);
    wrefresh(menuWindow);

    string menu1[5]= {"PLAY GAME","HOW TO PLAY","HIGH SCORE","CREDITS","QUIT"};
    int choice;
    int highlight=0;

    while(TRUE)
    {
        
        mvwprintw(menuWindow, 1,1,"* * * * * * * * * * * * * * * * * * * * * * * * ");
        mvwprintw(menuWindow, 2,1,"*   *   *   *   *   *   *   *   *   *   *   *   ");
        mvwprintw(menuWindow, 3,6,".______  .______   _______     ___      __  ___ ");
        mvwprintw(menuWindow, 4,6,"|   _  \\ |   _  \\ |   ____|   /   \\    |  |/  / ");
        mvwprintw(menuWindow, 5,6,"|  |_)  ||  |_)  ||  |__     /  ^  \\   |  '  / ");
        mvwprintw(menuWindow, 6,6,"|   _  < |      / |   __|   /  /_\\  \\  |    < ");
        mvwprintw(menuWindow, 7,6,"|  |_)  ||  |\\  \\ |  |____ /  _____  \\ |  .  \\ ");
        mvwprintw(menuWindow, 8,6,"|______/ | _| `._||_______/__/     \\__\\|__|\\__\\ ");
        mvwprintw(menuWindow, 9,1,"*     *     *     *     *     *     *     *  ");
        mvwprintw(menuWindow, 10,15,"  ______   __    __ .________.");
        mvwprintw(menuWindow, 11,15," /  __  \\ |  |  |  ||        |");
        mvwprintw(menuWindow, 12,15,"|  |  |  ||  |  |  |`--|  |--`");
        mvwprintw(menuWindow, 13,15,"|  |  |  ||  |  |  |   |  |  ");
        mvwprintw(menuWindow, 14,15,"|  `--'  ||  `--'  |   |  |  ");
        mvwprintw(menuWindow, 15,15," \\______/  \\______/    |__|  ");
        mvwprintw(menuWindow, 16,1,"*      *      *         *     *      *    * ");
        mvwprintw(menuWindow, 17,1,"   *     *         *       *       *        *"); 
        mvwprintw(menuWindow, 18,1," *    *    *     *    *         *      *   ");  
        for(int i=0;i<5;i++)
        {
            wattron(menuWindow, A_BOLD);//making all options bold
            if(i==highlight)
                wattron(menuWindow, A_REVERSE);//highlighting the selected option
            
            mvwprintw(menuWindow, 18+i+1, ((60-menu1[i].length())/2), menu1[i].c_str());//printing options
            wattroff(menuWindow, A_REVERSE);//de-highlighting the non selected options
        }
        choice = getch();//getting user input

        switch (choice)
        {
            case KEY_UP:
                highlight--;//changing highlighted option
                if(highlight<0)//checking whether the choice is going out of bounds
                    highlight=4;
                break;
            case KEY_DOWN:
                highlight++;//changing highlighted option
                if(highlight>4)//checking whether the choice is going out of bounds
                    highlight=0;
                break;
            default:
                break;
        }

        if (choice==10)//checking for option selected
        {
            break;
        }

        wrefresh(menuWindow);
    }
    if(highlight==0)
        {
            inputName();
        }
    else if(highlight==1)
    {
        instructions1();
    }
    else if(highlight==2)
    {
        highscore();
    }
    else if(highlight==3)
    {
        credits();
    }

    return 0;
}

int inputName() 
{
    refresh();

    // Create a 60x60 window
    WINDOW* win = newwin(26, 60, 0, 0);

    // Draw a box around the window
    box(win, 0, 0);


    //creating a play button:

    //create a string that stores text displayed on the button
    string playButton= "PLAY GAME";

    //makes text bold 
    wattron(win, A_BOLD);

    //highlighting the play button
    wattron(win, A_REVERSE);

    //prints play button
    mvwprintw(win, 19, ((60-playButton.length())/2), playButton.c_str());
    
    //turn off highlighting
    wattroff(win, A_REVERSE);


    // Create a string to store the player name
    string playerName;
    // Get input from the user until they press enter
    int ch;
    //declare and initialise variable to count and subsequently limit character count for name
    int char_limit = 0;
    //print a prompt to enter name
    mvwprintw(win, 11, 21, "Enter your name:");
    mvwprintw(win, 14, 23, "-----------");
    while ((ch = wgetch(win)) != '\n') {
        
        if (ch == KEY_BACKSPACE || ch == 127) {
            // Handle backspace key
            if (!playerName.empty()) {
                playerName.erase(playerName.size() - 1, 1);
                mvwprintw(win, 13, 25, "       ");
                mvwprintw(win, 13, 25, playerName.c_str());
                //account for backspace in character count
                char_limit--;
            }
        } else if (isprint(ch)) {
            // Handle printable characters
            //set character count limit to 7
            if (char_limit!=7){
                playerName += ch;
                mvwprintw(win, 13, 25, playerName.c_str()); 
                //account for increment in character count
                char_limit++;
            }
            

        }
        //refresh window
        wrefresh(win);
        
    }
    if(playerName.empty()) playerName = "NONAME";

    game(playerName);
    return 0;
}
int instructions1()
{
    WINDOW* instrucionWindow = newwin(26, 60, 0, 0); //instruction window initialization (rows,cols,y,x)
    box(instrucionWindow, 0, 0);
    wrefresh(instrucionWindow);

    string instructionmenu[2]={"<-BACK","NEXT->"};
    int choice;
    int highlight3=1;
    for(;;)
    {   
        //instructions on how to play the game
        mvwprintw(instrucionWindow, 5, 13, "1.");
        mvwprintw(instrucionWindow, 5, 15, "Press the left and right arrow");
        mvwprintw(instrucionWindow, 6, 15, "to move the paddle.");
        mvwprintw(instrucionWindow, 8, 13, "2.");
        mvwprintw(instrucionWindow, 8, 15, "Your objective is to break the");
        mvwprintw(instrucionWindow, 9, 15, "bricks using the ball.");
        mvwprintw(instrucionWindow, 11, 13, "3.");
        mvwprintw(instrucionWindow, 11, 15, "You will get points each time");
        mvwprintw(instrucionWindow, 12, 15, "ball hits the brick.");
        mvwprintw(instrucionWindow, 14, 13, "4.");
        mvwprintw(instrucionWindow, 14, 15, "You have three lives.");
        mvwprintw(instrucionWindow, 16, 13, "5.");
        mvwprintw(instrucionWindow, 16, 15, "If the ball drops down, you");
        mvwprintw(instrucionWindow, 17, 15, "lose a life.");
        mvwprintw(instrucionWindow, 20, 22, "Happy gaming!");
        wattron(instrucionWindow, A_BOLD);//making all options bold
        mvwprintw(instrucionWindow, 24, 27, "PAGE 1");  
        //print file "instructions1.txt" here  
        if(0==highlight3)
        {
            wattron(instrucionWindow, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucionWindow, 24, 1, instructionmenu[0].c_str());//printing options
            wattroff(instrucionWindow, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucionWindow, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
        }
        else if(1==highlight3)
        {
            wattron(instrucionWindow, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucionWindow, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
            wattroff(instrucionWindow, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucionWindow, 24, 1, instructionmenu[0].c_str());//printing options
        }
        wrefresh(instrucionWindow);
        
        choice = getch();//getting user input
        if((choice==KEY_LEFT)||(choice==KEY_RIGHT))
        {
                if(highlight3==0)
                    highlight3=1;
                else
                    highlight3=0;
        }
        if(choice==10)
        {
            break;
        }
    }
    if(highlight3==0)
    {
        mainmenu();
    }
    else
    {
        instructions2();
    }
    return 0;
}

int instructions2()
{
    WINDOW* instrucion2Window = newwin(26, 60, 0, 0); //instruction window initialization (rows,cols,y,x)
    box(instrucion2Window, 0, 0);
    wrefresh(instrucion2Window);

    string instructionmenu[2]={"<-BACK","NEXT->"};
    int choice;
    int highlight3=1;
    for(;;)
    {       
        wattron(instrucion2Window, A_BOLD);//making all options bold
        mvwprintw(instrucion2Window, 24, 27, "PAGE 2");
        //print file "instructions2.txt" here
        if(0==highlight3)
        {
            wattron(instrucion2Window, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucion2Window, 24, 1, instructionmenu[0].c_str());//printing options
            wattroff(instrucion2Window, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucion2Window, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
        }
        else if(1==highlight3)
        {
            wattron(instrucion2Window, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucion2Window, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
            wattroff(instrucion2Window, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucion2Window, 24, 1, instructionmenu[0].c_str());//printing options
        }
        wrefresh(instrucion2Window);
        
        choice = getch();//getting user input
        if((choice==KEY_LEFT)||(choice==KEY_RIGHT))
        {
                if(highlight3==0)
                    highlight3=1;
                else
                    highlight3=0;
        }
        if(choice==10)
        {
            break;
        }
    }
    if(highlight3==0)
    {
        instructions1();
    }
    else
    {
        instructions3();
    }
    return 0;
}
int instructions3()
{
    WINDOW* instrucion3Window = newwin(26, 60, 0, 0); //instruction window initialization (rows,cols,y,x)
    box(instrucion3Window, 0, 0);
    wrefresh(instrucion3Window);

    string instructionmenu[2]={"<-BACK","NEXT->"};
    int choice;
    int highlight3=1;
    for(;;)
    {       
        wattron(instrucion3Window, A_BOLD);//making all options bold
        mvwprintw(instrucion3Window, 24, 27, "PAGE 3");
        //print file "instructions3.txt" here
        if(0==highlight3)
        {
            wattron(instrucion3Window, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucion3Window, 24, 1, instructionmenu[0].c_str());//printing options
            wattroff(instrucion3Window, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucion3Window, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
        }
        else if(1==highlight3)
        {
            wattron(instrucion3Window, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucion3Window, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
            wattroff(instrucion3Window, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucion3Window, 24, 1, instructionmenu[0].c_str());//printing options
        }
        wrefresh(instrucion3Window);
        
        choice = getch();//getting user input
        if((choice==KEY_LEFT)||(choice==KEY_RIGHT))
        {
                if(highlight3==0)
                    highlight3=1;
                else
                    highlight3=0;
        }
        if(choice==10)
        {
            break;
        }
    }
    if(highlight3==0)
    {
        instructions2();
    }
    else
    {
        instructions4();
    }
    return 0;
}

int instructions4()
{
    WINDOW* instrucion4Window = newwin(26, 60, 0, 0); //instruction window initialization (rows,cols,y,x)
    box(instrucion4Window, 0, 0);
    wrefresh(instrucion4Window);

    string instructionmenu[2]={"<-BACK","END->"};
    int choice;
    int highlight3=1;
    for(;;)
    {       
        wattron(instrucion4Window, A_BOLD);//making all options bold
        mvwprintw(instrucion4Window, 24, 27, "PAGE 4");
        //print file "instructions4.txt" here
        if(0==highlight3)
        {
            wattron(instrucion4Window, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucion4Window, 24, 1, instructionmenu[0].c_str());//printing options
            wattroff(instrucion4Window, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucion4Window, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
        }
        else if(1==highlight3)
        {
            wattron(instrucion4Window, A_REVERSE);//highlighting the selected option
            mvwprintw(instrucion4Window, 24, (59-instructionmenu[1].length()), instructionmenu[1].c_str());//printing options
            wattroff(instrucion4Window, A_REVERSE);//de-highlighting the non selected options
            mvwprintw(instrucion4Window, 24, 1, instructionmenu[0].c_str());//printing options
        }
        wrefresh(instrucion4Window);
        
        choice = getch();//getting user input
        if((choice==KEY_LEFT)||(choice==KEY_RIGHT))
        {
                if(highlight3==0)
                    highlight3=1;
                else
                    highlight3=0;
        }
        if(choice==10)
        {
            break;
        }
    }
    if(highlight3==0)
    {
        instructions3();
    }
    else
    {
        mainmenu();
    }
    return 0;
}

int credits()
{
    return 0;
}

int highscore()
{
    return 0;
}

int gameOver(string playerName, int playerScore)
{
    WINDOW* endWindow = newwin(26, 60, 0, 0); //instruction window initialization (rows,cols,y,x)
    box(endWindow, 0, 0);
    wrefresh(endWindow);

    int highlight=0;
    int choice;
    for(;;)
    {
        mvwprintw(endWindow, 1,2,"* * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
        mvwprintw(endWindow, 2,2,"*   *   *   *   *   *   *   *   *   *   *   *   *   *   *");
        mvwprintw(endWindow, 3,2,"       *    ______    *       *         *     *    *  *");
        mvwprintw(endWindow, 4,2,"   *     * /  ____|      *      *    *     *     *    *");
        mvwprintw(endWindow, 5,2,"  *    *  |  |  ___   _____  _________     ___     *  *");
        mvwprintw(endWindow, 6,2,"    *   * |  | |_  | /  _  | |  _   _ \\  / _  \\  *    *");
        mvwprintw(endWindow, 7,2," *       *|  |__|  | | (_| | | | | | | ||  __/    *   *");
        mvwprintw(endWindow, 8,2," *     *   \\_______|  \\____| |_| |_| |_| \\____|    *  *");
        mvwprintw(endWindow, 9,2,"    *     *     *     *     *     *     *     *     *   *");
        mvwprintw(endWindow, 10,2,"*     *     *     *     *     *     *     *     *     *");
        mvwprintw(endWindow, 11,2,"  *      *   ______   *      *     *   *      *    * *");
        mvwprintw(endWindow, 12,2,"     *    * /  __  \\   *      *         *       *   *");
        mvwprintw(endWindow, 13,2,"  *     *  |  |  |  | __    __  ___   __ ___  *      *");
        mvwprintw(endWindow, 14,2,"     *    *|  |  |  | \\ \\  / / / _ \\ | '___|   *    *");
        mvwprintw(endWindow, 15,2,"         * |  `--'  |  \\ \\/ / |  __/ | /    *     *  *");
        mvwprintw(endWindow, 16,2," *     *    \\______/    \\__/   \\___| |_|   *   *    *");
        mvwprintw(endWindow, 17,2,"*     *     *     *     *     *     *     *     *    * *");
        mvwprintw(endWindow, 18,2,"   *     *     *     *     *     *     *     *    *    *"); 
        mvwprintw(endWindow, 19,2,"*     *     *     *     *     *     *     *     *    * *"); 
        mvwprintw(endWindow, 20,2,"   *     *     *     *     *     *     *     *    *    *");
        mvwprintw(endWindow, 21,2,"* * * * * * * * * * * * * * * * * * * * * * * ** * * * ");
        if(highlight==0)
        {
            wattron(endWindow, A_BOLD);//making all options bold
            wattron(endWindow,A_REVERSE);
            mvwprintw(endWindow, 24, 27, "BACK TO HOME");
            wattroff(endWindow,A_REVERSE);
        }
        choice=getch();
        if(choice==10)
        {
            mainmenu();
            return 0;
        }
        wrefresh(endWindow);
    }

    return 0;
}