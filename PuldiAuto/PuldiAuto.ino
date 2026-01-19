/*
 * Arduino Puldiauto (Remote Controlled Car)
 * 
 * See projekt kasutab Arduino Uno'd ja IR (infrapuna) puldijuhti,
 * et juhtida autot neljasse suunas: edasi, tagasi, vasakule, paremale.
 * 
 * Riistvara:
 * - Arduino Uno
 * - L298N mootorijuhtimismoodul
 * - 2x DC mootor
 * - IR vastuvõtja (TSOP1738 või sarnane)
 * - IR pult
 * - 9V aku või 4x AA patareid
 * 
 * Autor: KeimoP
 * Litsents: MIT
 */

#include <IRremote.h>

// IR vastuvõtja pin
const int IR_RECEIVE_PIN = 11;

// L298N mootorijuhtimismooduli pinid
// Vasak mootor
const int ENA = 5;  // PWM kiiruse juhtimiseks
const int IN1 = 7;  // Suuna juhtimiseks
const int IN2 = 6;  // Suuna juhtimiseks

// Parem mootor
const int ENB = 10; // PWM kiiruse juhtimiseks
const int IN3 = 9;  // Suuna juhtimiseks
const int IN4 = 8;  // Suuna juhtimiseks

// Mootorite kiirus (0-255)
int motorSpeed = 200;

// IR puldikoodid (need võivad erineda sõltuvalt puldist)
// Katseta oma puldi koodide määramiseks IRrecvDemo näidet
#define BUTTON_UP    0xFF629D
#define BUTTON_DOWN  0xFFA857
#define BUTTON_LEFT  0xFF22DD
#define BUTTON_RIGHT 0xFFC23D
#define BUTTON_OK    0xFF02FD
#define BUTTON_1     0xFF6897
#define BUTTON_2     0xFF9867
#define BUTTON_3     0xFFB04F

void setup() {
  // Seeriaühenduse alustamine
  Serial.begin(9600);
  Serial.println("Arduino Puldiauto käivitatud!");
  
  // IR vastuvõtja seadistamine
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  
  // Mootoripinide seadistamine väljunditeks
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Mootorite seiskamine
  stopMotors();
  
  Serial.println("Valmis käskude vastuvõtmiseks!");
}

void loop() {
  if (IrReceiver.decode()) {
    // Loeme IR signaali
    unsigned long command = IrReceiver.decodedIRData.command;
    
    // Kuvame käsu seerialiidesesse
    Serial.print("Vastuvõetud käsk: 0x");
    Serial.println(command, HEX);
    
    // Käsitleme erinevaid käske
    handleCommand(command);
    
    // Valmistume järgmiseks signaaliks
    IrReceiver.resume();
  }
}

void handleCommand(unsigned long cmd) {
  switch(cmd) {
    case 0x18: // UP nupp (hex kood võib erineda)
    case BUTTON_UP:
      moveForward();
      Serial.println("Liigub edasi");
      break;
      
    case 0x52: // DOWN nupp
    case BUTTON_DOWN:
      moveBackward();
      Serial.println("Liigub tagasi");
      break;
      
    case 0x08: // LEFT nupp
    case BUTTON_LEFT:
      turnLeft();
      Serial.println("Pöörab vasakule");
      break;
      
    case 0x5A: // RIGHT nupp
    case BUTTON_RIGHT:
      turnRight();
      Serial.println("Pöörab paremale");
      break;
      
    case 0x1C: // OK/SELECT nupp
    case BUTTON_OK:
      stopMotors();
      Serial.println("Seiskamine");
      break;
      
    case BUTTON_1:
      motorSpeed = 150; // Aeglane
      Serial.println("Kiirus: Aeglane");
      break;
      
    case BUTTON_2:
      motorSpeed = 200; // Keskmine
      Serial.println("Kiirus: Keskmine");
      break;
      
    case BUTTON_3:
      motorSpeed = 255; // Kiire
      Serial.println("Kiirus: Kiire");
      break;
      
    default:
      stopMotors();
      Serial.println("Tundmatu käsk - seiskamine");
      break;
  }
}

void moveForward() {
  // Vasak mootor edasi
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);
  
  // Parem mootor edasi
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}

void moveBackward() {
  // Vasak mootor tagasi
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);
  
  // Parem mootor tagasi
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motorSpeed);
}

void turnLeft() {
  // Vasak mootor tagasi
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motorSpeed);
  
  // Parem mootor edasi
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed);
}

void turnRight() {
  // Vasak mootor edasi
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);
  
  // Parem mootor tagasi
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motorSpeed);
}

void stopMotors() {
  // Mõlemad mootorid seiskuvad
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
