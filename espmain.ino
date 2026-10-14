#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize 16x2 I2C LCD (Address 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Definitions matching your physical board's 'D' labels
const int soilMoisturePin = 34; 
const int rainSensorPin = 33;   
const int trigPin = 26;         
const int echoPin = 27;         
const int pirPin = 25;          
const int relayPin = 32;        
const int buzzerPin = 23;       
const int redLedPin = 13;       
const int greenLedPin = 4;      

void setup() {
  Serial.begin(115200);
  
  // UART communication setup to talk to the ESP32-CAM on D16 (RX2) and D17 (TX2)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("AgriShield Active");
  delay(2000);
  lcd.clear();

  pinMode(soilMoisturePin, INPUT);
  pinMode(rainSensorPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  digitalWrite(relayPin, HIGH);    // Active-LOW relay (HIGH = Pump OFF)
  digitalWrite(greenLedPin, HIGH); // Green light ON = System healthy
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  int soilValue = analogRead(soilMoisturePin);
  int rainState = digitalRead(rainSensorPin);

  // Ultrasonic distance measurement for water tank
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int tankDistance = duration * 0.034 / 2; 

  int motionState = digitalRead(pirPin);

  // Print diagnostics to Serial Monitor
  Serial.print("Soil: "); Serial.print(soilValue);
  Serial.print(" | Rain: "); Serial.print(rainState);
  Serial.print(" | Tank: "); Serial.print(tankDistance);
  Serial.print("cm | Motion: "); Serial.println(motionState);

  // --- SECURITY LOGIC ---
  if (motionState == HIGH) {
    digitalWrite(redLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(buzzerPin, HIGH);
    
    // Command the camera module to capture an image over serial wire
    Serial2.println("CAPTURE_IMAGE"); 
    
    lcd.setCursor(0, 0);
    lcd.print("ALERT: INTRUDER! ");
  } else {
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(buzzerPin, LOW);
    
    lcd.setCursor(0, 0);
    lcd.print("System Status: OK");
  }

  // --- IRRIGATION LOGIC ---
  if (soilValue > 2500 && rainState == HIGH) {
    digitalWrite(relayPin, LOW); // Turn ON pump
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON (Water) ");
  } else {
    digitalWrite(relayPin, HIGH); // Turn OFF pump
    lcd.setCursor(0, 1);
    lcd.print("Pump: OFF        ");
  }

  delay(1000);
}