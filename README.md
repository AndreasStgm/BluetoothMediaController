# Bluetooth Media Controller

This project uses the [BLEKeyboard library](https://github.com/T-vK/ESP32-BLE-Keyboard) as a way to connect to a music player and control its media playback.
It is designed for people who have impaired vision.

## LED status indicators

The buttons will light up in different ways to indicate different statuses of the device.

1. Both buttons flashing on and off every second
   - This indicates that the device is powered on, but not connected to any device over bluetooth. It should be actively advertising itself to nearby bluetooth devices.
2. Both buttons flash shortly every 15 seconds
   - This indicates that the device is powered on AND correctly connected to a device over bluetooth. The device is powered on and working correctly.
3. Both buttons are off permanently
   - The device is powered off.

## Modifying button functions

This project is built using [PlatformIO](https://platformio.org/).
To modify or upload new versions to the device the [VSCode](https://code.visualstudio.com/) and the [PlatformIO Extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) must be installed.

The functions that the buttons perform can be modified in the constants at the top of the ´main.cpp´-file.
The following options are available through the keyboard library:

- ´KEY_MEDIA_PLAY_PAUSE´
- ´KEY_MEDIA_NEXT_TRACK´
- ´KEY_MEDIA_PREVIOUS_TRACK´
- ´KEY_MEDIA_VOLUME_UP´
- ´KEY_MEDIA_VOLUME_DOWN´

## Bill Of Materials (BOM):

|               Item               | Unit Cost |    Amount     |   Total Cost    |                                      Link                                      |
| :------------------------------: | :-------: | :-----------: | :-------------: | :----------------------------------------------------------------------------: |
|      5V Push Button (100mm)      |  € 8.39   |       2       |     € 16.78     |               https://www.aliexpress.com/item/4001241312568.html               |
| Female slide-on contact (4.8mm)  |  € 0.185  |    4 (10)     |     € 1.85      | https://www.gotron.be/opschuifcontact-vrouwelijk-4-8x0-8mm-rood-100-stuks.html |
| Female slide-on contact (6.3mm)  |  € 0.185  |    4 (10)     |     € 1.85      | https://www.gotron.be/opschuifcontact-vrouwelijk-6-3x0-8mm-rood-10-stuks.html  |
|     Red Flexible Wire (1mm)      |  € 0.14   | 4 x 20cm (5m) |     € 3.50      |          https://www.gotron.be/soepele-montagedraad-5m-rood-1mm.html           |
|    Black Flexible Wire (1mm)     |  € 0.14   | 4 x 20cm (5m) |     € 3.50      |          https://www.gotron.be/soepele-montagedraad-5m-zwart-1mm.html          |
|         ESP32 Dev Board          |  € 15.90  |       1       |     € 15.90     |                 https://www.gotron.be/nodemcu-esp32-joyit.html                 |
|       Test PCB (50x100mm)        |  € 1.15   |       1       |     € 1.15      |    https://www.gotron.be/testprint-50x100mm-met-halfdoorlopende-banen.html     |
| 10.000 mAh Powerbank (+shipping) |  € 29.99  |       2       | € 59.98 (+8.00) |       https://www.anker.com/eu-en/products/a1229?variant=41510217220286        |
|                                  |           |               |                 |                                                                                |
|              TOTAL               | € 112.51  |               |                 |                                                                                |
