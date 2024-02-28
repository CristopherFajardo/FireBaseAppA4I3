#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

int ledp1=23, ledp2=22, ledp3=21;

//Conectar a una red WiFi 
const char* WIFI_SSID = "Si a de ser";//el nombre de la red
const char* WIFI_PASSWORD = "si a de ser o tal vez";//la contraseña de la red
//Recursos de Firebase
const char* API_KEY = "AIzaSyAq1kk7Ag0BUNHxDsgjSEiP3Rf_8A_fFEg";
const char* FIREBASE_PROJECT_ID = "movil-fire";
//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION de Firebase
const char* USER_EMAIL = "esp32fajardo@gmail.com";
const char* USER_PASSWORD = "ESP32Fajardo.@";

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  // put your setup code here, to run once:
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}
void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}
void setup() {
  pinMode(ledp1,OUTPUT);
  pinMode(ledp2,OUTPUT);
  pinMode(ledp3,OUTPUT);
  
  digitalWrite(ledp1,LOW);
  digitalWrite(ledp2,LOW);
  digitalWrite(ledp3,LOW);

  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);//Verificamos la version
  setupWiFi();//Llamamos la funcion de configuración wifi
  setupFirebase();//Llamamos la funcion de configuración Firebase
}

void loop(){
String path = "controlLED";//RUTA DE COLECCION
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE
     //   Serial.print(document);
        const bool state = document["fields"]["encender"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
     //   Serial.println(" : ");
        if (strstr(document_name, "LED1") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          digitalWrite(ledp1, state);
          state ? Serial.print("Control 1 On") : Serial.println("Control 1 OFF");
        }
        if (strstr(document_name, "LED2") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          digitalWrite(ledp2, state);
          state ? Serial.print("Control 2 On") : Serial.println("Control 2 OFF");
        }
        if (strstr(document_name, "LED3") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          digitalWrite(ledp3, state);
          state ? Serial.print("Control 3 On") : Serial.println("Control 3 OFF");
        }
      }
    }
	}
}