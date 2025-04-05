#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard keyboardInstance;

const uint8_t BUTTON_1 = 34;
const uint8_t BUTTON_2 = 35;
const uint8_t BUTTON_1_LED = 32;
const uint8_t BUTTON_2_LED = 33;

uint16_t delayCounter = 0;

void setup()
{
    // Configuring the pins as in- and outputs
    pinMode(BUTTON_1, INPUT_PULLUP);
    pinMode(BUTTON_2, INPUT_PULLUP);
    pinMode(BUTTON_1_LED, OUTPUT);
    pinMode(BUTTON_2_LED, OUTPUT);

    keyboardInstance.begin();

    // Turning on the LED's to indicate startup
    digitalWrite(BUTTON_1_LED, HIGH);
    digitalWrite(BUTTON_2_LED, HIGH);
}

void loop()
{
    if (keyboardInstance.isConnected())
    {
        // Turn off the LEDs when connected
        delayCounter = 0;
        digitalWrite(BUTTON_1_LED, LOW);
        digitalWrite(BUTTON_2_LED, LOW);

        // Serial.println("<BLEKeyboard> Writing play/pause press.");
        // keyboardInstance.write(KEY_MEDIA_PLAY_PAUSE);

        // keyboardInstance.write(KEY_MEDIA_NEXT_TRACK);
        // keyboardInstance.write(KEY_MEDIA_PREVIOUS_TRACK);
        // keyboardInstance.write(KEY_MEDIA_VOLUME_UP);
        // keyboardInstance.write(KEY_MEDIA_VOLUME_DOWN);
    }
    else
    {
        if (delayCounter >= 1000)
        {
            // Flash the LEDs on and off every second to indicate unconnected state
            delayCounter = 0;
            digitalWrite(BUTTON_1_LED, !digitalRead(BUTTON_1_LED));
            digitalWrite(BUTTON_2_LED, !digitalRead(BUTTON_2_LED));
        }
    }

    delayCounter++;
    delay(1);
}
