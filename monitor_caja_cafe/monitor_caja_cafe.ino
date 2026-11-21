#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHT_PIN   15
#define OLED_ADDR 0x3C   

DHT dht(DHT_PIN, DHT11);
Adafruit_SSD1306 display(128, 64, &Wire, -1);
bool oledOK = false;

void setup() {
  Serial.begin(115200);
  delay(500);
  Wire.begin(21, 22);

  Serial.println("Buscando dispositivos I2C...");
  for (byte dir = 1; dir < 127; dir++) {
    Wire.beginTransmission(dir);
    if (Wire.endTransmission() == 0) Serial.printf("  Encontrado en 0x%02X\n", dir);
  }

  oledOK = display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  Serial.println(oledOK ? "OLED OK" : "OLED NO encontrada");

  pinMode(2, OUTPUT);
  dht.begin();
  delay(2000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  digitalWrite(2, !digitalRead(2));

  if (isnan(h) || isnan(t)) {
    Serial.println("DHT11: error de lectura (revisa DATA en GPIO 15 y alimentacion)");
  } else {
    Serial.printf("DHT11 OK -> T: %.1f C   H: %.0f %%\n", t, h);
  }

  if (oledOK) {
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("Prueba de montaje");
    display.setTextSize(2);
    display.setCursor(0, 20);
    if (isnan(t)) display.print("DHT error");
    else display.printf("T %.1f C", t);
    display.setCursor(0, 42);
    if (!isnan(h)) display.printf("H %.0f %%", h);
    display.display();
  }
  delay(2500);
}
