const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;
const int motorLeitura = 35;
int leitura;
float tensao;

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

  alvo = 2000;
  kp = 1;
  ki = 0;
  kd = 0;
  valorPID = 0;
  erro0 = 0;
  sumErro = 0;
}
  
void loop() {
  tensao = float(analogRead(motorLeitura));
  erro = alvo - tensao;
  ajustaPID(erro, &valorPID, &sumErro, &erro0, kp, ki, kd);
  
//  Serial.println(tensao);
  motorPWM(valorPID); 
}


void motorPWM (int valor)
{   
    if(valor>4095){
      valor = 4095;
      }
    ledcWrite(ledChannel, valor);
    digitalWrite(motor2,LOW); 
}


void ajustaPID (float erro,float *valorPID,float *sumErro,float *erro0,float kp,float ki,float kd)
{   
    *valorPID = erro*kp + *sumErro*ki + (erro - *erro0)*kd;
    *sumErro += erro;
    *erro0 = erro;
}
