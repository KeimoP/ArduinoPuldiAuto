# Vooluskeem ja ühendused

## Ülevaade

See dokument kirjeldab detailselt Arduino Puldiauto elektriühendusi.

## Täielik ühenduste tabel

| Komponent | Pin/Ühendus | Arduino/Sihtkoht | Märkused |
|-----------|-------------|------------------|----------|
| **L298N** | ENA | Arduino Pin 5 | PWM (vasak mootor kiirus) |
| **L298N** | IN1 | Arduino Pin 7 | Vasak mootor suund 1 |
| **L298N** | IN2 | Arduino Pin 6 | Vasak mootor suund 2 |
| **L298N** | IN3 | Arduino Pin 9 | Parem mootor suund 1 |
| **L298N** | IN4 | Arduino Pin 8 | Parem mootor suund 2 |
| **L298N** | ENB | Arduino Pin 10 | PWM (parem mootor kiirus) |
| **L298N** | GND | Arduino GND | Ühine maandus |
| **L298N** | 12V | 9V Aku + | Toide mootoritele |
| **L298N** | GND (toide) | 9V Aku - | Aku maandus |
| **L298N** | OUT1 | Vasak mootor + | Vasak mootor positiivne |
| **L298N** | OUT2 | Vasak mootor - | Vasak mootor negatiivne |
| **L298N** | OUT3 | Parem mootor + | Parem mootor positiivne |
| **L298N** | OUT4 | Parem mootor - | Parem mootor negatiivne |
| **L298N** | 5V | (Valikuline) | 5V väljund Arduinole |
| **IR Sensor** | VCC | Arduino 5V | Toide |
| **IR Sensor** | GND | Arduino GND | Maandus |
| **IR Sensor** | OUT/DATA | Arduino Pin 11 | Signaal |
| **Arduino** | VIN | (Valikuline) | 9V aku (kui ei kasuta USB) |
| **Arduino** | GND | Ühine GND | Kõigi komponentidega ühine |

## L298N Mooduli jumperite seadistamine

### ENA ja ENB Jumperid:
- **Jumper PEAL:** PWM kiiruse juhtimine on VÄLJAS, mootor töötab täisvõimsusel
- **Jumper EEMAL:** PWM kiiruse juhtimine on SEES (SOOVITATUD)

**Meie projektis:** Eemalda mõlemad jumperid (ENA ja ENB), et saaksime kasutada PWM-i kiiruse juhtimiseks.

### 5V Regulaatori jumper:
- **Jumper PEAL:** 5V regulaator ON (saab kasutada 5V väljundit)
- **Jumper EEMAL:** 5V regulaator OFF

**Meie projektis:** Hoia jumper peal, kui tahad kasutada L298N 5V väljundit Arduinole.

## Detailne ühendusdiagramm

```
┌─────────────────────────────────────────────────────────────┐
│                     ARDUINO UNO                              │
│  ┌────────────────────────────────────────────────────┐    │
│  │  Digital Pins              Analog Pins   Power     │    │
│  │  0  1  2  3  4  5  6  7  8  9 10 11 12 13         │    │
│  │              │  │  │  │  │  │  │                   │    │
│  │              ▼  ▼  ▼  ▼  ▼  ▼  ▼                   │    │
│  │             PWM          PWM                  5V GND│    │
│  └─────────────│──│──│──│──│──│──│───────────────│──│─┘    │
│                │  │  │  │  │  │  │               │  │       │
└────────────────│──│──│──│──│──│──│───────────────│──│───────┘
                 │  │  │  │  │  │  │               │  │
                 │  │  │  │  │  │  └───────────┐   │  │
                 │  │  │  │  │  │              │   │  │
    ┌────────────┘  │  │  │  │  │              │   │  └─┐
    │  ┌────────────┘  │  │  │  │              │   │    │
    │  │  ┌────────────┘  │  │  │              │   │    │
    │  │  │  ┌────────────┘  │  │              │   │    │
    │  │  │  │  ┌────────────┘  │              │   │    │
    │  │  │  │  │  ┌────────────┘              │   │    │
    │  │  │  │  │  │                           │   │    │
    ▼  ▼  ▼  ▼  ▼  ▼                           ▼   ▼    │
┌───────────────────────────────┐         ┌──────────┐  │
│         L298N MOODUL           │         │IR SENSOR │  │
│  ┌─────────────────────────┐  │         │ TSOP1738 │  │
│  │ IN1 IN2 IN3 IN4 ENA ENB │  │         │          │  │
│  │  7   6   9   8   5  10  │  │         │ OUT VCC  │  │
│  └─────────────────────────┘  │         │  │   │   │  │
│                                │         └──│───│───┘  │
│  ┌─────────────────────────┐  │            │   └──────┘
│  │ OUT1 OUT2 OUT3 OUT4     │  │            │
│  │  +    -    +    -       │  │            └─11
│  └──│────│────│────│────────┘  │
│     │    │    │    │           │
│     │    │    │    │    12V GND│
│     │    │    │    │     │  │  │
│     ▼    ▼    ▼    ▼     │  │  │
│  ┌────┐   ┌────┐         │  │  │
│  │ M1 │   │ M2 │         │  │  │
│  └────┘   └────┘         │  │  │
│  Vasak    Parem          │  │  │
│  Mootor   Mootor         │  │  │
└──────────────────────────┼──┼──┘
                           │  │
                     ┌─────┴──┴─────┐
                     │   9V AKU     │
                     │   +      -   │
                     └──────────────┘
```

## Sammud ühendamiseks

### 1. Ettevalmistus
- Veendu, et kõik komponendid on olemas
- Arduino ei ole ühendatud toitega
- Aku ei ole ühendatud

### 2. L298N → Arduino ühendused

**2.1 Juhtimispinnid:**
```
L298N Pin → Juhe värv (soovitus) → Arduino Pin
ENA       → Kollane              → 5 (PWM)
IN1       → Oranž                → 7
IN2       → Punane               → 6 (PWM)
IN3       → Pruun                → 9 (PWM)
IN4       → Hall                 → 8
ENB       → Valge                → 10 (PWM)
```

**2.2 Maandus:**
```
L298N GND → Must juhe → Arduino GND
```

**Kontrolli:**
- Kõik ühendused kindlad
- Õiged pin numbrid
- PWM pinnid ENA, ENB, IN2, IN3 jaoks

### 3. Mootorite ühendamine

**3.1 Vasak mootor:**
```
Mootor + → L298N OUT1
Mootor - → L298N OUT2
```

**3.2 Parem mootor:**
```
Mootor + → L298N OUT3
Mootor - → L298N OUT4
```

**Märkused:**
- Kui mootor pöörab vales suunas, vaheta + ja - ümber
- Mootorijuhtmed võivad olla punased ja mustad

### 4. IR Sensori ühendamine

**4.1 Sensori pin-ide tuvastamine:**

TSOP1738 (vaade eestpoolt):
```
    ┌───┐
    │ ● │  ← IR Vastuvõtja
    └┬─┬┘
     │ │ │
     1 2 3
     │ │ │
    OUT GND VCC
```

**4.2 Ühendused:**
```
IR Pin → Juhe värv → Arduino Pin
OUT    → Kollane   → 11
GND    → Must      → GND
VCC    → Punane    → 5V
```

**Tähtis:**
- Kontrolli oma sensori pinout-i datasheet-ist!
- Mõnel sensoril on pin-ide järjekord erinev
- Vale ühendus võib sensori kahjustada

### 5. Toite ühendamine

**5.1 Aku → L298N:**
```
Aku + (punane) → L298N 12V sisend
Aku - (must)   → L298N GND (toide terminal)
```

**5.2 Ühine maandus (VÄGA TÄHTIS!):**
```
L298N GND (signaal) → Arduino GND → Ühine punkt
L298N GND (toide)   ┘
```

**5.3 Arduino toide (vali üks variant):**

**Variant A - USB (testimiseks):**
```
Arduino USB port → Arvuti/Toiteadapter
```

**Variant B - Eraldi aku/L298N 5V väljund:**
```
L298N 5V väljund → Arduino 5V pin (kui L298N sisendpinge 7-12V)
või
Eraldi 9V aku → Arduino VIN pin
```

**Soovitus:** Kasuta USB-d testimiseks, seejärel lisa eraldi toide.

### 6. Lõplik kontroll enne toite sisselülitamist

**Kontrolli järgmist:**
- [ ] Kõik juhtmed on kindlalt ühendatud
- [ ] Ühine GND kõigi komponentide vahel
- [ ] L298N ENA ja ENB jumperid eemaldatud
- [ ] Mootorite polarisus kontrollitud
- [ ] IR sensori pinout õige
- [ ] Aku polarisus õige (+ ja -)
- [ ] Lühised puuduvad
- [ ] Kaablid ei puutu ratastes

## Toite vooluskeem

```
          9V AKU
            │
      ┌─────┴─────┐
      +           -
      │           │
      │           │
      ▼           ▼
   L298N 12V    L298N GND ──────┐
      │                         │
      ├─→ Mootorid (6-12V)      │
      │                         │
      └─→ 5V Regulaator         │
            │                   │
            └─→ Arduino 5V      │
                                │
    Arduino GND ────────────────┘
        │
    IR Sensor GND
```

## Elektriohutus

### Enne projekti alustamist:

1. **Kontrolli polarisust:**
   - + ja - õigesti ühendatud
   - Vale polarisus võib komponente kahjustada

2. **Ühine maandus:**
   - Kõik GND-d peavad olema ühendatud
   - Ilma ühise GND-ta signaalid ei toimi

3. **Lühised:**
   - Kontrolli, et + ja - juhtmed ei puutu
   - Kasuta isoleeritud juhtmeid

4. **Võimsus:**
   - L298N võib kuumeneda - see on normaalne
   - Kui muutub liiga kuumaks, vähenda koormat

5. **Patareide ohutus:**
   - Ära lühenda aku klemme
   - Kasuta õigeid patareisid (ei ülekoorma)
   - Li-Po akud vajavad eriti ettevaatlikkust

## Tõrkeotsingu ühendused

### Probleem: Midagi ei tööta

**Kontrolli:**
1. Multimeetriga mõõda aku pinget (peaks olema 7-9V)
2. Kontrolli Arduino toite LED (peaks põlema)
3. Kontrolli L298N toite LED (peaks põlema)
4. Kontrolli ühist maandust (GND kõikide vahel)

### Probleem: Mootorid ei pöörle

**Kontrolli:**
1. ENA ja ENB jumperid eemaldatud?
2. Mootori ühendused L298N-ga
3. Mootori testimine otse akuga (peaks pöörlema)
4. L298N väljundpinge mõõtmine

### Probleem: IR ei tööta

**Kontrolli:**
1. IR sensori polarisus (VCC, GND, OUT)
2. Õige pin Arduinole (11)
3. IR sensori toide (peaks olema 5V)
4. Puldi patareid

## Täiendav teave

### PWM Pinnid Arduino Uno-l:
- Pin 3, 5, 6, 9, 10, 11 - need saavad teha PWM-i
- Meie projektis kasutame 5, 6, 9, 10

### Voolu tarbimine:
- Arduino Uno: ~50mA
- IR sensor: ~1mA
- DC mootor (iga): 200-500mA (koormuseta), kuni 2A (koormuse all)
- **Kokku: ~1-2A normaalkasutuses**

### Soovitatud kaablid:
- Signaal (Arduino → L298N): 22-24 AWG, ~20-30cm
- Toide (Aku → L298N): 18-20 AWG, võimalikult lühike
- Mootorid (L298N → Mootorid): 20-22 AWG, ~10-20cm

---

**Küsimused vooluahelate kohta? Ava [issue](https://github.com/KeimoP/ArduinoPuldiAuto/issues)!**
