# Monitor de temperatura y humedad para caja de café

Sistema basado en **ESP32** que mide la temperatura y la humedad relativa del aire dentro de una caja con café y muestra los valores en una pantalla **OLED 0.96"** y en el monitor serie.

> **Etapa actual:** sensor – ADC – microcontrolador.

---

## Funcionamiento

1. El sensor **DHT11** mide la humedad (sensor capacitivo) y la temperatura (termistor NTC). Un microcontrolador interno del sensor convierte esas señales analógicas a digital y entrega los valores a la ESP32 por un bus de un solo hilo.
2. Al iniciar, la **ESP32** hace un escaneo del bus I2C e informa por el monitor serie las direcciones de los dispositivos encontrados (la OLED responde en **0x3C**).
3. Cada 2.5 s la ESP32 lee la temperatura y la humedad del DHT11.
4. Los valores se muestran en la **OLED** y en el **monitor serie**. Si la lectura falla, se indica el error en ambos.
5. El LED integrado de la ESP32 (GPIO 2) parpadea en cada ciclo de lectura como indicador de funcionamiento.

## Materiales

| Cantidad | Componente |
|---|---|
| 1 | ESP32 DevKit (30 pines) |
| 1 | Módulo sensor DHT11 (3 pines, con resistencia pull-up integrada) |
| 1 | Pantalla OLED 0.96" SSD1306, I2C (128×64) |
| 1 | Protoboard |
| — | Cables jumper |
| 1 | Cable USB de datos |

## Conexiones

| Componente | Pin del componente | Pin de la ESP32 | Función |
|---|---|---|---|
| OLED SSD1306 | VDD | 3V3 | Alimentación (3.3 V) |
| OLED SSD1306 | GND | GND | Tierra |
| OLED SSD1306 | SDA | GPIO 21 | Datos I2C |
| OLED SSD1306 | SCK | GPIO 22 | Reloj I2C |
| Módulo DHT11 | VCC | 3V3 | Alimentación (3.3 V) |
| Módulo DHT11 | GND | GND | Tierra |
| Módulo DHT11 | DATA | GPIO 15 | Señal digital (un hilo) |
| LED integrado | — | GPIO 2 | Indicador de funcionamiento |

- La OLED usa la dirección I2C **0x3C**.
- Todos los componentes se alimentan a **3.3 V**, por lo que las señales quedan dentro del rango que soportan los pines de la ESP32.

## Instrucciones

### 1. Preparar Arduino IDE
1. Instala [Arduino IDE](https://www.arduino.cc/en/software).
2. Agrega las placas ESP32: **Archivo → Preferencias → URLs adicionales de gestor de placas**:
   ```
   https://espressif.github.io/arduino-esp32/package_esp32_index.json
   ```
3. En **Herramientas → Placa → Gestor de placas**, instala **esp32** (Espressif Systems).

### 2. Instalar librerías
En **Herramientas → Administrar bibliotecas**, instala:
- **DHT sensor library** (Adafruit), y acepta instalar *Adafruit Unified Sensor*
- **Adafruit SSD1306**, y acepta instalar *Adafruit GFX Library*

### 3. Cargar el código
1. Clona o descarga este repositorio.
2. Abre `monitor_caja_cafe/monitor_caja_cafe.ino`.
3. Selecciona la placa **ESP32 Dev Module** y el puerto COM correspondiente.
4. Presiona **Subir**. Si se queda en `Connecting...`, mantén presionado el botón **BOOT** de la ESP32 hasta que empiece la carga.
5. Abre el **Monitor Serie** a **115200 baudios**.

### 4. Verificar
El monitor serie debe mostrar:
```
Buscando dispositivos I2C...
  Encontrado en 0x3C
OLED OK
DHT11 OK -> T: 24.0 C   H: 65 %
```
y la OLED debe mostrar la temperatura y la humedad.

## Parámetros configurables

Al inicio de `monitor_caja_cafe.ino`:

| Parámetro | Valor | Descripción |
|---|---|---|
| `DHT_PIN` | 15 | Pin de datos del sensor |
| `OLED_ADDR` | 0x3C | Dirección I2C de la OLED (algunas usan 0x3D) |

## Especificaciones del DHT11

| Variable | Rango | Precisión | Resolución |
|---|---|---|---|
| Humedad relativa | 20 – 90 % | ±5 % | 1 % |
| Temperatura | 0 – 50 °C | ±2 °C | 1 °C |
