#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <time.h>
#include <SoftwareSerial.h>
#include <function_declaration>
#include <EEPROM.h>


// Interrupt Handler
void handleInt() 
{
  ticks++;
}


void setup() {

    // Connect to I2C bus as master
  Wire.begin();
  // Pin declaretion
  pinMode(pump, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(light, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pressureInput, INPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
ultrasonic_setup();
shtc3_setup();  //shtc3
TSL2561B_setup();
//tsl2561_setup();

  attachInterrupt(0,handleInt,FALLING); // Attach Interrupt to pin D2

  DS3132_p_setup_adjust();
  DS3132_p_setup_sqw();
  mySerial.begin(9600);
  Serial.begin(9600);

}





void loop() {

 ultrasonic_sensor();
 mySerial_check();
 pumpTimings();
 SM_light ();
 update_time ();
 pressure();
 buzzerTimings ();
 analogWrite(fanPin,fanPwm);
 send_data();
 SM_writeEEPROM();
 //SAVE BUTTON
if (Save_Global == 1) {state_writeEEPROM = 2; Save_Global = 0;};
SM_readEEPROM();
//print_state_readEEPROM ();
//print_state_writeEEPROM ();

}
