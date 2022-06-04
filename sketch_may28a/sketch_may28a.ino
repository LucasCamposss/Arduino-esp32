//Código incompleto, só comecei
const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;
const int motorLeitura = 35;

int leitura;
float tensao;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;


void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(pot, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motorLeitura,INPUT);

 // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution); 
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor1, ledChannel);
}

void loop() {
  // le um valor entre 0 e 4095
  leitura = ((analogRead(pot)-2)/8)-255; 
  if (leitura>-3 && leitura <3)
  {
    leitura = 0;
  }

  tensao = 0;
  
  for (int i=0; i<100;i++){
    tensao = tensao + (float(analogRead(motorLeitura)))/100;
    delay(1);
  }
  
  //passo o valor de leitura para -255 a 255
  motorPWM(leitura);
  Serial.println(tensao);
}

//função que passa o valor pwm para a ponte H 
void motorPWM (int valor)
{
  //Serial.println(valor);
  if (valor<0){
    valor = -valor; 
    // se valor for negativo gira o motor para o outro lado
    // preciso passar o valor para positivo
    if(valor > 255){
      valor = 255;
    }
    ledcWrite(ledChannel, valor);
    digitalWrite(motor2,LOW); 
  }
  else{
    if(valor > 255){
      valor = 255;
    }
    ledcWrite(ledChannel, 0);
    digitalWrite(motor2,LOW); 
}
}
