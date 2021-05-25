//for RTC
#include "Wire.h"
#include "RTC.h"

//for WiFi
#include <WiFi.h>
#include <WiFiUdp.h>

// WiFi network nombre y contraseña
const char* ssid = "GONZALO";
const char* password = "84016940";

// puerto local a la escucha
unsigned int localPort_ = 5050;

WiFiUDP udp;

byte datos [3];
RTC rtc = RTC(50, 58, 11, 1, 20, 4, 21); // set RTC

void setup() {
  Serial.begin(115200);
  conectarWifi();
}

void loop() {
  enviarDatos();
  recibirDatos();
}

void conectarWifi() {
  // inicializa la conexion
  WiFi.begin(ssid, password);

/*  Serial.println("Conectando al WiFi network: " + String(ssid));
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
  if (rtc.isWorking()) {
    rtc.displayTime(); // display the real-time clock data on the Serial Monitor
    datos [0] = rtc.second;
    datos [1] = rtc.minute;
    datos [2] = rtc.hour;
  }
  // enviar datos a la dirección IP y el puerto del PC
  udp.beginPacket("192.168.1.103", 30);
  udp.write(datos, 3);
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
