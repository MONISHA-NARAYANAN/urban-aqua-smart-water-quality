#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "water quality monitoring"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <BlynkSimpleEsp32.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define SDA_PIN 21
#define SCL_PIN 22

LiquidCrystal_I2C lcd(0x27, 16, 2);

// === SENSOR PINS ===
const int oneWireBus = 4;       // DS18B20
const int turbidity_pin = 34;   // Turbidity sensor
const int ph_pin = 32;          // pH sensor

// === PH CALIBRATION VALUES ===
float acidVoltage = 2.50;       // Voltage at pH 7
float neutralVoltage = 3.00;    // Voltage at pH 4

// === ONE WIRE ===
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

void setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();

  Serial.begin(115200);
  sensors.begin();

  // Configure ADC
  analogReadResolution(12);           // 0–4095
  analogSetAttenuation(ADC_11db);     // Allows up to ~3.3V input
}

// === READ PH VOLTAGE WITH SMOOTHING ===
float readPHVoltage() {
  long sum = 0;

  for (int i = 0; i < 10; i++) {
    sum += analogRead(ph_pin);
    delay(20);
  }

  float adc_avg = sum / 10.0;

  // Convert ADC to voltage
  float voltage = adc_avg * (3.3 / 4095.0);

  return voltage;
}

// === CALCULATE pH FROM VOLTAGE ===
float getPH() {
  float voltage = readPHVoltage();

  Serial.print("pH Sensor Voltage: ");
  Serial.print(voltage, 4);
  Serial.println(" V");

  // Dynamic slope
  float slope = (7.0 - 4.0) / (acidVoltage - neutralVoltage);
  float intercept = 7.0 - slope * acidVoltage;

  float ph = slope * voltage + intercept;

  return ph;
}

// === MAIN LOOP ===
void loop() {
  Blynk.run();

  // TEMPERATURE SENSOR
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.println(temperatureC);
  Blynk.virtualWrite(V0, temperatureC);

  // TURBIDITY SENSOR
  int raw = analogRead(turbidity_pin);
  float turbidity = map(raw, 0, 3000, 5, 0);
  Serial.print("Turbidity: ");
  Serial.println(turbidity);
  Blynk.virtualWrite(V1, turbidity);

  // PH SENSOR
  float phValue = getPH();
  Serial.print("pH Value: ");
  Serial.println(phValue);
  Blynk.virtualWrite(V2, phValue);

  // LCD DISPLAY
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Tem:");
  lcd.print(temperatureC, 1);
  lcd.print("C");

  lcd.setCursor(9, 0);
  lcd.print("Tur:");
  lcd.print(turbidity);

  lcd.setCursor(0, 1);
  lcd.print("pH:");
  lcd.print(phValue, 2);

  delay(1000);
}
