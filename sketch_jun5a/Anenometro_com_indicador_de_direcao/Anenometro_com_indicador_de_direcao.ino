	// Pin definitions
	# define Hall sensor 4         //  Pino digital 2
	#include <WiFi.h>
	#include <HTTPClient.h>
	#include <WiFiClientSecure.h>
	#include <ArduinoJson.h>
	// Constants definitions
	const char* ssid= "Agrocity_2.4G";
	const char* password="Livinglab2025!";
	const char* serverUrl = "https://test.adatecnologia.com/devices/inputdatadevices/1";  
	const char* test_root_ca= \
	"-----BEGIN CERTIFICATE-----\n" \
	"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\n " \
	"bP6MvPJwNQzcmRk13NfIRmPVNnGuV/u3gm3c\n " \
	"-----END CERTIFICATE-----\n ";
	WiFiClientSecure client;

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

	  Serial.println("\nStarting connection to server...");
	  
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
	  

	  WindSpeed();
	  Serial.print(windspeed);
	  Serial.print(" [m/s] ");              
	  
	 
	  SpeedWind();
	  Serial.print(speedwind);
	  Serial.print(" [km/h] ");  
	  Serial.println();
	  counter = 0;  

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
	  delay (20000);

    
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
		//client.setInsecure();
		http.begin(serverUrl);
		http.addHeader("Content-Type", "application/json");

		int httpCode = http.POST(postData);
		//int httpCode =http.GET();
		Serial.print("Código de resposta: ");
		Serial.println(httpCode);
		Serial.println(http.getString());  // conteúdo da resposta
		Serial.println(http.getLocation());

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

	}




