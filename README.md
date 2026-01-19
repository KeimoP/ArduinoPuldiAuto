# Arduino Puldiauto - DIY Projekt

Arduino-põhine infrapuna puldiga juhitav auto. See on lihtne ja lõbus projekt algajatele, kes soovivad õppida robotite ehitamist ja programmeerimist.

## 📋 Sisukord

- [Ülevaade](#ülevaade)
- [Vajalikud komponendid](#vajalikud-komponendid)
- [Vooluskeem](#vooluskeem)
- [Montaaž](#montaaž)
- [Tarkvara seadistamine](#tarkvara-seadistamine)
- [Kasutamine](#kasutamine)
- [Video juhend](#video-juhend)
- [Tõrkeotsing](#tõrkeotsing)
- [Litsents](#litsents)

## 🎯 Ülevaade

See projekt võimaldab ehitada lihtsa puldijuhitava auto, mis kasutab:
- **Arduino Uno** mikrokonrollerit
- **L298N** mootorijuhtimismoodulit
- **IR (infrapuna)** puldijuhti ja vastuvõtjat
- Kaks **DC mootorit** liikumiseks

Auto saab liikuda neljasse suunas (edasi, tagasi, vasakule, paremale) ja on täiuslik platvorm robotika õppimiseks.

## 🛠️ Vajalikud komponendid

### Elektroonika:
1. **Arduino Uno** (või ühilduv kloon)
2. **L298N mootorijuhtimismoodul** - kahe mootoriga juhtimine
3. **TSOP1738 IR vastuvõtja** (või sarnane 38kHz IR sensor)
4. **IR pult** (võib kasutada vana TV pulti)
5. **2x DC mootor** (3-6V, ideaalsed on reduktoriga mootorid)
6. **Rattad** mootorite külge (tavaliselt kaasas robotauto komplektides)
7. **Toiteallikas:**
   - 9V aku või 4x AA patareihoidja mootorite jaoks
   - Arduino saab toite USB-st või eraldi 9V akust
8. **Juhtmed** (isane-isane, emane-emane, isane-emane)
9. **Breadboard** (valikuline, testimiseks)

### Mehaaniline:
- Auto šassii (võib olla puitplaat, plastik või ostetud robotauto raam)
- Tugiratas või libisemisjala (auto tasakaalu jaoks)
- Kruvikeere ja mutrid
- Kaablisidemed

### Hinnanguline kogumaksumus: 15-30€ (sõltuvalt tarnijast ja kvaliteedist)

## 📐 Vooluskeem

### Ühendused:

#### L298N → Arduino:
```
L298N       Arduino
ENA    →    Pin 5 (PWM)
IN1    →    Pin 7
IN2    →    Pin 6
IN3    →    Pin 9
IN4    →    Pin 8
ENB    →    Pin 10 (PWM)
GND    →    GND
```

#### IR vastuvõtja → Arduino:
```
IR Sensor   Arduino
VCC    →    5V
GND    →    GND
OUT    →    Pin 11
```

#### Mootorid → L298N:
```
Vasak mootor  →  OUT1 ja OUT2
Parem mootor  →  OUT3 ja OUT4
```

#### Toide:
```
- L298N 12V sisend → 9V aku +
- L298N GND → aku - ja Arduino GND
- Arduino toide → USB või eraldi toiteallikas
```

**NB!** Veendu, et kõik GND-d on ühendatud ühisesse maandusse.

### Skemaatiline diagramm:

```
                    ┌─────────────┐
                    │  Arduino    │
                    │   Uno       │
                    └──────┬──────┘
                           │
         ┌─────────────────┼─────────────────┐
         │                 │                 │
    ┌────▼────┐       ┌────▼────┐      ┌────▼────┐
    │ L298N   │       │IR Sensor│      │  Toide  │
    │ Mootor  │       │(TSOP1738)│     │  9V     │
    │ Juhtija │       └─────────┘      └─────────┘
    └────┬────┘
         │
    ┌────┴────┐
    │         │
  Motor1    Motor2
  (Vasak)   (Parem)
```

## 🔧 Montaaž

### Samm 1: Ettevalmistus
1. Kogu kõik komponendid kokku
2. Veendu, et Arduino IDE on installitud
3. Paigalda IRremote teek Arduino IDE-sse

### Samm 2: Šassii ettevalmistus
1. Kinnita mootorid šassii mõlemale küljele
2. Kinnita rattad mootorite telgedele
3. Lisa tagumisele osale tugiratas või libisemisjala
4. Kinnita L298N moodul šassii keskele
5. Kinnita Arduino Uno L298N kõrvale
6. Kinnita IR vastuvõtja auto esiossa (vaba nähtavusega)

### Samm 3: Elektriühendused
1. **Ühenda mootorid L298N-ga:**
   - Vasak mootor → OUT1 (+) ja OUT2 (-)
   - Parem mootor → OUT3 (+) ja OUT4 (-)

2. **Ühenda L298N Arduino-ga:**
   - Järgi ülalpool toodud vooluahelaskeemi
   - Kasuta PWM-i võimelisi pinne (5, 6, 9, 10) mootori kiiruse juhtimiseks

3. **Ühenda IR vastuvõtja:**
   - VCC → 5V
   - GND → GND  
   - OUT → Pin 11

4. **Ühenda toide:**
   - 9V aku positiivne → L298N 12V sisend
   - 9V aku negatiivne → L298N GND ja Arduino GND
   - Arduino võib saada toite USB-st testimise ajal

5. **Kontrolli kõik ühendused:**
   - Veendu, et ühendused on kindlad
   - Kontrolli polarisust (+ ja -)
   - Veendu ühises GND-s

### Samm 4: Kaablite korraldamine
1. Kasuta kaablisidemeid kaablite korrastamiseks
2. Hoia kaablid eemal rattaist ja liikuvatest osadest
3. Kinnita aku turvaliselt šassii külge

## 💻 Tarkvara seadistamine

### 1. Arduino IDE installimine
1. Laadi alla Arduino IDE [arduino.cc](https://www.arduino.cc/en/software)
2. Installi tarkvara oma arvutisse
3. Käivita Arduino IDE

### 2. IRremote teegi installimine
1. Ava Arduino IDE
2. Mine **Tools → Manage Libraries** (või Ctrl+Shift+I)
3. Otsi "IRremote"
4. Installi "IRremote by shirriff, z3t0, ArminJo" (uusim versioon)
5. Sulge Library Manager

### 3. Koodi üleslaadimine

1. Ühenda Arduino arvutiga USB kaabli kaudu
2. Ava fail `PuldiAuto/PuldiAuto.ino`
3. Vali õige laud: **Tools → Board → Arduino Uno**
4. Vali õige port: **Tools → Port → COM3** (Windows) või **/dev/ttyUSB0** (Linux)
5. Klõpsa **Upload** nuppu (nool paremale)
6. Oota, kuni üleslaadimine lõpeb

### 4. IR puldikoodide kalibreerimine

Sinu puldi koodid võivad erineda! Nende määramiseks:

1. Ava **Serial Monitor** (Tools → Serial Monitor või Ctrl+Shift+M)
2. Seadista baud rate: **9600**
3. Vajuta oma puldil nuppe
4. Vaata, millised koodid kuvatakse Serial Monitoris
5. Uuenda koodi muutujas `handleCommand()` oma puldi koodidega:

```cpp
case 0x18: // Asenda see oma UP nupu koodiga
```

### 5. Testimine

1. Ava Serial Monitor
2. Vajuta puldil nuppe
3. Peaks nägema sõnumeid nagu "Liigub edasi", "Pöörab vasakule" jne
4. Kui mootorid ei liigu, kontrolli ühendusi

## 🎮 Kasutamine

### Põhikäsud:

- **Nool Üles** - Auto liigub edasi
- **Nool Alla** - Auto liigub tagasi  
- **Nool Vasakule** - Auto pöörab vasakule (kohapeal)
- **Nool Paremale** - Auto pöörab paremale (kohapeal)
- **OK/Select** - Auto seiskub
- **Nupp 1** - Aeglane kiirus (150/255)
- **Nupp 2** - Keskmine kiirus (200/255)
- **Nupp 3** - Kiire kiirus (255/255)

### Näpunäited:

1. **Kiiruse reguleerimine:** Muuda `motorSpeed` väärtust (0-255)
2. **Sujuv juhtimine:** Lisa koodi `delay()` käsud pööramisel
3. **Automatiseerimine:** Lisa ultrahelisensor takistuste tuvastamiseks
4. **Joonejälgimine:** Lisa IR joonejälgimissensorid

## 🎥 Video juhend

### Soovitused videojuhendi tegemiseks:

1. **Sissejuhatus** (30 sek)
   - Projekti ülevaade
   - Lõpptulemus (töötav auto)

2. **Komponentide tutvustus** (1-2 min)
   - Näita kõiki osi
   - Selgita, mida iga komponent teeb

3. **Vooluskeem** (2-3 min)
   - Näita skeemi ekraanil
   - Selgita ühendusi

4. **Montaaž** (5-10 min)
   - Näita samm-sammult montaažiprotsessi
   - Rõhuta olulisi detaile (GND, polarisus)

5. **Programmeerimine** (3-5 min)
   - Näita koodi laadimist
   - Selgita koodiloogikat lihtsalt
   - Näita IR koodide kaliibreerimist

6. **Testimine ja demo** (2-3 min)
   - Näita auto sõitmist
   - Demo erinevaid funktsioone
   - Näita Serial Monitori väljundit

7. **Tõrkeotsing** (1-2 min)
   - Levinumad probleemid ja lahendused

8. **Kokkuvõte** (30 sek)
   - Projekti kokkuvõte
   - Edasiarenduse ideed

**Video kogupikkus:** 15-25 minutit

### Kasulikud lingid video tegemiseks:
- OBS Studio (tasuta videosalvestus): https://obsproject.com/
- DaVinci Resolve (tasuta videotöötlus): https://www.blackmagicdesign.com/products/davinciresolve
- Fritzing (skeemide joonistamine): https://fritzing.org/

## 🔍 Tõrkeotsing

### Auto ei liigu:

1. **Kontrolli toiteallikat:**
   - Kas aku on laetud?
   - Kas 9V ühendus on korras?

2. **Kontrolli ühendusi:**
   - Kas kõik juhtmed on korralikult ühendatud?
   - Kas L298N jumperid on õigesti paigaldatud?

3. **Kontrolli mootoreid:**
   - Ühenda mootor otse akuga (testimiseks)
   - Kui ei tööta, vaheta mootor

4. **Kontrolli L298N:**
   - Kas LED põleb?
   - Kontrolli, kas ENA ja ENB jumperid on peal

### IR pult ei tööta:

1. **Kontrolli IR vastuvõtjat:**
   - Kas on õigesti ühendatud?
   - Kas polarisus on õige? (VCC, GND, OUT)

2. **Kontrolli pulti:**
   - Kas patareid on sisas?
   - Kasuta kaamera telefonis, et näha IR LED-i vilkumist

3. **Kalibreeri koodid:**
   - Ava Serial Monitor
   - Vaata, millised koodid tulevad
   - Uuenda koodi nende koodidega

### Mootorid töötavad valesti:

1. **Pöörab vastupidises suunas:**
   - Vaheta mootorijuhtmed (+ ja -)

2. **Üks mootor aeglasem:**
   - See on normaalne, reguleeeri PWM väärtusi:
   ```cpp
   analogWrite(ENA, motorSpeed);
   analogWrite(ENB, motorSpeed - 20); // Aeglustab paremat mootorit
   ```

3. **Mootorid ei saa piisavalt toidet:**
   - Kasuta tugevamat akut
   - Kontrolli kaablite paksust

### Arduino ei käivitu:

1. Kontrolli USB ühendust
2. Vali õige port IDE-s
3. Proovi teist USB kaablit
4. Restarti Arduino IDE

## 🚀 Edasiarenduse ideed

1. **Ultrahelisensor** - Automaatne takistuste vältimise süsteem
2. **Bluetooth moodul** - Juhtimine nutitelefoni rakendusega
3. **Joonejälgimine** - Lisa IR sensorid joonejälgimiseks
4. **Kiirusesensor** - Jälgi läbitud vahemaad
5. **LED tuled** - Esi- ja tagaforid
6. **Servo mootor** - Pöörduv ultrahelisensor
7. **LCD ekraan** - Kuva kiirust ja režiimi
8. **Solaripaneel** - Keskkonnasõbralik toide

## 📚 Kasulikud ressursid

- [Arduino ametlik dokumentatsioon](https://www.arduino.cc/reference/en/)
- [IRremote teegi dokumentatsioon](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [L298N juhend](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)
- [Arduino foorum](https://forum.arduino.cc/)

## 🤝 Panus

Soovitused ja parandused on teretulnud! Ava issue või tee pull request.

## 📄 Litsents

See projekt on avaldatud MIT litsentsi all. Vaata `LICENSE` faili lisateabe saamiseks.

---

**Loodud armastusega Eesti DIY kogukonna jaoks! 🇪🇪**

Küsimused? Probleemid? Ava [issue](https://github.com/KeimoP/ArduinoPuldiAuto/issues)!