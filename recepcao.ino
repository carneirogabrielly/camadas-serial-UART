const int rxPin = 9;  // Pino para recepção
const int baudRate = 9600;  // Baudrate (9600)

void setup() {
  pinMode(rxPin, INPUT);
  Serial.begin(9600);  // Inicia o Monitor Serial para mostrar o que foi recebido
}

void loop() {
  char caractere = receberByte();
  
  if (caractere == -1) {
    Serial.println("Erro de paridade!");
  } else if (caractere ==-2) {
    Serial.println("Erro de stop!");
  } else {
    Serial.print("Caractere recebido: ");
    Serial.println(caractere);
  }
}

char receberByte() {
  // Espera pelo bit de start (nível baixo)
  while (digitalRead(rxPin) == HIGH);

  for (int32_t i = 0; i < 12500; i++) {
    asm("NOP");  // No Operation
  }

  char caractere = 0;

  // Recebe os 8 bits do caractere
  for (int i = 0; i < 8; i++) {
    caractere |= (digitalRead(rxPin) << i);
    funcao_espera();  // Espera o tempo de 1 bit
  }

  // Verifica o bit de paridade
  int paridadeRecebida = digitalRead(rxPin);
  int paridadeCalculada = calcularParidade(caractere);

  funcao_espera();  // Espera o tempo de 1 bit

  // Verifica se o bit de stop é alto (esperado)
  if (digitalRead(rxPin) == LOW) {
    return -2;  // Erro de stop
  }

  // Verifica se a paridade está correta
  if (paridadeRecebida != paridadeCalculada) {
    return -1;  // Erro de paridade
  }

  return caractere;
}

void funcao_espera() {
  // Função de espera com NOP para controlar o tempo de 1 bit
  for (int32_t i = 0; i < 8333; i++) {
    asm("NOP");  // No Operation
  }
}

int calcularParidade(char caractere) {
  int paridade = 0;
  for (int i = 0; i < 8; i++) {
    paridade ^= (caractere >> i) & 0x01;  // XOR para calcular a paridade
  }
  return paridade;  // Retorna a paridade calculada
}
