//Código incompleto, só comecei
const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;

int leitura;



void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(pot, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);

}

void loop() {

  //analogRead(pot); 
  // le um valor entre 0 e 4095
  leitura = ((analogRead(pot)-2)/8)-255; 
  
  if (leitura>-3 && leitura <3)
  {
    leitura = 0;
  }

  //passo o valor de leitura para -255 a 255
  motorPWM(leitura);
}

//função que passa o valor pwm para a ponte H 
//(aqui não tem então coloquei 2 leds)
void motorPWM (int valor)
{
  Serial.println(valor);
  if (valor<0){
    valor = -valor; 
    // se valor for negativo gira o motor para o outro lado
    // preciso passar o valor para positivo
    if(valor > 255){
      valor = 255;
    }
    analogWrite(motor2,valor); // valor deve estar entre 0 e 255
    analogWrite(motor1,0);
  }
  else{
    if(valor > 255){
      valor = 255;
    }
    analogWrite(motor1,valor); // saída invertida do que foi feito acima
    analogWrite(motor2,0);
  }
}
