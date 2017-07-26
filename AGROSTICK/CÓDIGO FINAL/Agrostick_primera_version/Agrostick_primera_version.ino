///////////////////////////////////  DECLARACIÓN DE LIBRERÍAS ////////////////////////
#include <avr/power.h>
#include <LowPower.h>
#include <SPI.h>
#include <LoRa.h>
#include <BME280.h>
BME280 bme;
bool metric = true;
///////////////////////////////////  ID DEL AGROSTICK  /////////////////////////////
int ID=1;

/////////////////////////////////DECLARACIÓN DE VARABLES////////////////////////////
int i=0;
int contador1=0,contador=0;
////////////////////////////////////////////////////////////////////
//Variables para el reloj
unsigned long reloj= 0;
float tiempo=0,tiempoReset=0,Reset=0;
////////////////////////////////////////////////////////////////////
//Variables para el cálculo de la cantidad de luz
int luz=0,InLuz=0;
///////////////////////////////////////////////////////////////////
int c=0;
//////////////////////////////////////////////////////////////////

void setup()
{
  void clock_prescale_set (clock_div_t __2);
  //Serial.begin(115200);
  pinMode(4, OUTPUT);
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT); 
  pinMode(9, OUTPUT);  
  digitalWrite(4,HIGH);
  delay(50);
  LoRa.begin(915E6);
  bme.begin();
    
}


void loop() 
{
 
 while ( i < 9 ){ 
      digitalWrite(4,LOW);
       digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      SPI.end();
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
      i++;
      contador1=0;  
      
      }
      
 
 if(i >= 9 && contador1 <1 ){  
  digitalWrite(4,HIGH);
  delay(50); 
///////////////////////////////////////////////////////////////
  if(contador1==0){
  LoRa.begin(915E6);
  bme.begin();
  }
////////////////////////////////////// 
 float temp(NAN), hum(NAN), pres(NAN);
 uint8_t pressureUnit(0);   
 bme.ReadData(pres, temp, hum, metric, pressureUnit); 
 float altitude = bme.CalculateAltitude(metric);
/////////////////////////////////////
c=analogRead(A1);
/////////////////////////////////////
int luz = analogRead(A0);
/////////////////////////////////////

 
  LoRa.beginPacket();
  LoRa.print(ID);
  LoRa.print(",");
  LoRa.print(int(hum));
  LoRa.print(",");
  LoRa.print(int(pres));
  LoRa.print(",");
  LoRa.print(int(temp));
  LoRa.print(",");
  LoRa.print(luz);
  LoRa.print(",");
  LoRa.print(c);
  LoRa.print(",");
  LoRa.print(contador);
  LoRa.endPacket();
 /////////////////////////////////
 contador++;
 contador1++;
 }
 else{
  i=0;
     }
  
}

