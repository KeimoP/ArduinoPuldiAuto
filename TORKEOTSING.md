# Tõrkeotsingu juhend

Kui sul on probleeme Arduino Puldiauto projektiga, vaata siit lahendusi tavalisematele probleemidele.

## 📋 Kiire kontroll-nimekiri

Enne detailset tõrkeotsingut kontrolli:
- [ ] Kas aku/patareid on laetud?
- [ ] Kas kõik juhtmed on korralikult ühendatud?
- [ ] Kas Arduino on toite all (LED põleb)?
- [ ] Kas L298N on toite all (LED põleb)?
- [ ] Kas ühine GND on olemas?
- [ ] Kas kood on õigesti Arduino-sse laaditud?
- [ ] Kas Serial Monitor on avatud (9600 baud)?

---

## 🔋 Toiteprobleemid

### Probleem: Midagi ei tööta, LED-id ei põle

**Võimalikud põhjused:**
1. Aku/patareid tühjad või pole ühendatud
2. Vale polarisus (+ ja - vahetatud)
3. Lühis voolukeskuses

**Lahendused:**
1. **Kontrolli akut:**
   ```
   Multimeetriga mõõda aku pinget:
   - 9V aku: peaks olema 7-9V
   - 4x AA: peaks olema 5-6V
   ```

2. **Kontrolli polarisust:**
   ```
   Punane juhe → + (pluss)
   Must juhe → - (miinus/GND)
   ```

3. **Kontrolli ühendusi:**
   - Veendu, et juhtmed on kindlalt sisestatud
   - Kontrolli, kas + ja - ei puutu

### Probleem: Arduino LED põleb, aga mootorid ei tööta

**Võimalikud põhjused:**
1. L298N ei saa piisavalt toidet
2. Mootorite ühendused puudu või valed
3. L298N jumperid (ENA/ENB) on valesti

**Lahendused:**
1. **Kontrolli L298N toidet:**
   - L298N vajab vähemalt 6V mootorite jaoks
   - Mõõda L298N 12V sisendi pinget

2. **Kontrolli ENA ja ENB jumpereid:**
   - Meie koodis PEAVAD need olema eemaldatud
   - Kui jumperid on peal, mootorid töötavad alati täisvõimsusel

3. **Kontrolli mootorite ühendusi:**
   - OUT1 ja OUT2 → Vasak mootor
   - OUT3 ja OUT4 → Parem mootor

---

## 🚗 Mootorite probleemid

### Probleem: Mootorid pöörlevad vales suunas

**Lahendus:**
Vaheta mootorijuhtmeid:
```
Enne:  Mootor + → OUT1, Mootor - → OUT2
Pärast: Mootor + → OUT2, Mootor - → OUT1
```

Või muuda koodis:
```cpp
void moveForward() {
  // Vaheta HIGH ja LOW
  digitalWrite(IN1, LOW);  // Oli HIGH
  digitalWrite(IN2, HIGH); // Oli LOW
  // ...
}
```

### Probleem: Üks mootor ei tööta

**Kontrolli:**
1. **Mootori testimine otse akuga:**
   ```
   Ühenda mootor otse 9V akuga:
   Mootor + → Aku +
   Mootor - → Aku -
   Kui mootor ei pöörle, mootor on katki
   ```

2. **L298N väljundi kontrollimine:**
   ```
   Multimeetriga mõõda pinget OUT pinidel
   Peaks olema ~6-9V kui mootor peaks töötama
   ```

3. **Juhtmeühenduste kontrollimine:**
   - Kontrolli IN1, IN2, ENA (vasak mootor)
   - Kontrolli IN3, IN4, ENB (parem mootor)

### Probleem: Üks mootor on aeglasem kui teine

**See on normaalne!** Kaks erinevat mootorit pole kunagi täpselt ühesugused.

**Lahendus - Tarkvara kompensimine:**
```cpp
// PuldiAuto.ino failis, muuda moveForward() funktsiooni:
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motorSpeed);  // Vasak mootor
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motorSpeed - 30);  // Parem mootor, 30 võrra aeglasem
}
```

Eksperimenteeri numbriga (20-40) kuni auto sõidab otse.

### Probleem: Mootorid ei saa piisavalt jõudu

**Võimalikud põhjused:**
1. Liiga nõrk aku
2. Liiga õhukesed juhtmed
3. motorSpeed liiga madal

**Lahendused:**
1. **Kasuta tugevamat toiteallikat:**
   - 9V aku asemel kasuta 4x AA patareisid
   - Või 7.4V Li-Po aku

2. **Suurenda tarkvara kiirust:**
   ```cpp
   int motorSpeed = 255;  // Maksimum (oli 200)
   ```

3. **Kontrolli juhtmeid:**
   - Kasuta paksemaid juhtmeid toite jaoks (18-20 AWG)
   - Hoia toite juhtmed võimalikult lühikesed

---

## 📡 IR Puldi probleemid

### Probleem: IR pult ei tööta üldse

**Kontrolli:**
1. **Puldi patareid:**
   - Vaheta uute vastu
   - Kontrolli polarisust patareihoidjas

2. **Puldi LED testimine:**
   ```
   Võta telefoni kaamera
   Vajuta puldil nuppu
   Vaata ekraanilt, kas LED vilgub (nähtav ainult kaamerast)
   Kui ei vilgu → pult on katki või patareid tühjad
   ```

3. **IR sensori ühendused:**
   ```
   TSOP1738:
   Pin 1 (OUT)  → Arduino Pin 11
   Pin 2 (GND)  → Arduino GND
   Pin 3 (VCC)  → Arduino 5V
   
   TÄHTIS: Kontrolli oma sensori datasheet-i!
   Pin järjekord võib erineda!
   ```

4. **IR sensori toide:**
   ```
   Multimeetriga mõõda:
   VCC ja GND vahel peaks olema 5V
   ```

### Probleem: Serial Monitor ei näita IR koode

**Lahendused:**
1. **Kontrolli Serial Monitori seadeid:**
   - Baud rate peab olema: **9600**
   - Vali õige port

2. **Kontrolli koodi:**
   ```cpp
   void setup() {
     Serial.begin(9600);  // Kontrolli, et see rida on olemas
     IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
   }
   ```

3. **Proovi IRrecvDemo näidet:**
   ```
   File → Examples → IRremote → ReceiveDemo
   Laadi see üles ja vaata, kas koodid tulevad
   ```

### Probleem: IR töötab, aga käsud on valed

**Sinu puldi koodid on erinevad!**

**Lahendus - Koodide kalibreerimine:**

1. **Ava Serial Monitor (Ctrl+Shift+M)**
2. **Vajuta puldil nuppu**
3. **Märgi üles kuvatav kood**, näiteks: `0x18`
4. **Uuenda PuldiAuto.ino failis:**

```cpp
void handleCommand(unsigned long cmd) {
  switch(cmd) {
    case 0x18:  // Asenda see SINU UP nupu koodiga
      moveForward();
      break;
      
    case 0x52:  // Asenda see SINU DOWN nupu koodiga
      moveBackward();
      break;
      
    case 0x08:  // Asenda see SINU LEFT nupu koodiga
      turnLeft();
      break;
      
    case 0x5A:  // Asenda see SINU RIGHT nupu koodiga
      turnRight();
      break;
      
    case 0x1C:  // Asenda see SINU OK nupu koodiga
      stopMotors();
      break;
  }
}
```

5. **Salvesta ja laadi uuesti Arduino-sse**

### Probleem: IR töötab ainult lähikonnas

**Võimalikud põhjused:**
1. Puldi patareid nõrgad
2. Sensori ees on takistus
3. Liiga palju päikesevalgust

**Lahendused:**
1. Vaheta puldi patareid
2. Veendu, et sensori ees pole takistusi
3. Testi siseruumis, vähem päikesevalgusega
4. Lisa sensori ette tume filter (valikuline)

---

## 💻 Programmeerimise probleemid

### Probleem: Arduino IDE ei leia plaati

**Lahendused:**
1. **Kontrolli USB kaablit:**
   - Kasuta andmeedastust toetavat kaablit (mitte ainult laadimiskaabel)
   - Proovi teist USB porti
   - Proovi teist USB kaablit

2. **Kontrolli plaadi valikut:**
   - Tools → Board → Arduino Uno

3. **Kontrolli porti:**
   - Tools → Port → Vali õige port
   - Windows: COM3, COM4, jne
   - Linux: /dev/ttyUSB0 või /dev/ttyACM0
   - Mac: /dev/cu.usbserial-*

4. **Installi CH340 draiver (kloonide jaoks):**
   - Otsi "CH340 driver download"
   - Installi ja restarti arvuti

### Probleem: Kompileerimise viga "IRremote.h: No such file"

**Lahendus:**
IRremote teek pole installitud.

```
1. Ava Arduino IDE
2. Tools → Manage Libraries (Ctrl+Shift+I)
3. Otsi "IRremote"
4. Installi "IRremote by shirriff, z3t0, ArminJo"
5. Sulge ja ava fail uuesti
6. Kompileeri uuesti
```

### Probleem: Kood ei üleslaadimisel

**Lahendused:**
1. **Eemalda IR sensor ajutiselt:**
   - IR sensor Pin 11-l võib segada üleslaadimist
   - Eemalda ühendus Pin 11-lt
   - Laadi kood üles
   - Ühenda IR sensor tagasi

2. **Kontrolli, et Serial Monitor on suletud:**
   - Serial Monitor peab olema suletud üleslaadimise ajal

3. **Proovi "Burn Bootloader":**
   - Tools → Burn Bootloader
   - Seejärel proovi uuesti üles laadida

---

## 🔧 Riistvara kontrollid

### L298N testimine

**Test 1 - Toite kontroll:**
```
Multimeeter DC voltage režiimis:
1. Mõõda L298N 12V sisendi ja GND vahel
   Peaks olema: 7-9V (sõltuvalt akust)

2. Mõõda L298N 5V väljundi ja GND vahel
   Peaks olema: ~5V (kui sisendpinge on 7-12V)
```

**Test 2 - Mootorite väljundi kontroll:**
```
1. Laadi üles kood
2. Multimeeter DC voltage režiimis
3. Käivita "liigub edasi" käsk
4. Mõõda OUT1 ja OUT2 vahel
   Peaks olema: 6-9V
5. Mõõda OUT3 ja OUT4 vahel
   Peaks olema: 6-9V
```

### IR Sensori testimine

**IRrecvDemo näide:**
```
1. File → Examples → IRremote → ReceiveDemo
2. Laadi Arduino-sse
3. Ava Serial Monitor (9600 baud)
4. Vajuta puldil nuppu
5. Peaks nägema hex koode
```

Kui koode ei tule:
- Kontrolli IR sensori ühendusi
- Kontrolli polarisust (VCC, GND, OUT)
- Proovi teist IR sensorit
- Kontrolli, et pult töötab (telefoni kaameraga)

---

## 🐛 Erilised olukorrad

### Auto pöörab ise ühe mootoriga

**Põhjus:** Üks mootor ei saa käske või on halb ühendus.

**Lahendus:**
1. Kontrolli selle mootoriga seotud pinne (IN3, IN4, ENB)
2. Kontrolli L298N ühendust selle mootori jaoks
3. Testi mootorit otse akuga

### Auto töötab ainult USB-ga, mitte akuga

**Põhjus:** Ühine GND puudu või aku liiga nõrk.

**Lahendus:**
1. **Kontrolli ühist GND:**
   ```
   Arduino GND
   L298N GND (signaal)  } Kõik peavad olema
   L298N GND (toide)    } ühendatud kokku
   Aku -
   ```

2. **Kontrolli aku:**
   - Mõõda aku pinget (peaks olema 7-9V)
   - Vaheta uue vastu

### Mootorid tõmbavad kogu toite ja Arduino restartib

**Põhjus:** Akul ei ole piisavalt võimsust (ampervool).

**Lahendus:**
1. Kasuta jõulisemat toiteallikat:
   - 4x AA (laetavad) asemel Li-Po aku
   - Suurema mahuga patareid

2. Lisa kondensaator L298N sisendi juurde:
   ```
   1000µF elektrolüüt kondensaator
   + → L298N 12V
   - → L298N GND
   ```

3. Kasuta Arduino jaoks eraldi toidet (USB või eraldi 9V)

### IR sõnumid tuleb duplikaatidena

**See on normaalne!** IR pult saadab koodi mitu korda, kui hoiad nuppu all.

**Kui soovid ainult üht käsku:**
```cpp
unsigned long lastCommand = 0;
unsigned long lastCommandTime = 0;

void loop() {
  if (IrReceiver.decode()) {
    unsigned long command = IrReceiver.decodedIRData.command;
    unsigned long currentTime = millis();
    
    // Ignoreeri koode, mis tulevad 200ms jooksul
    if (command != lastCommand || (currentTime - lastCommandTime) > 200) {
      handleCommand(command);
      lastCommand = command;
      lastCommandTime = currentTime;
    }
    
    IrReceiver.resume();
  }
}
```

---

## 🛠️ Kasulikud tööriistad

### Hädavajalik:
- **Multimeeter** - Pinge ja voolu mõõtmiseks
- **USB kaabel** - Programmeerimiseks
- **Telefon** - IR LED testimiseks

### Kasulik:
- **Logikaanalüsaator** - Signaalide kontrollimiseks
- **Jootekauplus** - Püsivate ühenduste jaoks
- **Soojendusliim** - Juhtmete kindlustamiseks

---

## 📞 Abi küsimine

Kui ükski neist lahendustest ei aita:

1. **Ava issue GitHubis:**
   - Mine: https://github.com/KeimoP/ArduinoPuldiAuto/issues
   - Kirjelda probleemi täpselt
   - Lisa pilte oma ühendustest
   - Kopeeri Serial Monitori väljund

2. **Lisa järgmine info:**
   - Arduino mudel (Uno, Nano, jne)
   - L298N mudel
   - IR sensori mudel
   - Toiteallikas (9V, 4xAA, jne)
   - Mida sa teinud oled
   - Mis töötab ja mis mitte
   - Serial Monitori väljund

3. **Kontrolli veel kord:**
   - Kõik ühendused
   - Polarisus (+ ja -)
   - Ühine GND
   - Juhtmete kindlus

---

**Edu projektiga! 🚗💨**
