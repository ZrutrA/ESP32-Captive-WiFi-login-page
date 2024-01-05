# ESP32-WiFi-Captive-Portal

## About this project

This project is a modification of https://github.com/adamff-dev/ESP8266-Captive-Portal

The programmed ESP32 chip creates an access point with any name that is used to capture passwords.
Captured passwords are saved in the ESP32 memory and do not disappear after restarting/turning off the device.
The built-in LED will flash 5 times after entering the password.
I provide versions in English and Polish.

## Reservation

This project is of a testing and educational nature. Only use it so that you do not break the law. I take no responsibility for what you do with this program.

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
![Screenshot_20240105-223704](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/ff16ff96-f526-4ff8-b0e5-c6f3ada0f497)

If you click on "Index" you will see what the access point's home page looks like.
![Screenshot_20240105-223603](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/75ed4f2f-aa30-4ea3-871f-3f5b0e0b9611)

If you click "Change SSID" you will go to a subpage where you can change the network name of the access point.
![Screenshot_20240105-223714](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/280dee60-4359-4498-b9e1-f6b71c4adcbc)

If you click "Clear Passwords" you will be able to clear the passwords saved on your device.
![Screenshot_20240105-223725](https://github.com/ZrutrA/ESP32-WiFi-Captive-Portal/assets/155777818/f3d2e050-a4a3-4d86-88a7-2d71279f06de)

