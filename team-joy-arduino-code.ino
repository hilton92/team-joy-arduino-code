/*
 * Author: Benjamin Hilton
 * Date: November 2018
 * Developed for ME 576
 * Core System Code
 */

// Pins for RGB LED
int redPin = 3;
int greenPin = 5;
int bluePin = 6;

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
int motorPWMPin = 11;
int motorIN_1 = 12;
int motorIN_2 = 13;

// Pin for Servo
int servoPWMPin = 9;

// Pin for Switch
int switchPin = 15;

// Analog Variables

int potSum = 0;
int basePotSum = 0;
int IRSum = 0;
int baseIRSum = 0;
int potDifference = 0;
int IRDifference = 0;

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
  myMotor.enable(); //turn on the motor
  setColor(0, 0, 255); //turn LED blue
  delay(600); //wait 0.6 seconds to let the sensors reach steady state
  calibrate(); // calibrate the sensors
  setColor(0, 255, 0); //turn LED green
}

void loop(){
  potSum = analogRead(pot1Pin) + analogRead(pot2Pin) + analogRead(pot3Pin) + analogRead(pot4Pin);
  potDifference = abs(potSum - basePotSum);
  IRSum = analogRead(IR1Pin) + analogRead(IR2Pin) + analogRead(IR3Pin) + analogRead(IR4Pin);
  IRDifference = abs(IRSum - baseIRSum);
  if (potDifference > 8 || IRDifference > 300){
    setColor(255, 0, 0);
    myMotor.disable();
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
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
  basePotSum = Pot_1 + Pot_2 + Pot_3 + Pot_4;
  baseIRSum = IR_1 + IR_2 + IR_3 + IR_4;
}
