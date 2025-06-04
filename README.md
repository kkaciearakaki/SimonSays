# SimonSays
This game is similar to the game Simon where different colors light up and players have to click the colors based on whatever flashes. 

The board will flash a teal color when turned on. To begin the game, the user has to shake the board. The board LEDs will display a pattern, where the left and right LEDs of the board will light up, signalling which button they press. If both sides of the board light up, the user has to press both buttons at the same time. As the player gets further into the game, more patterns will add up. For example, the first round the right side of the board will light up, and then the second round the right side will light up followed by the left.  Each time they get past a round, one point will be added. Once they get it incorrect, the board will flash a red light to signal the end of the game. The board will announce the final score. 

## Inputs: 
### Accelerometer 
* Used to begin game once board is turned on

### Switch Flag
* Used to turn the game on and off
* Can be used to stop the game regardless of where the player is 

### Left and Right Buttons
* How the user interacts with the game and how they earn points

## Outputs
### LEDS
* Used to tell user which buttons to press
* Used to show users which button they pressed
* Shows the end of the game
* Shows the player that the board is on and ready to be played

### A0 Pin (Audio)
* Used along with lights to tell users which button to press
* Used to show users which button they pressed
