#include <Arduino.h>
#include "RF24.h"
#include <SPI.h>
#include "DigitalIO.h"



RF24 myRadio(11, 12); // in Mega can use> (48, 49);
byte addresses[][6] = {"0"};

//ESTRUCTURA PAQUETE RECIBIDO

struct package
{
  int humedad;
  long resistencia;
  long temperatura;
};

typedef struct package Package;
Package data;

void setup()
{
  Serial.begin(9600);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop()
{

  if (myRadio.available())
  {
    while (myRadio.available())
    {
      myRadio.read(&data, sizeof(data));
    }

    Serial.print("Package : ");
    Serial.print("\n");

    Serial.print("Resistencia = ");
    Serial.print(data.resistencia);

    Serial.print("Humedad = ");
    Serial.print(data.humedad);

    Serial.print("Temperatura = ");
    Serial.print(data.temperatura);
    Serial.print("\n");
  }
}