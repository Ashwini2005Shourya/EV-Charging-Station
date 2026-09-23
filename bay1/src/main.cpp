#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"
#include "Network.h"
#include "Telementry.h"
#include "Edge_AI.h"
#include "Optimization.h"
#include "rpc.h"
#include "attributes.h"


void setup() {
  Serial.begin(115200); // initialize serial monitor
  dht.begin(); //initializing the DHT sensor

  //config esp32 with real time
  configTime(0,0,"pool.ntp.org", "time.nist.gov");

  //config periperals pins
  pinMode(BTN_PLUGIN, INPUT_PULLUP);
  pinMode(BTN_PLUGOUT, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  //connect board to WiFi
  connectWiFi();

  //config mqtt server
  mqtt.setServer(MQTT_SERVER, MQTT_PORT); //mqqt server address and port no.

  //set call back function to handle RPC requests from cloud
  mqtt.setCallback(mqttCallback);
  mqtt.setBufferSize(512); //set mqtt buffer size to 512 bytes
  //connect board to cloud
  connectMQTT(); //Token, device id

}

unsigned long now;
unsigned long last_print;

void loop() {
  mqtt.loop();
 // print values every 2 seconds
  
  now=millis();
  if ((now - last_print) >= 5000) 
  {
    last_print = now;
    // read data from sensors// voltage, current, temperature , power, bay status
    sample_sensor();

    //run edge ai inference to predict arrival probability and duration
    runEdgeAIInference();
    if (manualOverrideActive == false) {
    //decide load decision based on edge ai prediction and optimization logic
    runOptimization();
  }
    //publish the data to cloud using mqtt protocol
    publishTelemetry();
    
  }

  plugstat();
  updateLeds();
  
}

