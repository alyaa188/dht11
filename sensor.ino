#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char *ssid = "realme 8";
const char *password = "Qotb1172";
const char *serverUrl = "http://172.105.66.220:5000/update_sensor_data";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  pinMode(2, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  WiFiClient client;  // Create a WiFiClient object
  HTTPClient http;
  http.begin(client, serverUrl);  // Use begin(WiFiClient, url) here
  http.addHeader("Content-Type", "application/json");

  String jsonData = "{\"sensor_value\": 123}";
  int httpCode = http.POST(jsonData);

  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println("Response from server: " + payload);
    digitalWrite(2, HIGH);
    
  } else {
    Serial.println("Failed to update sensor data. HTTP code: " + String(httpCode));
  }

  http.end();

  delay(5000);
  digitalWrite(2, LOW);  // Adjust the delay according to your needs
}

/*
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

DHT dht(D3, DHT11); //(sensor pin,sensor type)

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
}
void loop()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    lcd.setCursor(0,0);
    lcd.print("Hello, world!");
}
*/
