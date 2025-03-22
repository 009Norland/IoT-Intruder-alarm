#include <LiquidCrystal.h>

// Initialize the LCD
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// Define pins for the ultrasonic sensor
const int trigPin = 10;  // Trigger pin
const int echoPin = 11;  // Echo pin

// Define pin for the buzzer
const int buzzerPin = 8; // Buzzer pin

// Define the distance threshold
const int distanceThreshold = 10; // 1 cm

// Variable to track system state
bool systemArmed = true; // Start with the system armed

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT); // Set the trigger pin as OUTPUT
  pinMode(echoPin, INPUT);  // Set the echo pin as INPUT
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as OUTPUT

  // Display initial state
  lcd.print("System Armed");
}

void loop() {
  long duration, distance;

  // Clear the trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Set the trigger to HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo pin
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm
  distance = (duration / 2) * 0.0343;

  // Check if the system is armed and distance is less than or equal to the threshold
  if (systemArmed && distance <= distanceThreshold) {
    lcd.clear();
    lcd.print("Disarmed");
    digitalWrite(buzzerPin, LOW); // Turn on the buzzer
  } else {
    lcd.clear();
    lcd.print("Intruder alert"); // Display "Safe" when no one is near
    digitalWrite(buzzerPin, HIGH); // Turn off the buzzer
  }

  delay(500); // Delay for stability
}