///////////////////////////////////  DECLARACIÓN DE LIBRERÍAS ////////////////////////
#include <avr/power.h>
#include <LowPower.h>
#include <SPI.h>
#include <LoRa.h>
#include <BME280.h>
BME280 bme;
bool metric = true;
///////////////////////////////////  ID DEL AGROSTICK  /////////////////////////////
int ID=15;
//int TiempoSleep=144;
int TiempoSleep=37;
//int TiempoSleep=;
int TiempoLectura=4;
int flag=0;
/////////////////////////////////DECLARACIÓN DE VARABLES////////////////////////////
const byte PinLluvia = 3, PinAnemometro = 2; //Se declaran los pines de interrupción
int i=0;
int battery=0;
/////////////////////////////////////////////////////////////////////
int AnemoState = 1;         // estado actual del pulsador
int lastAnemoState = 1;     // estado anterior del pulsador
int ContadorVueltas=0;
unsigned long contador=0, contador1=0;
int tiempoAnemo=0, tiempoAnteAnemo=0;
float VelocidadAnemo=0,intervaloAnemo=0;
////////////////////////////////////////////////////////////////////

int LluviaState = 1;         // estado actual del pulsador
int lastLluviaState = 1;     // estado anterior del pulsador
int ContadorLluvia=0;
int tiempoLluvia=0, tiempoAnteLluvia=0;
float VelocidadLluvia=0,intervaloLluvia=0;

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
//float b=0, angulo=0, error=0;
///////////////////////////////7
int c=0;
////////////////////////////////
//float Voltajes[] = {52,36,105,71,164,139,189,364,551,481,516,406,456,233,265,46};
//float Angulos[] = {0,22.5,45,67.5,90,112.5,135,157.5,180,202.5,225,247.5,270,292.5,315,337.5};
/////////////////////////////////////////////////////////////////
int factorAngulo=0;
//////////////////////////////////////////////////////////////// 
float temp(NAN), hum(NAN), pres(NAN);
////////////////////////////////////////////////////////////////
#define  volumen 0.2794
////////////////////////////////////////////////////////////////
int luzAnte=0,cAnte=0,batteryAnte=0;
float humAnte=0,tempAnte=0,presAnte=0,VelocidadAnemoAnte=0,anguloAnte=0,VelocidadLluviaAnte=0;

void lluvia() 
{   
      //tiempoLluvia=reloj;
      //intervaloLluvia=(tiempoLluvia-tiempoAnteLluvia)*0.001;
      //VelocidadLluvia=volumen/(intervaloLluvia);
      flag=1;
      
}

/////////////////////////////////////////


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
  pinMode(PinLluvia, INPUT_PULLUP);
  pinMode(PinAnemometro, INPUT_PULLUP);
  delay(50);
  LoRa.begin(915E6);
  bme.begin();
  attachInterrupt(digitalPinToInterrupt(PinLluvia), lluvia, FALLING);
  VelocidadLluvia=0;
 // Serial.begin(9600);
}


void loop() 
{

  if(contador<5){
    TiempoSleep=4;
    }
  else{
    TiempoSleep=37;
    }
  
  if(contador1==0 | flag==1){
  digitalWrite(4,HIGH);
  delay(50); 
  LoRa.begin(915E6);
  bme.begin();
  
 Serial.println("ya");   
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
      //Serial.println(ContadorVueltas);
      }
 lastAnemoState = AnemoState;

 ///////////////////////////////////////////////////////////////////

  if(VelocidadLluviaAnte=VelocidadLluvia){
        ContadorLluvia++;
                                         }
 
  if(ContadorLluvia>=4){  VelocidadLluvia=0; 
                        ContadorLluvia=0;
                         }
 }
 
if((contador1<1 && tiempoReset>=TiempoLectura)){
battery=analogRead(A0);
VelocidadAnemo=(ContadorVueltas);
a=analogRead(A1);
 // float Voltajes[]={0.66*b-18,0.41*b-5.7,1.16*b-12.5,0.75*b-2.7,1.8*b-21.5,1.5*b-10.5,4*b-32,3.7*b-34,6*b-54,5*b-45,5.6*b-55,4.3*b-31,5*b-55,2.5*b-17.5,3*b-30,0.5*b-2.5};
/*  
  for(int i=0;i<=15;i++)
  {
  error=abs(a-Voltajes[i]);
  if(error<=9)
  {
  angulo=Angulos[i];  
  }
  }*/  
//////////////////////////////////////

uint8_t pressureUnit(0);   
 bme.ReadData(pres, temp, hum, metric, pressureUnit); 

/////////////////////////////////////
c=analogRead(A3);
////////////////////////////////////
int luz = analogRead(A2);
/////////////////////////////////////

//  Serial.println(ya);
/*  Serial.print(",");
  Serial.print(int(hum));
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
  Serial.print(",");*/
 // Serial.println(long((VelocidadAnemo/(2*TiempoLectura))*2400));
  //Serial.println(",");
 // Serial.print(a);
 // Serial.print(",");
 // Serial.print(flag);
 // Serial.print(",");
  //Serial.println(contador);
//////////////////////////////////////////
if(abs(hum-humAnte)>=1 | abs(pres-presAnte)>=10 | abs(temp-tempAnte)>=1 | abs(luz-luzAnte)>=30 | abs(c-cAnte)>=50 | abs(VelocidadAnemo-VelocidadAnemoAnte)>=5 | flag==1 ){ 
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
  LoRa.print(long((VelocidadAnemo/(2*TiempoLectura))*2400));
  LoRa.print(",");
  LoRa.print(a);
  LoRa.print(",");
  LoRa.print(flag);
  LoRa.print(",");
  LoRa.print(contador);
  LoRa.endPacket();
}
///////////////////////////////////////////////////
  
  i=0;
  Reset=tiempo;
  contador++;
  contador1++;
  humAnte=hum;
  presAnte=pres;
  tempAnte=temp;
  luzAnte=luz;
  cAnte=c;
  batteryAnte=battery;
  VelocidadAnemoAnte=VelocidadAnemo;
  VelocidadLluviaAnte=VelocidadLluvia;
  flag=0;
  }
  }
/*  
  if(ContadorVueltas>0){
    //TiempoSleep=22;
    TiempoSleep=3;
    }
  */    
     
  while ( i < TiempoSleep && flag==0 ){ 
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
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
      i++;
      contador1=0;  
      }
   i=0;
}

