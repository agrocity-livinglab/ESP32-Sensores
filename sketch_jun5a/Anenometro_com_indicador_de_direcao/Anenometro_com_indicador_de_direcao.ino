// Pin definitions
# define Hall sensor 4         //  Pino digital 2
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
// Constants definitions
const char* ssid= "redeADAMovel";
const char* password="adatec40";
const char* serverUrl = "http://192.168.64.183/devices/inputdatadevices/1";  
int pin=34;
float valor =0;
int Winddir =0;
String direcao;

const float pi = 3.14159265;           // Numero pi
int period = 5000;               // Tempo de medida(miliseconds)
int delaytime = 2000;             // Time between samples (miliseconds)
int radius = 147;      // Raio do anemometro(mm)

// Variable definitions
unsigned int Sample = 0;   // Sample number
unsigned int counter = 0; // magnet counter for sensor
unsigned int RPM = 0;          // Revolutions per minute
float speedwind = 0;         // Wind speed (m/s)
float windspeed = 0;           // Wind speed (km/h)

void setup()
{
  // Set the pins
  pinMode(4, INPUT);
  digitalWrite(4, HIGH);     //internall pull-up active
    
  //Start serial 
  Serial.begin(115200);       // sets the serial port to 9600 baud
  
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");


  // Dados JSON que vamos enviar
  //StaticJsonDocument<200> doc;
  //doc["sensor"] = "umidade";
  //doc["valor"] = 62.5;

  //String jsonString;
  //serializeJson(doc, jsonString);

  // Envio POST
  //HTTPClient http;
  //http.begin(serverUrl);
  //http.addHeader("Content-Type", "application/json");
  
  //int httpResponseCode = http.POST(jsonString);

  //Serial.print("Código de resposta: ");
  //Serial.println(httpResponseCode);

  //if (httpResponseCode > 0) {
    //String response = http.getString();
    //Serial.println("Resposta:");
    //Serial.println(response);
  //}

  //http.end();
}

 
void loop()
{
  // Anemômetro
  Sample++;
  Serial.print(Sample);
  Serial.print(": Iniciar medição...");
  windvelocity();
  Serial.println("   finalizada.");
  Serial.print("Counter: ");
  Serial.print(counter);
  Serial.print(";  RPM: ");
  RPMcalc();
  Serial.print(RPM);
  Serial.print(";  Wind speed: ");
  
//*****************************************************************
//print m/s  
  WindSpeed();
  Serial.print(windspeed);
  Serial.print(" [m/s] ");              
  
//*****************************************************************
//print km/h  
  SpeedWind();
  Serial.print(speedwind);
  Serial.print(" [km/h] ");  
  Serial.println();
  counter = 0;  

  StaticJsonDocument<300> innerDoc;
  innerDoc["date_time"] = "2025-06-20T16:00:00"; // substitua por data dinâmica se quiser
  innerDoc["status"] = 1;
  innerDoc["data_type"] = "wind";
  innerDoc["wind_speed_kmh"] = speedwind;
  innerDoc["wind_direction_deg"] = Winddir;
  innerDoc["wind_direction"] = direcao;

  String innerJson;
  serializeJson(innerDoc, innerJson);

  // --- Criar JSON externo com payload ---
  StaticJsonDocument<400> outerDoc;
  outerDoc["payload"] = innerJson;

  String postData;
  serializeJson(outerDoc, postData);

  // --- Enviar via POST para o servidor ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(postData);
    Serial.print("Código de resposta: ");
    Serial.println(httpCode);

    if (httpCode > 0) {
      String response = http.getString();
      Serial.println("Resposta do servidor:");
      Serial.println(response);
    } else {
      Serial.println("Falha no envio HTTP POST");
    }

    http.end();
  } else {
    Serial.println("WiFi desconectado.");
  } 

  delay(delaytime);                        //delay between prints

// Indicador de Direção do Vento
valor = analogRead(pin)* (3.3 / 4095.00);
 
Serial.print("leitura do sensor :");
Serial.print(valor);
Serial.println(" volt");

if (valor <= 0.11) {
Winddir = 315;
direcao = "Leste";
}
else if (valor <= 0.22) { 
Winddir = 270;
direcao = "Sul";
}
else if (valor <= 0.45) { 
Winddir = 225;
direcao = "Oeste";
}
else if (valor <= 0.98) { 
Winddir = 180;
direcao = "Norte";
}
/*else if (valor <= 0.57) { 
Winddir = 135;
direcao = "Sudeste";
}
else if (valor <= 0.75) { 
Winddir = 90;
direcao = "Leste";
}
else if (valor <= 1.25) {  
Winddir = 45;
direcao = "Nordeste";
}*/
else {  
Winddir = 000;
direcao = "Norte";
}
 Serial.print("Direção a :");
 Serial.print(Winddir);
 Serial.print(" graus");
 Serial.print(" / ");
 Serial.print(direcao);
 Serial.println("\n");
//  delay (1000);
}


// Measure wind speed
void windvelocity(){
  speedwind = 0;
  windspeed = 0;
  
  attachInterrupt(4, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {
  }
}


void RPMcalc(){
  RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
}

void WindSpeed(){
  windspeed = ((4 * pi * radius * RPM)/60) / 1000;  // Calculate wind speed on m/s
}

void SpeedWind(){
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  // Calculate wind speed on km/h
}

void addcount(){
  counter++;
} 
