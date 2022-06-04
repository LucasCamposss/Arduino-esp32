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
  leitura = ((analogRead(pot))/16); 
  if (leitura <15)
  {
    leitura = 0;
  }
  tensao = 0; 
  // tentando melhorar a leitura que está variando muito(fazendo a média das ultimas 100)
  for (int i=0; i<100;i++){
    tensao = tensao + (float(analogRead(motorLeitura)))/100;
    delay(1);
  }
  
  tensao = 2*tensao/1241;//passando o valor da leitura binaria de 12 bits para um valor em volts(a leitura é de até 3.3V)
  //multipliquei por 2 pq foi feito um divisor de tensão na entrada da porta usada na leitura 
  Serial.println(tensao);
  Serial.println(leitura);
  //passo o valor de leitura para -255 a 255
  motorPWM(leitura);

}



//função que passa o valor pwm para a ponte H 
void motorPWM (int valor)
{
  if (valor>0){ 
    // se valor for negativo gira o motor para o outro lado
    // preciso passar o valor para positivo
    if(valor > 255){
      valor = 255;
    }
    ledcWrite(ledChannel, valor);
    digitalWrite(motor2,LOW); 
  }
  else{
    valor = -valor;
    if(valor > 255){
      valor = 255;
    }
    ledcWrite(ledChannel, 0);
    digitalWrite(motor2,LOW); 
  }
}
