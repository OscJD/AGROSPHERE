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

/////////////////////////////////DECLARACIÓN DE VARABLES////////////////////////////
const byte PinLluvia = 3, PinAnemometro = 2; //Se declaran los pines de interrupción
int i=0;
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
float Voltajes[] = {2.53,1.3,1.48,0.27,0.29,0.21,0.6,0.4,0.92,0.78,2.03,1.93,3.05,2.66,3.15,2.26};
float Angulos[] = {0,22.5,45,67.5,90,112.5,135,157.5,180,202.5,225,247.5,270,292.5,315,337.5};
//////////////////////////////////////////////////////////////////
//float temperature=0,pascal=0;
//static float meters=0, metersold=0;
/////////////////////////////////////////////////////////////////
int factorAngulo=0;
//////////////////////////////////////////////////////////////// 
#define  volumen 0.2794
////////////////////////////////////////////////////////////////

void lluvia() 
{   
      tiempoLluvia=reloj;
      intervaloLluvia=(tiempoLluvia-tiempoAnteLluvia)*0.001;
      VelocidadLluvia=volumen/(intervaloLluvia);
      
}

/////////////////////////////////////////


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
   if (bme.begin());
    else
    {
        //while (1) {}
    }
  pinMode(PinLluvia, INPUT_PULLUP);
  pinMode(PinAnemometro, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PinLluvia), lluvia, FALLING);
  VelocidadLluvia=0;
  
}


void loop() 
{
  
  reloj=millis();
  tiempo=reloj/1000;
 while ( i < 10 ){ 
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
      
 
 if(i >= 10 && contador1 <1 ){  
  digitalWrite(4,HIGH);
  delay(50); 
///////////////////////////////////////////////////////////////
  if(contador1==0){
  LoRa.begin(915E6);
  bme.begin();
  }
    
 AnemoState = digitalRead(PinAnemometro);

 if (AnemoState==1 && lastAnemoState==0) {
    // si el estado cambio, el contador incrementa
      ContadorVueltas++;
      tiempoAnemo=reloj;
      intervaloAnemo=(tiempoAnemo-tiempoAnteAnemo)*0.001;
      VelocidadAnemo=0.5/(intervaloAnemo);
      }
 else{
  
  if(VelocidadAnemoAnte=VelocidadAnemo){
        ContadorVueltas++;
        }
  
  }
 if(ContadorVueltas>=4){  VelocidadAnemo=0;
                          ContadorVueltas=0;   
 }
 ///////////////////////////////////////////////////////////////////

  if(VelocidadLluviaAnte=VelocidadLluvia){
        ContadorLluvia++;
                                         }
 
  if(ContadorLluvia>=4){  VelocidadLluvia=0; 
                        ContadorLluvia=0;
                         }
  
// guarda el estado actual como el ultimo estado,
  lastAnemoState = AnemoState;
/////////////////////////////////////// 
 float temp(NAN), hum(NAN), pres(NAN);
 uint8_t pressureUnit(3);   
 bme.ReadData(pres, temp, hum, metric, pressureUnit); 
 float altitude = bme.CalculateAltitude(metric);
//////////////////////////////////////
a=analogRead(A3);
b=a*(0.00488);

  for(int i=0;i<=15;i++)
  {
  error=abs(b-Voltajes[i]);
  if(error<=0.02)
  {
  angulo=Angulos[i];  
  }
  }  

/////////////////////////////////////
c=analogRead(A1);
/////////////////////////////////////
int luz = analogRead(A0);
// print out the value you read:
  if( 0<=luz && luz<=600)
    {
    InLuz=1;
    }
  else if(600<luz && luz<=650)
    {
    InLuz=2;
     }
  else if( 650<luz )
    {
    InLuz=3;
     }
/////////////////////////////////////

 
  LoRa.beginPacket();
  LoRa.print(ID);
  LoRa.print(",");
  LoRa.print(int(hum));
  LoRa.print(",");
  LoRa.print(int(altitude));
  LoRa.print(",");
  LoRa.print(pres);
  LoRa.print(",");
  LoRa.print(temp);
  LoRa.print(",");
  LoRa.print(VelocidadAnemo);
  LoRa.print(",");
  LoRa.print(angulo);
  LoRa.print(",");
  LoRa.print(ContadorLluvia);
  LoRa.print(",");
  LoRa.print(VelocidadLluvia);
  LoRa.print(",");
  LoRa.print(InLuz);
  LoRa.print(",");
  LoRa.print(c);
  LoRa.print(",");
  LoRa.print(contador);
  LoRa.endPacket();
 /////////////////////////////////
 }
 else{
  i=0;
  Reset=tiempo;
     }
  tiempoReset=tiempo-Reset;
  tiempoAnteAnemo=tiempoAnemo;
  tiempoAnteLluvia=tiempoLluvia;
  VelocidadLluviaAnte=VelocidadLluvia;
  VelocidadAnemoAnte=VelocidadAnemo;
  contador++;
  contador1++;
}

