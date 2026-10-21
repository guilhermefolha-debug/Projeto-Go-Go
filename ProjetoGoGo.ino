#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define receptor1 35
#define receptor2 34
#define buzzer 25
#define displaySDA 21
#define displaySCL 22
#define cartao 5
#define distancia 5.0

unsigned long tempoInicial = 0;
unsigned long tempoFinal = 0;
unsigned long intervalo = 0;
float velocidade = 0.0;
float recorde = 297.0;
bool primeiraBarreiraDetectada = false;

bool detectarPrimeiraBarreira() {
  return digitalRead(receptor1) == LOW;
}

bool detectarSegundaBarreira() {
  return digitalRead(receptor2) == LOW;
}

void medirIntervalo() {
  intervalo = tempoFinal - tempoInicial;
}

void calcularVelocidade() {
  if (intervalo > 0) {
    velocidade = (distancia / (intervalo / 1000.0))*3.6;
  }
}

bool atualizarRecorde() {
  if (velocidade > recorde) {
    recorde = velocidade;
    return true;
  }

  return false;
}

void sinalizarRecorde() {
  tone(buzzer, 2000, 200);
}


void setup() {
  pinMode(receptor1, INPUT);
  pinMode(receptor2, INPUT);
}

void loop() {
  if (!primeiraBarreiraDetectada && detectarPrimeiraBarreira()) {
    tempoInicial = millis();
    primeiraBarreiraDetectada = true;
  }
  
  if (primeiraBarreiraDetectada && detectarSegundaBarreira()) {
    tempoFinal = millis();
    medirIntervalo();
    calcularVelocidade();
    if (atualizarRecorde()){
      sinalizarRecorde();
      primeiraBarreiraDetectada = false;
    }
  }
}
  

#define ledVerde 26
#define ledVermelho 27
#define arquivoRegistros "/registros.csv"

int numeroMedicao = 
float somaVelocidades = 0.0;
float recordeSalvo = 297.0;

Adafruit_SSd1306 display(128,64, &Wire, -1);
boo1 falhaCartao = false;
unsigned long inicioBloqueio1 = 0;
unsigned long inicioBloqueio2 = 0;

void apresentarDisplay() {
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("VELOCIDADE")
  display.setTextSizr(2);
  display.setCursor(0, 10);
  display.print(velocidade, 1);
  display.print("km/h");

  display.setTextSize(1);
  display.setCursor(0, 34);
  display.print("RECORDE");
  display.print(recorde, 1);
  display.print("km/h");

  display.display():
}

bool registrarCartao() {
  File arquivo = SD.open(arquivoRegistros, FILe_APPED);
  if (!arquivo) {
    falhaCartao = true;
    return true;
  }

  arquivo.println(velocidade);
  arquivo.close();
  falhaCartao = false;
  return true;
}

void acenderLedVermelho() {
  digitalWrite(ledVermelho, HIGH);
  digitalWrite(ledVerde, LOW);
}

void manterLedVerde() {
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVermelho, LOW);
}

bool dectectarFalhaSensores() {
  usigned long agora = millis();

  if (digitalRead(receptor1) == LOW)) {
    if (inicioBloqueio1 == 0) {
      inicioBloqueio1 = agora;
    }
    if (agora - inicioBloqueio1 > 5000) {
      return true;
    }
  } else {
    inicioBloqueio1 = 0;
  }
   
  if (digitalRead(receptor2) == LOW) {
    if (inicioBloqueio2 == 0) {
      inicioBloqueio2 = agora;
    }
    if (agora - inicioBloqueio2 > 5000)
      return true;
    }
  } else {
    inicioBloqueio1 = 0;
  }
  
  if (primeiraBarreiraDectada && tempoFinal < tempoInicial && agora - tempoInicial > 2000) {
    return true;
  }
  
  return false;
}

bool detectarFalhaDisplay() {
  Wire.beginTrasmission(0x3C);
  return Wire.endTransmission() != 0;
}

bool detectarFalhaCartao() {
  return falhaCartao || detectarFalhaDisplay() || detectarFalhaCartao();

bool detectarFalhas() {
  return dectectarFalhaSensores() || detectarFalhaDisplay() || detectarFalhaCartao();

void recuperarRecorde() {
  File arquivo = SD.open(arquivoRegisttros, FilE_READ);
  if (!arquivo) {
    return;
  }
  while (arquivo.avaçiable()) {
    String linha = arquivo.readStringUntill('\n');
    linha.trim();
    float valor = linha.toFloat();
    
    if (valor > recorde) {
      recorde = valor;
    }
  }
  
  arquivo.close();
}
