#include <ThingSpeak.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include<ESP8266WiFi.h>

#define ONE_WIRE_BUS  D4

int pHpin = A0; // Connect the sensor's Po output to analogue pin 0.

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

float Po;

//Setup  a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

WiFiClient client;
unsigned long myChannelNumber = ENTER YOUR THINGSPEAK CHANNEL ID ;//Channel Id
const char* myWriteAPIKey = "YOUR_THINHSPEAK_WRITEAPI_KEY";

void setup()
{
  Serial.begin(115200);
  delay(10);

  //connect to WiFi network

  WiFi.begin(ssid,password);

  ThingSpeak.begin(client);
 
}

void temp_read()
{
  // send the command to get temperatures
  sensors.requestTemperatures();

 //print the temperatures in celcius
  sensors.requestTemperatures();
   
  float temp=sensors.getTempCByIndex(0);

  ThingSpeak.writeField(myChannelNumber,2,temp,myWriteAPIKey);//Update in thingSpeak
  
}

void ph_read()
{
  Po = ((1023 - analogRead(pHpin)) / 73.07); // Read the analogue input value from the pH sensor then scale 0-14.
  Serial.print("Ph value: ");
  Serial.println(Po, 2); // Print the result in the serial monitor.
  ThingSpeak.writeField(myChannelNumber,3,Po,myWriteAPIKey);//Update in thingSpeak
}

void loop()
{
  ph_read();

  delay(2000);

  temp_read();
}
