<h1 align="center">ESP8266-WIoT</h1>
<h3 align="center">This sketch was written for WIoT project that can be found here:</h3>
<h3 align="center">https://github.com/hntirgeam/WIoT-Logger</h3>

<ol>
  
  <li><a href="#how-to">How to</a></li>
  <li><a href="#used-libraries">Used libraries</a></li>
  <li><a href="#wiring">Wiring</a></li>
</ol>

## How to
1) Download Arduino IDE from [here](https://www.arduino.cc/en/software)
2) In your Arduino IDE, go to File > Preferences
3) Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into the “Additional Boards Manager URLs”
4) Open the Boards Manager. Go to `Tools > Board > Boards Manager. Search for ESP8266 and press install button
5) Open `.ino` file
6) Edit `#define` fields to match your settings
7) In `Tools > Board > ESP8266 Boards` select your board (I, for example, use NodeMCU)
8) Connect your board to PC. Select corresponding COM-port
9) Press little arror in top left corner to upload sketch


## Used libraries
* [Adafruit BME280 Library](https://github.com/adafruit/Adafruit_BME280_Library)
* [WifWaf MH-Z19 Library](https://github.com/WifWaf/MH-Z19)

## Wiring


![alt text](https://user-images.githubusercontent.com/56179857/146787587-48fcf983-f65b-49f8-b840-845956b0c13a.jpg)
