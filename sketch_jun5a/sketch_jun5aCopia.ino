// Constants (Change the following variables if needed)
const int anemometerPin = 34;  // analog pin 0 (A0)
const float minVoltage = 0.15;  // Voltage corresponding to 0 m/s
const float maxVoltage = 0.6;  // Voltage corresponding to 32.4 m/s (max speed)
const float maxWindSpeed = 32.4; // Maximum wind speed in m/s

// Conversion factors
const float mps_to_kmh = 3.6;   // 1 m/s = 3.6 km/h
const float mps_to_mph = 2.23694; // 1 m/s = 2.23694 mph

void setup() {
  Serial.begin(9600);  
}

void loop() {
  // Read analog value from anemometer (ADC value between 0-1023 on Arduino for 0-5V)
  int adcValue = analogRead(anemometerPin);
  
  // Convert ADC value to voltage (Arduino ADC range is 0-5.0V)
  float voltage = (adcValue / 4095.00) * 3.3;
  
  // Ensure the voltage is within the anemometer operating range
  if (voltage < minVoltage) {
    voltage = minVoltage;
  } else if (voltage > maxVoltage) {
    // voltage = maxVoltage;
  }
  
  // Map the voltage to wind speed
  float windSpeed_mps = ((voltage - minVoltage) / (maxVoltage - minVoltage)) * maxWindSpeed;

  // Convert wind speed to km/h and mph
  float windSpeed_kmh = windSpeed_mps * mps_to_kmh;
  float windSpeed_mph = windSpeed_mps * mps_to_mph;

  // Print wind speed
  Serial.print("tensão: ");
  Serial.print(voltage);
  Serial.print(" Pino: ");
  Serial.print(adcValue);
  Serial.print(" Wind Speed: ");
  Serial.print(windSpeed_mps);
  Serial.print(" m/s, ");
  Serial.print(windSpeed_kmh);
  Serial.print(" km/h, ");
  Serial.print(windSpeed_mph);
  Serial.println(" mph");
  
  delay(1000); 
}