#include <SPI.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5
#define SEALEVELPRESSURE_HPA (1013.25)

// hardware SPI
Adafruit_BME280 bme(BME_CS);

// WiFi network nombre y contraseña
const char* ssid = "GONZALO";
const char* password = "84016940";

// puerto local a la escucha
unsigned int localPort_ = 3030;

WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  conectarWifi();

  //bme setup
  unsigned status;
  status = bme.begin();
}

void loop() {
  enviarDatos();
  recibirDatos();
}

void conectarWifi() {
  // inicializa la conexion
  WiFi.begin(ssid, password);

  /*Serial.println("Conectando al WiFi network: " + String(ssid));
  // intenta conectar a una red Wifi:
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());*/

  // si hay una conexion, informar por el puerto serie:
  udp.begin(localPort_);
}

void enviarDatos() {

  // convertir valores de float a binario
  float valueHum = bme.readHumidity();
  static uint8_t arr[4] = {0};
  memcpy(arr, (uint8_t *)&valueHum, 4);

  // enviar datos a la dirección IP y el puerto del PC
  udp.beginPacket("192.168.1.103", 29);
  udp.write(arr, 4);
  udp.endPacket();
  delay(1000);

}
void recibirDatos() {
  // si hay datos disponibles, leer un paquete
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // lee un paquete de packetBufffer
    char pBuffer [255];
    int len = udp.read(pBuffer, 255);
    if (len > 0) pBuffer[len] = 0;
  }
}
