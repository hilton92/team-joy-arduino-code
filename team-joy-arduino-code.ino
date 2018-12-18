/*
 * Author: Benjamin Hilton
 * Date: November 2018
 * Developed for ME 576
 * Team Joy
 */

int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int analogPin1 = 0;
int analogPin2 = 1;
int analogPin3 = 2;
int val1 = 0;
int val2 = 0;
int val3 = 0;



class Sensor{
  int potPin;
  int irPin;
  int numLocation;
  float prevPot{0.f};
  float prevIR{0.f};
  float valPot{0.f};
  float valIR{0.f};
  public:
  Sensor(int pot, int IR, int number){
    potPin = pot;
    irPin = IR;
    numLocation = number;
  }

  void sense_arm(){
    //Read from pot
    valPot = analogRead(potPin);
    //Compare to previous value
    //
    //Read from IR
    valIR = analogRead(irPin);
    //Compare to previous value
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*val1 = analogRead(analogPin1);
  val2 = analogRead(analogPin2);
  val3 = analogRead(analogPin3);
  Serial.println("Pin 1:");
  Serial.println(val1);
  Serial.println("Pin 2:");
  Serial.println(val2);
  Serial.println("Pin 3:");
  Serial.println(val3);
  delay(2000);*/

  
  setColor(255, 0, 0); // Red Color
  delay(1000);
  setColor(0, 255, 0); // Green Color
  delay(1000);
  setColor(0, 0, 255); // Blue Color
  delay(1000);
  setColor(255, 255, 255); // White Color
  delay(1000);
  setColor(170, 0, 255); // Purple Color
  delay(1000);
}



void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
