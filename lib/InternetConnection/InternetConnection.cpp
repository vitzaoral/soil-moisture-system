#include "InternetConnection.h"
#include <BlynkSimpleEsp8266.h>
#include "../../src/settings.cpp"

// Blynk virtual pins:
// V1 - water level (long)
// V20 - water distance (long)
// V2 - pump 1
// V3 - pump 2

// MoistureStatus balcoony
// V4, V5, V6, V7, V8

// MoistureStatus bedroom
// V9, V10, V11, V12, V13, V14, V15

// Meteo Data
// V16 - temperature
// V17 - humidity
// V18 - presure
// V19 - meteo data status

// WIFI - balcony system
// V21 - IP address
// V22 - WIFI signal strength

// WIFI - bedroom system
// V23 - IP address
// V24 - WIFI signal strength

WiFiClient client;
Settings settings;

const char *ssid = settings.ssid;
const char *password = settings.password;
const char *blynkAuth = settings.blynkAuth;

// number of attempts to connecting WIFI, API etc.
const int timeout = 10;

// Initialize WiFi connection. Return true if connection is sucessfull.
bool InternetConnection::initialize(void)
{
    WiFi.begin(ssid, password);

    Serial.print("WiFi connecting to: ");
    Serial.println(ssid);
    int i = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        if (i == timeout)
        {
            Serial.println("Timeout on WiFi connection");
            return false;
        }
        i++;
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Wifi signal stregth: ");
    Serial.println(WiFi.RSSI());

    return true;
}

// Initialize WiFi connection and Blynk. Return true if connection is sucessfull.
bool InternetConnection::initializeBlynk(void)
{
    Serial.println("WiFi connecting to Blynk");
    Blynk.config(blynkAuth);

    // timeout 3sec
    Blynk.connect(1000);

    if (Blynk.connected())
    {
        Blynk.run();
    }

    Serial.println(Blynk.connected() ? "Blynk connected" : "Timeout on or internet connection");
    bool connected = Blynk.connected();

    if (connected)
    {
        // send local IP address and WIFI signal stregth
        Blynk.virtualWrite(V23, WiFi.localIP().toString());
        Blynk.virtualWrite(V24, WiFi.RSSI());
    }
    return connected;
}

void InternetConnection::runBlynk(void)
{
    Blynk.run();
}

bool InternetConnection::sendSoilMoistureToBlynk(SoilMoistureStatus status)
{
    if (Blynk.connected())
    {
        Blynk.virtualWrite(V9, status.A);
        Blynk.virtualWrite(V10, status.B);
        Blynk.virtualWrite(V11, status.C);
        Blynk.virtualWrite(V12, status.D);
        Blynk.virtualWrite(V13, status.E);
        Blynk.virtualWrite(V14, status.F);
        Blynk.virtualWrite(V15, status.G);
        Serial.println("Send moisture status to Blynk OK");
        Blynk.run();
        return true;
    }
    else
    {
        Serial.println("Blynk is not connected.");
        return false;
    }
}

// Run OTA in loop
void InternetConnection::handleOTA(void)
{
    ArduinoOTA.handle();
}

void InternetConnection::initializeOTA(void)
{
    ArduinoOTA.setHostname(settings.hostNameOTA);
    ArduinoOTA.setPassword(settings.passwordOTA);
    ArduinoOTA.begin();
}