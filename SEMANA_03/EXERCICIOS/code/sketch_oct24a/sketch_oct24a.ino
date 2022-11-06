//porta dos leds
int ledAzul = 10;
int ledAmarelo= 3;
int ledVermelho = 15;
int ledVerde = 5;
//porta dos botões
int botao1 = 4;
int botao2 = 1;

//porta do buzzer
int buzzer = 7;

int sensor = 17;
int sensorLeitura = 0;

int vetor[100];
int posicaoMedidas = 0;
int binario[4];
int sons = 0;
void setup() {
  pinMode(ledAzul, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(botao1) == LOW) {
    sensorLeitura = analogRead(sensor);
    sensorLeitura = (sensorLeitura * 15) / 4095;
    Serial.print ("Valor do sensor: ");
    Serial.println(sensorLeitura);
    //armazena os valores em um vetor
    vetor[posicaoMedidas] = sensorLeitura;
    Serial.print ("Valores do vetor: ");
    Serial.println(vetor[posicaoMedidas]);
    // função que converte em binário
    binario(binario, vetor[posicaoMedidas]);
    //mostra nos leds o valor lido
    ligaLed(binario);
    somBuzzer(vetor[posicaoMedidas]);
    ledDesliga();

    posicaoMedidas += 1;
    sons += 1;
  }

  if (digitalRead(botao2) == LOW) {
    for(int i = 0; i < sons; i++)
    {
     
      binario(binario, vetor[i]);
      ligaLed(binario);
      somBuzzer(vetor[i]);
      ledDesliga();
    }
    for(int i = 0; i < sons; i++)
    {
      vetor[i] = 0;
    }
    sons = 0;
  }
}
void ledDesliga(void)
{
  delay(700);
  digitalWrite(ledAzul, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledVerde, LOW);
}
void ligaLed(int *binario)

{
  if (binario[0] == 0) {
    digitalWrite(ledAzul, LOW);
  }
  else {
    digitalWrite(ledAzul, HIGH);
  }
  if (binario[1] == 0) {
    digitalWrite(ledAmarelo, LOW);
  }
  else {
    digitalWrite(ledAmarelo, HIGH);
  }
  if (binario[2] == 0) {
    digitalWrite(ledVermelho, LOW);
  }
  else {
    digitalWrite(ledVermelho, HIGH);
  }
  if (binario[3] == 0) {
    digitalWrite(ledVerde, LOW);
  }
  else {
    digitalWrite(ledVerde, HIGH);
  }
}
void binario(int *vetor, int valor)
{
  int i = 4;
  while (i > 0)
  {
    i--;
    vetor[i] = valor % 2;
    valor = valor/2;
  }
}
void somBuzzer(int sensorLeitura) {
  //alterando o tom a cada valor binário
  switch(sensorLeitura) {
void tom(char buzzer, int frequencia, int duracao){
  float periodo = 1000.0/frequencia; 
  for (int i = 0; i< duracao/(periodo); i++)
  {
    digitalWrite(buzzer, HIGH);
    delayMicroseconds(periodo*500); 
    digitalWrite(buzzer, LOW);
    delayMicroseconds(periodo*500);
  }
}
    case 1:
      tom(buzzer, 600, 500);
    break;
    case 2:
      tom(buzzer, 700, 500);
    break;
    case 3:
      tom(buzzer, 800, 500);
    break;
    case 4:
      tom(buzzer, 900, 500);
    break;
    case 5:
      tom(buzzer, 1000, 500);
    break;
    case 6:
      tom(buzzer, 1100, 500);
    break;
    case 7:
      tom(buzzer, 1200, 500);
    break;
    case 8:
      tom(buzzer, 1300, 500);
    break;
    case 9:
      tom(buzzer, 1400, 500);
    break;
    case 10:
      tom(buzzer, 1500, 500);
    break;
    case 11:
      tom(buzzer, 1600, 500);
    break;
    case 12:
      tom(buzzer, 1700, 500);
    break;
    case 13:
      tom(buzzer, 1800, 500);
    break;
    case 14:
      tom(buzzer, 1900, 500);
    break;
    case 15:
      tom(buzzer, 2000, 500);
    break;
    default:
      tom(buzzer, 2100, 500);
  }
}
