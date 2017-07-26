///////////////////////////////////  DECLARACIÓN DE LIBRERÍAS ////////////////////////
#include <avr/power.h>
#include <LowPower.h>
#include <SPI.h>
#include <LoRa.h>
#include <BME280.h>
BME280 bme;
bool metric = true;
///////////////////////////////////  ID DEL AGROSTICK  /////////////////////////////
int ID=8;
int tiempo=144;
//int tiempo=3;
/////////////////////////////////DECLARACIÓN DE VARABLES////////////////////////////
int i=0;
int contador1=0;
long contador=0;
///////////////////////////////////////////////////////////////////
//Variables para el cálculo de la cantidad de luz
int luz=0;
///////////////////////////////////////////////////////////////////
int c=0;
//////////////////////////////////////////////////////////////////
float temp(NAN), hum(NAN), pres(NAN);

////////////////////////////////////////////////////////////////////
int luzAnte=0,cAnte=0,battery=0;
float tempAnte=0,humAnte=0,presAnte=0,batteryAnte=0;

void setup()
{
  void clock_prescale_set (clock_div_t __2);
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
  Serial.begin(9600);  
}


void loop() 
{
 
 if( contador1 <1 ){ 
  Serial.println("ya"); 
  digitalWrite(4,HIGH);
  delay(50); 
///////////////////////////////////////////////////////////////
  if(contador1==0){
  LoRa.begin(915E6);
  bme.begin();
  }
////////////////////////////////////// 

 uint8_t pressureUnit(0);   
 bme.ReadData(pres, temp, hum, metric, pressureUnit); 
/////////////////////////////////////
c=analogRead(A3);
/////////////////////////////////////
int luz = analogRead(A2);
/////////////////////////////////////
battery=analogRead(A0);

if(abs(hum-humAnte)>=1 | abs(pres-presAnte)>=10 | abs(temp-tempAnte)>=1 | abs(luz-luzAnte)>=50 | abs(c-cAnte)>=50 ){ 
  LoRa.beginPacket();
  LoRa.print(ID);
  LoRa.print(",");
  LoRa.print(int(hum));
  LoRa.print(",");
  LoRa.print(long(pres));
  LoRa.print(",");
  LoRa.print(int(temp));
  LoRa.print(",");
  LoRa.print(luz);
  LoRa.print(",");
  LoRa.print(c);
  LoRa.print(",");
  LoRa.print(battery);
  LoRa.print(",");
  LoRa.print(contador);
  LoRa.endPacket();
}
 /////////////////////////////////
 contador++;
 contador1++;
 humAnte=hum;
 presAnte=pres;
 tempAnte=temp;
 luzAnte=luz;
 cAnte=c;
 batteryAnte=battery;
 }
 else{
  contador1=0;
     }

 while ( i < tiempo ){ 
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
  i=0;  
  
}

