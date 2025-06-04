# SimonSays
This game is similar to the game Simon where different colors light up and players have to click the colors based on whatever flashes. 

The board will flash a teal color when turned on. To begin the game, the user has to shake the board. The board LEDs will display a pattern, where the left and right LEDs of the board will light up, signalling which button they press. If both sides of the board light up, the user has to press both buttons at the same time. As the player gets further into the game, more patterns will add up. For example, the first round the right side of the board will light up, and then the second round the right side will light up followed by the left.  Each time they get past a round, one point will be added. Once they get it incorrect, the board will flash a red light to signal the end of the game. The board will announce the final score. 

## Inputs: 
**Accelerometer** 
- `CircuitPlayground.motionX()` Returns the reported motion in the X direction
- `CircuitPlayground.motionY()` Returns the reported motion in the Y direction
- `CircuitPlayground.motionZ()` Returns reported motion in the Z direction
- `currentAcceleration()` Detects board motion, signals for the game to start

**Switch Flag**
- `attachInterrupt(digitalPinToInterrupt(7), switchInterrupt, CHANGE)` Sets up the switch flag as an interrupt, turns the game off and on

**Left and Right Buttons**
- `attachInterrupt(digitalPinToInterrupt(4), rightInterrupt, RISING)` Sets up the right button as an interrupt when pressed
  -   Pressed when right side of the board lights up to earn points
- `attachInterrupt(digitalPinToInterrupt(5), leftInterrupt, RISING)` Sets up the left button as an interrupt when pressed, used to earn points
  - Pressed when left side of the board lights up to earn points
- When all LEDS are lit, both buttons are pressed together
  
## Outputs
**LEDS**
- `showCommand()` Used to show the player how to interact with the game
  - If right LEDS (0-4) are lit `rgb(0, 0, 255), right button should be pressed
  - If left LEDS (5-10) are lit `rgb(0, 0, 255), left button should be pressed
  - If all LEDS (0-10) are lit `rgb(0, 0, 255), both buttons are pressed
- 

### A0 Pin (Audio)
* Used along with lights to tell users which button to press
* Used to show users which button they pressed
