//Autor: Fábio Henrique Cabrini
//Resumo: Esse programa possibilita ligar e desligar o led onboard, além de mandar o status para o Broker MQTT.
//        Também publica coordenadas do GPS usando TinyGPS++.
//Revisões:
//Rev1: 26-08-2023 Código portado para o ESP32 para leitura de luminosidade
//Rev2: 28-08-2023 Ajustes para funcionamento no FIWARE Descomplicado
//Rev3: 01-11-2023 Refinamento do código
//Rev4: 15-09-2025 Ajustes de GPS e boas práticas (por Daniel + GPT)

#include <WiFi.h>
#include <PubSubClient.h>
#include <TinyGPS++.h>

#define GPS_BAUDRATE 9600
#define RXD2 16
#define TXD2 17

// Configurações - variáveis editáveis
const char* default_SSID = "Wokwi-GUEST";
const char* default_PASSWORD = "";
const char* default_BROKER_MQTT = "20.81.234.239";
const int default_BROKER_PORT = 1883;
const char* default_TOPICO_SUBSCRIBE = "/TEF/lamp001/cmd";
const char* default_TOPICO_PUBLISH_1 = "/TEF/lamp001/attrs";
const char* default_TOPICO_PUBLISH_2 = "/TEF/lamp001/attrs/x";
const char* default_ID_MQTT = "fiware_001";
const int default_D4 = 2; // LED onboard do ESP32

// Variáveis editáveis
char* SSID = const_cast<char*>(default_SSID);
char* PASSWORD = const_cast<char*>(default_PASSWORD);
char* BROKER_MQTT = const_cast<char*>(default_BROKER_MQTT);
int BROKER_PORT = default_BROKER_PORT;
char* TOPICO_SUBSCRIBE = const_cast<char*>(default_TOPICO_SUBSCRIBE);
char* TOPICO_PUBLISH_1 = const_cast<char*>(default_TOPICO_PUBLISH_1);
char* TOPICO_PUBLISH_2 = const_cast<char*>(default_TOPICO_PUBLISH_2);
char* ID_MQTT = const_cast<char*>(default_ID_MQTT);
int D4 = default_D4;

WiFiClient espClient;
PubSubClient MQTT(espClient);
TinyGPSPlus gps;

char EstadoSaida = '0';
const char* topicPrefix = "lamp001";

// ===== FUNÇÕES =====
void reconectWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  digitalWrite(D4, LOW); // LED inicia apagado
}

void initWiFi() {
  Serial.println("Conectando ao Wi-Fi...");
  reconectWiFi();
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) msg += (char)payload[i];

  Serial.print("Mensagem recebida: ");
  Serial.println(msg);

  String onTopic = String(topicPrefix) + "@on|";
  String offTopic = String(topicPrefix) + "@off|";

  if (msg.equals(onTopic)) {
    digitalWrite(D4, HIGH);
    EstadoSaida = '1';
  } else if (msg.equals(offTopic)) {
    digitalWrite(D4, LOW);
    EstadoSaida = '0';
  }
}

void reconnectMQTT() {
  while (!MQTT.connected()) {
    Serial.print("Tentando se conectar ao Broker MQTT: ");
    Serial.println(BROKER_MQTT);

    if (MQTT.connect(ID_MQTT)) {
      Serial.println("Conectado ao broker MQTT!");
      MQTT.subscribe(TOPICO_SUBSCRIBE);
    } else {
      Serial.println("Falha na conexão. Tentando novamente em 2s...");
      delay(2000);
    }
  }
}

void VerificaConexoesWiFIEMQTT() {
  if (!MQTT.connected()) reconnectMQTT();
  reconectWiFi();
}

void EnviaEstadoOutputMQTT() {
  if (EstadoSaida == '1') {
    MQTT.publish(TOPICO_PUBLISH_1, "s|on");
    Serial.println("LED Ligado");
  } else {
    MQTT.publish(TOPICO_PUBLISH_1, "s|off");
    Serial.println("LED Desligado");
  }
}

void handleGPS() {
  // Processa os dados recebidos pela Serial2
  while (Serial2.available() > 0) {
    gps.encode(Serial2.read());
  }

  String texto_gps;

  if (gps.location.isValid()) {
    String lat_texto = String(gps.location.lat(), 6);
    String lng_texto = String(gps.location.lng(), 6);
    texto_gps = lat_texto + " " + lng_texto;

    Serial.print("Latitude: ");
    Serial.println(lat_texto);
    Serial.print("Longitude: ");
    Serial.println(lng_texto);

  } else {
    Serial.println("Location: INVALID");
    texto_gps = "INVALID";
  }

  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: check wiring");
  }

  MQTT.publish(TOPICO_PUBLISH_2, texto_gps.c_str());
}

// ===== SETUP =====
void setup() {
  Serial.begin(9600);
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, RXD2, TXD2);

  pinMode(D4, OUTPUT);

  initWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);

  delay(2000);
  MQTT.publish(TOPICO_PUBLISH_1, "s|on"); // status inicial
}

// ===== LOOP =====
void loop() {
  VerificaConexoesWiFIEMQTT();
  MQTT.loop();

  EnviaEstadoOutputMQTT();
  handleGPS();

  delay(1000); // publica a cada 1s
}
