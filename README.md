# ESP32 Fake WiFi login page capturing passwords

## About this project

This project is a modification of https://github.com/adamff-dev/ESP8266-Captive-Portal

The programmed ESP32 chip creates an access point with any name that is used to capture passwords. Captured passwords are saved in the ESP32 memory and do not disappear after restarting/shutting down the device. When the new password is saved on the device, the LED will first flash 5 times and then turn on continuously. If you have the device in sight, you immediately know that you have a new password. Clearing the password in the login panel or restarting the device turns off the LED light.

I provide versions in English and Polish.

## Reservation

This project is of a testing and educational nature. Only use it so that you do not break the law. I take no responsibility for what you do with this program.

## Connection diagram

To build the device with ESP32-Fake-WiFi-login-page, I used the XIAO ESP32C3 module with an external WiFi antenna (any ESP32 module with an external or built-in antenna can be used). I also used a green LED (330 ohm resistor protects the LED from damage) and a USB-A to USB-C cable. I connected the diode to output 4. If we connect the LED to another output in our module, remember to change the led_gpio=4 parameter in the program to the appropriate one.

![ESP32-Fake-WiFi-login-page-Connection](https://github.com/ZrutrA/ESP32-Fake-WiFi-login-page/blob/main/ESP32-Fake-WiFi-login-page-Connection-v1.4.jpg)

I enclosed the assembled device in a housing printed on a 3D printer. 
I am sharing the ESP32 BOX-v1.stl file - throw it on a 3D printer and make an identical housing.

[![fot1](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/672de2bc-eaa3-467a-8633-c086c5b0617c)](https://github.com/ZrutrA/ESP32-Fake-WiFi-login-page/blob/main/fot1.jpg)

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

Connect your programmed esp32 module to the power supply. Search for and log in to an open Wi-Fi network called "Free WiFi" (or another one if you changed the name during programming). Find and click "Use this network as is" in the menu.
In your browser, go to 172.0.0.1/pass . Passwords will be visible there (if they are entered by people trying to log in to the access point).

![pass](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/65cd339a-011c-47a4-a990-e3840e6ea986)

If you click on "Index" you will see what the access point's home page looks like.

![index](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/fc16452e-c852-463b-8f13-caf5db87392b)

If you click "Change SSID" you will go to a subpage where you can change the network name of the access point.

![ssid](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/21155a40-538b-43b5-aad4-2023c474aaf5)

If you click "Clear Passwords" you will be able to clear the passwords saved on your device.

![clear](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/871341df-d318-4f31-bfc3-61934a300981)


