#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <Arduino.h>
// #include "ESPAsyncWebServer.h"
#include <ESP8266WebServer.h>
#define wifiConnectedLed 5
#define LED_BUILTIN 4

WiFiManager wm;
ESP8266WebServer server(80);  // Crie um servidor web na porta 80

void handleRoot() {

  String html = "<html><body>";
  html += "<h1>Acesso bem-sucedido</h1>";
  html += "<p>Endereço IP do ESP8266: " + WiFi.localIP().toString() + "</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleComando() {
  // Lida com o comando POST recebido
  if (server.hasArg("comando")) {
    String comando = server.arg("comando");
    Serial.println("Comando inciado...");
    if (comando == "ligar") {
      digitalWrite(LED_BUILTIN, HIGH); // Ligar um LED (opcional)
      server.send(200, "text/plain", "Comando de ligar recebido");
      Serial.println("Comando de ligar recebido");
    } else if (comando == "desligar") {
      digitalWrite(LED_BUILTIN, LOW); // Desligar o LED (opcional)
      server.send(200, "text/plain", "Comando de desligar recebido");
      Serial.println("Comando de desligar recebido");
    } else {
      server.send(400, "text/plain", "Comando inválido");
      Serial.println("Comando inválido");
    }
  } else {
    server.send(400, "text/plain", "Comando ausente");
    Serial.println("Comando ausente");
  }
}


void setup() {
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    

    Serial.begin(115200);

    // pin to see if its connect into the network
    pinMode(wifiConnectedLed, OUTPUT);
    // pin to make vibrate 
    pinMode(LED_BUILTIN, OUTPUT);
    // set wifi led low 
    digitalWrite(wifiConnectedLed, LOW);
    // make test in motor turning on and off  
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);

    // ************ ONLY FOR TEST ********************* //
    //reset settings - wipe credentials for testing
    wm.resetSettings();
    // ************************************************//

    //set static ip:
    IPAddress _ip = IPAddress(192, 168, 15, 100);
    IPAddress _gw = IPAddress(192, 168, 15, 1);
    IPAddress _sn = IPAddress(255, 255, 255, 0);

    
    wm.setSTAStaticIPConfig(_ip, _gw, _sn);

    // wm.setConfigPortalBlocking(false);
    // set time in seconds to close window
    wm.setConfigPortalTimeout(300);
    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name
    if(wm.autoConnect("Alarme","alarme123")){
        Serial.println("conectado...yeey :)");
        Serial.println("Inicio do projeto conectado");
        Serial.print("Local IP: ");
        Serial.println(WiFi.localIP());

        digitalWrite(wifiConnectedLed, HIGH);

        // WiFiServer server(80);
        // server.begin();  // Starts the Server
                // Configuração de rota para a página de alarme
        // Configuração do servidor da Web
        // Manipulador de rota para a raiz

        server.on("/", HTTP_GET, handleRoot);
        server.on("/comando", HTTP_POST, handleComando);
        server.begin();  // Inicia o servidor web


        // // Configurar rota para lidar com comandos POST
        // server.on("/comando", HTTP_POST, handleComando);
        // server.begin();
        // Serial.println("Servidor HTTP iniciado");
    }
    else {
        Serial.println("Configportal running");
    }
}

void loop() {

  server.handleClient();  // Lida com solicitações de clientes web

}






