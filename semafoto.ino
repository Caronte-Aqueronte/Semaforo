#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Definir el pin del potenciómetro
int potPin = A0;

int tiempoVerde = 10;
int tiempoAmarillo = 10;
int tiempoRojo = 10;

int carrosEnCalle = 0;

//pantalla lcd
LiquidCrystal_I2C lcd(0x27, 20, 4);  // establece la dirección LCD en 0x27 para una pantalla de 16 caracteres y 2 líneas

//pines de los leds
const int rojoPin = 13;
const int amarilloPin = 12;
const int verdePin = 11;


void setup() {
  Serial.begin(9600);

  // Inicialización de los pines de los LEDs
  pinMode(rojoPin, OUTPUT);
  pinMode(amarilloPin, OUTPUT);
  pinMode(verdePin, OUTPUT);


  lcd.init();  // inicializacion de la pantalla
  lcd.backlight();
}

void loop() {
  // Leer el valor del potenciómetro
  int potValue = analogRead(potPin);

  // Mapear el valor del potenciómetro al rango del brillo del LED (0 a 255)
  int carrosEnCalle = map(potValue, 0, 1023, 0, 50);

  //TIEMPOS SEMAFOROOO
  tiempoAmarillo = 5;
  //si la cantidad de carros esentre 0 y 5
  if (carrosEnCalle >= 0 && carrosEnCalle <= 15) {
    tiempoVerde = 6;
    tiempoRojo = 20;
  } else if (carrosEnCalle >= 16 && carrosEnCalle <= 30) {
    tiempoVerde = 13;
    tiempoRojo = 8;
  } else if (carrosEnCalle >= 31) {
    tiempoVerde = 20;
    tiempoRojo = 6;
  }
  semaforo(carrosEnCalle);
}

void semaforo(int carrosEnCalle) {
  //SEMAFORO
  int delayInt = 500;
  // Cambiar a luz verde
  digitalWrite(verdePin, HIGH);

  while (tiempoVerde > 0) {
    delay(1000);
    tiempoVerde--;
    //imprimir los resultados en una lcd
    lcd.clear();
    String salida = "";
    lcd.setCursor(0, 0);
    salida.concat("Cars:");
    salida.concat(String(carrosEnCalle));
    salida.concat(" Verd:");
    salida.concat(String(tiempoVerde) + "s");
    lcd.print(salida);  //imprimir primera parte de la salida
    salida = "";
    lcd.setCursor(0, 1);
    salida.concat("Amar:");
    salida.concat(String(tiempoAmarillo) + "s");
    salida.concat(" Roj:");
    salida.concat(String(tiempoRojo) + "s");
    lcd.print(salida);  //imprimir primera parte de la salida
  }
  //parpadeo verde
  digitalWrite(verdePin, LOW);
  delay(delayInt);
  digitalWrite(verdePin, HIGH);
  delay(delayInt);
  digitalWrite(verdePin, LOW);
  delay(delayInt);
  digitalWrite(verdePin, HIGH);
  delay(delayInt);
  digitalWrite(verdePin, LOW);
  delay(delayInt);
  digitalWrite(verdePin, HIGH);
  delay(delayInt);

  // Cambiar a luz amarilla
  digitalWrite(verdePin, LOW);
  digitalWrite(amarilloPin, HIGH);

  while (tiempoAmarillo > 0) {
    delay(1000);
    tiempoAmarillo--;
    //imprimir los resultados en una lcd
    lcd.clear();
    String salida = "";
    lcd.setCursor(0, 0);
    salida.concat("Cars:");
    salida.concat(String(carrosEnCalle));
    salida.concat(" Verd:");
    salida.concat(String(tiempoVerde) + "s");
    lcd.print(salida);  //imprimir primera parte de la salida
    salida = "";
    lcd.setCursor(0, 1);
    salida.concat("Amar:");
    salida.concat(String(tiempoAmarillo) + "s");
    salida.concat(" Roj:");
    salida.concat(String(tiempoRojo) + "s");
    lcd.print(salida);  //imprimir primera parte de la salida
  }



  // Cambiar a luz roja
  digitalWrite(amarilloPin, LOW);
  digitalWrite(rojoPin, HIGH);


  while (tiempoRojo > 0) {
    delay(1000);
    tiempoRojo--;
    //imprimir los resultados en una lcd
    lcd.clear();
    String salida = "";
    lcd.setCursor(0, 0);
    salida.concat("Cars:");
    salida.concat(String(carrosEnCalle));
    salida.concat(" Verd:");
    salida.concat(String(tiempoVerde) + "s");
    lcd.print(salida);  //imprimir primera parte de la salida
    salida = "";
    lcd.setCursor(0, 1);
    salida.concat("Amar:");
    salida.concat(String(tiempoAmarillo) + "s");
    salida.concat(" Roj:");
    salida.concat(String(tiempoRojo) + "s");
    lcd.print(salida);  //imprimir primera parte de la salidas
  }

  //parpadeo rojo
  digitalWrite(rojoPin, LOW);
  delay(delayInt);
  digitalWrite(rojoPin, HIGH);
  delay(delayInt);
  digitalWrite(rojoPin, LOW);
  delay(delayInt);
  digitalWrite(rojoPin, HIGH);
  delay(delayInt);
  digitalWrite(rojoPin, LOW);
  delay(delayInt);
  digitalWrite(rojoPin, HIGH);
  delay(delayInt);
  // Reiniciar el ciclo
  digitalWrite(rojoPin, LOW);
}
