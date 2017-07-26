///////////////////////////////////  DECLARACIÓN DE LIBRERÍAS ////////////////////////
#include <avr/power.h>
#include <LowPower.h>
#include <SPI.h>
#include <LoRa.h>
#include <BME280.h>
BME280 bme;
bool metric = true;
///////////////////////////////////  ID DEL AGROSTICK  /////////////////////////////
int ID=10;
int TiempoSleep=5;
int TiempoLectura=5;
int flag=0;
/////////////////////////////////DECLARACIÓN DE VARABLES////////////////////////////
const byte PinLluvia = 3, PinAnemometro = 2; //Se declaran los pines de interrupción
int i=0;
int battery=0;
/////////////////////////////////////////////////////////////////////
int AnemoState = 1;         // estado actual del pulsador
int lastAnemoState = 1;     // estado anterior del pulsador
int ContadorVueltas=0;
int contador=0, contador1=0;
int tiempoAnemo=0, tiempoAnteAnemo=0;
float VelocidadAnemo=0,intervaloAnemo=0,VelocidadAnemoAnte=0;
////////////////////////////////////////////////////////////////////

int LluviaState = 1;         // estado actual del pulsador
int lastLluviaState = 1;     // estado anterior del pulsador
int ContadorLluvia=0;
int tiempoLluvia=0, tiempoAnteLluvia=0;
float VelocidadLluvia=0,intervaloLluvia=0,VelocidadLluviaAnte=0;

////////////////////////////////////////////////////////////////////
//Variables para el reloj
unsigned long reloj= 0;
float tiempo=0,tiempoReset=0,Reset=0;
////////////////////////////////////////////////////////////////////
//Variables para el cálculo de la cantidad de luz
int luz=0,InLuz=0;
///////////////////////////////////////////////////////////////////
//Variables para obtener la posición de la veleta
int a=0;
float b=0, angulo=0, error=0;
///////////////////////////////7
int c=0;
////////////////////////////////
//float Voltajes[] = {2.53,1.3,1.48,0.27,0.29,0.21,0.6,0.4,0.92,0.78,2.03,1.93,3.05,2.66,3.15,2.26};
float Voltajes[] = {968,615,647,250,295,129,189,66,95,85,475,417,805,720,908,847};
float Angulos[] = {0,22.5,45,67.5,90,112.5,135,157.5,180,202.5,225,247.5,270,292.5,315,337.5};
//////////////////////////////////////////////////////////////////
//float temperature=0,pascal=0;
//static float meters=0, metersold=0;
/////////////////////////////////////////////////////////////////
int factorAngulo=0;
//////////////////////////////////////////////////////////////// 
float temp(NAN), hum(NAN), pres(NAN);
////////////////////////////////////////////////////////////////
#define  volumen 0.2794
////////////////////////////////////////////////////////////////

void lluvia() 
{   
      tiempoLluvia=reloj;
      intervaloLluvia=(tiempoLluvia-tiempoAnteLluvia)*0.001;
      VelocidadLluvia=volumen/(intervaloLluvia);
      flag=1;
      
}

/////////////////////////////////////////


void setup()
{
  void clock_prescale_set (clock_div_t __2);
  Serial.begin(9600);
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
  pinMode(PinLluvia, INPUT_PULLUP);
  pinMode(PinAnemometro, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PinLluvia), lluvia, FALLING);
  VelocidadLluvia=0;
}


void loop() 
{
  
  if(contador1==0){
  digitalWrite(4,HIGH);
  delay(30); 
  LoRa.begin(915E6);
  bme.begin();
  }
    
 while(tiempoReset<TiempoLectura ){  
  reloj=millis();
  tiempo=reloj/1000;
  tiempoReset=tiempo-Reset;
  //Serial.println(tiempoReset);
///////////////////////////////////////////////////////////////
 
 AnemoState = digitalRead(PinAnemometro);

 if ((AnemoState==1 && lastAnemoState==0)) {
    // si el estado cambio, el contador incrementa
      ContadorVueltas++;
      Serial.println(ContadorVueltas);
      }
 lastAnemoState = AnemoState;

 ///////////////////////////////////////////////////////////////////

  if(VelocidadLluviaAnte=VelocidadLluvia){
        ContadorLluvia++;
                                         }
 
  if(ContadorLluvia>=4){  VelocidadLluvia=0; 
                        ContadorLluvia=0;
                         }
  
// guarda el estado actual como el ultimo estado,
  
/////////////////////////////////////// 
 }
 
if((contador1<1 && tiempoReset>=TiempoLectura)){

  VelocidadAnemo=ContadorVueltas/10;

 a=analogRead(A1);

  for(int i=0;i<=15;i++)
  {
  error=abs(a-Voltajes[i]);
  if(error<=5)
  {
  angulo=Angulos[i];  
  }
  }  
//////////////////////////////////////

uint8_t pressureUnit(0);   
 bme.ReadData(pres, temp, hum, metric, pressureUnit); 

/////////////////////////////////////
c=analogRead(A3);
////////////////////////////////////
int luz = analogRead(A2);
/////////////////////////////////////
battery=analogRead(A0);
///////////////////////////////////

 /*
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
  LoRa.print(VelocidadAnemo);
  LoRa.print(",");
  LoRa.print(angulo);
  LoRa.print(",");
  LoRa.print(VelocidadLluvia);
  LoRa.print(",");
  LoRa.print(contador);
  LoRa.endPacket();
 /////////////////////////////////
*/
  Serial.print(ID);
  Serial.print(",");
  /*Serial.print(int(hum));
  Serial.print(",");
  Serial.print(long(pres));
  Serial.print(",");
  Serial.print(int(temp));
  Serial.print(",");
  Serial.print(luz);
  Serial.print(",");
  Serial.print(c);
  Serial.print(",");
  Serial.print(battery);
  Serial.print(",");
 */ Serial.print(VelocidadAnemo);
  Serial.print(",");
  Serial.print(angulo);
  Serial.print(",");
  Serial.print(intervaloLluvia);
  Serial.print(",");
  Serial.println(contador);
  i=0;
  Reset=tiempo;
  contador++;
  contador1++;
  flag=0;
  }
  
  
     
  while ( i < TiempoSleep ){ 
      tiempoReset=tiempo-Reset;
  tiempoAnteAnemo=tiempoAnemo;
  tiempoAnteLluvia=tiempoLluvia;
  VelocidadLluviaAnte=VelocidadLluvia;
  ContadorVueltas=0;
      digitalWrite(4,LOW);
      digitalWrite(13,LOW);
      digitalWrite(12,LOW);
      digitalWrite(11,LOW);
      digitalWrite(10,LOW);
      digitalWrite(9,LOW);
      SPI.end();
      LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);  
      i++;
      contador1=0;  
      
      }
      
}

