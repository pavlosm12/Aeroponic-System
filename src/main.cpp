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
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  

shtc3_setup();  //shtc3
tsl2561_setup();
//Ultrasonic_sensor_setup();
  
  attachInterrupt(0,handleInt,FALLING); // Attach Interrupt to pin D2

  DS3132_p_setup_adjust();
  DS3132_p_setup_sqw();
  mySerial.begin(9600);
  Serial.begin(9600);
}





void loop() {
 // -------------------- Receive Bluetooth signal ----------------------
 test12();
 mySerial_check();
 pumpTimings();

//print_time ();

//SM_led1();
//Ultrasonic_sensor_readings();
//SM_writeEEPROM();
//SM_readEEPROM();
//print_state_writeEEPROM ();
//print_state_readEEPROM ();

}
