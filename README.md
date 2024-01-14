# ESP32-WiFi-Captive-Portal

## About this project

This project is a modification of https://github.com/adamff-dev/ESP8266-Captive-Portal

The programmed ESP32 chip creates an access point with any name that is used to capture passwords. Captured passwords are saved in the ESP32 memory and do not disappear after restarting/shutting down the device. When the new password is saved on the device, the LED will first flash 5 times and then turn on continuously. If you have the device in sight, you immediately know that you have a new password. Clearing the password in the login panel or restarting the device turns off the LED light.

I provide versions in English and Polish.

## Reservation

This project is of a testing and educational nature. Only use it so that you do not break the law. I take no responsibility for what you do with this program.

## Connection diagram

To build a device with ESP32-WiFi-Captive-Portal, I used the XIAO ESP32S3 module with an external WiFi antenna (you can use any ESP32 module with an external or built-in antenna). I also used a green LED and a USB A cable.

I enclosed the assembled device in a housing printed on a 3D printer.
Link to the housing design:https://www.thingiverse.com/thing:3940612

## Installation using Arduino IDE.

1. Download and install Arduino IDE
https://www.arduino.cc/en/software
(This manual is based on arduino-ide_2.2.1 version)

2. Download the file pl-ESP32-WiFi_Captive_Portal.ino to your computer and open it in the Arduino IDE by clicking File -> Open

3. Launch the Arduino IDE, go to Tools -> Board -> Boards Manager. In the "Filter your search" field, enter esp32. Install "Ardunio ESP32 Boards by ardunio" and "ESP32 by espressif Systems".

4. Select the ESP32 module you have and want to program it in Tools -> Board -> esp32

5. Connect your ESP32 module to the computer and select the port where it is visible (Tools -> Port -> Com[no])

6. Upload the program to your ESP32 chip: Sketch -> Upload

7. Restart your programmed module and enjoy its operation. Ready.

## Start-up and operation

Connect your programmed esp32 module to the power supply. Search for and log in to an open Wi-Fi network called "Free WiFi" (or another one if you changed the name during programming).
In your browser, go to 172.0.0.1/pass . Passwords will be visible there (if they are entered by people trying to log in to the access point).

![pass](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/f9772e2b-02c5-46b7-b7ac-6983a882ed77)

If you click on "Index" you will see what the access point's home page looks like.

![index](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/29fecc19-4d97-4bc0-88da-ef9315b21e11)

If you click "Change SSID" you will go to a subpage where you can change the network name of the access point.

![ssid](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/7e28b350-d66d-43ab-922b-ec6a14a8faa0)

If you click "Clear Passwords" you will be able to clear the passwords saved on your device.

![clear](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/398a7726-6834-4d9b-bc64-ce8f5e438ab1)


