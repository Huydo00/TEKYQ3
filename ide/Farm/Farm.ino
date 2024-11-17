#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"
#include <Servo.h>     
WiFiClient client;
/* 1. Define the WiFi credentials */
// #define WIFI_SSID "Huy Do"
// #define WIFI_PASSWORD "0938360303"
#define WIFI_SSID "TEKY OFFICE"
#define WIFI_PASSWORD "Teky@2018"

String apiKey = "L6282CFT0GQORMGR";
const char* server = "api.thingspeak.com";

/* 2. Define the API Key */
#define API_KEY "AIzaSyAn0rRvInY8z2XsOMulwNpv9ckU-OKB2CY"

/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "hhuys0105@gmail.com"
#define USER_PASSWORD "12345678"

/* 4. Define the RTDB URL */
#define DATABASE_URL "smh-iot-2e746-default-rtdb.firebaseio.com/" 

/***********************DEVICE***********************/
#define LED1 4     //D2
#define TRONG 0     //D3
#define SVROOF 2   //D4
#define LIGHT 14   //D5  BT 0
#define L1 12    //D6
#define L2 13    //D7
#define L3 15    //D8
/***********************SENSOR***********************/ 
#define SOIL A0  //A0     BT1
#define RAIN 16  //D0     BT1
#define DHT_SENSOR_PIN 5  //D1
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
Servo myservo;
/***********************VARIABLE***********************/
uint16_t flameSensor;
float humidity;
float temperature;
float valueSOIL;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup()
{
    // Y
    pinMode(LED1,OUTPUT);
    pinMode(L1,OUTPUT);
    pinMode(L2,OUTPUT);
    pinMode(L3,OUTPUT);
    
    myservo.attach(SVROOF);
    // // X
    dht.begin();
    pinMode(LIGHT,INPUT);
    pinMode(SOIL,INPUT);
    pinMode(RAIN,INPUT);

    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    firebaseconnect();
}
void firebaseconnect(){
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    Firebase.reconnectNetwork(true);
    fbdo.setBSSLBufferSize(4096, 1024);
    fbdo.setResponseSize(2048);
    Firebase.begin(&config, &auth);
    Firebase.setDoubleDigits(5);
    config.timeout.serverResponse = 10;
}

void RF(){
  int rain = digitalRead(RAIN);
  if(rain == 0){
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X4", 0);
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/Y1", 0);
  }
  else{
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X4", 1);
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/Y1", 1);
  }
}

void LIGHTAUTO(){
  int photpholight = digitalRead(LIGHT);
  if(photpholight == 1){
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X5", 1);
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/Y2", 1);
  }
  else{
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X5", 0);
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/Y2", 0);
  }
}

int led1, led2, led3, sv1;
void li1(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/farm/I/Y2")){
    String sValue = fbdo.stringData();
    led1 = sValue.toInt();
    if (led1 == 1){
      digitalWrite(LED1,HIGH);
    }else{
      digitalWrite(LED1,LOW);
    }
  }
}

void li2(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/farm/I/Y3")){
    String sValue = fbdo.stringData();
    led2 = sValue.toInt();
    if (led2 == 1){
      digitalWrite(L1,HIGH);
      delay(100);
      digitalWrite(L1,LOW);
      delay(100);
      digitalWrite(L2,HIGH);
      delay(100);
      digitalWrite(L2,LOW);
      delay(100);
      digitalWrite(L3,HIGH);
      delay(100);
      digitalWrite(L3,LOW);
      delay(100);
    }else{
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
    }
  }
}

void DOOR(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/farm/I/Y1")){
    String sValue = fbdo.stringData();
    sv1 = sValue.toInt();
    if (sv1 == 0){
      myservo.write(0);
    }
    else{
      myservo.write(180);
    }
  }
}

void thingspeak(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X1", humidity);
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X2", temperature);
  valueSOIL = analogRead(SOIL);
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/farm/I/X3", valueSOIL);

  if (client.connect(server,80)){    
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(temperature);
    postStr +="&field2=";
    postStr += String(humidity);
    postStr +="&field3=";
    postStr += String(valueSOIL);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    }
  client.stop();
}

void loop(){
  li1();
  li2();
  DOOR();
  LIGHTAUTO();
  RF();
  thingspeak();
}