#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"
#include "Network.h"

DHT dht(DHT_PIN, DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax) {
  return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

void sample_sensor(void){
  int raw_cur= analogRead(CURRENT_PIN); //0 to 4095    //0-32 Amphere 
  int raw_vol= analogRead(VOLTAGE_PIN); //0 to 4095    //0-250 Volts


  voltage=mapFloat(raw_vol, 0, 4095, 0, 250); // convert raw voltage to actual voltage

  if(bayStatus=="Charging")
  {
    current=mapFloat(raw_cur, 0, 4095, 0, 32); // convert raw current to actual current
  }
   else
  {
    current=0; // if not charging, current is zero
  }

  //read curr and store 5 values array



  //cal pow
  power=voltage*current; // calculate power in watts

  
  float t = dht.readTemperature(DHT_PIN); // to read temperature in Celsius, use dht.readTemperature(true) for Fahrenheit
  if (!isnan(t)) temperature = t; // check if the reading is valid
  
}

float recentAvgCurrent()
{
  float sum=0;
  //read recent 5 current values
  for(int i=0; i<5;i++)
  {
    sum=sum+current;
     
  }

  return sum/5.0; // return the average of the last 5 current readings
}



bool plugin_flag_once = 1;
bool plugout_flag_once = 1;

void plugstat(void)
{
  // detect the switch is pressed or not
    bool pluginReading = digitalRead(BTN_PLUGIN);

  // Switch1-Plug In---IF on change the bay_status from free to charging
    if(pluginReading==LOW && plugin_flag_once)
    {
        sessionStartMs = millis(); // record the start time of the charging session
        //plug_in switch is pressed
        plugin_flag_once = 0; // to avoid multiple detection of the same event
        // change the bay status to charging
        if(bayStatus=="Free")
        {
            bayStatus="Charging";
            Serial.println("Bay_3 plugin detected, BAY_3 Status=Charging");
            digitalWrite(RELAY_PIN, HIGH); // turn on the relay to start charging
        }
    }

    if(pluginReading==HIGH)
    {
        //plug_in switch is released
        plugin_flag_once = 1; // to avoid multiple detection of the same event
    }


    // Switch2-Plug Out--- IF on then charging is done and bay status is free
    
      bool plugoutReading = digitalRead(BTN_PLUGOUT);

    if(plugoutReading==LOW && plugout_flag_once)
    {
        //plug_out switch is pressed
        plugout_flag_once = 0; // to avoid multiple detection of the same event
        // change the bay status to free
        if(bayStatus=="Charging")
        {
            bayStatus="Free";
            Serial.println("Bay_3 plugout detected, BAY_3 Status=Free");
        }
    }
    if (plugoutReading==HIGH)
    {
        //plug_out switch is released
        plugout_flag_once = 1; // to avoid multiple detection of the same event
    }
}


// update LED's as well
void update_leds_status(void)
{
  if(bayStatus=="Free")
  {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
   
  }
  else if(bayStatus=="Charging")
  {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
  }
}