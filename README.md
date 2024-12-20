# Magnet-Rätsel

Ein interaktives Arduino-Rätselspiel, bei dem Spieler verschiedene Magnetwerkzeuge verwenden müssen, um einen geheimen Code zu entschlüsseln.

## Hardware-Anforderungen

- Arduino Mega
- 8x8 LED Matrix (MAX7219)
- Hall-Effekt-Sensor (analog)
- Verschiedene Magnete mit unterschiedlichen Stärken
- Jumperkabel
- Breadboard

## Anschlüsse

LED Matrix:
- DIN -> Pin 51 (MOSI)
- CS  -> Pin 53 (SS)
- CLK -> Pin 52 (SCK)
- VCC -> 5V
- GND -> GND

Hall-Effekt-Sensor:
- VCC -> 5V
- GND -> GND
- OUT -> A0

## Bibliotheken

- LedControl.h (für LED Matrix)

## Spielablauf

1. Das Spiel zeigt nacheinander Zahlen von 1-4 auf der LED-Matrix an
2. Der Spieler muss das richtige Magnetwerkzeug finden, das den entsprechenden Schwellenwert auslöst
3. Bei korrekter Magnetfeldstärke wird die nächste Zahl angezeigt
4. Nach erfolgreicher Eingabe aller Zahlen wird der Endcode angezeigt

## Installation

1. Bibliotheken installieren
2. Hardware gemäß Anschlussplan verbinden
3. Code hochladen
4. Spiel starten und verschiedene Magnete testen
