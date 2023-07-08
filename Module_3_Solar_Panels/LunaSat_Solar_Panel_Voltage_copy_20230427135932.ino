
void setup() {
  Serial.begin(9600);
}


void loop() {
  int solarCellReading = analogRead(A1);
  float voltage = solarCellReading * (3.3 / 1023.0);
  
  Serial.println(voltage, 5);
  delay(100);
}
