const int switchPin = 3;
byte a = 65; //Para imprimir A con strings en UE4
byte b = 66; //Para imprimir B con strings en UE4

byte c = 49; //Para imprimir 1 con strings en UE4
byte d = 50; //Para imprimir 2 con strings en UE4

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {  // If switch is ON,
    Serial.write(c);
    //Serial.write("\n");

  } else {
    Serial.write(d);  // If the switch is not OFF,
    //Serial.write("\n");
  }
  delay(100);
}
