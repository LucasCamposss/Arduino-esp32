const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;
const int motorLeitura = 35;
int leitura;
float tensao;


const int freq = 30000;
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
}
  
void loop() {
  leitura = float((analogRead(pot)));
  tensao = analogRead(motorLeitura);
  tensao = 2*tensao/1241;
  Serial.println(tensao);
  motorPWM(leitura);
}
void motorPWM (int valor)
{
    if(valor > 4095){
      valor = 4095;
    }
    if(valor < 0){
      valor = 0;
    }
    ledcWrite(ledChannel, valor);
    digitalWrite(motor2,LOW); 
}
