#ifndef CONFIG_H
#define CONFIG_H
//-------------------------------
// Pin configurations SRS Section 8.1
//-------------------------------
#define CURRENT_PIN           35
#define VOLTAGE_PIN           34
#define DHT_PIN               15
#define DHT_TYPE              DHT22
#define RELAY_PIN             26
#define BTN_PLUGIN            32
#define BTN_PLUGOUT           33
#define LED_GREEN             18
#define LED_YELLOW            19
#define LED_RED               21    

//=======WIFI details======================
constexpr const char* WIFI_SSID = "Wokwi-GUEST";
constexpr const char* WIFI_PASS = "";

//=============ThingsBoard Details===================
constexpr const char* MQTT_SERVER="mqtt.thingsboard.cloud";
constexpr int MQTT_PORT=1883;

// ThinhgsBoard device access token
constexpr const char* TB_TOKEN="KgYmeo1OmP2Wn7VSDy7f";
constexpr const char* BAY_ID="BAY_1"; 



#endif