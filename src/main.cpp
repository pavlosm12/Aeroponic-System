#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <time.h>
#include <SoftwareSerial.h>
#include <led_schedule>





// Interrupt Handler
void handleInt() 
{
  ticks++;
}



void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(photoResistorPin, INPUT);
  pinMode(tmp36_Pin, INPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // Attach Interrupt to pin D2
  attachInterrupt(0,handleInt,FALLING);
  DS3132_p_setup_adjust();
  DS3132_p_setup_sqw();

  mySerial.begin(9600);
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}








void loop() {
 // -------------------- Receive Bluetooth signal ----------------------
 test12();
 mySerial_check();
  // put your main code here, to run repeatedly:




//analogWrite(led3, pwmLed);
if (blink_enable == 0){

digitalWrite(led1,pump_button);
}



/*
if(millis() >= time_now + period)
{
        time_now += period;
        Serial.print("Photo resistor: ");
        Serial.print(photoValue);
        Serial.println(" %");
        Serial.print("Temperature = ");
        Serial.print(tmp36_temperature);
        

}
 */

print_time ();

SM_led1();
SM_pump ();
print_state_led1 ();
print_state_pump ();





}
