#include "command_frequencies.h"
char Incoming_value = "";

enum {commandWaiting, commandPlay, commandConfirm, cameraMode};
unsigned char commandState;

void setup()
{
  Serial.begin(9600);
  commandState = 0;
  pinMode(A3, INPUT);
  pinMode(8, OUTPUT);
}

void loop() {
    switch (commandState) {
      case commandWaiting:
      Serial.println("Waiting for Command");
      
      if (Serial.available() > 0) {
        Incoming_value = Serial.read();
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
    if(command_name == "sit")
    {
      for (int i = 0; i < 3; i++)
      {
        tone(8, sit[i], sit[3]);
        delay(sit[3]);
      }
    }
      
    else if(command_name == "stay") {
      for (int i = 0; i < 3; i++)
      {
        tone(8, stay[i], stay[3]);
        delay(stay[3]);
      }
    }

    else if(command_name == "down") {
      for (int i = 0; i < 3; i++)
      {
        tone(8, down[i], down[3]);
        delay(down[3]);
      }
    }

    else if(command_name == "left") {
      for (int i = 0; i < 3; i++)
      {
        tone(8, left[i], left[3]);
        delay(left[3]);
      }
    }

    else if(command_name == "right") {
      for (int i = 0; i < 3; i++)
      {
        tone(8, right[i], right[3]);
        delay(right[3]);
      }
    }

    else if(command_name == "left") {
      for (int i = 0; i < 3; i++)
      {
        tone(8, left[i], left[3]);
        delay(left[3]);
      }
    }
}

void confirmCommand(char command_name) {
  Serial.println("CONFIRMING!");
}