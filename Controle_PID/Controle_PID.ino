#include "esp_adc_cal.h"

const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;
const int motorLeitura = 26;
int leitura;
float tensao;
float entrada;

float alvo;
float erro;
float erro0;
float sumErro;
float kp;
float ki;
float kd;
float valorPID;

const int freq = 20000;
const int ledChannel = 0;
const int resolution = 12;

void setup() {
  Serial.begin(115200);
  pinMode(pot, INPUT);
  pinMode(motorLeitura,INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  
  ledcSetup(ledChannel, freq, resolution); 
  ledcAttachPin(motor1, ledChannel);

  alvo = 3.0;
  kp = 0.001;
  ki = 0.00;
  kd = 0.00;
  valorPID = 0;
  erro0 = 0;
  sumErro = 0;
  entrada = 0;
}
  
void loop() {
  if (Serial.available() > 0) {
    // lê do buffer o dado recebido:
    alvo = (Serial.readString()).toFloat();
  }
  if (alvo<=0){
    alvo = 0.00001;
  }
  tensao = float(analogRead(motorLeitura));
  tensao = 2*readADC_Cal(tensao)*0.001;
  
  erro = (alvo - tensao)/alvo;
  ajustaPID(erro, &valorPID, &sumErro, &erro0, kp, ki, kd);
  
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


void ajustaPID (float erro,float *valorPID,float *sumErro,float *erro0,float kp,float ki,float kd)
{   
    *valorPID = erro*kp + *sumErro*ki + (erro - *erro0)*kd;
    *sumErro += erro;
    *erro0 = erro;
}


uint32_t readADC_Cal(int ADC_Raw)
{
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1000, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}
