#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <time.h>
#include <SoftwareSerial.h>
#include <led_schedule>
#include <EEPROM.h>


// Interrupt Handler
void handleInt() 
{
  ticks++;
}


void setup() {

    // Connect to I2C bus as master
  Wire.begin();
  // put your setup code here, to run once:
  pinMode(pump, OUTPUT);
  pinMode(fanPin, OUTPUT);
  pinMode(light, OUTPUT);
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
 // -------------------- Receive Bluetooth signal ----------------------
 ultrasonic_sensor();
 test12();
 mySerial_check();
 pumpTimings();
 SM_light ();
 print_time ();
 pressure();

 //SAVE BUTTON
//if (Save_Global == 1) {state_writeEEPROM = 2;};


//SM_led1();
//Ultrasonic_sensor_readings();
//SM_writeEEPROM();
//SM_readEEPROM();
//print_state_writeEEPROM ();
//print_state_readEEPROM ();

}
