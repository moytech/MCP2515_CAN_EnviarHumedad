/*

Display sensor dht11

Practicas CAN con módulo MCP2515  https://github.com/moytech

Este programa recibe la temperatura y humedad de un sensor DHT11. Se muestra en
un display con módulo I2C. Se recibe por el protocolo CAN bus con ayuda del módulo MCP2515.
También se muestra en serial monitor.

Autor: Moytech
github: https://github.com/moytech
Programa: Display sensor dht11
Fecha: Julio 2024

*/

#include <SPI.h>
#include <mcp2515.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CS 10
int temprec, humrec;

struct can_frame datareceive;
MCP2515 mcp2515(CS);

void setup() 
{
  Serial.begin(9600);                                   //iniciar serial monitor
  SPI.begin();                                          //iniciar SPI
  mcp2515.reset();                                      //reset MCP2515
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);            //configuración CAN bus
  mcp2515.setNormalMode();                              //modo normal
  lcd.init();                                           //iniciar lcd
  lcd.backlight();                                      //led lcd on
}

void loop() 
{
  if(mcp2515.readMessage(&datareceive)== MCP2515::ERROR_OK)
  {
    temprec= datareceive.data[0];                         //temperatura
    humrec= datareceive.data[1];                          //humedad
    
    Serial.println("Datos recibidos: ");                  //imprimir en serial monitor
    Serial.print("Temperatura: ");
    Serial.println(datareceive.data[0]);
    Serial.print("Humedad: ");
    Serial.println(datareceive.data[1]);

    lcd.clear();                                          //configuración de lcd
    lcd.setCursor(0, 0);
    lcd.print(temprec);                                   //temperatura en lcd
    lcd.print(" Temp");
    lcd.setCursor(0, 1);
    lcd.print(humrec);                                    //humedad en lcd
    lcd.print(" %");
  }
}
