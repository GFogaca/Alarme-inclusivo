#include <WiFiManager.h> 
// #include <Arduino.h>
// #include <ESP8266WebServer.h>

#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define wifiConnectedLed 5
#define motor 4

WiFiManager wm;
ESP8266WebServer server(80); 

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


int alarmHour = -1;
int alarmMinute = -1;

void setAlarm(int hour, int minute) {
  alarmHour = hour;
  alarmMinute = minute;
  Serial.print(alarmHour);
  Serial.print(":");
  Serial.print(alarmMinute);
}

void ligar() {
  digitalWrite(motor, HIGH);
  Serial.println("Alarme acionado!");
}

void handleRoot() {

  String html = "<html><body>";
  html += "<h1>Acesso bem-sucedido</h1>";
  html += "<p>Endereço IP do ESP8266: " + WiFi.localIP().toString() + "</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleComando() {
  // POST command
  if (server.hasArg("comando")) {
    String comando = server.arg("comando");
    Serial.println("Comando inciado...");
    if (comando == "ligar") {
      digitalWrite(motor, HIGH); 
      server.send(200, "text/plain", "Comando de ligar recebido");
      Serial.println("Comando de ligar recebido");
    } else if (comando == "desligar") {
      digitalWrite(motor, LOW); 
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


void handleConfigurarAlarme() {
  Serial.print(server.hasArg("hora"));
  Serial.print(server.hasArg("minuto"));
  if (server.hasArg("hora") && server.hasArg("minuto")) {
    int hora = server.arg("hora").toInt();
    int minuto = server.arg("minuto").toInt();
    setAlarm(hora, minuto);
    server.send(200, "text/plain", "Alarme configurado");
    Serial.println("Alarme configurado para " + String(hora) + ":" + String(minuto));
  } else {
    server.send(400, "text/plain", "Parâmetros inválidos");
    Serial.println("Parâmetros inválidos");
  }
}

void setup() {
    WiFi.mode(WIFI_STA);   
    Serial.begin(115200);

    // pin to see if its connect into the network
    pinMode(wifiConnectedLed, OUTPUT);
    // pin to make vibrate 
    pinMode(motor, OUTPUT);
    // set wifi led low 
    digitalWrite(wifiConnectedLed, LOW);
    // make test in motor turning on and off  
    digitalWrite(motor, HIGH);
    delay(1000);
    digitalWrite(motor, LOW);

    // ************ ONLY FOR TEST ********************* //
    //reset settings - wipe credentials for testing
    wm.resetSettings();
    // ************************************************//

    IPAddress staticIP(192, 168, 15, 100);
    IPAddress gateway(192, 168, 15, 1);
    IPAddress subnet(255, 255, 255, 0);
    IPAddress dns(8, 8, 8, 8);

    WiFi.config(staticIP, gateway, subnet, dns);


    // set time in seconds to close window
    wm.setConfigPortalTimeout(300);
    
    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name
    if(wm.autoConnect("Alarme","alarme123")){
        Serial.println("conectado!! :)");
        Serial.println("Inicio do projeto conectado");
        Serial.print("Local IP: ");
        Serial.println(WiFi.localIP());

        Serial.print("Status da Conexão: ");
        Serial.println(WiFi.status());


        digitalWrite(wifiConnectedLed, HIGH);

        // Configuração do servidor da Web
        // Manipulador de rota para a raiz
        server.on("/", HTTP_GET, handleRoot);
        server.on("/comando", HTTP_POST, handleComando);
        server.on("/configurar-alarme", HTTP_POST, handleConfigurarAlarme);
        server.begin();  // Inicia o servidor web

        // Inicia o cliente NTP
        timeClient.begin();
        // Configura o fuso horário para Brasília (UTC-3)
        timeClient.setTimeOffset(-3 * 60 * 60);

      }
    else {
        Serial.println("Configportal running");
    }
    

}

void loop() {

  server.handleClient();

  timeClient.update();

if (alarmHour >= 0 && alarmMinute >= 0) {
    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();
    if (currentHour == alarmHour && currentMinute == alarmMinute) {
      ligar();
      // Reinicializa o alarme após ser acionado
      alarmHour = -1;
      alarmMinute = -1;
    }
  }

}






