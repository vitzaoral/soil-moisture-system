#include "SoilMoisture.h"

// PINS
#define MUX_A D6
#define MUX_B D7
#define MUX_C D8
#define MOSFET D3
#define ANALOG_INPUT A0

void SoilMoisture::initialize()
{
    // set pinmodes
    pinMode(MUX_A, OUTPUT);
    pinMode(MUX_B, OUTPUT);
    pinMode(MUX_C, OUTPUT);
    pinMode(MOSFET, OUTPUT);
}

void SoilMoisture::changeMux(int c, int b, int a)
{
    digitalWrite(MUX_A, a);
    digitalWrite(MUX_B, b);
    digitalWrite(MUX_C, c);
}

int SoilMoisture::getMoistureValueFromAnalogValue(float value)
{
    // map(hodnota, minimumPůvodníStupnice, maximumPůvodníStupnice, minimumNovéStupnice, maximumNovéStupnice);
    int result = map(value, 1024, 300, 0, 100);
    Serial.print(" Humidity: ");
    Serial.println(result);
    return result;
}

SoilMoistureStatus SoilMoisture::getSoilMoistureStatus()
{
    SoilMoistureStatus status = {0, 0, 0, 0, 0, 0, 0};

    digitalWrite(MOSFET, HIGH);
    Serial.println("Soil moisture sensors ON");
    delay(2000);

    changeMux(LOW, LOW, LOW);
    int value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 0 pin of Mux
    Serial.print(" Analog value X0/A: ");
    Serial.println(value);
    status.A = getMoistureValueFromAnalogValue(value);

    changeMux(LOW, LOW, HIGH);
    value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 1 pin of Mux
    Serial.print(" Analog value X1/B: ");
    Serial.println(value);
    status.B = getMoistureValueFromAnalogValue(value);

    changeMux(LOW, HIGH, LOW);
    value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 2 pin of Mux
    Serial.print(" Analog value X2/C: ");
    Serial.println(value);
    status.C = getMoistureValueFromAnalogValue(value);

    changeMux(LOW, HIGH, HIGH);
    value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 3 pin of Mux
    Serial.print(" Analog value X3/D: ");
    Serial.println(value);
    status.D = getMoistureValueFromAnalogValue(value);

    changeMux(HIGH, LOW, LOW);
    value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 4 pin of Mux
    Serial.print(" Analog value X4/E: ");
    Serial.println(value);
    status.E = getMoistureValueFromAnalogValue(value);

    changeMux(HIGH, LOW, HIGH);
    value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 5 pin of Mux
    Serial.print(" Analog value X5/F: ");
    Serial.println(value);
    status.F = getMoistureValueFromAnalogValue(value);

    changeMux(HIGH, HIGH, LOW);
    value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 6 pin of Mux
    Serial.print(" Analog value X6/G: ");
    Serial.println(value);
    status.G = getMoistureValueFromAnalogValue(value);

    // changeMux(HIGH, HIGH, HIGH);
    // value = analogRead(ANALOG_INPUT); //Value of the sensor connected Option 7 pin of Mux

    digitalWrite(MOSFET, LOW);
    Serial.println("Soil moisture sensors OFF");

    return status;
}
