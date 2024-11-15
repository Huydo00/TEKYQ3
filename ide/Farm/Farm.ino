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

#define LED1 16
#define DHT_SENSOR_PIN 2
#define DHT_SENSOR_TYPE DHT11
DHT dht(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

uint16_t flameSensor;
uint8_t humidity;
uint8_t temperature;
int humd;

// Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

void setup()
{
    dht.begin();
    pinMode(LED1,OUTPUT);
    
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

void loop()
{
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    Firebase.RTDB.setInt(&fbdo, "/TEKYQ3/smh/temp", 0);

    if(Firebase.RTDB.getString(&fbdo, "/TEKYQ3/smh/humd")){
      String sValue = fbdo.stringData();
      humd = sValue.toInt();
      if (humd == 1){
        digitalWrite(LED1,HIGH);
      }else{
        digitalWrite(LED1,LOW);
      }
    }
    delay(2000);
}