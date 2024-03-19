#include "command_frequencies.h"
#include <SoftwareSerial.h>

SoftwareSerial HM10(2,3);
char Incoming_value = "";

enum {commandWaiting, commandPlay, commandConfirm, cameraMode};
unsigned char commandState;

void setup()
{
  Serial.begin(9600);
  HM10.begin(9600);
  commandState = 0;
  pinMode(8, OUTPUT);
}

void loop() {
    switch (commandState) {
      case commandWaiting:
      
      if (HM10.available()) {
        Incoming_value = HM10.read();

        if (Incoming_value == '\0'){
          break;
        }

        commandState = commandPlay;
        break;
      }
      
      else {
        break;
      }

      case commandPlay:
      Serial.println("Playing Command. Wait one second.");
      playCommand(Incoming_value);
      commandState = commandConfirm;
      break;

      case commandConfirm:
      Serial.println("Confirming the command was played");
      confirmCommand(Incoming_value);
      commandState = commandWaiting;
      break;

      default:
      Serial.println("\n We hit the default");
      commandState = commandWaiting;
      break;
    }
}

void playCommand(char command_name) {
    if(command_name == '1')
    {
      Serial.println("Running Sit!");
      for (int i = 0; i < 3; i++)
      {
        tone(8, sit[i], sit[3]);
        delay(sit[3]);
      }
    }
      
    else if(command_name == '2') {
      for (int i = 0; i < 3; i++)
      {
        tone(8, down[i], down[3]);
        delay(down[3]);
      }
    }

    else if(command_name == '3') {
      for (int i = 0; i < 3; i++)
      {
        tone(8, stay[i], stay[3]);
        delay(stay[3]);
      }
    }

    else if(command_name == '4') {
      for (int i = 0; i < 3; i++)
      {
        tone(8, forward[i], forward[3]);
        delay(forward[3]);
      }
    }

    else if(command_name == '5') {
      for (int i = 0; i < 3; i++)
      {
        tone(8, left[i], left[3]);
        delay(left[3]);
      }
    }

    else if(command_name == '6') {
      for (int i = 0; i < 3; i++)
      {
        tone(8, right[i], right[3]);
        delay(right[3]);
      }
    }
}

void confirmCommand(char command_name) {
  Serial.println("CONFIRMING!");
}