#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard keyboardInstance;

void setup()
{
    Serial.begin(115200);
    Serial.println("Starting BLE Keyboard instance.");
    keyboardInstance.begin();
}

void loop()
{
    if (keyboardInstance.isConnected())
    {
        Serial.println("<BLEKeyboard> Writing play/pause press.");
        keyboardInstance.write(KEY_MEDIA_PLAY_PAUSE);

        keyboardInstance.write(KEY_MEDIA_NEXT_TRACK);
        keyboardInstance.write(KEY_MEDIA_PREVIOUS_TRACK);
        keyboardInstance.write(KEY_MEDIA_VOLUME_UP);
        keyboardInstance.write(KEY_MEDIA_VOLUME_DOWN);
    }
}
