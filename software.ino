
#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 4, 5, 6, 7, 8);     

const int input_digital = 2;  
unsigned long timp_afisare;        
unsigned long timp_masurare;     
unsigned long impulsuri;      
double frecventa;         
float perioada;
int unitate_masura = 1;     

void setup()     
{
  lcd.begin(16, 2);          
  lcd.setCursor(0, 0);            
  lcd.print("Frecventmetru");         
  lcd.setCursor(0, 1);            
  lcd.print("Proiect 2 ETTI");

  Serial.begin(9600);
  Serial.println("Frecventmetru");
  Serial.println("Proiect 2 ETTI");
}

void loop()                     
{
  perioada = 2 * pulseIn(input_digital, HIGH); 

  if (millis() - timp_afisare > 500) {   
    Serial.print("Frecventa:");
    Serial.print(frecventa);
    if (unitate_masura == 1)Serial.println("Hz");    
    else  if (unitate_masura == 2)Serial.println("kHz");

    lcd.clear();
    lcd.setCursor(0, 0);     
    lcd.print("Frecventmetru");
    lcd.setCursor(0, 1);     
    lcd.print("F:");
    lcd.print(frecventa);      
    if (unitate_masura == 1)lcd.print("Hz");    
    else  if (unitate_masura == 2)lcd.print("kHz");
    timp_afisare = millis(); 
  }  

  if (micros() - timp_masurare >= 100000) {   
    if (perioada)frecventa = 1000000 / perioada;   
    else frecventa = 0;

    if (frecventa > 1000) {     
      frecventa = frecventa / 1000;
      unitate_masura = 2;          
    }
    else unitate_masura = 1;  
    timp_masurare = micros();  //tine minte momentul de timp cand s-a facut masuratoare de frecventa
  }  //if timp

}  //loop
