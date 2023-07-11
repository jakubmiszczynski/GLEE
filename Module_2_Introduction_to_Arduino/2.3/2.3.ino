int LED1 = 4;
int LED2 = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("Start serial");
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 30; i = i+2) {
    Serial.print(i);
    Serial.println(" Sheep");
    digitalWrite(LED1, HIGH);
    Serial.println("LED on");
    delay(2000);
  }
  digitalWrite(LED1, LOW);
  Serial.println("LED off");
  delay(10);
}
