#define SOIL_SENSOR A0  // Soil sensor analog pin
#define BUZZER_PIN 9    // Active buzzer pin

int dryThreshold = 300; // Adjust based on soil type

void setup() {
    Serial.begin(9600);
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
    int soilMoisture = analogRead(SOIL_SENSOR);
    Serial.println(soilMoisture); // Check sensor values in Serial Monitor

    if (soilMoisture < dryThreshold) {
        Serial.println("The plant is thirsty! Water it!");
        digitalWrite(BUZZER_PIN, HIGH); // Buzzer ON
        delay(3000); // Buzzer stays on for 3 second
        digitalWrite(BUZZER_PIN, LOW); // Buzzer OFF
        delay(2000); // Wait before checking again
    } else {
        digitalWrite(BUZZER_PIN, LOW); // Ensure buzzer is off
    }

    delay(1000); // Update every second
}
