# RC-auto ehituse dokumentatsioon (Arduino)

## Projekti ülevaade
Ehita robot, mis suudab liikuda ja läbida takistustega raja. Robot peab olema programmeeritud ning kasutama tehnilist lahendust, mida õpilane ise mõistab ja juhib.

---

## Raami hankimine ja 3D-printimine
Auto raam laaditi alla Printables platvormilt. Tegemist on mudeliga, mis on mõeldud spetsiaalselt Arduino-põhise RC-auto jaoks.

**3D-mudeli allikas:**  
https://www.printables.com/model/644267-arduino-car-chassis-4wd/

Raam prinditi 3D-printeriga ning sisaldab eelnevalt disainitud kinnitusaauke mootorite ja elektroonika jaoks, mis lihtsustas oluliselt kokkupanekut.

---

## Kasutatud komponendid

| Komponent | Kogus | Kirjeldus |
|---------|------|----------|
| Arduino Uno (või ühilduv) | 1 | Põhikontroller auto juhtimiseks |
| Adafruit Motor Shield V1 | 1 | DC-mootorite juhtimiseks |
| TT DC mootor | 4 | Rataste liigutamiseks |
| RC vastuvõtja (FlySky / TGY-IA6B) | 1 | Vastuvõtab signaale saatjalt |
| RC saatja (FlySky / Turnigy) | 1 | Auto juhtimiseks |
| 9V patarei | 2 | Arduino ja mootorite toiteks |
| Jumper-juhtmed | mitu | Ühenduste loomiseks |
| Jootetina | – | Elektriliste ühenduste jootmiseks |

---

## Mootorite paigaldamine
Raamile kinnitati neli TT-tüüpi DC-mootorit.  
Iga mootor kinnitati kahe kruviga, kasutades raamile eelnevalt disainitud kinnitusauke.

### Mootorite ühendused Motor Shieldiga

| Ratas | Mootori väljund |
|-----|----------------|
| Esimene parem (FR) | M3 |
| Esimene vasak (FL) | M4 |
| Tagumine parem (RR) | M2 |
| Tagumine vasak (RL) | M1 |

Iga mootori külge ühendati kaks juhet, mis viidi vastavasse M-pessa Motor Shieldil.

---

## Arduino ja Motor Shieldi paigaldamine
Pärast mootorite ühendamist paigaldati Adafruit Motor Shield otse Arduino peale (stackimine).

- Motor Shield kinnitati raamile kahe kruviga
- Arduino ja Motor Shield moodustavad ühe tervikliku juhtploki
- Tagatud on stabiilne mehaaniline ja elektriline ühendus

---

## RC-vastuvõtja ühendamine

Motor Shieldile joodeti A0–A5 pinid, et kasutada Arduino analoogsisendeid.

### Ühendused
- **A0 → CH1 (steering)**
- **A2 → CH3 (throttle)**
- **5V → Vastuvõtja 5V**
- **GND → Vastuvõtja GND**

Pärast ühendamist seoti vastuvõtja RC-saatjaga.

---

## Toitelahendus
Toiteks kasutati kahte eraldi 9V patareid:

- 1× 9V patarei → Arduino
- 1× 9V patarei → Motor Shield (mootorid)

**Oluline:**  
Motor Shieldi toitejumper eemaldati, et Arduino ja mootorid saaksid eraldi toidet.

Patareid paigutati auto esiossa, et mass oleks ühtlaselt jaotunud.

---

## Visuaalne dokumentatsioon

### Valmis RC-auto
Alloleval pildil on näha projekti lõpptulemus koos 3D-prinditud raamiga, paigaldatud elektroonika ja ratastega.

![Valmis RC-auto](valmis_auto.jpg)

### Analoogsignaalide ühendused
Järgneval pildil on näha RC-vastuvõtja ja Arduino vaheline analoogsignaalide juhtmestik (steering ja throttle).

![Analoogsignaalide juhtmestik](analogwires.jpg)

## Tarkvara ja programmeerimine
Arduino ühendati arvutiga USB-kaabli abil ning programm laaditi üles Arduino IDE kaudu.

### Funktsionaalsus
- Edasi liikumine
- Tagurpidi liikumine
- Steering vasakule ja paremale
- Neutraalala throttle’i keskel
- Mootorite seiskamine signaali puudumisel

---

## Kasutatav kood

```cpp
#include <AFMotor.h>


// Motor setup
AF_DCMotor rearLeft(1);
AF_DCMotor rearRight(2); // M2 inverted
AF_DCMotor frontRight(3);
AF_DCMotor frontLeft(4);


// Receiver pins
#define THROTTLE_PIN A2  // throttle
#define STEER_PIN    A0  // steering


void setup() {
  Serial.begin(9600);
}


void loop() {
  // Read RC PWM signals
  unsigned long throttle = pulseIn(THROTTLE_PIN, HIGH, 50000);
  unsigned long steer    = pulseIn(STEER_PIN, HIGH, 50000);


  int speed = 0;


  // ----- Forward -----
  if (throttle > 1600) {
    speed = map(throttle, 1601, 2000, 0, 200);
    speed = constrain(speed, 0, 200);


    int leftSpeed = speed;
    int rightSpeed = speed;


    // Steering
    if (steer > 1600) {       // turn left
      leftSpeed = 0;
    }
    else if (steer < 1400) {  // turn right
      rightSpeed = 0;
    }


    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);


    rearLeft.run(FORWARD);
    frontLeft.run(FORWARD);


    rearRight.run(BACKWARD); // M2 inverted
    frontRight.run(FORWARD);
  }
  // ----- Reverse -----
  else if (throttle >= 1150 && throttle <= 1400) {
    speed = map(throttle, 1150, 1400, 0, 200);
    speed = constrain(speed, 0, 200);


    int leftSpeed = speed;
    int rightSpeed = speed;


    // Steering in reverse
    if (steer > 1600) {       // turn left
      leftSpeed = 0;
    }
    else if (steer < 1400) {  // turn right
      rightSpeed = 0;
    }


    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);


    rearLeft.run(BACKWARD);
    frontLeft.run(BACKWARD);


    rearRight.run(FORWARD); // M2 inverted
    frontRight.run(BACKWARD);
  }
  // ----- Neutral / Steering only -----
  else if (throttle > 1400 && throttle <= 1600) {
    int leftSpeed  = 0;
    int rightSpeed = 0;


    if (steer > 1600) {       // turn left
      leftSpeed = 0;
      rightSpeed = 150;
    }
    else if (steer < 1400) {  // turn right
      leftSpeed = 150;
      rightSpeed = 0;
    }


    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);


    rearLeft.run(FORWARD);
    frontLeft.run(FORWARD);


    rearRight.run(BACKWARD); // M2 inverted
    frontRight.run(FORWARD);
  }
  // ----- Full Neutral below 1150 -----
  else {
    rearLeft.run(RELEASE);
    frontLeft.run(RELEASE);
    rearRight.run(RELEASE);
    frontRight.run(RELEASE);
  }


  // ----- Serial debug -----
  Serial.print("Throttle: "); Serial.print(throttle);
  Serial.print(" | Steering: "); Serial.print(steer);
  Serial.print(" | Speed: "); Serial.println(speed);


  delay(50);
}




