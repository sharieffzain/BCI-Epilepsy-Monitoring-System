#include "synapse.h" 
 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
 
// Pin configuration for DHT11 
 
#define flagpin 8 
 
// Initialize the LCD with I2C address 0x27 and size 16x4 
LiquidCrystal_I2C lcd(0x27, 16, 4); 
 
// Define button pins 
const int buttonEOG = 4; // Pin for EOG 
const int buttonECG = 5; // Pin for ECG 
const int buttonEEG = 6; // Pin for EEG 
const int buttonEMG = 7; // Pin for EMG 
 
const int sensorPin = A0; // Analog input pin 
unsigned long previousMillis = 0; // Variable to store the last time a 
sample was taken 
unsigned long interval = 4; // Default interval between samples in 
milliseconds 
unsigned long dhtPreviousMillis = 0; // Variable to store the last time DHT 
data was read 
unsigned long dhtInterval = 2000; // Interval for reading DHT data (2 
seconds) 
 
synapse exg_synapse; 
 
void setup() { 
  Serial.begin(115200); // For communication with PC 
  Serial1.begin(115200); // For communication with ESP32 
   
  dht.begin(); // Initialize the DHT sensor 
 
  lcd.init(); // Initialize the LCD 
  lcd.backlight(); 
   
  displayInitialMessage(); // Display initial message 
   
  pinMode(buttonEOG, INPUT_PULLUP); 
  pinMode(buttonECG, INPUT_PULLUP); 
  pinMode(buttonEEG, INPUT_PULLUP); 
  pinMode(buttonEMG, INPUT_PULLUP); 
  pinMode(flagpin, OUTPUT); 
} 
 
void loop() { 
  if (digitalRead(buttonEOG) == LOW) { 
    runEOGFilters(); 
    delay(500);  
    while (digitalRead(buttonEOG) == LOW); 
    displayInitialMessage(); 
    return; 
  } 
 
  if (digitalRead(buttonECG) == LOW) { 
    runECGFilters(); 
    delay(500);  
    while (digitalRead(buttonECG) == LOW); 
    displayInitialMessage(); 
    return; 
  } 
 
  if (digitalRead(buttonEEG) == LOW) { 
    runEEGFilters(); 
    delay(500);  
    while (digitalRead(buttonEEG) == LOW); 
85 
 
    displayInitialMessage(); 
    return; 
  } 
 
  if (digitalRead(buttonEMG) == LOW) { 
    runEMGFilters(); 
    delay(500);  
    while (digitalRead(buttonEMG) == LOW); 
    displayInitialMessage(); 
    return; 
  } 
} 
 
void displayInitialMessage() { 
  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("1: EOG"); 
   
  lcd.setCursor(0, 1); 
  lcd.print("2: ECG"); 
   
  lcd.setCursor(0, 2); 
  lcd.print("3: EEG"); 
   
  lcd.setCursor(0,3); 
  lcd.print("4: EMG"); 
   
} 
 
void runEOGFilters() { 
   lcd.clear(); 
   lcd.setCursor(0,0); 
   lcd.print("EOG Selected"); 
 
   while (true) { 
     unsigned long currentMillis = millis(); 
     if (currentMillis - previousMillis >= interval) { 
       previousMillis = currentMillis; 
       float sensorValue = analogRead(sensorPin); 
       float filters_out = exg_synapse.apply_EOG_filters(sensorValue); 
       Serial.println(filters_out); 
       Serial1.println(filters_out); 
 
       lcd.setCursor(0,2); 
       lcd.print("EOG: "); 
                  digitalWrite(flagpin,LOW); 
 
       lcd.setCursor(0,2); 
       lcd.print(filters_out); 
       if(filters_out > 390 || filters_out < -390){ 
        digitalWrite(flagpin,HIGH); 
        delay(700); 
         
         
       } 
        
     } 
 
     if (millis() - dhtPreviousMillis >= dhtInterval) { 
       dhtPreviousMillis = millis(); 
       
     } 
 
      
   } 
} 
 
void runECGFilters() { 
   lcd.clear(); 
   lcd.setCursor(0,0); 
   lcd.print("ECG Selected"); 
 
   while (true) { 
     unsigned long currentMillis = millis(); 
     if (currentMillis - previousMillis >= interval) { 
       previousMillis = currentMillis; 
       float sensorValue = analogRead(sensorPin); 
       float filters_out = exg_synapse.apply_ECG_filters(sensorValue); 
       Serial.println(filters_out); 
       Serial1.println(filters_out); 
       digitalWrite(flagpin,LOW); 
 
       lcd.setCursor(0,2); 
       lcd.print(filters_out); 
       if(filters_out > 480 || filters_out < -480){ 
        digitalWrite(flagpin,HIGH); 
        delay(700); 
         
         
       } 
     } 
 
     if (millis() - dhtPreviousMillis >= dhtInterval) { 
       dhtPreviousMillis = millis(); 
       
     } 
 
     
   } 
} 
 
void runEEGFilters() { 
   lcd.clear(); 
   lcd.setCursor(0,0); 
   lcd.print("EEG Selected"); 
 
   while (true) { 
     unsigned long currentMillis = millis(); 
     if (currentMillis - previousMillis >= interval) { 
       previousMillis = currentMillis; 
       float sensorValue = analogRead(sensorPin); 
       float filters_out = exg_synapse.apply_EEG_filters(sensorValue); 
       Serial.println(filters_out); 
       Serial1.println(filters_out); 
 
       lcd.setCursor(0,2); 
       lcd.print("EEG: "); 
                  digitalWrite(flagpin,LOW); 
 
       lcd.setCursor(0,2); 
       lcd.print(filters_out); 
       if(filters_out > 410 || filters_out < -410){ 
        digitalWrite(flagpin,HIGH); 
        delay(700); 
         
         
       } 
     
     } 
 
     if (millis() - dhtPreviousMillis >= dhtInterval) { 
       dhtPreviousMillis = millis(); 
       
     } 
 
      
   } 
} 
 
void runEMGFilters() { 
   lcd.clear(); 
   lcd.setCursor(0,0); 
   lcd.print("EMG Selected"); 
 
while (true) { 
unsigned long currentMillis = millis(); 
if (currentMillis - previousMillis >= interval) { 
previousMillis = currentMillis; 
float sensorValue = analogRead(sensorPin); 
float filters_out = exg_synapse.apply_EMG_filters(sensorValue); 
Serial.println(filters_out); 
Serial1.println(filters_out); 
lcd.setCursor(0,2); 
lcd.print("EMG: "); 
digitalWrite(flagpin,LOW); 
lcd.setCursor(0,2); 
lcd.print(filters_out); 
if(filters_out > 280 || filters_out < -280){ 
digitalWrite(flagpin,HIGH); 
delay(700); 
} 
} 
if (millis() - dhtPreviousMillis >= dhtInterval) { 
dhtPreviousMillis = millis(); 
} 
} 
} 