# Přístroj na měrení stavu pacienta
Cílem mého projektu je vytvořit přístroj k měření teploty a vlhkosti v místnosti plus teplotu, tep a úroveň kyslíku v krvi pacienta. Přístroj bude informace posílat skrze MQTT na server a přehledně zobrazovat.

Součástky:
1. ESP32 ✔
2. MAX30100 Čidlo pulzu a kyslíku v krvi ✔
3. DS18B20 teplotní čídlo ✔
-https://www.digikey.cz/en/blog/types-of-temperature-sensors
4. DHT11 Čidlo vlhkosti vzduchu ✔

Inspirace:
-https://circuitdigest.com/microcontroller-projects/iot-based-patient-monitoring-system-using-esp8266-and-arduino

https://www.projectsof8051.com/arduino-and-iot-based-patient-health-monitoring-system-project/

Pracovní plán:
 -15.10 - Čekání na součástky(není určeno kdy dorazí), začátek psaní kódu a MQTT serveru
 15.10-14.11 - Sestavování obvodu a spojení s MQTT serverem, tvorba prezentace, dokumentace
 14.11-neurčito - Dokončování projektu 
