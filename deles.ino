#include <Ultrasonic.h>
#include <dht11.h>


// Definições dos pinos e variáveis de controle
#define BIN1 46
#define BIN2 48
#define BIN3 50
#define BIN4 52

#define TEMP 10
#define ECHO_PIN 11

#define LEDA 5
#define LEDB 6
#define LEDC 7

#define BUZZ 2

#define trig 22
#define echo 24

#define sensorPresenca 8

bool isProgramActive = false;
int modoAtual = 0;

bool medirDistancia = false;  // Variável para controlar a execução contínua da medição de distância
bool detectarMov = false;     // Variável para controlar a execução contínua do sensor de movimento
bool detecTemp = false;

dht11 DHT11;

double distancia = 0;


int VAL1 = 0;
int VAL2 = 0;
int VAL3 = 0;
int VAL4 = 0;
int valorSensor = 0;

// Função para desligar todos os componentes
void desligarTudo() {
    digitalWrite(LEDA, LOW);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDC, LOW);
    digitalWrite(BUZZ, LOW);
    medirDistancia = false; // Desativa medição de distância quando o programa é encerrado
    while (true) {
        // Fica preso aqui para garantir que o programa pare
    }
}

// Função para medir a distância usando sensor ultrassônico
void distancias() {
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    distancia = pulseIn(echo, HIGH);
    distancia = distancia * 340;
    distancia = distancia / 2;
    distancia = distancia / 10000;
    Serial.println(distancia);
}

void detectarMovimento() {
  valorSensor = digitalRead(sensorPresenca);
  if (valorSensor == true) {
    Serial.println("TEM GENTE");
  } else if (valorSensor == false) {
    Serial.println("NÃO TEM GENTE");
    
  } else {
    Serial.println("NÃO TEM GENTE");

  }
}

void temperatura() {
  DHT11.read(TEMP);

  Serial.print("Humidade: ");
  Serial.print(DHT11.humidity);
  Serial.println("%");
  
  Serial.println("Temperatura: ");
  Serial.println(DHT11.temperature);
  Serial.println("c");
  Serial.println("________________________________");
  delay(2000);
}

// Função para processar comandos recebidos via monitor serial
void serialTeste() {
    if (Serial.available() > 0) {
        String comando = Serial.readStringUntil('\n'); // Lê a linha de comando até nova linha
        comando.trim(); // Remove espaços em branco extras

        if (comando == "FIM_PROG") {
            Serial.println("Programação desativada via comando serial.");
            desligarTudo();
            modoAtual = 0;
            medirDistancia = false;
            detectarMov = false;
            detecTemp = false;
        } else if (comando == "DIST_CHECKA") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            medirDistancia = true;
            detectarMov = false;  // Ativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "PRES_READA") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = true;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "LED_ONA") {
            digitalWrite(LEDA, HIGH);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "LED_OFFA") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "LED_ONB") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, HIGH);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "LED_OFFB") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "LED_ONC") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, HIGH);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "LED_OFFC") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;
        } else if (comando == "BUZZ_ON") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, HIGH);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;

        } else if (comando == "BUZZ_OFF") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = false;

        } else if (comando == "TEMP_READA") {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMov = false;  // Ativa detecção de movimento contínua
            medirDistancia = false;  // Desativa medição de distância contínua
            detecTemp = true;
            

        }
    }
}


// Função para processar comandos recebidos via binário
void binarioTeste() {
    // Verifica se a combinação é 1101 para encerrar a programação
    if (VAL1 == 1 && VAL2 == 0 && VAL3 == 1 && VAL4 == 1) {
        Serial.println("Programação encerrada");
        isProgramActive = false;
        desligarTudo();
        modoAtual = 0;
    }

    if (isProgramActive) {
        if((VAL1 == 0) && (VAL2 == 0) && (VAL3 == 0) && (VAL4 == 0)) {
            digitalWrite(LEDA, HIGH);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        }
        else if ((VAL1 == 1) && (VAL2 == 0) && (VAL3 == 0) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        } 
        else if ((VAL1 == 0) && (VAL2 == 1) && (VAL3 == 0) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, HIGH);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        }
        else if ((VAL1 == 1) && (VAL2 == 1) && (VAL3 == 0) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        } 
        else if ((VAL1 == 0) && (VAL2 == 0) && (VAL3 == 1) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        }
        else if ((VAL1 == 1) && (VAL2 == 0) && (VAL3 == 1) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
        }
        else if ((VAL1 == 1) && (VAL2 == 1) && (VAL3 == 1) && (VAL4 == 0)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            distancias(); // Executa medição de distância
        }
        else if ((VAL1 == 0) && (VAL2 == 0) && (VAL3 == 0) && (VAL4 == 1)) {
            digitalWrite(LEDA, LOW);
            digitalWrite(LEDB, LOW);
            digitalWrite(LEDC, LOW);
            digitalWrite(BUZZ, LOW);
            detectarMovimento();
        }

    }
}

// Configuração inicial do Arduino
void setup() {
    pinMode(BIN1, INPUT);
    pinMode(BIN2, INPUT);
    pinMode(BIN3, INPUT);
    pinMode(BIN4, INPUT);
    pinMode(LEDA, OUTPUT);
    pinMode(BUZZ, OUTPUT);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(sensorPresenca, INPUT);

    
  
    Serial.begin(9600);
    Serial.println("Digite os comandos no formato: 'comando'");
    Serial.println("Comandos disponíveis:");
    Serial.println(" - ativar: INICIO_PROG");
    Serial.println(" - desativar: FIM_PROG");
}

void loop() {
    // Lê os valores das entradas binárias
    VAL1 = digitalRead(BIN1);
    VAL2 = digitalRead(BIN2);
    VAL3 = digitalRead(BIN3);
    VAL4 = digitalRead(BIN4);

    delay(500);

    // Verifica se o programa está no estado inicial e aguarda comandos para ativar
    if (modoAtual == 0) {
        if (Serial.available() > 0) {
            String comando = Serial.readStringUntil('\n');
            comando.trim();
            if (comando == "INICIO_PROG") {
                Serial.println("Programação ativada via comando serial.");
                modoAtual = 1;
            }
        }
        if (VAL1 == 0 && VAL2 == 0 && VAL3 == 1 && VAL4 == 1) {
            Serial.println("Programação ativada");
            isProgramActive = true;
            modoAtual = 2;
        }
    }

    // Verifica o modo atual e executa a função correspondente
    if (modoAtual == 1) {
        serialTeste(); // Checa comandos e executa continuamente
    } else if (modoAtual == 2) {
        binarioTeste(); // Checa e executa com base nos valores binários
    }

    // Executa medição de distância continuamente se ativado
    if (medirDistancia) {
        distancias();

    }

    // Executa detecção de movimento continuamente se ativado
    if (detectarMov) {
        detectarMovimento();
    }
    if (detecTemp) {
      temperatura();
    }
}
