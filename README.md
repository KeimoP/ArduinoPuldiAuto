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
#define THROTTLE_PIN A2
#define STEER_PIN    A0

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long throttle = pulseIn(THROTTLE_PIN, HIGH, 50000);
  unsigned long steer    = pulseIn(STEER_PIN, HIGH, 50000);

  int speed = 0;

  if (throttle > 1600) {
    speed = map(throttle, 1601, 2000, 0, 200);
    int leftSpeed = speed;
    int rightSpeed = speed;

    if (steer > 1600) leftSpeed = 0;
    else if (steer < 1400) rightSpeed = 0;

    rearLeft.setSpeed(leftSpeed);
    frontLeft.setSpeed(leftSpeed);
    rearRight.setSpeed(rightSpeed);
    frontRight.setSpeed(rightSpeed);

    rearLeft.run(FORWARD);
    frontLeft.run(FORWARD);
    rearRight.run(BACKWARD);
    frontRight.run(FORWARD);
  }
  else {
    rearLeft.run(RELEASE);
    frontLeft.run(RELEASE);
    rearRight.run(RELEASE);
    frontRight.run(RELEASE);
  }

  delay(50);
}
