#define SOUND_SENSOR A0
#define LED_PIN 6
#define NUM_LEDS 60

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

int soundThreshold = 650;
bool ledState = false;
unsigned long lastClapTime = 0;
const int clapDelay = 500; // Minimum time between claps (ms)
int clapCount = 0;

void setup() {
    Serial.begin(9600);
    pinMode(SOUND_SENSOR, INPUT);
    strip.begin();
    strip.show();
}

void loop() {
    int soundLevel = analogRead(SOUND_SENSOR);
    Serial.println(soundLevel);

    if (soundLevel > soundThreshold) {
        if (millis() - lastClapTime > clapDelay) {
            clapCount++;
            lastClapTime = millis();
        }
    }

    if (clapCount == 2) {
        ledState = !ledState;
        if (ledState) {
            rainbowEffect(10); // Turn ON effect
        } else {
            strip.clear();  // Turn OFF all LEDs
            strip.show();
        }
        clapCount = 0; // Reset clap count
    }

    delay(50); // Small delay to reduce sensor noise
}

void rainbowEffect(int wait) {
    for (long firstPixelHue = 0; firstPixelHue < 65536; firstPixelHue += 256) {
        if (!ledState) return; // Stop effect if LED is turned off
        strip.rainbow(firstPixelHue);
        strip.show();
        delay(wait);
    }
}
