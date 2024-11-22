#include <DHT.h>

#define DHTPIN 2           // Pino onde o DHT22 está conectado
#define DHTTYPE DHT22      // Tipo do sensor
#define PIR_PIN 3          // Pino onde o sensor PIR está conectado
#define LED_PIN 4         // Pino do LED que simboliza o ar-condicionado

DHT dht(DHTPIN, DHTTYPE);

const int numReadings = 10;
float tempReadings[numReadings] = {0}; // Leituras de temperatura
float humReadings[numReadings] = {0};  // Leituras de umidade
int readIndex = 0;
float tempTotal = 0;
float humTotal = 0;
float tempAverage = 0;
float humAverage = 0;

const float highTempThreshold = 24.0;    // Define o valor de alta temperatura como 24°C
const unsigned long activeTime = 250000; // Tempo de funcionamento em milissegundos (250 segundos)

bool isActive = false;
unsigned long startTime = 0;
unsigned long lastReadTime = 0;          // Para controlar leituras com `millis()`

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
  dht.begin();
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // Configura o LED como saída
  digitalWrite(LED_PIN, LOW); // Garante que o LED começa desligado
}

void loop() {
  unsigned long currentTime = millis();

  // Verifica se o PIR detecta movimento
  if (digitalRead(PIR_PIN) == HIGH && !isActive) {
    isActive = true;
    startTime = currentTime;
    Serial.println("Movimento detectado - Sensor DHT ativado!");
  }

  // Verifica se o tempo ativo expirou
  if (isActive && (currentTime - startTime >= activeTime)) {
    isActive = false;
    Serial.println("Tempo expirado - Sensor DHT desativado.");
  }

  // Executa leituras do DHT22 apenas se estiver ativo
  if (isActive && (currentTime - lastReadTime >= 2000)) {
    lastReadTime = currentTime;

    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (!isnan(temperature) && !isnan(humidity)) {
      // Atualiza as médias de temperatura e umidade
      tempTotal = tempTotal - tempReadings[readIndex];
      humTotal = humTotal - humReadings[readIndex];

      tempReadings[readIndex] = temperature;
      humReadings[readIndex] = humidity;

      tempTotal = tempTotal + tempReadings[readIndex];
      humTotal = humTotal + humReadings[readIndex];

      readIndex = (readIndex + 1) % numReadings;

      tempAverage = tempTotal / numReadings;
      humAverage = humTotal / numReadings;

      // Envia os dados para o monitor serial
      Serial.print("Temperatura média: ");
      Serial.print(tempAverage);
      Serial.println(" °C");

      Serial.print("Umidade média: ");
      Serial.print(humAverage);
      Serial.println(" %");

      // Controle do LED para alta temperatura
      if (tempAverage >= highTempThreshold) {
        Serial.println("ALERTA: Temperatura alta detectada! LIGANDO AR-CONDICIONADO...");
        digitalWrite(LED_PIN, HIGH); // Liga o LED
      } else {
        Serial.println("Temperatura normal. DESLIGANDO AR-CONDICIONADO...");
        digitalWrite(LED_PIN, LOW); // Desliga o LED
      }
    } else {
      Serial.println("Erro ao ler o sensor DHT22.");
    }
  }
}
