// Potenciometro conectado 35
const int portPin = 35;
char inchar;

// Almacenamiento del valor de puerto (Rango de 0-4095)
int potValor = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

  potValor = analogRead(portPin);
  Serial.println(potValor);
  /* while (Serial.available()) {
     inchar = Serial.read();

     // Lectura del valor en cada vuelta del bucle
     if (inchar == '2') {
       potValor = analogRead(portPin);
       Serial.println(potValor);  //Envío del valor al puerto serie
     }
    }*/
}
