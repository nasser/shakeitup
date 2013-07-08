/*
///////////////////////////////////////////////
For "Shake it up!" demo game 
Eyebeam Digital Day Camp Summer 2013
Ramsey Nasser and Kaho Abe

**** Must install https://github.com/moderndevice/CapSense in Arduino libraries folder to use this!****
///////////////////////////////////////////////

Based on code from Adafruit Tutorial on 
Example code for a Flora game controller with capacitive touch sensing! Full tutorial and video:

http://learn.adafruit.com/plush-game-controller/

Uses Modern Device's Capacitive Sensing library: https://github.com/moderndevice/CapSense

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried & Becky Stern for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
  
*/
#include <CapPin.h>                             //including Cap Sense Library

CapPin cPin_10 = CapPin(10);                    // read pin 10 (D10 on Flora)  
char key = 'a';                                 // should mimic "a" key when "button" is pressed
boolean currentPressed = false;                 //starts off as "button" not being pressed

// Capactive touch threashhold, you might want to mess with this if you find its too
// sensitive or not sensitive enough
#define THRESH 500


void setup()                                     // runs once!
{
  Serial.begin(115200);                          //starts Serial Communication at 115200 bytes per second -- baud rate
  Serial.println("start");                       //should print "start" in serial monitor
  Keyboard.begin();                              //starts keyboard mimicing capabilities
}


void loop()                    
{ 

    long total =  cPin_10.readPin(2000);         //reads capacitive pin

    // check if we are sensing that a finger is touching the pad 
    // and that it wasnt already pressed
    if ((total > THRESH) && (! currentPressed)) { //if it's over threshold and not pressed 
      Serial.println("pressed");                  //then print "pressed"
      currentPressed = true;                      //currentPressed becomes True -- important to check if it's being pressed or not

      Keyboard.press(key);                         //mimics keyboard press key -- in this case is 'a'       
    }
    else if ((total <= THRESH) && (currentPressed)) { // if it is less than the threshold and button is pressed -- else if checks only if the previous if statement is false
      // key was released (no touch, and it was pressed before)
      Serial.println("released");                 //prints "released"
      currentPressed = false;                     //sets currentPressed to false
      Keyboard.release(key);                      //mimics keyboard release key -- in this case is 'a'   
    }
    
    delay(5);                                    //to keep it from running too fast
}
