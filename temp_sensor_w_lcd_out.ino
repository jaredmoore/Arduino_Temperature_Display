//Pin Definitions
//Pin Definitions
//The 74HC595 uses a serial communication 
//link which has three pins

//Used for single LED manipulation
int ledState = 0;
const int ON = HIGH;
const int OFF = LOW;

//These are used in the bitwise math that we use to change individual LEDs
//For more details http://en.wikipedia.org/wiki/Bitwise_operation
int bits[] = {B00000001, B00000010, B00000100, B00001000, B00010000, B00100000, B01000000, B10000000};
int masks[] = {B11111110, B11111101, B11111011, B11110111, B11101111, B11011111, B10111111, B01111111};

// Define the LED digit patters, from 0 - 9
// Note that these patterns are for common cathode displays
// For common anode displays, change the 1's to 0's and 0's to 1's
// 1 = LED on, 0 = LED off, in this order:
//                                    Arduino pin: 2,3,4,5,6,7,8
//byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,0 },  // = 0
//                                 { 0,1,1,0,0,0,0 },  // = 1
//                                 { 1,1,0,1,1,0,1 },  // = 2
//                                 { 1,1,1,1,0,0,1 },  // = 3
//                                 { 0,1,1,0,0,1,1 },  // = 4
//                                 { 1,0,1,1,0,1,1 },  // = 5
//                                 { 1,0,1,1,1,1,1 },  // = 6
//                                 { 1,1,1,0,0,0,0 },  // = 7
//                                 { 1,1,1,1,1,1,1 },  // = 8
//                                 { 1,1,1,0,0,1,1 }   // = 9
//                               };

byte seven_seg_digits[10][7] = { { 1,1,1,1,1,1,1 },  // = 0
                                 { 0,1,1,0,0,0,0 },  // = 1
                                 { 1,1,0,1,1,0,1 },  // = 2
                                 { 1,0,1,1,0,1,1 },  // = 3
                                 { 0,1,1,0,0,1,1 },  // = 4
                                 { 1,1,1,0,0,1,1 },  // = 5
                                 { 1,0,1,1,1,1,1 },  // = 6
                                 { 1,1,1,0,0,0,0 },  // = 7
                                 { 1,1,1,1,1,1,1 },  // = 8
                                 { 1,1,1,1,1,1,0 }   // = 9
                               };
                               
//int seven_seg_ints_rev[20] = {63,6,91,79,102,109,125,7,127,103,191,134,219,207,230,237,253,135,255,231};
int seven_seg_ints_rev[20] = {238,40,205,109,43,103,231,44,239,47};
//{63,6,91,79,102,109,125,7,127,103,191,134,219,207,230,237,253,135,255,231};

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

/*
 * changeLED(int led, int state) - changes an individual LED 
 * LEDs are 0 to 7 and state is either 0 - OFF or 1 - ON
 */
// void changeLED(int led, int state){
//   ledState = ledState & masks[led];  //clears ledState of the bit we are addressing
//   if(state == ON){ledState = ledState | bits[led];} //if the bit is on we will add it to ledState
//   updateLEDs(ledState);              //send the new LED state to the shift register
// }
 
 // Arduino 7 segment display example software
// http://www.hacktronics.com/Tutorials/arduino-and-7-segment-led.html
// License: http://www.opensource.org/licenses/mit-license.php (Go crazy)

void writeDot(byte dot) {
  digitalWrite(9, dot);
}
    
//Place represents what column digit to write.
//0 - ones
//1 - tens
void sevenSegWrite(byte digit, int place) {
  updateLEDs(digit,place);
}
