#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "DHT.h"

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Huy Do"
#define WIFI_PASSWORD "0938360303"

/* 2. Define the API Key */
#define API_KEY "AIzaSyAn0rRvInY8z2XsOMulwNpv9ckU-OKB2CY"

/* 3. Define the user Email and password that alreadey registerd or added in your project */
#define USER_EMAIL "hhuys0105@gmail.com"
#define USER_PASSWORD "12345678"

/* 4. Define the RTDB URL */
#define DATABASE_URL "smh-iot-2e746-default-rtdb.firebaseio.com/" 

/***********************DEVICE***********************/
#define LED1 4   //D2
#define LED2 0   //D3
#define LED3 2   //D4
#define LED4 14   //D5
#define MORTOR1 12 //D6
#define MORTOR2 13 //D7
#define SVDOOR 15   //D8
/***********************SENSOR***********************/ 
#define MQ A0        //A0        //MQ2
#define IRSENSOR 16  //D0        //IR SENSOR
#define DHT_SENSOR_PIN 5  //D1  //DHT11
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

/***********************VARIABLE***********************/
uint16_t flameSensor;
uint8_t humidity;
uint8_t temperature;
int humd;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup()
{
    dht.begin();
    pinMode(LED1,OUTPUT);
    pinMode(LED2,OUTPUT);
    pinMode(LED3,OUTPUT);
    
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
    /* Assign the api key (required) */
    config.api_key = API_KEY;
    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    /* Assign the RTDB URL (required) */
    config.database_url = DATABASE_URL;
    // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
    Firebase.reconnectNetwork(true);
    // Since v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
    // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
    fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);
    // Limit the size of response payload to be collected in FirebaseData
    fbdo.setResponseSize(2048);
    Firebase.begin(&config, &auth);
    Firebase.setDoubleDigits(5);
    config.timeout.serverResponse = 10 * 1000;
}

void dht11(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/temp", 0);

}
void MQ2(){
  
}
int led1, led2, led3, led4;
void led(){
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/LED1")){
    String sValue = fbdo.stringData();
    led1 = sValue.toInt();
    if (led1 == 1){
      digitalWrite(LED1,HIGH);
    }else{
      digitalWrite(LED1,LOW);
    }
  }
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/LED2")){
    String sValue = fbdo.stringData();
    led2 = sValue.toInt();
    if (led2 == 1){
      digitalWrite(LED2,HIGH);
    }else{
      digitalWrite(LED2,LOW);
    }
  }
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/LED3")){
    String sValue = fbdo.stringData();
    led3 = sValue.toInt();
    if (led3 == 1){
      digitalWrite(LED3,HIGH);
    }else{
      digitalWrite(LED3,LOW);
    }
  }
  if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/O/LED4")){
    String sValue = fbdo.stringData();
    led4 = sValue.toInt();
    if (led4 == 1){
      digitalWrite(LED4,HIGH);
    }else{
      digitalWrite(LED4,LOW);
    }
  }
  
}
void motor(){
  
}

void loop(){
  dht11();
  MQ2();
  led();
  motor();
  delay(100);
}