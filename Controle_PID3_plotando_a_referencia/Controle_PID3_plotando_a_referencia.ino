#include "esp_adc_cal.h"

const int pot = 34;
const int motor1 = 27;
const int motor2 = 33;
const int motorLeitura = 26;
const int pinoSaida = 18;
const int dacPin = 25;

int leitura;
float tensao;
float entrada;
int numCont;

float alvo;
float erro;
float erro0;
float sumErro;
float kp;
float ki;
float kd;
float valorPID;
float T;
float TD;
int cont;

const int freq = 20000;
const int ledChannel = 0;
const int resolution = 12;

void setup() {
  
  pinMode(pot, INPUT);
  pinMode(motorLeitura,INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(pinoSaida, OUTPUT);
  pinMode(dacPin, OUTPUT);  
  ledcSetup(ledChannel, freq, resolution); 
  ledcAttachPin(motor1, ledChannel);

  alvo = 3.0;
//Variando valores encontrados
//  kp = 1.593;
//  ki = 30.2;
//  kd = 0.021;
  kp = 5.429;
  ki = 10.59;
  kd = 0.015;
  //-------------------------
  valorPID = 0;
  erro0 = 0;
  sumErro = 0;
  entrada = 0;
  T = 0.000062;
  TD = 1/T;
  cont = 1;
  numCont = 20000;
}
  
void loop() {
  if (cont<=numCont){
    alvo = 3.0;
    cont++;
    dacWrite(dacPin,240);
    }
  else{
    alvo = 2.0;
    cont++;
    dacWrite(dacPin,159);
    if(cont>=numCont*2)
    {
      cont=1;
     }
    }
 
  tensao = float(analogRead(motorLeitura));
  tensao = 2*readADC_Cal(tensao)*0.001;
  
  erro = (alvo - tensao)/alvo;
  ajustaPID(erro, &valorPID, &sumErro, &erro0, kp, ki, kd,T,TD);
  
  entrada = entrada+valorPID;
  if(entrada>1){
    entrada = 1;
  }
  if(entrada<0){
    entrada = 0;
  }
  motorPWM(entrada); 
}


void motorPWM (float valor)
{   
    if(valor>1){
      valor = 1;
    }
    if(valor<0){
      valor = 0;
    }
    valor = valor*4095;
         
    ledcWrite(ledChannel, valor);
    digitalWrite(motor2,LOW); 
}


void ajustaPID (float erro,float *valorPID,float *sumErro,float *erro0,float kp,float ki,float kd, float T, float T2)
{   
    *valorPID = erro*kp + *sumErro*ki*T + (erro - *erro0)*kd*T2;
    *sumErro += erro;
    *erro0 = erro;
}


uint32_t readADC_Cal(int ADC_Raw)
{
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1000, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}
