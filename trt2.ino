#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include <esp_system.h>
#include <esp_task_wdt.h>
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"
#define WDT_TIMEOUT 0.1

#define WIFI_SSID "MAGGY_2.4G"
#define WIFI_PASSWORD "0844331856"


#define API_KEY "AIzaSyB0Elhnm0EVUXn7BnmLVf_cOf0_aStTd08"


#define DATABASE_URL "ec-and-firebase-default-rtdb.asia-southeast1.firebasedatabase.app" 


#define pumpPinD8 19
#define pumpPinD7 18 
#define pumpPinD6 5
#define pumpPinD5 17
#define pumpPinD4 16
#define pumpPinD3 4
#define pumpPinD2 15
#define pumpPinD14 25
#define pumpPinD15 26


bool modeStatus = false;
bool pumpStatusD8 = false;
bool pumpStatusD7 = false;
bool pumpStatusD6 = false;
bool pumpStatusD5 = false;
bool pumpStatusD4 = false;
bool pumpStatusD3 = false;
bool pumpStatusD2 = false;
bool pumpStatusD14 = false;
bool pumpStatusD15 = false;

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void setup(){
  Serial.begin(115200);
  
  esp_task_wdt_config_t wdt_config = {
  .timeout_ms = WDT_TIMEOUT*1000,
  .idle_core_mask = 0,
  .trigger_panic = true      
  };

  
  esp_task_wdt_init(&wdt_config);
  esp_task_wdt_add(NULL);

  pinMode(pumpPinD8, OUTPUT);
  pinMode(pumpPinD7, OUTPUT);
  pinMode(pumpPinD6, OUTPUT); 
  pinMode(pumpPinD5, OUTPUT);
  pinMode(pumpPinD4, OUTPUT);
  pinMode(pumpPinD3, OUTPUT); 
  pinMode(pumpPinD2, OUTPUT);
  pinMode(pumpPinD14, OUTPUT);
  pinMode(pumpPinD15, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;


  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){

    if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    
    sendDataPrevMillis = millis();
    esp_task_wdt_reset();
    if (Firebase.RTDB.getBool(&fbdo,"Pump/Status"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD2 = fbdo.boolData();
        Serial.print(fbdo.dataPath()+":"+ pumpStatusD2+" ");
        digitalWrite(pumpPinD2,pumpStatusD2);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status1"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD3 = fbdo.boolData();
        Serial.print(fbdo.dataPath()+":"+pumpStatusD3+" ");
        digitalWrite(pumpPinD3,pumpStatusD3);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status2"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD4 = fbdo.boolData();
        Serial.print(fbdo.dataPath()+":"+pumpStatusD4+" ");
        digitalWrite(pumpPinD4,pumpStatusD4);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status3"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD5 = fbdo.boolData();
        Serial.print(fbdo.dataPath()+":"+  pumpStatusD5 +" " );
        digitalWrite(pumpPinD5,pumpStatusD5);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }
            
    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status4"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD6 = fbdo.boolData();
        Serial.print(fbdo.dataPath() + ":"+  pumpStatusD6 + " " );
        digitalWrite(pumpPinD6,pumpStatusD6);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status5"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD7 = fbdo.boolData();
        Serial.print(fbdo.dataPath() + ":"+  pumpStatusD7 + " " );
        digitalWrite(pumpPinD7,pumpStatusD7);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status6"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD8 = fbdo.boolData();
        Serial.print(fbdo.dataPath() + ":"+  pumpStatusD8 + " " );
        digitalWrite(pumpPinD8,pumpStatusD8);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status7"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD14 = fbdo.boolData();
        Serial.print(fbdo.dataPath() + ":"+  pumpStatusD14 + " " );
        digitalWrite(pumpPinD14,pumpStatusD14);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }

    if(Firebase.RTDB.getBool(&fbdo,"Pump/Status8"))
    {
      if( fbdo.dataType() == "boolean")
      {
        pumpStatusD15 = fbdo.boolData();
        Serial.println(fbdo.dataPath() + ":"+  pumpStatusD15 + " " );
        digitalWrite(pumpPinD15,pumpStatusD15);
      }
    }else
      {
        Serial.print("FAILED : " + fbdo.errorReason());
      }
    }
}
