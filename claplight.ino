#include <Adafruit_NeoPixel.h>  // Library for controlling NeoPixel LEDs

#define LED_PIN 6          // Pin connected to the NeoPixel strip
#define NUM_LEDS 60        // Number of LEDs in the NeoPixel strip
#define SOUND_SENSOR A0    // Pin connected to the sound sensor

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);  // Create NeoPixel strip object

int soundThreshold = 150;  // Threshold for detecting sound; adjust based on sensor's readings
bool soundDetected = false;  // Flag to check if sound was already detected

void setup() {
    Serial.begin(9600);  // Start serial communication for debugging
    pinMode(SOUND_SENSOR, INPUT);  // Set the sound sensor pin as input
    strip.begin();  // Initialize the NeoPixel strip
    strip.show();  // Initialize all LEDs to off (start state)
}

void loop() {
    int soundLevel = analogRead(SOUND_SENSOR);  // Read the analog value from the sound sensor
    Serial.println(soundLevel);  // Print the sound level for debugging purposes

    // If sound level exceeds the threshold and sound wasn't detected before
    if (soundLevel > soundThreshold && !soundDetected) {
        soundDetected = true;  // Set flag to prevent multiple triggers
        rainbowEffect(10);  // Trigger the rainbow effect with a 10ms delay between colors
        delay(300);  // Add delay to prevent rapid retriggering of the effect
    }

    // If the sound level drops below a certain point (sound stops)
    if (soundLevel < soundThreshold - 50) {
        soundDetected = false;  // Reset the flag when sound is no longer detected
    }
}

// Function to display a rainbow effect on the NeoPixel strip
void rainbowEffect(int wait) {
    // Loop through 65536 color hues to create a smooth rainbow transition
    for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
        strip.rainbow(firstPixelHue);  // Set the rainbow colors starting from firstPixelHue
        strip.show();  // Update the LEDs to show the new colors
        delay(wait);  // Wait before updating again to create the effect
    }
}
