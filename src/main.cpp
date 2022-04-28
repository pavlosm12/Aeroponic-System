#include <Arduino.h>
#include <DS3132_p>
#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <time.h>
#include <Bluetooth_module>
#include <SoftwareSerial.h>
int led_counter = 0 ;


// Interrupt Handler
void handleInt() 
{
  ticks++;
}

void tick_counter()
{
if (ticks != old_tick_value) 
{
  led_counter++;
}
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
 
  if(millis() >= time_now2 + period2)
{
  Tmp36();
  Ky_018();
  Dht_11();
        time_now2 += period2;
  send_BT(tmp36_temperature_ID,temp36_temperature_scaled);  
  send_BT(photoValue_ID,photoValue);
  send_BT(humidity_ID, h_scaled);    // function to write id and value to the bluetooth interface (and split value in MSB and LSB
  send_BT(tempdht11_ID, t_scaled);    // function to write id and value to the bluetooth interface (and split value in MSB and LSB
}
  mySerial_check ();
 

if (blink_enable == 1)
{
currentMillis = millis();
if((ledState == HIGH) && (currentMillis - previousMillis >= led_on))
    {
    	ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(led2, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= led_off))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(led2, ledState);	  // Update the actual LED
    }    
}

 if (blink_enable == 0)
{
  ledState = LOW;
  digitalWrite(led2, ledState);
}
   
  // put your main code here, to run repeatedly:



analogWrite(led3, pwmLed);
digitalWrite(led1,state_led1);

if(minute != old_minute_value){
  old_minute_value = minute;
  led_counter++;

}

if (timepicker == minute)
{
led_counter = 0;
     analogWrite(led3, ledstrip_pwm);
    }
else  if (led_counter >= ledstrip_duration)
{
  analogWrite(led3, 0);

}



if(millis() >= time_now + period)
{
        time_now += period;
        Serial.print("Photo resistor: ");
        Serial.print(photoValue);
        Serial.println(" %");
        Serial.print("Temperature = ");
        Serial.print(tmp36_temperature);
        Serial.println(" C");
        Serial.print("HOUR = ");
        Serial.println (hour);
        Serial.print("MINUTE = ");
        Serial.println (minute);
        Serial.print("OLD_HOUR = ");
        Serial.println (old_hour_value);       
        Serial.print("Led_counter = ");
        Serial.println (led_counter);  

}
 
print_time ();






}
