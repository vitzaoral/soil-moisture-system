#include <Arduino.h>
#include <InternetConnection.h>
#include <SoilMoisture.h>
#include <Ticker.h>

const int sendDataToInternetInterval = 60000;

InternetConnection connection;

void sendDataToInternet();
Ticker timerSendDataToInternet(sendDataToInternet, sendDataToInternetInterval);

// Connections to APIs are OK
bool apisAreConnected = false;

void initializeInternetConnection()
{
    if (connection.initialize())
    {
        apisAreConnected = connection.initializeBlynk();
        connection.initializeOTA();
    }
}

void sendDataToInternet()
{
    if (apisAreConnected)
    {
        bool successBlynk = false;

        SoilMoistureStatus soilMoistureStatus = SoilMoisture::getSoilMoistureStatus();
        successBlynk = connection.sendSoilMoistureToBlynk(soilMoistureStatus);

        if (successBlynk)
        {
            Serial.println("Data was sent");
        }
        else
        {
            Serial.println("No internet connection, try initialize connection");
            apisAreConnected = false;
            initializeInternetConnection();
        }
    }
    else
    {
        initializeInternetConnection();
    }
}

void startTimers()
{
    timerSendDataToInternet.start();
}

void updateTimers()
{
    timerSendDataToInternet.update();
}

void setup()
{
    Serial.begin(9600);
    delay(100);
    SoilMoisture::initialize();
    initializeInternetConnection();
    startTimers();
}

void loop()
{
    updateTimers();
    connection.runBlynk();
    connection.handleOTA();
}