const int txPin = 4;  // Pino que vai transmitir os dados (Pino 4)
const int baudRate = 9600;  // Defina o baudrate (9600)

void setup() {
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, HIGH);
  delay(5000);  // Delay inicial para garantir que tudo esteja preparado
}

void loop() {

  delay(200);  // Espera 1 segundo antes de enviar novamente

  char caractere = 'A';  // Caractere a ser enviado
  enviarByte(caractere);
  
}

void enviarByte(char caractere) {
  // Enviar bit de start (nível baixo)
  digitalWrite(txPin, LOW);
  funcao_espera();  // Espera o tempo de 1 bit

  // Enviar os 8 bits do caractere
  for (int i = 0; i < 8; i++) {
    int bit = (caractere >> i) & 0x01;  // Extrai o bit
    digitalWrite(txPin, bit);  // Escreve o bit no pino
    funcao_espera();  // Espera o tempo de 1 bit
  }

  // Calcular e enviar o bit de paridade (paridade par)
  int paridade = calcularParidade(caractere);
  digitalWrite(txPin, paridade);
  funcao_espera();  // Espera o tempo de 1 bit

  // Enviar bit de stop (nível alto)
  digitalWrite(txPin, HIGH);
  funcao_espera();  // Espera o tempo de 1 bit
}

int calcularParidade(char caractere) {
  int paridade = 0;
  for (int i = 0; i < 8; i++) {
    paridade ^= (caractere >> i) & 0x01;  // XOR para calcular a paridade
  }
  return paridade;  // Retorna a paridade calculada
}

void funcao_espera() {
  // Função de espera com NOP para controlar o tempo de 1 bit
  for (int32_t i = 0; i < 8333; i++) {
    asm("NOP");  // No Operation
  }
}
