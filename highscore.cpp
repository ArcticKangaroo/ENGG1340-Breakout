#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <cstring>

using namespace std;

struct PlayerScores 
{
    string PlayerName;
    int PlayerScore;
};

void InputToFile() 
{
    string playername;
    int playerscore;
    PlayerScores player1;
    cout << "Enter player name: ";
    cin >> player1.PlayerName;
    cout << "Enter player score: ";
    cin >> player1.PlayerScore;
    ofstream scorefile;
    scorefile.open("scores", ios_base::app);
    if (scorefile.is_open()) {
        scorefile << player1.PlayerName << " " << player1.PlayerScore << endl;
        scorefile.close();
        cout << "Score added to the file." << endl;
    } else {
        cout << "Error opening file." << endl;
    }
}

bool ScoreComparison(const PlayerScores& s1, const PlayerScores& s2) 
{
    return s1.PlayerScore > s2.PlayerScore;
}

vector<PlayerScores> SortFile() 
{
    vector<PlayerScores> scores;
    PlayerScores tempScore;
    ifstream inputFile("scores");
    if (inputFile.is_open()) {
        while (inputFile >> tempScore.PlayerName >> tempScore.PlayerScore) {
            scores.push_back(tempScore);
        }
        inputFile.close();
        sort(scores.begin(), scores.end(), ScoreComparison);
    } else {
        cout << "Error opening file." << endl;
    }
    return scores;
}

int main() 
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    refresh();

    WINDOW* hsWindow = newwin(26,60,3,0);
    // Draw box
    box(hsWindow, 0, 0);
    wrefresh(hsWindow);

    // Get and sort scores
    vector<PlayerScores> sortedScores = SortFile();

    // Print scores
    int row = 12;
    int choice;
        wattron(hsWindow, A_BOLD);
        mvwprintw(hsWindow, 3, 24, "TOP 5 SCORES");
        mvwprintw(hsWindow, 10, 21, "NAME        SCORE");
        wattroff(hsWindow, A_BOLD);
        for (int i = 0; i < 5 && i < sortedScores.size(); i++) 
        {
            mvwprintw(hsWindow, row, 21, sortedScores[i].PlayerName.c_str());
            mvwprintw(hsWindow, row++, 33, to_string(sortedScores[i].PlayerScore).c_str());
        }
        wattron(hsWindow, A_REVERSE);
        mvwprintw(hsWindow, 24, 24, "BACK TO MENU");
        wattroff(hsWindow, A_REVERSE);
        wrefresh(hsWindow);
        for(;;)
        {
            choice=getch();
            if(choice==10)
            {
                break;
            }
        }
    getch();
    endwin();
    return 0;
}