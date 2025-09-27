#include <WiFi.h> 
#include <FirebaseESP32.h> 
#include <DHT.h> 
// Replace these with your own Firebase and WiFi credentials 
#define 
FIREBASE_HOST 
rtdb.firebaseio.com" 
"https://smartparkingg-f7952-default
#define FIREBASE_AUTH "jncsa-dac jascsacas t" 
#define WIFI_SSID "k1" 
#define WIFI_PASSWORD "12345678" 
// Define Firebase Data object 
FirebaseData firebaseData; 
// Define DHT sensor type and pin 
#define DHTTYPE DHT11 
#define DHTPIN 4 // Change to the GPIO pin you're using 
DHT dht(DHTPIN, DHTTYPE); 
// Define button pin 
#define BUTTON_PIN 2 
void setup() 
{ 
Serial.begin(115200); 
// Connect to WiFi 
WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
while (WiFi.status() != WL_CONNECTED) 
{ 
delay(1000); 
Serial.println("Connecting to WiFi..."); 
} 
Serial.println("Connected to WiFi"); 
// Initialize Firebase 
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
Firebase.reconnectWiFi(true); 
// Initialize DHT sensor 
dht.begin(); 
// Initialize button pin 
pinMode(BUTTON_PIN, INPUT_PULLUP); 
} 
void loop() 
{ 
// Read button state 
int buttonState = digitalRead(BUTTON_PIN); 
// Check if button is pressed 
if (buttonState == LOW) 
{ 
// Send trigger to Firebase 
Firebase.setBool(firebaseData, "/flag", true); 
Serial.println("Button pressed, trigger sent to Firebase"); 
// Read DHT11 sensor data 
float temperature = dht.readTemperature(); 
// Check if any reads failed and exit early (to try again). 
if (isnan(temperature) ) 
{ 
Serial.println("Failed to read from DHT sensor!"); 
return; 
} 
// Send DHT11 data to Firebase 
Firebase.setFloat(firebaseData, "/temperature", temperature); 
Serial.println("Temperature and humidity data sent to Firebase"); 
// Small delay to avoid multiple triggers 
delay(1000); 
} 
}