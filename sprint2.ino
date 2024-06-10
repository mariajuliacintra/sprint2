// Constantes para os pinos
#define botao_selecionar_heroi 2
#define botao_dado_heroi 3
#define led_heroi 6
#define botao_selecionar_vilao 5
#define botao_dado_vilao 4
#define led_vilao 7
#define Buzzer 8  // Pino do buzzer


bool partida_em_andamentoH = false;
bool partida_em_andamentoV = false;
bool dado_heroi_lancado = false;
bool dado_vilao_lancado = false;

int contH = 0;
int contV = 0;
int Dado_heroi = 0;  // Variável para o sorteio dos números
int Dado_vilao = 0;  // Variável para o sorteio dos números

void setup() {
  // Definição das entradas e saídas de dados
  pinMode(led_heroi, OUTPUT);
  pinMode(led_vilao, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(botao_selecionar_heroi, INPUT);
  pinMode(botao_selecionar_vilao, INPUT);
  pinMode(botao_dado_heroi, INPUT);
  pinMode(botao_dado_vilao, INPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);
  delay(1000);
  Serial.println("\
 ====================== \n\
|  Bem-vindo ao jogo,  |\n\
|  selecione um        |\n\
|      personagem.     |\n\
 ======================");
  Serial.println(" ");
}

void loop() {

  int estado_botao_heroi = digitalRead(botao_selecionar_heroi);  // Armazena o estado do botão herói
  int estado_botao_vilao = digitalRead(botao_selecionar_vilao);  // Armazena o estado do botão vilão

  delay(1000);

  // Selecionando o Herói
  if (estado_botao_heroi == HIGH && partida_em_andamentoH == false) {  //seleciona o heroi
    Serial.println("Heroi selecionado");
    Serial.println("-----------------------------------------------------");
    digitalWrite(led_heroi, HIGH);
    delay(1000);
    digitalWrite(led_heroi, LOW);
    contH += 1;
    partida_em_andamentoH = true;
  }

  // Sorteando os dados do héroi
  if (contH == 1 && digitalRead(botao_dado_heroi) == HIGH && dado_heroi_lancado == false) {  //sorteia o heroi
    Serial.print("Lancando os dados do heroi");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Dado_heroi = random(1, 7);
    Serial.println("");
    delay(500);
    Serial.println("---------------------------------------------------------");
    delay(500);
    Serial.print("Valor sorteado do Heroi: ");
    Serial.println(Dado_heroi);
    delay(500);
    Serial.println("---------------------------------------------------------- ");
    dado_heroi_lancado = true;
  }

  // Selecionando o vilão
  if (estado_botao_vilao == HIGH && partida_em_andamentoV == false) {
    Serial.println("Vilao selecionado");
    Serial.println("---------------------------------------------------------");
    digitalWrite(led_vilao, HIGH);
    delay(1000);
    digitalWrite(led_vilao, LOW);
    contV += 1;
    partida_em_andamentoV = true;
  }

  // Sorteando os dados do vilão
  if (contV == 1 && digitalRead(botao_dado_vilao) == HIGH && dado_vilao_lancado == false) {
    Serial.print("Lancando os dados do vilao");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Serial.print(".");
    delay(1000);
    Dado_vilao = random(1, 7);
    Serial.println("");
    delay(500);
    Serial.println("----------------------------------------------------------");
    delay(500);
    Serial.print("Valor sorteado do Vilao: ");
    Serial.println(Dado_vilao);
    delay(500);
    Serial.println("-----------------------------------------------------------");
    dado_vilao_lancado = true;
  }

  // Sistema de comparação

  if (Dado_heroi > 0 && Dado_vilao > 0) {

    // Vilão venceu
    if (Dado_heroi < Dado_vilao) {
      Serial.print("");
      delay(1000);
      Serial.println("Vilao venceu!!!");
      fim_de_jogo();
      for (byte cont = 0; cont < 10; cont++) {
        digitalWrite(led_vilao, HIGH);
        delay(300);
        digitalWrite(led_vilao, LOW);
        delay(300);
      }
      musica_vilao();
      delay(2000);
      for (byte cont = 0; cont < 20; cont++) {
        Serial.println(" ");
      }
      delay(1000);
      Serial.println("\
 ====================== \n\
|  Bem-vindo ao jogo,  |\n\
|  selecione um        |\n\
|      personagem.     |\n\
 ======================");
      Serial.println("");
    }

    // Herói venceu
    else if (Dado_heroi > Dado_vilao) {
      Serial.print("");
      delay(1000);
      Serial.println("Heroi venceu!!!");
      fim_de_jogo();
      for (byte cont = 0; cont < 10; cont++) {
        digitalWrite(led_heroi, HIGH);
        delay(300);
        digitalWrite(led_heroi, LOW);
        delay(300);
      }
      musica_heroi();
      delay(2000);
      for (byte cont = 0; cont < 20; cont++) {
        Serial.println(" ");
      }
      delay(1000);
      Serial.println("\
 ====================== \n\
|  Bem-vindo ao jogo,  |\n\
|  selecione um        |\n\
|      personagem.     |\n\
 ======================");
      Serial.println(" ");
    }

    // Empate
    else {
      delay(1000);
      Serial.println("Empate!");
      delay(1000);
      Serial.println("Jogue novamente");
      fim_de_jogo();
      digitalWrite(led_heroi, HIGH);
      digitalWrite(led_vilao, HIGH);
      delay(3000);
      digitalWrite(led_heroi, LOW);
      digitalWrite(led_vilao, LOW);
      delay(2500);
      for (byte cont = 0; cont < 20; cont++) {
        Serial.println(" ");
      }
      delay(1000);
      Serial.println("\
 ====================== \n\ 
|  selecione um        |\n\
|      personagem.     |\n\
 ======================");
      Serial.println("");
    }
  }
}

// Funções

void fim_de_jogo() {
  contH = 0;
  contV = 0;
  Dado_heroi = 0;
  Dado_vilao = 0;
  dado_heroi_lancado = false;
  dado_vilao_lancado = false;
  partida_em_andamentoH = false;
  partida_em_andamentoV = false;
}

void musica_vilao() {  //Star wars:Marcha imperial

  delay(1000);

  tone(Buzzer, 392);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 392);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 392);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 311);  //D#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 466);  //A#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 392);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 311);  //D#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 466);  //A#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 392);  //G
  delay(582);
  noTone(Buzzer);
  delay(582);

  tone(Buzzer, 587);  //D
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 587);  //D
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 622);  //D#
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 466);  //A#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 370);  //F#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 311);  //D#
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 311);  //D#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 466);  //A#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 392);  //G
  delay(582);
  noTone(Buzzer);
  delay(582);

  tone(Buzzer, 784);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 392);  //G
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 392);  //G
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 784);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 740);  //F#
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 698);  //F
  delay(97);
  noTone(Buzzer);
  delay(97);

  tone(Buzzer, 659);  //E
  delay(97);
  noTone(Buzzer);
  delay(97);

  tone(Buzzer, 622);  //D#
  delay(97);
  noTone(Buzzer);
  delay(97);

  tone(Buzzer, 659);  //E
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 415);  //G#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 554);  //C#
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 523);  //C
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 494);  //B
  delay(97);
  noTone(Buzzer);
  delay(97);

  tone(Buzzer, 466);  //A#
  delay(97);
  noTone(Buzzer);
  delay(97);

  tone(Buzzer, 440);  //A
  delay(97);
  noTone(Buzzer);
  delay(97);

  tone(Buzzer, 466);  //A#
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 311);  //D#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 370);  //F#
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 311);  //D#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 466);  //A#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 392);  //G
  delay(291);
  noTone(Buzzer);
  delay(291);

  tone(Buzzer, 311);  //D#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 466);  //A#
  delay(145);
  noTone(Buzzer);
  delay(145);

  tone(Buzzer, 392);  //G
  delay(582);
  noTone(Buzzer);
  delay(582);
}

void musica_heroi() {

  delay(1000);

  tone(Buzzer, 659);  //E
  delay(130);
  noTone(Buzzer);
  delay(130);

  tone(Buzzer, 659);  //E
  delay(130);
  noTone(Buzzer);
  delay(130);

  tone(Buzzer, 659);  //E
  delay(160);
  noTone(Buzzer);
  delay(160);

  tone(Buzzer, 523);  //C
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 659);  //E
  delay(130);
  noTone(Buzzer);
  delay(130);

  tone(Buzzer, 784);  //G
  delay(300);
  noTone(Buzzer);
  delay(300);

  tone(Buzzer, 392);  //G
  delay(250);
  noTone(Buzzer);
  delay(250);

  tone(Buzzer, 523);  //C
  delay(320);
  noTone(Buzzer);
  delay(320);

  tone(Buzzer, 392);  //G
  delay(178);
  noTone(Buzzer);
  delay(178);

  tone(Buzzer, 440);  //A
  delay(178);
  noTone(Buzzer);
  delay(178);

  tone(Buzzer, 494);  //B
  delay(119);
  noTone(Buzzer);
  delay(119);

  tone(Buzzer, 466);  //A#
  delay(119);
  noTone(Buzzer);
  delay(119);

  tone(Buzzer, 440);  //A
  delay(119);
  noTone(Buzzer);
  delay(119);

  tone(Buzzer, 392);  //G
  delay(178);
  noTone(Buzzer);
  delay(178);

  tone(Buzzer, 523);  //C
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 659);  //E
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 784);  //G
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 880);  //A
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 784);  //G
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 659);  //E
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 784);  //G
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 659);  //E
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 523);  //C
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 659);  //E
  delay(150);
  noTone(Buzzer);
  delay(150);

  tone(Buzzer, 523);  //C
  delay(500);
  noTone(Buzzer);
  delay(500);
}