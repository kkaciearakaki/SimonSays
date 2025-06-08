# SimonSays
## How to play
1. Start by turning on the board by using the switch
  - There will be blinking teal lights
2. When you're ready to play, shake the board
3. Wait for the color pattern to show. The LEDs will show blue
  - If the right side of the board lights up, press the right button
  - If the left side of the board lights up, press the left button
  - If all the LEDS light up, press both buttons
4. Press the corresponding button(s)
  - When there is a green flash and pitch, you know to press the next button in the pattern
5. More light patterns will be added to the previous one. See how many commands you can remember as more is added

### Scoring 
Players earn +1 point by correctly inputting the pattern that is displayed on the board. As the game goes on, more commands will be asked of the player.  

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
  - If right LEDS (0-4) are lit `rgb(0, 0, 255)`, right button should be pressed
  - If left LEDS (5-10) are lit `rgb(0, 0, 255)`, left button should be pressed
  - If all LEDS (0-10) are lit `rgb(0, 0, 255)`, both buttons are pressed
- `getUserInput()` Used to process the player's move
  - If right LEDS (0-4) are lit `rgb(0, 255, 0)`, the right button was pressed
  - If left LEDS (5-10) are lit `rgb(0, 255, 0)`, the left button was pressed
  - If all LEDS (0-10) are lit `rgb(0, 255, 0)`, both buttons were pressed

### A0 Pin (Audio)
- `showCommand()` Used to show player how to interact with the game
  - Plays a different tone depending on what command is called for
- `getUserInput()` Used to process the player's move
  - Plays a different tone depending on what buttons the user presses
- `tone(A0, ###)` Plays a tone from the A0 pin, HZ depends on number put in place of ###
- `noTone(A0)` Turns off the tone currently playing

### Serial Monitor 
- Shows player final score when game is over
