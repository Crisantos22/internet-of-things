#include <Wifi.h>
#include <WebServer.h>

const char* ssid= "ALUMNOS_TEC";
const char* password= "";

//Inicializar Server
WebServer server(80);
const int ledPin = 14;

void handleRoot(){
  String html = " <h1> Controlar LED </h1>";
  html += "<p><a href=\"/on\"><button> ON </button></a></p> ";
  html += "<p><a href=\"/off\"><button> OFF </button></a></p> ";
  server.send(200, "text/html",html);
  }

void handleOn(){
  digitalWrite(ledPin, HIGH),
  server.send(200, "text/html", "LED ENCENDIDO <br> <a href=\"/\"> VOLVER</a>");
}

void handleOff(){
  digitalWrite(ledPin, HIGH),
  server.send(200, "text/html", "LED APAGADO <br> <a href=\"/\"> VOLVER</a>");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  Serial.begin(115200);
  delay(400);
  Wifi.begin(ssid, password);

  Serial.print("CONECTANDO A WI-FI....");

  while(Wifi.status() !=WI_CONNECTED){
    delay(500);
    Serial.print("*");
  }
  Serial.println("\nCONECTADO");
  Serial.println("\nIP DEL SERVIDOR: ");
  Serial.println(Wifi.localIP());

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  
}
