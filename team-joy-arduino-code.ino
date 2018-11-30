/*
 * Author: Benjamin Hilton
 * Date: November 2018
 * Developed for ME 576
 * Team Joy
 */

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

}

void loop() {
  // put your main code here, to run repeatedly:

}
