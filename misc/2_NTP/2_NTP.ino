//BASIC INFORMATION
// Program: NTP setup for ESP32
// Author:  Paweł Bartkiewicz 
// email:   15g.pawel.bart@gmail.com
// github:  PaweuQ

#include <WiFi.h>
#include "time.h"

// Your Wi-Fi credentials
const char* ssid     = "XYZ";
const char* password = "XYZ";

// NTP server and time settings
const char* ntpServer = "pool.ntp.org"; // NTP server address
const long  gmtOffset_sec = 3600;       // Offset from GMT in seconds (example: +1 hour)
const int   daylightOffset_sec = 3600;  // Daylight saving offset in seconds (if applicable)

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  Serial.printf("Connecting to %s", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");

  // Configure time via NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  Serial.println("Time synchronized with NTP server.");
}

void loop() {
  // Create a time structure
  struct tm timeinfo;

  // Get the current time
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    delay(2000);
    return;
  }

  // Print formatted time
  Serial.printf("%04d-%02d-%02d %02d:%02d:%02d\n",
                timeinfo.tm_year + 1900,
                timeinfo.tm_mon + 1,
                timeinfo.tm_mday,
                timeinfo.tm_hour,
                timeinfo.tm_min,
                timeinfo.tm_sec);

  delay(1000); // Update every second
}
