#include <MIDI.h>
#include <Servo.h>

//Declare servos
Servo base, shoulder, elbow;
//Declare buffers for their states
int basep = 15; 
int shoulderp = 60; 
int elbowp = 50; 
int buff = 0;

//Servo values are valid between 0 - 180


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

  //resetServoPosition();
}

//Set all servos to a base position
void resetServoPosition() {
  base.write(basep); //15 is straight ahead
  shoulder.write(shoulderp); // 60 is straight up, 80 is slightly leaning forward
  elbow.write(elbowp); // 50 is straight out, 80 is slightly leaning forward
}

void handleNoteOn(byte channel, byte note, byte velocity){

  note = note * 1.42;
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
    default:
      base.write(note);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  MIDI.read();
}
