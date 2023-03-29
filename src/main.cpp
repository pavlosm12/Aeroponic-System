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
  // Pin declaration
  pinMode(pump, OUTPUT); // Relay module Input 1 connected to Arduino pin 4
  pinMode(fanPin, OUTPUT); // Q1 TIP120 gate resistor connected to Arduino pin 6
  pinMode(light, OUTPUT); // Q2 TIP120 gate resistor connected to Arduino pin
  pinMode(buzzer, OUTPUT); // Buzzer positive pin connected to Arduino pin 7
  pinMode(pressureInput, INPUT); // Pressure Sensor Signal output connected to Arduino pin A0
  pinMode(rxPin, INPUT); //declaring Arduino pin 9 as Input
  pinMode(txPin, OUTPUT); //declaring Arduino pin 10 as Output
  
ultrasonic_setup();
shtc3_setup();  // Initialize of shtc3 sensor
TSL2561B_setup(); // Initialize of shtc3 sensor

  attachInterrupt(0,handleInt,FALLING); // Attach Interrupt to pin D2
  DS3132_p_setup_adjust(); // Initialize the RTC module
  DS3132_p_setup_sqw(); // Enables the squarewave output of the RTC module
  mySerial.begin(9600); // Enables serial communication via Arduino PWM pins 9 & 10
  Serial.begin(9600); // Enables serial communication via Arduino PWM pins 0 & 1
}


void loop() {

 mySerial_check();
 ultrasonic_sensor();
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
print_state_light();
//print_state_readEEPROM ();
//print_state_writeEEPROM ();

}
