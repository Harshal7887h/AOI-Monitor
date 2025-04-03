#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "lBV2IdFDqSKkA1flTUHcvR80cGqF-imG";  
char ssid[] = "realme 9 5G";  
char pass[] = "Harshal7887###";

#define DHTPIN D4  
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define MQ135PIN A0  

BlynkTimer timer;


void sendSensorData() {
    float air_quality = analogRead(MQ135PIN);  
    float temperature = dht.readTemperature();  
    float humidity = dht.readHumidity();  
    
    Blynk.virtualWrite(V0, air_quality);
    Blynk.virtualWrite(V1, temperature);
    Blynk.virtualWrite(V2, humidity);

    if (air_quality > 400) {  
        Blynk.logEvent("air_quality_alert", "⚠️ High Pollution Detected! Take Precautions.");
    }
}

void setup() {
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
    dht.begin();
    timer.setInterval(5000L, sendSensorData);
}
void loop() {
    Blynk.run();
    timer.run();
}
