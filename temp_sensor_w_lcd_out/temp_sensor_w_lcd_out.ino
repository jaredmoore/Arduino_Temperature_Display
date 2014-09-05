// Script to connect one 7 segment LCD to an Arduino UNO through a 74HC595N register.
//
// Example code initially taken from the following and adapted for my purposes.
// Arduino 7 segment display example software
// http://www.hacktronics.com/Tutorials/arduino-and-7-segment-led.html
// License: http://www.opensource.org/licenses/mit-license.php (Go crazy)

//Pin Definitions
//Pin Definitions
//The 74HC595 uses a serial communication 
//link which has three pins

//Used for single LED manipulation
int ledState = 0;
const int ON = HIGH;
const int OFF = LOW;

int seven_seg_ints_rev[20] = {238,40,205,109,43,103,231,44,239,47};

int data[1]  = {10};
int clock[1] = {11};
int latch[1] = {12};

int i = 0;

/*
 * setup() - this function runs once when you turn your Arduino on
 * We set the three control pins to outputs
 */
void setup()
{
  pinMode(10, OUTPUT); //7 Segment Data - 1 
  pinMode(11, OUTPUT); //7 Segment Clk  - 1  
  pinMode(12, OUTPUT); //7 Segment Latch- 1    
  
  Serial.begin(9600);
}

/*
 * loop() - this function will start after setup finishes and then repeat
 * we set which LEDs we want on then call a routine which sends the states to the 74HC595
 */
void loop()                     // run over and over again
{ 
  //Write out values to the LEDs
  
  Serial.println(i);
  sevenSegWrite(seven_seg_ints_rev[i],0);  //Write the tens digit
  delay(500);
  
  i = (i+1) % 10;
}

/*
 * updateLEDs() - sends the LED states set in ledStates to the 74HC595
 * sequence
 */
void updateLEDs(int value, int place){
  Serial.println(value);
  digitalWrite(latch[place], LOW);     //Pulls the chips latch low
  shiftOut(data[place], clock[place], MSBFIRST, value); //Shifts out the 8 bits to the shift register
  digitalWrite(latch[place], HIGH);   //Pulls the latch high displaying the data
}
