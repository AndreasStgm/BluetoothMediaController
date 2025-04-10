#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard keyboardInstance("BLEMediaControl");

// Here the media functions are defined. The media keys are the following:
//     - KEY_MEDIA_PLAY_PAUSE
//     - KEY_MEDIA_NEXT_TRACK
//     - KEY_MEDIA_PREVIOUS_TRACK
//     - KEY_MEDIA_VOLUME_UP
//     - KEY_MEDIA_VOLUME_DOWN
const uint8_t *BUTTON_1_COMMAND = KEY_MEDIA_PLAY_PAUSE;
const uint8_t *BUTTON_2_COMMAND = KEY_MEDIA_NEXT_TRACK;

enum DeviceState
{
    WAITING,
    SEND_COMMAND_1,
    SEND_COMMAND_2
};
enum ButtonState
{
    RELEASED,
    PRESSED
};

const uint8_t BUTTON_1 = 34;
const uint8_t BUTTON_2 = 35;
const uint8_t BUTTON_1_LED = 32;
const uint8_t BUTTON_2_LED = 33;

uint16_t delayCounter = 0;

DeviceState currentDeviceState = DeviceState::WAITING;
ButtonState button1State = ButtonState::RELEASED;
ButtonState button2State = ButtonState::RELEASED;
const uint8_t BUTTON_DEBOUNCE_TIME = 50;

void button1StateChangeISR()
{
    // Assigning two longs between which the taken time in ms will be counted to debounce the button input
    static unsigned long last_cycle_interrupt_time = 0;
    unsigned long cycle_interrupt_time = millis();

    // If the current time is longer than the required debounce time
    if (cycle_interrupt_time - last_cycle_interrupt_time > BUTTON_DEBOUNCE_TIME)
    {
        // And the button was in a released state
        if (button1State == ButtonState::RELEASED)
        {
            // The button now is being pressed (detecting the edge from unpressed to pressed)
            button1State = ButtonState::PRESSED;
        }
        // And the button was in the pressed state
        else if (button1State == ButtonState::PRESSED)
        {
            // The button now has been released again after pressing (detecting the edge from pressed to unpressed)
            button1State = ButtonState ::RELEASED;

            // Send command 1 to the connected device
            currentDeviceState = DeviceState::SEND_COMMAND_1;
        }
    }

    // The ISR is now completed, the current time is now the last time for the next time the ISR is triggered
    last_cycle_interrupt_time = cycle_interrupt_time;
}
void button2StateChangeISR()
{ // Assigning two longs between which the taken time in ms will be counted to debounce the button input
    static unsigned long last_cycle_interrupt_time = 0;
    unsigned long cycle_interrupt_time = millis();

    // If the current time is longer than the required debounce time
    if (cycle_interrupt_time - last_cycle_interrupt_time > BUTTON_DEBOUNCE_TIME)
    {
        // And the button was in a released state
        if (button2State == ButtonState::RELEASED)
        {
            // The button now is being pressed (detecting the edge from unpressed to pressed)
            button2State = ButtonState::PRESSED;
        }
        // And the button was in the pressed state
        else if (button2State == ButtonState::PRESSED)
        {
            // The button now has been released again after pressing (detecting the edge from pressed to unpressed)
            button2State = ButtonState ::RELEASED;

            // Send command 1 to the connected device
            currentDeviceState = DeviceState::SEND_COMMAND_2;
        }
    }
    // The ISR is now completed, the current time is now the last time for the next time the ISR is triggered
    last_cycle_interrupt_time = cycle_interrupt_time;
}

void setup()
{
    // Configuring the pins as in- and outputs
    pinMode(BUTTON_1, INPUT);
    pinMode(BUTTON_2, INPUT);
    pinMode(BUTTON_1_LED, OUTPUT);
    pinMode(BUTTON_2_LED, OUTPUT);

    // Configure the interrupts for the buttons
    attachInterrupt(digitalPinToInterrupt(BUTTON_1), button1StateChangeISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON_2), button2StateChangeISR, CHANGE);

    // Starting the BLE keyboard instance
    keyboardInstance.begin();
}

void loop()
{
    if (keyboardInstance.isConnected())
    {
        // Turn off the LEDs when connected
        digitalWrite(BUTTON_1_LED, LOW);
        digitalWrite(BUTTON_2_LED, LOW);

        // Send the corresponding command if one of the buttons has been pressed
        if (currentDeviceState == DeviceState::SEND_COMMAND_1)
        {
            // Send the command
            keyboardInstance.write(BUTTON_1_COMMAND);
            // Set the devices state back to waiting for a press
            currentDeviceState = DeviceState::WAITING;
        }
        else if (currentDeviceState == DeviceState::SEND_COMMAND_2)
        {
            // Send the command
            keyboardInstance.write(BUTTON_2_COMMAND);
            // Set the devices state back to waiting for a press
            currentDeviceState = DeviceState::WAITING;
        }

        if (delayCounter >= 15000)
        {
            delayCounter = 0;
            // Flash the LEDs every 15 seconds to indicate that the device is powered
            digitalWrite(BUTTON_1_LED, HIGH);
            digitalWrite(BUTTON_2_LED, HIGH);
            delay(100);
            digitalWrite(BUTTON_1_LED, LOW);
            digitalWrite(BUTTON_2_LED, LOW);
        }
    }
    else
    {
        if (delayCounter >= 1000)
        {
            delayCounter = 0;
            // Flash the LEDs on and off every second to indicate unconnected state
            digitalWrite(BUTTON_1_LED, !digitalRead(BUTTON_1_LED));
            digitalWrite(BUTTON_2_LED, !digitalRead(BUTTON_2_LED));
        }
    }

    delayCounter++;
    delay(1);
}
