#include <MIDI.h>
#include <Servo.h>

//Declare servos
Servo base, shoulder, elbow;

//Declare buffers for servo states
//Servo values are valid between 0 - 180
int basep = 15;     //15 is straight ahead
int shoulderp = 60; // 60 is straight up, 80 is slightly leaning forward
int elbowp = 50;    // 50 is straight out, 80 is slightly leaning forward


MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  // put your setup code here, to run once:
  //Define the servos
  base.attach(6);
  shoulder.attach(5);
  elbow.attach(4);

  // Initiate MIDI
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleControlChange(handleControlChange);

  resetServoPosition();
}

//Set all servos to a base position
void resetServoPosition() {
  base.write(basep);
  shoulder.write(shoulderp);
  elbow.write(elbowp);
}

void handleNoteOn(byte channel, byte note, byte velocity){

  note = note * 1.42;   // Multiply with 1.42 to scale the 0-127 tange to 0-180
  switch (channel){
    case 1: // Base
      base.write(note);
      break;
    case 2: // Shoulder
      shoulder.write(note);
      break;
    case 3: // Elbow
      elbow.write(note);
      break;
  }
}

void handleControlChange(byte channel, byte number, byte value){

  int pos = number + value;

  switch (channel){
    case 1: // Base
      base.write(pos);
      break;
    case 2: // Shoulder
      shoulder.write(pos);
      break;
    case 3: // Elbow
      elbow.write(pos);
      break;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  MIDI.read();
}
