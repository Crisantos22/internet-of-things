#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ALUMNOS TEC";
const char* password = "";

WebServer server(80);

const int potPin = 34;

const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Potenciómetro</title>
    <style>
        body{
            font-family: sans-serif;
            text-align: center;
            margin: 50px;
        }
        h1{
            color: cornflowerblue;
        }
        #potValue{
            font-size: 24px;
            color: blue;
        }
    </style>
</head>
<body>
    <h1>Lectura del Potenciómetro</h1>
    <p>Valor Actual:</p>
    <p id="potValue">---</p>

    <script>
        function updatePot(){
            fetch('/pot')
            .then(response => response.text())
            .then(data => document.getElementById('potValue').innerText = data);
        }
        setInterval(updatePot, 1000);
    </script>
</body>
</html>
)rawliteral";

void handleRoot(){
  server.send(200, "text/html", htmlPage);
}

void handlePot(){
  int value = analogRead(potPin);
  server.send(200, "text/plain", String(value));
}

void setup() {
  Serial.begin(115200);
  delay(400);

  WiFi.begin(ssid, password);
  Serial.print("CONECTANDO A WIFI...");

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n¡CONECTADO!");
  Serial.println("IP DEL SERVIDOR:");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/pot", handlePot);
  server.begin();
}

void loop() {
  server.handleClient();
}