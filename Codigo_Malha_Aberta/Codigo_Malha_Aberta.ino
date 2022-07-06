const int pot = 34;
const int motor1 = 25;
const int motor2 = 33;
const int motorLeitura = 26;
int leitura;
float tensao;


const int freq = 30000;
const int ledChannel = 0;
const int resolution = 12;

void setup() {
  Serial.begin(115200);
  pinMode(pot, INPUT);
  pinMode(motorLeitura, INPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);

  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(motor1, ledChannel);
}

void loop() {
  leitura = analogRead(pot);
  tensao = float(analogRead(motorLeitura));
  tensao = 2 * tensao / 1240.909;
//  Serial.println(tensao);
  motorPWM(leitura);
}
void motorPWM (int valor)
{
  //    if(valor > 1000){
  //      valor = 4095*0.7;
  //    }
  //
  //    if(valor <= 1000){
  //      valor = 4095*0;
  //    }
  ledcWrite(ledChannel, valor);
  digitalWrite(motor2, LOW);
}
