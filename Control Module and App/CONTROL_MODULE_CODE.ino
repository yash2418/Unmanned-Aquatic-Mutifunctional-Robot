#include <WiFi.h>
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = ""; //WIFI SSID
const char* password = "";    //WIFI PASSWORD

/* data received from application */
String  data ="";

#define forward1 2
#define forward2 4

#define reverse1 5
#define reverse2 18

#define conveyer1 13
#define conveyer2 27

#define weedcutter1 25
#define weedcutter2 32


void setup() {
  pinMode(forward1,OUTPUT);
  pinMode(forward2,OUTPUT);
  pinMode(reverse1,OUTPUT);
  pinMode(reverse2,OUTPUT);
  pinMode(conveyer1,OUTPUT);
  pinMode(conveyer2,OUTPUT);
  pinMode(weedcutter1,OUTPUT);
  pinMode(weedcutter2,OUTPUT);

  stop_mov();
  digitalWrite(conveyer1,HIGH);
  digitalWrite(conveyer2,HIGH);
  digitalWrite(weedcutter1,HIGH);
  digitalWrite(weedcutter2,HIGH);
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //connectWiFi();
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) 
    return; 
    data = checkClient();
    Serial.print(data);

    if(data == "FORWARD")
    {
      //FORWARD MOVEMENT:
      forward_mov();
    }
    else if(data == "LEFT")
    {
      //LEFT MOVEMENT:
      left_mov();
    }
    else if(data == "RIGHT")
    {
      //RIGHT MOVEMENT:
      right_mov();
    }
    else if(data == "STOP")
    {
      //STOP MOVEMENT:
      stop_mov();
    }
    else if(data == "DOWN")
    {
      //BACKWARD MOVEMENT:
      reverse_mov();
    }
    else if(data == "CONVON")
    {
      //CONVEYER ON:
      conv_on();
    }
    else if(data == "CONVOFF")
    {
      //CONVEYER OFF:
      conv_off();
    }
    else if(data == "WEEDON")
    {
      //WEED CUTTER ON:
      weed_on();
    }
    else if(data == "WEEDOFF")
    {
      //WEED CUTTER OFF:
      weed_off();
    }
    
}

void forward_mov()
{
  digitalWrite(forward1,LOW);
  digitalWrite(forward2,LOW);
  digitalWrite(reverse1,HIGH);
  digitalWrite(reverse2,HIGH);
}

void reverse_mov()
{
  digitalWrite(forward1,LOW);
  digitalWrite(forward2,LOW);
  digitalWrite(reverse1,LOW);
  digitalWrite(reverse2,LOW);
}

void left_mov()
{
  digitalWrite(forward1,LOW);
  digitalWrite(forward2,HIGH);
  digitalWrite(reverse1,HIGH);
  digitalWrite(reverse2,HIGH);
}

void right_mov()
{
  digitalWrite(forward1,HIGH);
  digitalWrite(forward2,LOW);
  digitalWrite(reverse1,HIGH);
  digitalWrite(reverse2,HIGH);
}

void stop_mov()
{
  digitalWrite(forward1,HIGH);
  digitalWrite(forward2,HIGH);
  digitalWrite(reverse1,HIGH);
  digitalWrite(reverse2,HIGH);
}

void conv_on()
{
  digitalWrite(conveyer1,LOW);
  digitalWrite(conveyer2,LOW);
}

void conv_off()
{
  digitalWrite(conveyer1,HIGH);
  digitalWrite(conveyer2,HIGH);
}

void weed_on()
{
  digitalWrite(weedcutter1,LOW);
  digitalWrite(weedcutter2,LOW);
}

void weed_off()
{
  digitalWrite(weedcutter1,HIGH);
  digitalWrite(weedcutter2,HIGH);
}

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
