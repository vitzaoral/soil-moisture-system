# Soil moisture system
IoT soil moisture system based on ESP8266 Wemos D1 Mini. Use resitance soil moisture sensors, data are send to Blynk.
Project is free to use, coded in C++, created in Visual Code with [PlatfomIO IDE](http://docs.platformio.org/en/latest/ide/vscode.html).

> To build a project, you need to download all the necessary libraries and create the *settings.cpp* file in the src folder:
```c++
// Watering system project settings
struct Settings
{
    const char *ssid = "WIFI ssid";
    const char *password = "WIFI password";
    const char *blynkAuth = "blynkAuth";
};
```

### Soil moisture sensor corrosion problem
After some time you realize that the sensor provides drier and drier results, even if the soil is wet. It is because of corrosion caused by electrolysis. The copper atoms on the positive electrode are being ionised, transported via the soil's water content across to the negative electrode where they are being deposited and returning to being copper atoms. This explains why the negative electrode looks surprisingly clean for having been buried - the top layer of atoms are recently deposited and likely very pure (in picture). To avoid this you have some choices:
* Use AC instead of DC
* Use [capacitive sensors](https://www.aliexpress.com/item/NEW-Capacitive-soil-moisture-sensor-not-easy-to-corrode-wide-voltage-wire-for-arduino/32832538686.html) instead of resistance (they are more expensive)
* When use DC, power on sensor only when data are readed. It will reduce the speed of corrosion (as electrolytic corrosion will be faster than that of unpowered copper) but it will not prevent it in the long-run. I use MOSFET for switch ON/OFF sensors

![Electrolysis corrosion](https://github.com/vitzaoral/soil-moisture-system/blob/master/schema/corrosion.jpg)

### Currents list:
* [Wemos D1 Mini](https://www.aliexpress.com/item/D1-mini-V2-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/32681374223.html)
* [7x Soil Moisture Sensor](https://www.aliexpress.com/item/Smart-Electronics-Soil-Moisture-Hygrometer-Detection-Humidity-Sensor-Module-For-arduino-Development-Board-DIY-Robot-Smart/32562744759.html)
* [Mosfet IRF520](https://www.aliexpress.com/item/20PCS-IRF520-TO-220-IRF520N-TO220-IRF520NPBF-free-shipping/32715603916.html)
* [74HC4051 Multiplexer](https://www.aliexpress.com/item/10PCS-LOT-CD4051BE-CD4051-4051BE-4051-DIP16-new-and-original-IC/32807746646.html)

### Schema:
![Schema](https://github.com/vitzaoral/soil-moisture-system/blob/master/schema/soil-moisture-system-schema.jpg)

### PCB circuit:
![PCB 1](https://github.com/vitzaoral/soil-moisture-system/blob/master/schema/pcb_1.jpg)

![PCB 2](https://github.com/vitzaoral/soil-moisture-system/blob/master/schema/pcb_2.jpg)

### Blynk:
![Blynk](https://github.com/vitzaoral/soil-moisture-system/blob/master/schema/blynk.png)