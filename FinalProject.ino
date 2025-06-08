#include <Adafruit_CircuitPlayground.h> 
#include <AsyncDelay.h> 

volatile bool slideSwitch = digitalRead(7)==HIGH; 
volatile bool leftPressed = false; 
volatile bool rightPressed = false; 

volatile bool continueGame = false; 

int currentRound = 0; 

int toneFreq; 

int pattern[100]; 


void setup() {
  Serial.begin(9600); 
  CircuitPlayground.begin(); 

  // Setting up buttons and switches
  pinMode(7, INPUT_PULLUP); 
  pinMode(5, INPUT_PULLDOWN); 
  pinMode(4, INPUT_PULLDOWN); 
  attachInterrupt(digitalPinToInterrupt(4), rightInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(5), leftInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(7), switchInterrupt, CHANGE);

  randomSeed(analogRead(A9)); // So that the random numbers are different each time

  CircuitPlayground.setAccelRange(LIS3DH_RANGE_8_G);
} 

void loop() {  

  if (slideSwitch) { 
    while (true) { 
      for (int i = 0; i < 10; i++) { 
        CircuitPlayground.setPixelColor(i, 0, 155, 155); 
      }
      delay(500); 
      CircuitPlayground.clearPixels(); 
      delay(500); 

      if(!slideSwitch){
        return;
      }

      if (currentAcceleration() > 30) {
        continueGame = true; 
        CircuitPlayground.clearPixels(); 
        break;
      } 
    }
  }
  
  createPattern(); 
  currentRound = 0;

  delay(500); 

  while(continueGame) { // only runs for 100 total rounds
    for (int i = 0; i < currentRound+1; i++) { 
      showCommand(i); 
      tone(A0, toneFreq); 
      delay(500); 
      noTone(A0); 
      CircuitPlayground.clearPixels(); 
      delay(500); 
      if (!continueGame) { 
        return; 
      }
    } 

    for (int i = 0; i < currentRound+1; i++) { // Goes through pattern array, gets each column value and compares it to what the user inputs
      int input = getUserInput(); 
      if (input != pattern[i]) { // The user selected the wrong buttons
        continueGame = false; 
        break; 
      } 
      delay(100); 
      CircuitPlayground.clearPixels(); 
      noTone(A0); 
    }

    if (!continueGame && slideSwitch) { 
      noTone(A0); 
      CircuitPlayground.clearPixels();
      Serial.println("GAME OVER");
      unsigned long endTime = millis(); 
      while(millis() - endTime < 3000) { 
        endBlink(); 
      }

      Serial.print("Final Score: "); 
      Serial.println(currentRound); 


      break; 
    } 

    currentRound+=1;

    delay(1000); 

  }

} 


// If 0, right button should be pressed | If 1, left button should be pressed | If 2, both left and right button should be pressed 

void showCommand(int command) { 
  if (pattern[command] == 0) { 
    for (int i = 0; i < 5; i++) { 
      CircuitPlayground.setPixelColor(i, 0, 0, 255); 
    }
    toneFreq = 261; // C4
  } else if (pattern[command] == 1) { 
    for (int i = 5; i < 10; i++) { 
      CircuitPlayground.setPixelColor(i, 0, 0, 255); 
    } 
    toneFreq = 349; // F4
  } else { 
    for (int i = 0; i < 10; i++) { 
      CircuitPlayground.setPixelColor(i, 0, 0, 255); 
    }
    toneFreq = 523; // C5
  }
}

void endBlink() { 
  for(int i = 0; i < 10; i++) { 
    CircuitPlayground.setPixelColor(i, 255, 0, 0); 
  }
  delay(200); 
  CircuitPlayground.clearPixels(); 
  delay(200); 
}

int getUserInput() { 
  unsigned long startTime = millis();

  // Reset button press flags before waiting for input
  leftPressed = false;
  rightPressed = false;

  while (millis() - startTime < 3000) { // Gives the user 3 seconds to respond
    // Check for button presses
    if (leftPressed || rightPressed) {
      delay(100); // Gives the board time to process if both buttons were pressed

      if (leftPressed && rightPressed) { // Both buttons pressed
        for(int i = 0; i < 10; i++) { 
          CircuitPlayground.setPixelColor(i, 0, 255, 0);
        }
        rightPressed = false; 
        leftPressed = false; 
        tone(A0, 523); // Play C5
        return 2;
      }
   
      if (rightPressed && !leftPressed) { // Only Right button pressed
        for (int i = 0; i < 5; i++) { 
          CircuitPlayground.setPixelColor(i, 0, 255, 0); 
        } 
        rightPressed = false; 
        tone(A0, 261); // Play C4

        return 0;
      }
      if (leftPressed && !rightPressed) { 
        for (int i = 5; i < 10; i++) { 
          CircuitPlayground.setPixelColor(i, 0, 255, 0); 
        }
        tone(A0, 349); // Play F4 
        leftPressed = false; 
        return 1;
      }
    }

    delay(10); // To avoid giving the board too much information to process at once
  }
  return -1; // No valid input within the time limit
}

int currentAcceleration() { // Checks acceleration
  int X = 0; 
  int Y = 0; 
  int Z = 0; 
  for (int i=0; i<10; i++) { // Takes 10 readings of the motions
    // Reads acceleration in the x, y, and z directions 
    X += CircuitPlayground.motionX(); 
    Y += CircuitPlayground.motionY();
    Z += CircuitPlayground.motionZ();
    delay(1);
  }

  // Averages the readings to simplify the numbers
  X /= 10;
  Y /= 10;
  Z /= 10;
  
  return sqrt(X*X + Y*Y + Z*Z); // Calculates total acceleration
} 

void switchInterrupt() { 
  slideSwitch = digitalRead(7)==HIGH; // True when on, False when off 

  if (!slideSwitch) { 
    continueGame = false; 
  } 
}

void rightInterrupt() { 
  rightPressed = true;
}

void leftInterrupt() { 
  leftPressed = true; 
}

void createPattern() { 
  for (int i = 0; i < 100; i++) { 
    pattern[i] = random(0, 3); 
  }
}
