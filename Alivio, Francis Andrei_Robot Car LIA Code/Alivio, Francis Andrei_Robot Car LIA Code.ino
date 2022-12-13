/*
Robot Car

This program is the recreated code of the Smart Robot Car V4.0 with the functions of the IR Remote, Line Tracking, and Obstacle.

This program makes use of #define, #include, IRremote.h, int, IRrecv, irrecv, decode_results, float, Servo.h, Servo, myservo, void, pinMode, digitalWrite, Serial.begin, irrecv.enableIRIn, myservo.attach, analogWrite, 
delayMicroseconds, pulseIn, return, if, irrecv.decode, Serial.println, results.value, irrecv.resume, switch, case, break, analogRead, Serial.print, else if, else, myservo.write, and delay.
*/

// MOTORS
#define PWMA 5 // Defines "PWMA" as the value of 5
#define PWMB 6 // Defines "PWMB" as the value of 6
#define AIN1 7 // Defines "AIN1" as the value of 7
#define BIN1 8 // Defines "BIN1" as the value of 8

// INFRARED REMOTE
#include "IRremote.h" // Includes IRremote library
int receiver = 9; // Creates an integer variable called "receiver" and give it the value of 9
IRrecv irrecv(receiver); // Set pin 9 ("receiver") as the infrared receiver
decode_results results; // Decode the results of the infrared receiver
int mode = 1; // Createes an integer variable called "mode" and give it the value of 1

// LINES
int right; // Creates an integer variable called "right"
int middle; // Creates an integer variable called "middle"
int left; // Creates an integer variable called "left"

// ULTRASONIC
#define trigPin 13 // Defines "trigPin" as the value of 13
#define echoPin 12 // Defines "echoPin" as the value of 12
float duration, distance; // Creates float variables called "duration" and "distance"

// SERVO
#include <Servo.h> // Includes Servo library
Servo myservo; // Begins the servo

void setup() { // Run the following code once
  // MOTORS
  pinMode(PWMA, OUTPUT); // Sets pin 5 ("PWMA") as an output
  pinMode(PWMB, OUTPUT); // Sets pin 6 ("PWMB") as an output
  pinMode(AIN1, OUTPUT); // Sets pin 7 ("AIN1") as an output
  pinMode(BIN1, OUTPUT); // Sets pin 8 ("BIN1") as an output
  pinMode(3, OUTPUT); // Sets pin 3 as an output
  digitalWrite(3, 1); // Gives pin 3 a high voltage

  // REMOTE
  Serial.begin(9600); // Sets the data rate in bits per second for serial data transmission
  irrecv.enableIRIn(); // Begins the infrared receiver

  // ULTRASONIC
  pinMode(trigPin, OUTPUT); // Sets pin 13 ("trigPin") as an output
  pinMode(echoPin, INPUT); // Sets pin 12 ("echoPin") as an input

  // SERVO
  myservo.attach(10); // Attaches the servo motor to pin 10
}

// MOVE MOTORS
void move(bool a, int x, bool b, int y) { // Creates a function called "move" with the following code
  digitalWrite(AIN1, a); // Gives pin 7 ("AIN1")
  analogWrite(PWMA, x); // Gives pin 5 ("PWMA")
  digitalWrite(BIN1, b); // Gives pin 8 ("BIN1")
  analogWrite(PWMB, y); // Gives pin 6 ("PWMB")
}

// READ ULTRASONIC SENSOR
void read() { // Creates a function called "move" with the following code
  digitalWrite(trigPin, LOW); // Gives pin 13 ("trigPin") a low voltage
  delayMicroseconds(2); // Delays the code for 2 microseconds
  digitalWrite(trigPin, HIGH); // Gives pin 13 ("trigPin") a high voltage
  delayMicroseconds(10); // Delays the code for 10 microseconds
  digitalWrite(trigPin, LOW); // Gives pin 13 ("trigPin") a low voltage

  duration = pulseIn(echoPin, HIGH); // Gives "duration" the value of the read high pulse of pin 12 ("echoPin")
  distance = (duration / 2) * 0.0343; // Gives "distance" the value of the quotient of the value of the distance and 2, and the product of the quotient and 0.0343
  return distance; // Terminates the function
}

void loop() { // Run the following code in repeat
  // REMOTE
  if (irrecv.decode(&results)) { // If the infrared receiver has decoded, do the following code
    Serial.println(results.value); // Prints in the serial monitor the result of the infrared receiver
    irrecv.resume(); // Resumes reading the infrared receiver

    switch(results.value) { // Checks the value of the result of the infrared receiver
      // FORWARD
      case 16736925: // If the result of the infrared receiver is 16736925, do the following code
      if (mode == 1) { // If the value of the variable "mode", do the following code
        move(1, 255/2, 1, 255/2); // Moves the robot car forward through function "move"
      }
      break; // Exits the switch...case loop
      
      // BACKWARD
      case 16754775: // If the result of the infrared receiver is 16754775, do the following code
      if (mode == 1) { // If the value of the variable "mode", do the following code
        move(0, 255/2, 0, 255/2); // Moves the robot car backward through function "move"
      }
      break; // Exits the switch...case loop
      
      // RIGHT
      case 16761405: // If the result of the infrared receiver is 16761405, do the following code
      if (mode == 1) { // If the value of the variable "mode", do the following code
        move(0, 255/3, 1, 255/3); // Turns the robot car right through function "move"
      }
      break; // Exits the switch...case loop
      
      // LEFT
      case 16720605: // If the result of the infrared receiver is 16720605, do the following code
      if (mode == 1) { // If the value of the variable "mode", do the following code
        move(1, 255/3, 0, 255/3); // Turns the robot car left through function "move"
      }
      break; // Exits the switch...case loop

      // STOP
      case 16712445: // If the result of the infrared receiver is 16712445, do the following code
      if (mode == 1) { // If the value of the variable "mode", do the following code
        move(0, 0, 0, 0); // Stops the robot car through function "move"
      }
      break; // Exits the switch...case loop

      // CHANGE TO MANUAL MODE
      case 16738455: // If the result of the infrared receiver is 16738455, do the following code
      mode = 1; // Gives the variable "mode" the value of 1
      move(0, 0, 0, 0); // Stops the robot car through function "move"
      break; // Exits the switch...case loop

      // CHANGE TO LINE TRACKING MODE
      case 16750695: // If the result of the infrared receiver is 16750695, do the following code
      mode = 2; // Gives the variable "mode" the value of 2
      move(0, 0, 0, 0); // Stops the robot car through function "move"
      break; // Exits the switch...case loop

      // CHANGE TO OBSTACLE MODE
      case 16756815: // If the result of the infrared receiver is 16756815, do the following code
      mode = 3; // Gives the variable "mode" the value of 3
      move(0, 0, 0, 0); // Stops the robot car through function "move"
      break; // Exits the switch...case loop
    }
  }

  // LINE TRACKING
  if (mode == 2) { // If the value of the variable "move" is 2, do the following code
    right = analogRead(A0); // Gives the variable "right" the value of the read analog value of pin A0
    middle = analogRead(A1); // Gives the variable "middle" the value of the read analog value of pin A1
    left = analogRead(A2); // Gives the variable "left" the value of the read analog value of pin A2

    // BASIC MOVEMENT
    if (right > 40) { // If the value of the variable "right" is greater than 40, do the following code
      move(0, 43, 1, 43); // Turns the robot car left through function "move"
    }

    else if (middle > 40) { // If the value of the variable "middle" is greater than 40, do the following code
      move(1, 85, 1, 85); // Moves the robot car forward through function "move"
    }

    else if (left > 40) { // If the value of the variable "left" is greater than 40, do the following code
      move(1, 43, 0, 43); // Turns the robot car right through function "move"
    }

    else { // If the conditions above are not followed, do the following code
      move(1, 85, 0, 85); // Turns the robot car right through function "move"

      if (middle > 40) { // If the value of the variable "middle" is greater than 40, do the following code
        return; // Terminates the function
      }
    }
  }

  // OBSTACLE
  if (mode == 3) { // Checks if the value of the variable "move" is 3, then do the following code
    move(1, 128, 1, 128); // Moves the robot car forward
    myservo.write(90); // Moves the servo into a 90 degree angle

    read(); // Reads the ultrasonic sensor through function "read"

    // IF THE FRONT IS BLOCKED, LOOK RIGHT
    if (distance <= 30) { // If the value of the variable "distance" is less than or equal to 30, do the following code
      move(0, 0, 0, 0); // Stops the robot car through function "move"
      myservo.write(180); // Moves the servo into an 180 degree angle
      delay(750); // Delays the code for 750 millisecond
      read(); // Reads the ultrasonic sensor through function "read"
      myservo.write(90); // Moves the servo into a 90 degree angle

      // IF THE RIGHT IS BLOCKED, LOOK LEFT
      if (distance <= 30) { // If the value of the variable "distance" is less than or equal to 30, do the following code
        move(0, 0, 0, 0); // Stops the robot car through function "move"
        myservo.write(0); // Moves the servo into a 0 degree angle
        delay(750); // Delays the code for 750 millisecond
        read(); // Reads the ultrasonic sensor through function "read"
        myservo.write(90); // Moves the servo into a 90 degree angle

        // IF THE LEFT IS BLOCKED, TURN BACK
        if (distance <= 30) { // If the value of the variable "distance" is less than or equal to 30, do the following code
        move(1, 255/3, 0, 255/3); // Turns the robot car left through function "move"
        delay(1500); // Delays the code for 1500 milliseconds
        return; // Terminates the function

        // IF THE LEFT IS OPEN, TURN RIGHT
        } else { // If the value of the variable "distance" is not less than or equal to 30, do the following code
          move(0, 255/3, 1, 255/3); // Turns the robot car right through function "move"
          delay(750); // Delays the code for 750 millisecond
        }

      // IF THE RIGHT IS OPEN, TURN RIGHT
      } else { // If the value of the variable "distance" is not less than or equal to 30, do the following code
        move(1, 255/3, 0, 255/3); // Turns the robot car left through function "move"
        delay(750); // Delays the code for 750 millisecond
      }
    }
  }
}
