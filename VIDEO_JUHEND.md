# Video juhendi plaan ja nõuanded

See dokument on abiks, kui soovid teha Arduino Puldiauto projekti kohta videojuhendi.

## 🎬 Video struktuuri soovitus

### Kogu video pikkus: 15-25 minutit

---

## 📝 Detailne stsenaarium

### 1. SISSEJUHATUS (0:00 - 1:00)

**Kaadrid:**
- Auto töötamise demo (5-10 sekundit)
- Titlekaart: "Arduino Puldiauto - DIY Projekt"
- Sina ekraanil, tutvustad end

**Tekst:**
```
Tere! Täna ehitame koos Arduino-põhise puldijuhitava auto.

See projekt on suurepärane algajatele, kes soovivad õppida:
- Arduino programmeerimist
- Mootorite juhtimist
- Infrapuna sensori kasutamist
- Robotite ehitamist

Lähme asjasse!
```

**Näpunäited:**
- Räägi selgelt ja aeglaselt
- Näita entusiasmi
- Näita lõplikku tulemust kohe alguses

---

### 2. KOMPONENTIDE TUTVUSTUS (1:00 - 3:00)

**Kaadrid:**
- Close-up iga komponendi kohta
- Näita käes ja selgita, mis see on

**Komponendid (näita järjekorras):**

1. **Arduino Uno** (10 sek)
   - "See on meie projekti aju - Arduino Uno"
   - Näita porte ja pinne

2. **L298N Mootorijuhtimismoodul** (15 sek)
   - "Sellega juhime kahte mootorit"
   - Näita pinne, sisendeid, väljundeid

3. **IR Vastuvõtja (TSOP1738)** (10 sek)
   - "Infrapuna sensor, millega vastu võtame puldi signaale"
   - Näita 3 jalga

4. **IR Pult** (10 sek)
   - "Tavaline infrapuna pult"
   - Demonstreeri telefoni kaameraga LED vilkumist

5. **DC Mootorid + Rattad** (15 sek)
   - "Kaks DC mootorit liikumiseks"
   - Keera käes, näita rattaid

6. **Toiteallikas** (10 sek)
   - "9V aku või 4x AA patareid"
   - Näita mõlemat varianti

7. **Juhtmed ja šassii** (10 sek)
   - "Dupont juhtmed ja auto raam"

**Tekst:**
```
Kogu komplekt maksab umbes 20-30 eurot.
Kõik osad leiab AliExpress-ist või kohalikest elektroonika poodidest.
Täpsem osade nimekiri on kirjelduses.
```

**Näpunäited:**
- Kasuta valget tausta
- Hea valgustus
- Selged close-up kaadrid

---

### 3. VOOLUSKEEM (3:00 - 6:00)

**Kaadrid:**
- Ekraanijagamine: sina koos skeemiga
- Zoom skeemi detailidele
- Näita ühendusi tahvlil

**Sisu:**

**3.1 Skeemi ülevaade (30 sek)**
```
"Vaatame, kuidas komponendid omavahel ühendatakse.
Siin on meie vooluskeem..."
```
- Näita täielikku skeemi
- Selgita peamisi blokke

**3.2 Arduino → L298N ühendused (60 sek)**
```
"Arduino juhib L298N-i 6 pinniga:
- Pin 5 (ENA) kontrollib vasaku mootorikiirust
- Pin 7 ja 6 (IN1, IN2) kontrollivad vasaku mootoriga suunda
- Pin 10 (ENB) kontrollib parema mootorikiirust  
- Pin 9 ja 8 (IN3, IN4) kontrollivad parema mootoriga suunda

Ja loomulikult GND ühine maandus."
```
- Näita iga ühendust skeemil
- Kasuta erinevaid värve

**3.3 L298N → Mootorid (30 sek)**
```
"L298N OUT1 ja OUT2 lähevad vasaku mootoriga
OUT3 ja OUT4 lähevad parema mootoriga"
```

**3.4 IR Sensor → Arduino (30 sek)**
```
"IR sensor on lihtne:
VCC läheb 5V-le
GND maandusele
OUT läheb Arduino Pin 11-le"
```

**3.5 Toide (30 sek)**
```
"VÄGA TÄHTIS: ühine maandus!
Aku miinus läheb L298N GND-le
L298N GND ühendub Arduino GND-ga
Kõik GND-d peavad olema kokku!"
```

**Näpunäited:**
- Kasuta graafikat (nooled, värvid)
- Näita skeemi aeglaselt
- Korda tähtsamaid punkte

---

### 4. MONTAAŽ - OSA 1: MEHAANILINE (6:00 - 10:00)

**Kaadrid:**
- Ülevalt alla vaade lauale
- Käed ja komponendid hästi nähtavad
- Time-lapse kiirete sammude jaoks

**Sammud:**

**4.1 Šassii ettevalmistus (30 sek)**
```
"Alustame šassii ettevalmistamisega..."
```
- Näita puidust/plastik šassii
- Märgi mootorite asukohad

**4.2 Mootorite kinnitamine (60 sek)**
```
"Kinnitame mootorid šassii mõlemale küljele..."
```
- Näita kruvimist
- Lisa rattad mootorite telgedele
- Kontrolli, et rattad pöörlevad vabalt

**4.3 Tugiratta lisamine (30 sek)**
```
"Tagumisele osale lisame tugiratta..."
```
- Kinnita tugiratas

**4.4 Komponentide paigutus (60 sek)**
```
"Nüüd paigutame elektroonika komponendid..."
```
- L298N šassii keskele
- Arduino L298N kõrvale
- IR sensor esiossa
- Aku tagaosa (tasakaal)

**4.5 Komponentide kinnitamine (30 sek)**
- Näita kuumliimi/kahepoolse teibi kasutamist
- Time-lapse kinnitamisest

**Näpunäited:**
- Selged kaadrid
- Hea valgustus ülevalt
- Räägi, mida teed

---

### 5. MONTAAŽ - OSA 2: ELEKTRIÜHENDUSED (10:00 - 14:00)

**Kaadrid:**
- Close-up ühenduste tegemisest
- Split-screen: käed + skeem

**Sammud:**

**5.1 Mootorite ühendamine L298N-ga (60 sek)**
```
"Esimesena ühendame mootorid L298N-ga..."
```
- Vasak mootor → OUT1 ja OUT2
- Parem mootor → OUT3 ja OUT4
- Selgita polarisust (hiljem saab vahetada)

**5.2 L298N → Arduino signaalid (90 sek)**
```
"Nüüd ühendame juhtimissignaalid..."
```
- Näita iga ühendust ühekaupa
- ENA → Pin 5
- IN1 → Pin 7
- IN2 → Pin 6
- IN3 → Pin 9
- IN4 → Pin 8
- ENB → Pin 10
- GND → GND

**5.3 IR Sensor (60 sek)**
```
"IR sensor ühendamine on lihtne..."
```
- Näita TSOP1738 pinout-i
- OUT → Pin 11
- GND → GND
- VCC → 5V

**5.4 Toite ühendamine (30 sek)**
```
"Viimane samm - toide..."
```
- Aku + → L298N 12V
- Aku - → L298N GND
- Kontrolli ühist GND-d

**Näpunäited:**
- Iga ühendus selgelt nähtav
- Kasuta värvilisi juhtmeid
- Paus iga ühenduse järel

---

### 6. PROGRAMMEERIMINE (14:00 - 18:00)

**Kaadrid:**
- Ekraani salvestus (Arduino IDE)
- Split-screen: ekraan + sina

**Sammud:**

**6.1 Arduino IDE setup (60 sek)**
```
"Avame Arduino IDE..."
```
- Näita IDE avamist
- Tools → Board → Arduino Uno
- Tools → Port → valik

**6.2 Teegi installimine (60 sek)**
```
"Vajame IRremote teeki..."
```
- Tools → Manage Libraries
- Otsi "IRremote"
- Installi näidates

**6.3 Koodi avamine (30 sek)**
```
"Avan PuldiAuto.ino faili..."
```
- Näita faili struktuuri
- Scroll läbi kood (kiiresti)

**6.4 Koodi selgitus (60 sek - valikuline, võib teha lühemaks)**
```
"Kiire ülevaade koodist..."
```
- setup() - millal käivitatakse
- loop() - peamine tsükkel
- handleCommand() - käskude töötlemine
- moveForward(), turnLeft(), jne - liikumisfunktsioonid

**6.5 Üles laadimine (30 sek)**
```
"Laadime koodi Arduino-sse..."
```
- Upload nupp
- Näita progressi
- "Done uploading" sõnum

**Näpunäited:**
- Ekraan peab olema selge
- Suurenda fondi
- Ära tee liiga kiirel

---

### 7. IR KOODIDE KALIBREERIMINE (18:00 - 20:00)

**Kaadrid:**
- Split-screen: Serial Monitor + pult

**Sammud:**

**7.1 Serial Monitori avamine (30 sek)**
```
"Avame Serial Monitori..."
```
- Tools → Serial Monitor
- Seadista 9600 baud

**7.2 Koodide lugemine (60 sek)**
```
"Vajutame puldil nuppu ja vaatame koode..."
```
- Vajuta UP → näita koodi (nt 0x18)
- Vajuta DOWN → näita koodi
- Vajuta LEFT → näita koodi
- Vajuta RIGHT → näita koodi

**7.3 Koodide uuendamine (60 sek)**
```
"Kui sinu koodid on erinevad, uuendame neid..."
```
- Näita handleCommand() funktsiooni
- Muuda case väärtusi
- Salvesta ja laadi uuesti

**Näpunäited:**
- Selgelt nähtav Serial Monitor
- Suurendanud tekst

---

### 8. TESTIMINE JA DEMO (20:00 - 22:00)

**Kaadrid:**
- Põrand-vaade auto sõitmisest
- Side-view ja top-view
- Slow-motion (valikuline)

**Sammud:**

**8.1 Esimene test (30 sek)**
```
"Paigutame auto põrandale ja katsetame..."
```
- Vajuta UP → auto liigub edasi
- Vajuta DOWN → tagasi
- Demonstreeri kõiki suundi

**8.2 Erinevad kiirused (30 sek)**
```
"Vajutades nuppe 1, 2, 3 saame muuta kiirust..."
```
- Demonstreeri aeglast
- Demonstreeri keskist
- Demonstreeri kiiret

**8.3 Täisvõimekuse demo (60 sek)**
- Sõida ringi
- Tee 8-kuju
- Näita manöövertsimisvõimet
- Lõbus demo muusikaga

**Näpunäited:**
- Hea valgustus
- Stabiilne kaamera või statiiv
- Võid lisada muusikat

---

### 9. TÕRKEOTSING (22:00 - 23:30)

**Kaadrid:**
- Sina ekraanil + bullet-points

**Tavaprobleemid (kiire ülevaade):**

```
"Kui midagi ei tööta:

1. Kontrolli akut - kas laetud?
2. Kontrolli ühendusi - kõik kinni?
3. Kontrolli ühist GND-d
4. Kui mootorid vales suunas - vaheta juhtmeid
5. Kui IR ei tööta - kontrolli sensorit ja koode

Täielik tõrkeotsingu juhend on GitHubis."
```

**Näpunäited:**
- Ära veeda liiga palju aega
- Viita GitHubi dokumentatsioonile

---

### 10. KOKKUVÕTE JA EDASIARENDUSED (23:30 - 25:00)

**Kaadrid:**
- Sina + lõplik auto

**Sisu:**

**10.1 Kokkuvõte (30 sek)**
```
"Täna ehitasime edukalt Arduino puldiauto!

Õppisime:
- Arduino programmeerimist
- Mootorite juhtimist L298N-ga
- IR puldi kasutamist
- Elektroonika komponentide ühendamist"
```

**10.2 Edasiarendused (45 sek)**
```
"Kuidas seda projekti edasi arendada?

1. Lisa ultrahelisensor - automaatne takistuste vältimine
2. Lisa Bluetooth moodul - juhtimine telefonist
3. Lisa joonejälgimise sensorid
4. Lisa LED tuled
5. Lisa LCD ekraan info näitamiseks

Kõik juhendid on GitHubis!"
```

**10.3 Lõpp (15 sek)**
```
"Kõik failid, kood ja dokumentatsioon on GitHubis:
github.com/KeimoP/ArduinoPuldiAuto

Like ja subscribe kui video meeldis!
Näeme järgmises projektis!"
```

---

## 🎥 Tehnilised soovitused

### Kaamera seadistused:
- **Resolutsioon:** 1080p minimum (4K ideaalne)
- **Kaadrisagedus:** 30fps (või 60fps smooth'imaks)
- **Fookus:** Autofookus või manuaal
- **Valgustus:** Päevavalgus või studio valgustus

### Salvestustarkvara:

**Ekraanisalvestus:**
- **OBS Studio** (Windows, Mac, Linux) - TASUTA
  - https://obsproject.com/
  - Parim valiku screencast'imiseks
  - Võimaldab multi-source'i (kaamera + ekraan)

**Videokaamera salvestus:**
- Telefon (kaasaegsed telefonid on piisavad)
- DSLR/Mirrorless (kui sul on)
- Webcam (vähemalt 1080p)

### Montaaž:

**Tasuta tarkvara:**
- **DaVinci Resolve** - Professionaalne, tasuta
  - https://www.blackmagicdesign.com/products/davinciresolve
  - Windows, Mac, Linux
  
- **Shotcut** - Lihtne, tasuta
  - https://shotcut.org/
  
- **OpenShot** - Algajasõbralik
  - https://www.openshot.org/

**Tasuline:**
- Adobe Premiere Pro
- Final Cut Pro (Mac)

### Audio:

**Mikrofon:**
- Vähemalt korralik USB mikrofon
- Või telefoni kõrvaklapid mikrofoniga
- Väldib arvuti ventilaatori müra

**Audio töötlus:**
- **Audacity** (tasuta)
  - Müra eemaldamine
  - Normalisering

### Graafika:

**Skeemide joonistamine:**
- **Fritzing** - Elektroonika skeemid
  - https://fritzing.org/
  
- **draw.io** - Diagrammid
  - https://app.diagrams.net/

**Thumbnails ja title cards:**
- **GIMP** (tasuta Photoshop)
  - https://www.gimp.org/
  
- **Canva** (online, lihtne)
  - https://www.canva.com/

### Muusika:

**Taustmuusika allikad (autoriõiguseta):**
- YouTube Audio Library
- Epidemic Sound (tasuline)
- Free Music Archive
- Incompetech

---

## 📋 Enne salvestamist (checklist)

### Ettevalmistus:
- [ ] Skript kirjutatud
- [ ] Komponendid korrastatud ja puhastatud
- [ ] Laud korrastatud
- [ ] Valgustus seadistatud
- [ ] Kaamera testsalvestus
- [ ] Audio testsalvestus
- [ ] Kõik failid avatud ja valmis

### Salvestuse ajal:
- [ ] Telefon vaiksel
- [ ] Taustamüra minimeeritud
- [ ] Hea valgustus
- [ ] Kaamera stabiilne
- [ ] Regulaarsed pausid (puhkus)

### Pärast salvestust:
- [ ] Vaata materjal läbi
- [ ] Kontrolli audio kvaliteeti
- [ ] Kontrolli video fookust
- [ ] Märgi üles, mis tuleb uuesti teha

---

## 🎬 Montaaži näpunäited

### Üldine struktuur:
1. **Intro** (5-10 sek) - Titlekaart, muusika
2. **Hook** (10-20 sek) - Näita lõpptulemus kohe
3. **Põhisisu** - Järgi stsenaariumi
4. **Outro** (10-20 sek) - Call-to-action, lingid

### Tempo:
- Kõnna aegluses kohtas, mis on keerulised
- Kiirenda (time-lapse) lihtsaid samme
- Hoia vaataja huvi üleval

### B-roll:
- Lisa lõikeid:
  - Auto sõitmisest eri nurkadest
  - Komponentide close-up'e
  - Käte liikumist
  - Testude tulemusi

### Tiitrid ja graafika:
- Näita komponendi nimei ekraanil
- Pin-numbrid nähtavad
- Tähtis info highlight-itud
- Sammude nummrid

### Ülemised kolmandikud (Lower thirds):
- Nimi ja tiitel
- Veebilingid
- Hoiatused

---

## 📊 YouTube optimeerimine

### Pealkiri:
- **Eesti:** "Arduino Puldiauto - Täielik DIY Juhend | IR Remote Control Car"
- **Inglise:** "Arduino RC Car Tutorial - Complete Guide | IR Remote Control"

### Kirjeldus:
```
🚗 Õpi ehitama oma Arduino puldijuhitav auto!

Selles videos ehitan samm-sammult IR puldiga juhitava auto kasutades:
- Arduino Uno
- L298N mootorijuhtimismoodul
- IR vastuvõtja ja pult
- 2x DC mootor

📂 Kõik failid GitHubis:
https://github.com/KeimoP/ArduinoPuldiAuto

📋 Ajamärgid:
0:00 - Intro
1:00 - Komponendid
3:00 - Vooluskeem
6:00 - Mehaaniline montaaž
10:00 - Elektriühendused
14:00 - Programmeerimine
18:00 - IR kalibreerimine
20:00 - Testimine
22:00 - Tõrkeotsing
23:30 - Kokkuvõte

🔧 Osad:
- Arduino Uno
- L298N
- TSOP1738
- IR Pult
- DC Mootorid
- Šassii
- Juhtmed

#arduino #diy #robotics #tutorial #eesti
```

### Thumbnail:
- Näita auto
- Suur tekst: "ARDUINO PULDIAUTO"
- Sinu nägu/käed
- Värviline ja silmatorkav

### Tags:
```
arduino, arduino uno, rc car, remote control car, diy, tutorial, 
robotics, l298n, ir sensor, estonian, eesti, puldiauto, 
arduino project, arduino car, motor control, electronics
```

---

## 📈 Postitamise strateegia

### Optimaalne aeg:
- **Argipäevad:** 18:00-20:00 (pärast tööd/kooli)
- **Nädalavahetus:** 10:00-12:00 (hommikusel ajal)

### Jagamine:
- Facebook grupid (Arduino, DIY, Elektroonika)
- Reddit (r/arduino, r/electronics, r/DIY)
- Twitter/X
- Instagram (lühike teaser)
- TikTok (30-60 sek clips)

### Community engagement:
- Vasta kommentaaridele
- Küsi tagasisidet
- Aita probleemide lahendamisel

---

## ✅ Lõplik kontroll-nimekiri

Enne video avaldamist:
- [ ] Kõik sammud selgelt nähtavad
- [ ] Audio kvaliteet hea
- [ ] Video kvaliteet hea (fookus, valgustus)
- [ ] Tiitrid ja graafika korrektsed
- [ ] Muusika ei ülekulu kõnet
- [ ] Ajamärgid lisatud
- [ ] Kirjeldus täielik
- [ ] Linkid töötavad
- [ ] Thumbnail atraktiivne
- [ ] End card lisatud (subscribe, järgmine video)

---

**Edu video tegemisega! 🎬**

Küsimused? Ava [issue](https://github.com/KeimoP/ArduinoPuldiAuto/issues)!
