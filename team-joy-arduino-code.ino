/*
 * Author: Benjamin Hilton
 * Date: November 2018
 * Developed for ME 576
 * Core System Code
 */
#include <Servo.h>


// Pins for RGB LED
int redPin = 3;
int greenPin = 2;
int bluePin = 0;

// Pins for Potentiometers
int pot1Pin = 7;
int pot2Pin = 6;
int pot3Pin = 5;
int pot4Pin = 4;

// Pins for IR sensors
int IR1Pin = 3;
int IR2Pin = 2;
int IR3Pin = 1;
int IR4Pin = 0;

// Pins for Motor Driver
int motorPWMPin = 8;
int motorIN_1 = 9;
int motorIN_2 = 10;

// Pin for Servo
int servoPWMPin = 6;

// Pin for Switch 
int switchPin = 12;

// Analog Variables
int potSum = 0;
int basePotSum = 0;
int IRSum = 0;
int baseIRSum = 0;
int potDifference = 0;
int IRDifference = 0;
int switchVal = 0;

// Servo Variables
int counter = 1;
int limit = 60;
int stepDelay = 10;
int cycleDelay = 1500;
int servoDirection = 1;
int prevDirection = 0;
int waitCounter = 0;

class DCMotor{
  int pwmPin;
  int IN_1;
  int IN_2;
  public:
  // constructor
  DCMotor(int pwm, int IN1, int IN2){
    pwmPin = pwm;
    IN_1 = IN1;
    IN_2 = IN2;
  }

  void enable(){
    digitalWrite(pwmPin, HIGH);
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  }
  
  void disable(){
    digitalWrite(pwmPin, LOW);
    digitalWrite(IN_1, HIGH);
    digitalWrite(IN_2, LOW);
  }
};

DCMotor myMotor(motorPWMPin, motorIN_1, motorIN_2); //create motor object
Servo myServo;


void setup() {
  // Setup Inputs and Outputs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(motorPWMPin, OUTPUT);
  pinMode(motorIN_1, OUTPUT);
  pinMode(motorIN_2, OUTPUT);
  pinMode(servoPWMPin, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
  myServo.attach(servoPWMPin);
  myMotor.enable(); //turn on the motor
  setColor(0, 0, 1); //turn LED blue
  delay(2000); //wait 2 seconds to let the sensors reach steady state
  calibrate(); // calibrate the sensors
  setColor(0, 1, 0); //turn LED green
}

void loop(){
  potSum = analogRead(pot1Pin) + analogRead(pot3Pin) + analogRead(pot4Pin);
  potDifference = abs(potSum - basePotSum);
  IRSum = analogRead(IR1Pin) + analogRead(IR2Pin) + analogRead(IR3Pin) + analogRead(IR4Pin);
  IRDifference = abs(IRSum - baseIRSum);
  //Serial.println(IRDifference);
  if (potDifference > 30 || IRDifference > 260){
    setColor(1, 0, 0);
    if (digitalRead(switchPin) == HIGH){
        myMotor.disable();
    }
    for (int i = 0; i < 50; i++){
      servo_take_step();
    }
  }
  setColor(0, 1, 0); //turn LED green
  servo_take_step();
}

void setColor(int redValue, int greenValue, int blueValue) {
  digitalWrite(redPin, redValue);
  digitalWrite(greenPin, greenValue);
  digitalWrite(bluePin, blueValue);
}

void servo_take_step(){
  myServo.write((counter + 20));
  delay(stepDelay);
  if (counter == limit || counter == 0){
    if (waitCounter == 150){
      if (counter == 60){
        servoDirection = -1;
      }
      if (counter == 0){
        servoDirection = 1;
      }
      waitCounter = 0;
    }
    else{
      servoDirection = 0;
    }
    waitCounter = waitCounter + 1;
  }
  counter = counter + servoDirection;
  Serial.println(counter);
}

void calibrate(){
  int Pot_1 = analogRead(pot1Pin);
  int Pot_2 = analogRead(pot2Pin);
  int Pot_3 = analogRead(pot3Pin);
  int Pot_4 = analogRead(pot4Pin);
  int IR_1 = analogRead(IR1Pin);
  int IR_2 = analogRead(IR2Pin);
  int IR_3 = analogRead(IR3Pin);
  int IR_4 = analogRead(IR4Pin);
  basePotSum = Pot_1 + Pot_3 + Pot_4;
  baseIRSum = IR_1 + IR_2 + IR_3 + IR_4;
}
