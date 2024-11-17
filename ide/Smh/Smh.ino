#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"
#include <Servo.h>     

/* 1. Define the WiFi credentials */
// #define WIFI_SSID "Huy Do"
// #define WIFI_PASSWORD "0938360303"
#define WIFI_SSID "TEKY OFFICE"
#define WIFI_PASSWORD "Teky@2018"

/* 2. Define the API Key */
#define API_KEY "AIzaSyAn0rRvInY8z2XsOMulwNpv9ckU-OKB2CY"

/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "hhuys0105@gmail.com"
#define USER_PASSWORD "12345678"

/* 4. Define the RTDB URL */
#define DATABASE_URL "smh-iot-2e746-default-rtdb.firebaseio.com/" 

/***********************DEVICE***********************/
#define LED1 4     //D2
#define LED2 0     //D3
#define SVDOOR 2   //D4
#define LED3 14    //D5
#define BUZZER 12    //D6
#define MORTOR1 13 //D7
#define MORTOR2 15 //D8
/***********************SENSOR***********************/ 
#define MQ A0        //A0        //MQ2
#define IRSENSOR 16  //D0        //IR SENSOR
#define DHT_SENSOR_PIN 5  //D1  //DHT11
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
Servo myservo;
/***********************VARIABLE***********************/
uint16_t flameSensor;
float humidity;
float temperature;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup()
{
    // Y
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
    pinMode(BUZZER,OUTPUT);
    pinMode(MORTOR1,OUTPUT);
    pinMode(MORTOR2,OUTPUT);
    myservo.attach(SVDOOR);
    // X
    dht.begin();
    pinMode(MQ,INPUT);
    pinMode(IRSENSOR,INPUT);

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

void dht11(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/I/X1", humidity);
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/I/X2", temperature);

}
void MQ2(){
  int MQ = analogRead(MQ);
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/I/X3", MQ);
}

int sv1; 
int pos = 0;
void DOOR(){
  int Ir = digitalRead(IRSENSOR);
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/I/X4", Ir);
  if(Ir == 0){
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/O/Y1", 1);
    myservo.write(0);
    delay(2000);
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/O/Y1", 0);
    myservo.write(180);
    delay(2000);
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/I/X4", 1);
  }
  else if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/Y1")){
    String sValue = fbdo.stringData();
    sv1 = sValue.toInt();
    if (sv1 == 1){
      myservo.write(0);
    }
    else{
      myservo.write(180);
    }
  }
}

int led1, led2, led3;
void li1(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/Y2")){
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
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/Y4")){
    String sValue = fbdo.stringData();
    led2 = sValue.toInt();
    if (led2 == 1){
      digitalWrite(LED2,HIGH);
    }else{
      digitalWrite(LED2,LOW);
    }
  }
}
void li3(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/Y6")){
    String sValue = fbdo.stringData();
    led3 = sValue.toInt();
    if (led3 == 1){
      digitalWrite(LED3,HIGH);
    }else{
      digitalWrite(LED3,LOW);
    }
  }
}

int b1;
void buzz(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/I/X3")){
    String sValue = fbdo.stringData();
    b1 = sValue.toInt();
    if (b1 >= 700){
      Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/O/Y7", 1);
      digitalWrite(BUZZER,HIGH);
    }else{
      Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/O/Y7", 0);
      digitalWrite(BUZZER,LOW);
    }
  }
}

int m1,m2;
void motor(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/Y3")){
    String sValue = fbdo.stringData();
    m1 = sValue.toInt();
    if (m1 == 1){
      digitalWrite(MORTOR1,HIGH);
    }else{
      digitalWrite(MORTOR1,LOW);
    }
  }
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/Y5")){
    String sValue = fbdo.stringData();
    m2 = sValue.toInt();
    if (m2 == 1){
      digitalWrite(MORTOR2,HIGH);
    }else{
      digitalWrite(MORTOR2,LOW);
    }
  }
}

void loop(){
  dht11();
  MQ2();
  li1();
  li2();
  li3();
  DOOR();
  motor();
  buzz();
  // delay(10);
}