
#include <SoftwareSerial.h>
const int switchPin = 10;  // The switch is on Arduino pin 10
const int LEDpin = 13;     //  Indicator LED

// Variables: 
byte note = 0;              // The MIDI note value to be played
byte trailnote = 0;
int AnalogValue = 0;        // value from the analog input
int lastNotePlayed = 0;     // note turned on when you press the switch
int lastSwitchState = 0;    // state of the switch during previous time through the main loop
int currentSwitchState = 0;

//software serial
SoftwareSerial midiSerial(2, 3); // digital pins that we'll use for soft serial RX & TX

void setup() 
{
    //  set the states of the I/O pins:
    pinMode(switchPin, INPUT);
    pinMode(LEDpin, OUTPUT);
    
    //  Set MIDI baud rate:
    Serial.begin(9600);
    blink(3);
    midiSerial.begin(31250);
}

void loop() 
{
    //  My potentiometer gave a range from 0 to 1023:
    AnalogValue = analogRead(0);
    //  convert to a range from 0 to 127:
    note = AnalogValue/8;
    if(lastSwitchState == 1)
    {
      currentSwitchState = note >=2;
    }
    else
    {
      currentSwitchState = note-trailnote >=5;
    }
    // Check to see that the switch is pressed:
    if (currentSwitchState == 1) {
      //  check to see that the switch wasn't pressed last time
      //  through the main loop:
      if (lastSwitchState == 0) {
        // set the note value based on the analog value, plus a couple octaves:
        // note = note + 60;
        // start a note playing:
        noteOn(0x90, 0x45, note);
        // save the note we played, so we can turn it off:
        lastNotePlayed = note;
        digitalWrite(LEDpin, HIGH);
      }
     }
    else {   // if the switch is not pressed:
      //  but the switch was pressed last time through the main loop:
      if (lastSwitchState == 1) {
        //  stop the last note played:
        noteOn(0x90, 0x45  ,0x00);
        digitalWrite(LEDpin, LOW);
      }
    }

    //  save the state of the switch for next time
    //  through the main loop:
    lastSwitchState = currentSwitchState;
    trailnote = analogRead(0)/8;
    delay(10);
}

//  plays a MIDI note.  Doesn't check to see that
//  cmd is greater than 127, or that data values are  less than 127:
void noteOn(byte cmd, byte data1, byte  data2) 
{
    midiSerial.write(cmd);
    midiSerial.write(data1);
    midiSerial.write(data2);
    Serial.println(data1);
   //prints the values in the serial monitor so we can see what note we're playing
   Serial.print("cmd: ");
   Serial.print(cmd);
   Serial.print(", data1: ");
   Serial.print(data1);
   Serial.print(", data2: ");
   Serial.println(data2);
}

  // Blinks an LED n times
  void blink(int n) {
    int i;
    for (i=0; i < n; i++) {
      digitalWrite(LEDpin, HIGH);
      delay(100);
      digitalWrite(LEDpin, LOW);
      delay(100);
    }
  }
