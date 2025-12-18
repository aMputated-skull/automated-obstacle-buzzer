serial.exe // Include NewPing Library
#include <NewPing.h>

// Pin connections
#define TRIGGER_PIN 9
#define ECHO_PIN 10

// Maximum distance (in cm)
#define MAX_DISTANCE 400

    // Create sonar object
    NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
    Serial.begin(9600); // Start serial communication
}

void loop()
{
    int d = sonar.ping_cm(); // Read distance in cm

    if (d > 0 && d < 10)
    {
        Serial.println("ALARM"); // Send trigger to