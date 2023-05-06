<br/>
<div align="center">
  <h3 align="center">ASCII Breakout</h3>
  <p align="center"><i>Breakout remade for the Linux terminal</i></p>
  <img width="480" height="480" src="https://user-images.githubusercontent.com/62847649/236564562-6724a29f-6a8e-4140-a952-3a8c48c73d41.png" alt="Screenshot">
</div>

<br/>
<hr/>

### About
The classic game Breakout implemented in C++ and ncurses for the Linux command line, for the final project of HKU's ENGG1340.

### Gameplay
https://user-images.githubusercontent.com/62847649/236627143-70ff03c3-d35b-45a5-a86c-4d0bae8307f3.mp4  

#### Instructions
* Use the left and right arrow keys to move the paddle.  
* Strike the ball with the paddle to hit the bricks. 
* The player earns points for each brick destroyed.
* The player loses a life if the ball falls off the bottom of the screen.
* The game is over when the player runs out of lives or clears all the bricks.

### Project Requirements

| Coding Requirements                      | Feature                                                                                                    |
| ---------------------------------------- | ---------------------------------------------------------------------------------------------------------- |
| Generation of Random Events              | We randomised the direction of the ball when the game starts and every time it hits the paddle.            |   
| Data Structures for Storing Game Status  | We use different classes to store the status of in-game objects like the ball, the paddle, and the level. The player data is also stored in a class at any given point.                                                                                               |
| Dynamic Memory Management (DMM)          | We utilize dynamic memory allocation to create and remove instances of the ball in each round of gameplay. |
| File Input/Output                        | We use file handling to maintain a record of the top 5 scores in the leaderboard.                          |
| Multiple Files of Program Code           | We use separate files for handling different parts of the game - the gameplay, the menu, and the highscores functionality, which are joined together by main.cpp.                                                                                                   |


### External Libraries
`ncurses` - The ncurses library was used to draw console graphics smoothly instead of having to redraw the whole window every time the game updates.

### Instructions for Building
* Clone the project repository: `git clone https://github.com/ArcticKangaroo/ASCII-Breakout.git`
* Navigate to the project directory: `cd ASCII-Breakout/`
* Make the game: `make breakout`
* Execute the game: `./breakout`
* To remove the game, run `make clean`

### Project Members
This project was made by:
* Anubhav Kashyap  
* Lakshya Tulsyan 
* Arnav Kejriwal  
* James Megadyanto  
* Achal Agarwal
 

### License
Distributed under the MIT License. See `LICENSE` for more information.
