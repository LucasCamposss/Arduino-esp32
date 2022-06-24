//Código de malha aberta
const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;
const int motorLeitura = 35;
int leitura;
float tensao;

// setting PWM properties
const int freq = 30000;
const int ledChannel = 0;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
//  Serial.println("Hello, ESP32!");
  pinMode(pot, INPUT);
  pinMode(motorLeitura,INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  
 // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution); 
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(motor1, ledChannel);
}

void loop() {
  // le um valor entre 0 e 4095
  //Serial.println(analogRead(pot));
  leitura = ((analogRead(pot))/16); //passa a leitura pra um valor entre 0 e 255
  if (leitura <15)
  {
    leitura = 0;
  }
  
  /* 
  if (leitura >15)
  {
    leitura = 255;
  }
   
 */
  tensao = analogRead(motorLeitura);
  tensao = 2*tensao/1241;//passando o valor da leitura binaria de 12 bits para um valor em volts(a leitura é de até 3.3V)
  //multipliquei por 2 pq foi feito um divisor de tensão na entrada da porta usada na leitura 
  Serial.println(tensao);
 // Serial.println(leitura);
  //passo o valor de leitura para 0 a 255
  motorPWM(leitura);
}



//função que passa o valor pwm para a ponte H 
void motorPWM (int valor)
{
    if(valor > 255){
      valor = 255;
    }
    if(valor < 0){
      valor = 0;
    }
    ledcWrite(ledChannel, valor);
    digitalWrite(motor2,LOW); 
}
