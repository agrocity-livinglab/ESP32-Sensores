int pulseCount = 0;
unsigned long previousMillis = 0;
const int anemometerPin = 2;

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  pinMode(anemometerPin, INPUT_PULLDOWN); // se o ESP32 suportar esse modo
  attachInterrupt(digitalPinToInterrupt(anemometerPin), countPulse, FALLING);  
  
}

void loop() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= 1000) {
    detachInterrupt(digitalPinToInterrupt(anemometerPin));
    
    // 1 segundo passou: imprime número de pulsos
    Serial.print("Pulsos por segundo: ");
    Serial.println(pulseCount);
    
    
    // Reinicia contagem
    pulseCount = 0;
    previousMillis = currentMillis;
    
    attachInterrupt(digitalPinToInterrupt(anemometerPin), countPulse, FALLING);
  }
}
