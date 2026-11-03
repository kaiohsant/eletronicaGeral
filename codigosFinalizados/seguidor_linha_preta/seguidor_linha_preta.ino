// Seguidor de linha preta

// ---------- Pinos de controle dos motores ----------
#define M1   9   // Velocidade do 1º motor (0 a 255) - porta IN2 da ponte H
#define M2   11  // Velocidade do 2º motor (0 a 255) - porta IN4 da ponte H
#define dir1 8   // Direção do 1º motor (HIGH ou LOW) - porta IN1 da ponte H
#define dir2 10  // Direção do 2º motor (HIGH ou LOW) - porta IN3 da ponte H

// ---------- Pinos dos sensores ----------
#define pin_S1 6
#define pin_S2 7

bool Sensor1 = 0;
bool Sensor2 = 0;

// Velocidade dos motores (0 a 255).
// Pistas menores ou curvas mais fechadas pedem velocidades menores.
int velocidade = 220;

void setup() {
  // Configuração dos pinos
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);

  // Direção inicial dos motores
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);
}

void loop() {
  // Leitura dos sensores (1 = vendo preto, 0 = vendo branco)
  Sensor1 = digitalRead(pin_S1);
  Sensor2 = digitalRead(pin_S2);

  if (Sensor1 == 0 && Sensor2 == 0) {
    // Ambos sensores veem branco (linha entre eles): segue em frente
    analogWrite(M1, velocidade);
    analogWrite(M2, velocidade);
  } else if (Sensor1 == 1 && Sensor2 == 0) {
    // Sensor1 está sobre a linha preta: vira para um lado
    analogWrite(M1, velocidade);
    analogWrite(M2, 0);
  } else if (Sensor1 == 0 && Sensor2 == 1) {
    // Sensor2 está sobre a linha preta: vira para o outro lado
    analogWrite(M1, 0);
    analogWrite(M2, velocidade);
  } else {
    // Ambos sensores veem preto: para
    analogWrite(M1, 0);
    analogWrite(M2, 0);
  }
}
