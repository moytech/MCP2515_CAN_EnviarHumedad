/*

Sensor dht11

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa envía la temperatura y humedad de un sensor DHT11. Se muestra en el 
Serial monitor. Se envía por el protocolo CAN bus con ayuda del módulo MCP2515 
y lo recibe otro módulo para mostrarlo en un display.

Autor: Moytech
github: https://github.com/moytech
Programa: Sensor dht11
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>
#include "DHT.h"
DHT dht;
#define CS 10

struct can_frame datasend;
MCP2515 mcp2515(CS);                                        

int sensor= 2;                                              //sensor en pin 2
float temp, hum;

void setup() 
{
  Serial.begin(9600);                                       //iniciar serial monitor
  SPI.begin();                                              //iniciar SPI
  mcp2515.reset();                                          //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);                //configuración CAN bus
  mcp2515.setNormalMode();                                  //modo normal
  dht.setup(sensor);                                        //configuración dht11
}

void loop() 
{
  hum= dht.getHumidity();                                   //humedad
  temp= dht.getTemperature();                               //temperatura
  datasend.can_id= 0x11;                                    //CAN id
  datasend.can_dlc= 2;                                      //2 bytes
  datasend.data[0]= (int) temp;                             //temp en byte[0]
  datasend.data[1]= (int) hum;                              //hum en byte[1]
  mcp2515.sendMessage(&datasend);                           //enviar datos

  Serial.println("Enviar datos: ");                         //imprimir en monitor serial
  Serial.print("Temperatura: ");
  Serial.println(datasend.data[0]);
  Serial.print("Humedad: ");
  Serial.println(datasend.data[1]);

  delay(5000);                                              //esperar 5 seg.
}
