//BASIC INFORMATION
//Program: Raindrops module
//Author: Paweł Bartkiewicz 
//mail: 15g.pawel.bart@gmail.com

//ADDITIONAL INFORMATION

const int analogPin = 34; // Analog input from sensor (A0 on module -> GPIO34 on ESP32)
const int digitalPin = 25; // Digital input from sensor (D0 on module -> GPIO25 on ESP32)

void setup() {
  Serial.begin(9600);
  pinMode(digitalPin, INPUT);

}

void loop() {
  
  int analogValue = analogRead(analogPin);  // Read analog value (0 - 4095 for ESP32 ADC)
  int digitalValue = digitalRead(digitalPin); // Read digital value from comparator (1 or 0 depending on water detection)

  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print("  |  Digital: ");
  Serial.println(digitalValue);

  // Weather condition based on analog value
  if (analogValue > 3500) {
    Serial.println("It is not raining.");
  } 
  else if (analogValue <= 3500 && analogValue > 2000) {
    Serial.println("Single drops of water detected.");
  } 
  else if (analogValue <= 2000) {
    Serial.println("It is raining.");
  }

  Serial.println(); // Blank line for readability

  delay(2000);

}
