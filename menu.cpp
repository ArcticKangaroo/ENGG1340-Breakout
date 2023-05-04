#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int mainmenu();
int instructions1();
int instructions2();
int instructions3();
int instructions4();
int highscore();
int credits();

int main() // main menu window
{
    initscr(); //Initialize ncurses
    cbreak(); //Don't buffer input
    keypad(stdscr, TRUE); //Enable input from special keys
    noecho(); //Don't echo input
    curs_set(0); //Don't display cursor
    nodelay(stdscr, TRUE); //Set getch() to non-blocking mode
    refresh(); //Update screen initially (prevents getch() from clearing the screen)
    mainmenu();
    endwin();
    return 0;
    //g++ -lncurses menu.cpp -o menu
}
int mainmenu()
{
    WINDOW* menuWindow = newwin(26, 60, 3, 0); //main menu window initialization (rows,cols,y,x)
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
            gamemodes();
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

int instructions1()
{
    WINDOW* instrucionWindow = newwin(26, 60, 3, 0); //instruction window initialization (rows,cols,y,x)
    box(instrucionWindow, 0, 0);
    wrefresh(instrucionWindow);

    string instructionmenu[2]={"<-BACK","NEXT->"};
    int choice;
    int highlight3=1;
    for(;;)
    {   
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
    WINDOW* instrucion2Window = newwin(26, 60, 3, 0); //instruction window initialization (rows,cols,y,x)
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
    WINDOW* instrucion3Window = newwin(26, 60, 3, 0); //instruction window initialization (rows,cols,y,x)
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
    WINDOW* instrucion4Window = newwin(26, 60, 3, 0); //instruction window initialization (rows,cols,y,x)
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