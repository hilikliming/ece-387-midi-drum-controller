// John J. Hall
// ECE 387 -- Midi Drum Machine
// This is the third revision of MIDI_Control incorporating multi input functionality

#include <SoftwareSerial.h>
const int switchPin = 10;  // The switch is on Arduino pin 10
const int LEDpin = 13;     //  Indicator LED

// Variables: 
byte note0 = 0;              // The MIDI note values to be played
byte note1 = 0;  
byte note2 = 0;  
byte note3 = 0;

// last cycle 'trailing' note for comparison of difference in velocities...
byte trailnote0 = 0;
byte trailnote1 = 0;
byte trailnote2 = 0;
byte trailnote3 = 0;

// placeholder for their appropriate notes. initialized in Bank A
byte note0Val = 0x45;
byte note1Val = 0x46;
byte note2Val = 0x47;
byte note3Val = 0x48;

int Analog0 = 0;        // value from the analog input
int Analog1 = 0; 
int Analog2 = 0; 
int Analog3 = 0; 

int lastNote0Played = 0;     // last note turned on when you give a sufficient impulse
int lastNote1Played = 0; 
int lastNote2Played = 0; 
int lastNote3Played = 0; 

int lastSwitchState0 = 0;    // state of the switch during previous time through the main loop
int lastSwitchState1 = 0; 
int lastSwitchState2 = 0; 
int lastSwitchState3 = 0; 

int currentSwitchState0 = 0;
int currentSwitchState1 = 0;
int currentSwitchState2 = 0;
int currentSwitchState3 = 0;

boolean bankState = true; // Start in bank A

//software serial
SoftwareSerial midiSerial(4, 5); // digital pins that we'll use for soft serial RX & TX
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

void getNotes()
{
  //  My potentiometer gave a range from 0 to 1023:
    Analog0 = analogRead(0);
    Analog1 = analogRead(1);
    Analog2 = analogRead(2);
    Analog3 = analogRead(3);
    //  convert to a range from 0 to 127:
    note0 = Analog0/8;
    note1 = Analog1/8;
    note2 = Analog2/8;
    note3 = Analog3/8;
}

void getSwitchState()
{
  // send note if any of the notes are depressed are above 2
  if(lastSwitchState0 == 1){currentSwitchState0 = (note0 >=2);}
    else {currentSwitchState0 = note0-trailnote0 >=5;}
  if(lastSwitchState1 == 1){currentSwitchState1 = (note1 >=2);}
    else {currentSwitchState1 = note1-trailnote1 >=5;}
  if(lastSwitchState2 == 1){currentSwitchState2 = (note2 >=2);}
    else {currentSwitchState2 = note2-trailnote2 >=5;}
  if(lastSwitchState3 == 1){currentSwitchState3 = (note3 >=2);}
    else {currentSwitchState3 = note3-trailnote3 >=8;}
}

void doNotes()
{
  // Check to see that the switch is pressed:
    if (currentSwitchState0 == 1) {
      //  check to see that the switch wasn't pressed last time
      if (lastSwitchState0 == 0) { 
        // set the note value based on the analog value, plus a couple octaves:
        noteOn(0x90, note0Val, note0);
        // save the note we played, so we can turn it off:
        lastNote0Played = note0;
      }
     }
    else {   // if the switch is not pressed:
      //  but the switch was pressed last time through the main loop:
      if (lastSwitchState0 == 1) {
        //  stop the last note played:
        noteOn(0x90, note0Val  ,0x00);
        digitalWrite(LEDpin, LOW);
      }
    }
    if (currentSwitchState1 == 1) {
      if (lastSwitchState1 == 0) { noteOn(0x90, note1Val, note1); lastNote1Played = note1;}
    }
    else {if (lastSwitchState1 == 1) {noteOn(0x90, note1Val  ,0x00); digitalWrite(LEDpin, LOW);}
    }
    if (currentSwitchState2 == 1) {
      if (lastSwitchState2 == 0) { noteOn(0x90, note2Val, note2); lastNote2Played = note2;}
    }
    else {if (lastSwitchState2 == 1) {noteOn(0x90, note2Val  ,0x00); digitalWrite(LEDpin, LOW);}
    }
    if (currentSwitchState3 == 1) {
      if (lastSwitchState3 == 0) { noteOn(0x90, note3Val, note3); lastNote3Played = note3;}
    }
    else {if (lastSwitchState3 == 1) {noteOn(0x90, note3Val  ,0x00); digitalWrite(LEDpin, LOW);}
    }
    if(currentSwitchState0 == 1 ||currentSwitchState1 == 1 ||currentSwitchState2 == 1 ||currentSwitchState3 == 1)
    {
      digitalWrite(LEDpin, HIGH);
    }
}
void cleanUp()
{
  //  save the state of the 'switches' for next time
    lastSwitchState0 = currentSwitchState0;
    trailnote0 = analogRead(0)/8;
    lastSwitchState1 = currentSwitchState1;
    trailnote1 = analogRead(1)/8;
    lastSwitchState2 = currentSwitchState2;
    trailnote2 = analogRead(2)/8;
    lastSwitchState3 = currentSwitchState3;
    trailnote3 = analogRead(3)/8;
}
void loop() 
{
    // Gets notes for use
    getNotes();
    // Update switch state
    getSwitchState();
    doNotes();
    cleanUp();
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
