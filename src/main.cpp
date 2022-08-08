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
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  

shtc3_setup();  //shtc3
tsl2561_setup();
Ultrasonic_sensor_setup();
  
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
  // put your main code here, to run repeatedly:




//analogWrite(led3, pwmLed);
if (Auto_EN_DIS == 0){

digitalWrite(led1,Manual_ON_OFF);
}





// PUMP AUTO/MANUAL BUTTONS LOGIC //
 
if ( Auto_EN_DIS !=0 )
{

  SM_pump();
}

if (Auto_EN_DIS != 1)
{
  if (Manual_ON_OFF != 0)
  {
    digitalWrite(4,Manual_ON_OFF); //insert pump pin here 
  }
}
// PUMP AUTO/MANUAL BUTTONS LOGIC //
print_time ();

//SM_led1();
SM_pump ();
Ultrasonic_sensor_readings();
pressure();
SM_writeEEPROM();
SM_readEEPROM();
print_state_writeEEPROM ();
print_state_readEEPROM ();

analogWrite(led2,pwmLed);


}
