#define LED_PIN = 4;

void setup()
{
  Serial.begin(115200);
  Serial.println("BEGIN");
  pinMode(LED_PIN, OUTPUT);
}

void loop()
{
  Serial.println("Blink");
  digitalWrite(LED_PIN, HIGH);
  delay(800);
  digitalWrite(LED_PIN, LOW);
  delay(200);
}
