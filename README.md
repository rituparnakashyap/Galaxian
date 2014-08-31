Galaxian - A game in C
========
## About the Game ##

This code is old, written around 2007 and only compiles with Turbo C 3.0 only. I just started coding around that time and just knew while and for loops. The submission is only educational. 

## Game Logic ##

The game starts with full efficiency of the tank and the skull i.e. 10 for skull and 100 for tanks effiency of tank is a time function and also decreases(by 5) the the colored ball hits the tank. Whereas for the skull effiency decreases by 1 from 10 when the fire of the tank hit the skull. The games end when all the skull is destroyed or the tank effiency becomes 0. 

The game graphics is shown in either in the main frame screen or some ports on the main frame.Eg the main game has 6 view ports one each for the skull ,one for the tank and other for showing the fire of the tanks and the colored balls.The boarder,the score and the tank effiency is shown in the screen main frame. Whereas the loading sreen contains no view ports but the menu screen and level screen contains one each.

## Globals Variable  ##

*   char key :It stores the particular keybord hit at a instant during the infinite 'do-while' loop in the hitman function.
*   time_t t_skull1[4],t_skull2[4]: It contains the times of the of two particular instant of the 'ith' skull. It is used in the difftime(); function that determines the opening and closing of the jaws of the 'ith' skull. 
*   int timecon_skull[2][4] :It stores the condition of the ith skull at any particluar instant of the game.timecon_skull[0][i] contains the condition of existance of the ith skull.If the value is 0 skull has no existance and if its 1 it has existance.timecon_skull[1][i] is used for the condition if ith skull has travelled 2 sec.It takes 0 value if it has not travel 2 sec in the infinit do-while loop between two instant and 1 if it had travelled.
*   int skullloop[4]: It cointains the number of time the ith skull is shown in the screen.It is again initialised to 0,if the skullloop[i] takes the value 1000 if is again initialised to 0.skullloop%3 gives the value 0 or 1 or 2 which determine position of the ith skull in x-axis.
*   int skull_x_pos[4]: It stores the x-axis co-ordinate of the ith skull at a particular skull.It is use while shooting down the skull.
*   int damage[5]: It stores the efficency % of the skull and the tank.Initial values of 4 skull damage ( stored in i=0 to i=3) is 10.While that of the tank is 100 (stored in i=4).
*   int score: It contains the score of the game.
*   int levels: it stores the level of the game,which in turn determine the speed of the game.
*   int **ballx,**bally: (** for its respective color)It contains the x-axis and the y-axis co-ordinate of
a particular color ball in a particular instant.

## User Defined Function ##

*   void hitman(void): It is the main-board of the game,dealing with the every expect of the game from calling the other user defined function and other game calculation.It also shows the 
fires of the tanks.It is called in the use defined function level().
*   void fire(int pos): It inisiated the x and y axis position of the fire of the tank.
*   void tank(int pos): It shows the tank in different x-axis co-ordinate with the key-board hit. 
*   void skullpic(int): It Shows the skull position in the screen.It takes the input variable int i which determines the position of the ith skull in the screen.
*   void loading(int i):It shows the loading graphics.
*   void credit(void): It shows the credit graphics.
*   void damage_count(int):This function calculate the damage of the 4 skull or the tank.It also calculate the score of the game.The input variable determines if the damage count is to be the tank or the skulls.Input variables i=0 to i=3 is for skulls whereas is for i=4.
*   void gameover(int choice):This function shows the gameover screen of the game.The input variable choice 
determines the mode how the game ends.Input variable 'choice' if 0 set the mode the you won ,1 if you lose,2 if there if a premature termination.
*   void col_ball(void):The function shows the coloured ball in the screen.
*   void hig_scr(void):This function maintains a file system which stores the highest score played in the game.This highest score is shown in the gameover screen of the game.
*   void level(void):This function shows the level menu of the game.This also passes the value to the variable 'levels'.

*****

Copy the below file to the directory containing the games .exe file from the BIN of Turbo C++ v3

*   SIMP.CHR
*   TRIP.CHR
*   TSCR.CHR
*   BOLD.CHR
*   SCRI.CHR
*   EURO.CHR
*   GOTH.CHR
*   LCOM.CHR
*   LITT.CHR
*   SANS.CHR
*   Egavga.bgi


## Playing Keys ##

Left 'a';
Right 'd';
Up "w';
Down 's';
Select 'f';
Shoot 'k';
Exit to Windows during the game 'q';
