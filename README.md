# VIN projekt - Odklepanje vrat z matrično tipkovnico

## Ideja
Ideja je preko tipkovnice prebrati varnostno kodo in na podlagi vnosa vrniti ustrezen odziv. V kolikor je bila prejeta koda pravilna se nam odprejo vrata (v mojem primeru sem vrata simuliral z zeleno LED, ki se obarva ob pravilni kombinaciji), v nasprotnem primeru smo opozorjeni, da vnesena koda ni pravilna.

## Delovanje
Arduino nano bere pritisnjene tipke na tipkovnici. Ob vsakem pritisku znak pošlje preko I2C protokola Arduino Unu. Ta doda znak k dosedaj prejetim znakom. V kolikor je prejeti znak * ali pa je koda daljša od 6 znakov preveri ali se prejeta koda ujema s pravo kodo. V kolikor se ujema se na zaslon izpiše dobrodošli in prižge se zelena LED, v nasprotnem primeru pa se na zaslon izpiše neveljavna koda in prižge se rdeča LED.

## Demonstracija (video)
[![Demonstracija projekta](https://i.ytimg.com/vi/Sgy8DASde9M/maxresdefault.jpg)](https://www.youtube.com/watch?v=Sgy8DASde9M)

## Shema vezja
Shema je priložena v obliki slike "VIN_shema.png"

## Komponente
- Arduino Uno
- Arduino Nano
- Matrična Tipkovnica (4x4)
- 2x LED (zelena in rdeča)
- LCD zaslon (16x2)


## Opis komponent

#### Arduino Uno in Arduino Nano
![image](./Slike-komponent/arduino_uno.png)
![image](./Slike-komponent/nano.jpg)  
Sta mikrokrmilnika, ki nam omogočata nadzorovanje vhodno izhodnih naprav. Imata pine za napajanje (5V in 3.3V), pine za ozemljitev, digitalne pine (tu sta le visoko in nizko stanje) in analogne pine (tu se napetost pretvori v vrednost med 0 in 1023).

#### Matrična Tipkovnica (4x4)
![image](./Slike-komponent/keypad.png)  
Ima osem pinov za priklov. Štirje služijo za vrstice in štirje za stolpce. Pritisnjene tipke zaznavamo s skeniranjem. Pine vseh vrstic nastavimo na visoko stanje. Nato se postavimo v prvo vrstico in stanje spremenimo na nizko, zatem postopoma pregledamo pine vseh stolpcev. Če je bila pritisnjena tipka v danem stolpcu in vrstici je vhodno stanje na pinu stolpca nizko. To ponavljamo za vse vrstice in stolpce in s tem beležimo pritiske tipk. Omenjeni nivoji so lahko tudi obratni, če namesto pull-up vezave uporabimo pull-down.

#### LCD Zaslon (16x2)
![image](./Slike-komponent/lcd.jpg)  
Zaslon nam omogoča izpis 32 znakov (po 16 na vrstico).
Ima naslednje pine:
- VSS - povezava na gnd
- VDD - povezava na 5V
- V0 - pin za nastavitev kontrasta (0-5V, večja kot je napetost večji je kontrast)
- RS - pin za izbiro registra (0 - ukazni, 1 - podatkovni)
- RW - pin za izbiro načina (0 - write, 1 - read)
- E - pin za vklop zaslona
- D0-D7 - pini za prenos podatkov
- LED+ - Anoda za osvetlitev odzadja 
- LED- - Katoda za osvetlitev odzadja

## I2C protokol
Je protokol, ki nam omogoča sinhron prenos podatkov. Preko protokola lahko povežemo več naprav hkrati in zahteva le dve žici. Prva je SDA (Serial Data), ta služi za prenos podatkov. Druga pa je SCL (Serial Clock), ta prenaša urin signal. Podatki, ki se prenašajo preko I2C protokola so sestavljeni v sporočila. Vsako sporočilo ima start bit, 7-10 bitov za naslov prejemnika, bit za določanje branja/pisanja, sledijo 8 bitni okvirji s podatki (za vsakim okvirjem se pošlje še potrditveni bit, ki nam pove ali je bil okvir uspešno prejet, tega pošlje prejemnik) in na koncu prenosa še stop bit.
