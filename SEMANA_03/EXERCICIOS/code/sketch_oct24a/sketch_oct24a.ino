//porta dos leds
int led_blue = 10;
int led_yellow= 3;
int led_red = 15;
int led_green = 5;
//porta dos botões
int botao1 = 4;
int botao2 = 1;
//porta do buzzer
int buzzer = 7;
//porta do sensor
int sensor = 17;
int valorSensor = 0;

int vetorMedidas[100];
int posicaoMedidas = 0;
int valorBinario[4];
int notasVetor = 0;
void setup() {
  pinMode(led_blue, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botao1, INPUT_PULLUP);
  pinMode(botao2, INPUT_PULLUP);
  pinMode(sensor, INPUT);
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(botao1) == LOW) {
    valorSensor = analogRead(sensor);
    valorSensor = (valorSensor * 15) / 4095;
    Serial.print ("Leitura atual do sensor: ");
    Serial.println(valorSensor);
    //armazena os valores em um vetor
    vetorMedidas[posicaoMedidas] = valorSensor;
    Serial.print ("Valor armazenado no vetor: ");
    Serial.println(vetorMedidas[posicaoMedidas]);
    // função que converte em binário
    binario(valorBinario, vetorMedidas[posicaoMedidas]);
    //mostra nos leds o valor lido
    acendeLed(valorBinario);
    tocarBuzzer(vetorMedidas[posicaoMedidas]);
    apagaLed();
    // próxima posição livre no vetor
    posicaoMedidas += 1;
    notasVetor += 1;
  }
  //botão 2 pressionado
  if (digitalRead(botao2) == LOW) {
    for(int i = 0; i < notasVetor; i++)
    {
      // converte em binário todos os valores do vetor
      binario(valorBinario, vetorMedidas[i]);
      acendeLed(valorBinario);
      tocarBuzzer(vetorMedidas[i]);
      apagaLed();
    }
    for(int i = 0; i < notasVetor; i++)
    {
      vetorMedidas[i] = 0;
    }
    notasVetor = 0;
  }
}
void apagaLed(void)
{
  delay(700);
  digitalWrite(led_blue, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
}
void acendeLed(int *valorBinario)
//alterando os estados do led
{
  if (valorBinario[0] == 0) {
    digitalWrite(led_blue, LOW);
  }
  else {
    digitalWrite(led_blue, HIGH);
  }
  if (valorBinario[1] == 0) {
    digitalWrite(led_yellow, LOW);
  }
  else {
    digitalWrite(led_yellow, HIGH);
  }
  if (valorBinario[2] == 0) {
    digitalWrite(led_red, LOW);
  }
  else {
    digitalWrite(led_red, HIGH);
  }
  if (valorBinario[3] == 0) {
    digitalWrite(led_green, LOW);
  }
  else {
    digitalWrite(led_green, HIGH);
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
void tocarBuzzer(int valorSensor) {
  //alterando o tom a cada valor binário
  switch(valorSensor) {
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
