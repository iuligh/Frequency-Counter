
#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);     //definire pini pe care este conectat LCD

const int input_digital = 2;  //pinul folosit pentru masurarea frecventei
unsigned long timp_afisare;        //contor pentru perioada de afisare
unsigned long timp_masurare;     //contor pentru perioada de masurare
unsigned long impulsuri;      //numarul masurat de impulsuri primite
double frecventa;         //valoarea calculata pentru frecventa
float perioada;
int unitate_masura = 1;     //memoreaza unitatea de masura folosita Hz/kHz/MHz

void setup()     //se fac configurari o singura data in functia setup()
{
  lcd.begin(16, 2);          //initilizare LCD cu 2x16 caractere
  lcd.setCursor(0, 0);            //afisez pe primul rand al LCD
  lcd.print("Frecventmetru");          //mesaj initial pe LCD
  lcd.setCursor(0, 1);            //afisez pe al doilea rand al LCD
  lcd.print("Proiect 2 ETTI");

  Serial.begin(9600);
  Serial.println("Frecventmetru");
  Serial.println("Proiect 2 ETTI");
}

void loop()                     // bucla infinita while(1)
{
  perioada = 2 * pulseIn(input_digital, HIGH); //T= 2*Ton, pentru ca factorul de umplere este 50%

  if (millis() - timp_afisare > 500) {   //la fiecare 0.5 secunde
    Serial.print("Frecventa:");
    Serial.print(frecventa);
    if (unitate_masura == 1)Serial.println("Hz");    //afiseaza unitatea de masura corespunzatoare
    else  if (unitate_masura == 2)Serial.println("kHz");

    lcd.clear();
    lcd.setCursor(0, 0);     //afisez pe primul rand al LCD
    lcd.print("Frecventmetru");
    lcd.setCursor(0, 1);     //afisez pe al doilea rand al LCD
    lcd.print("F:");
    lcd.print(frecventa);      //afiseaza valoarea frecventei
    if (unitate_masura == 1)lcd.print("Hz");    //afiseaza unitatea de masura corespunzatoare
    else  if (unitate_masura == 2)lcd.print("kHz");
    timp_afisare = millis(); //tin minte momentul de timp cand a avut loc afisarea
  }  //if timp afisare

  if (micros() - timp_masurare >= 100000) {   //la fiecare 0.1 secunde
    if (perioada)frecventa = 1000000 / perioada;   //microsecunde =>Hz
    else frecventa = 0;

    if (frecventa > 1000) {     //transforma in kHz
      frecventa = frecventa / 1000;
      unitate_masura = 2;          //memoreaza unitatea de masura kHz
    }
    else unitate_masura = 1;   //altfel lasa unitatea de masura Hz
    timp_masurare = micros();  //tine minte momentul de timp cand s-a facut masuratoare de frecventa
  }  //if timp

}  //loop
