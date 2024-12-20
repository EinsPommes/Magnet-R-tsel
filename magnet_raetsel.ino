#include <LedControl.h>

// LED Matrix Pins
#define DIN_PIN 51  // MOSI
#define CS_PIN  53  // SS
#define CLK_PIN 52  // SCK

// Hall-Effekt-Sensor Pin
#define HALL_SENSOR_PIN A0

// LED Matrix Konfiguration
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1);

// Schwellenwerte für verschiedene Magnetfeldstärken
const int THRESHOLD_1 = 300;  // Schwach
const int THRESHOLD_2 = 400;  // Mittel
const int THRESHOLD_3 = 500;  // Stark
const int THRESHOLD_4 = 600;  // Sehr stark

// Spielvariablen
int currentLevel = 1;
const int MAX_LEVEL = 4;
bool codeFound = false;
const int CODE_SEQUENCE[] = {2, 4, 1, 3};  // Richtige Reihenfolge der Magnete
int playerSequence[4] = {0, 0, 0, 0};

// Ziffern-Muster für LED Matrix (8x8)
const byte DIGITS[5][8] = {
  // 1
  {
    B00011000,
    B00111000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00111100,
    B00000000
  },
  // 2
  {
    B00111100,
    B01100110,
    B00000110,
    B00001100,
    B00110000,
    B01100000,
    B01111110,
    B00000000
  },
  // 3
  {
    B00111100,
    B01100110,
    B00000110,
    B00011100,
    B00000110,
    B01100110,
    B00111100,
    B00000000
  },
  // 4
  {
    B00001100,
    B00011100,
    B00101100,
    B01001100,
    B01111110,
    B00001100,
    B00001100,
    B00000000
  }
};

void setup() {
  Serial.begin(9600);
  
  // LED Matrix initialisieren
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);
  
  Serial.println("Magnet-Raetsel gestartet!");
  Serial.println("Finde die richtige Reihenfolge der Magnete!");
  
  displayNumber(currentLevel);
}

void loop() {
  if (!codeFound) {
    int sensorValue = analogRead(HALL_SENSOR_PIN);
    int detectedMagnet = detectMagnet(sensorValue);
    
    if (detectedMagnet > 0) {
      handleMagnetDetection(detectedMagnet);
      delay(1000);  // Entprellen
    }
  }
}

int detectMagnet(int sensorValue) {
  if (sensorValue > THRESHOLD_4) return 4;
  if (sensorValue > THRESHOLD_3) return 3;
  if (sensorValue > THRESHOLD_2) return 2;
  if (sensorValue > THRESHOLD_1) return 1;
  return 0;
}

void handleMagnetDetection(int magnetStrength) {
  Serial.print("Magnet erkannt mit Staerke: ");
  Serial.println(magnetStrength);
  
  if (magnetStrength == CODE_SEQUENCE[currentLevel - 1]) {
    playerSequence[currentLevel - 1] = magnetStrength;
    Serial.println("Richtig!");
    
    if (currentLevel < MAX_LEVEL) {
      currentLevel++;
      displayNumber(currentLevel);
    } else {
      checkWinCondition();
    }
  } else {
    Serial.println("Falsch! Versuche es noch einmal.");
    // Optional: Fehlermuster anzeigen
    displayError();
    delay(1000);
    displayNumber(currentLevel);
  }
}

void checkWinCondition() {
  bool correct = true;
  for (int i = 0; i < MAX_LEVEL; i++) {
    if (playerSequence[i] != CODE_SEQUENCE[i]) {
      correct = false;
      break;
    }
  }
  
  if (correct) {
    codeFound = true;
    Serial.println("Gratulation! Code gefunden!");
    displayVictory();
  } else {
    Serial.println("Falsche Sequenz! Starte von vorne.");
    resetGame();
  }
}

void displayNumber(int number) {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, DIGITS[number - 1][row]);
  }
}

void displayError() {
  lc.clearDisplay(0);
  // X-Muster anzeigen
  for (int i = 0; i < 8; i++) {
    lc.setLed(0, i, i, true);
    lc.setLed(0, i, 7-i, true);
  }
}

void displayVictory() {
  // Blinkendes Muster
  for (int i = 0; i < 3; i++) {
    lc.clearDisplay(0);
    delay(300);
    for (int row = 0; row < 8; row++) {
      lc.setRow(0, row, B11111111);
    }
    delay(300);
  }
}

void resetGame() {
  currentLevel = 1;
  for (int i = 0; i < MAX_LEVEL; i++) {
    playerSequence[i] = 0;
  }
  displayNumber(currentLevel);
}
