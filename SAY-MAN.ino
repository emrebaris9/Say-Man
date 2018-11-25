#define echoPin 13 // --> Sensör_1
#define trigPin 7

#define echoPin2 10
#define trigPin2 9 // --> Sensör_2

#define ledpin  6 // --> Sensör_1 led
#define ledpin2  8 // --> Sensör_2 led

int kisi_sayisi=0;

boolean sensor1 = false;
boolean sensor2 = false;

boolean giris_durumu = false;
boolean cikis_durumu = false;

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledpin,OUTPUT);
  pinMode(ledpin2,OUTPUT);

  lcd.begin(16,2);
  lcd.print("Sistem Aciliyor");
  lcd.setCursor(0,1);
  lcd.print("Lutfen Bekleyin");
  delay(2000);
  lcd.clear();

  lcd.print("Y.Selim SAYDAM");
  lcd.setCursor(0,1);
  lcd.print("Y.Emre BARIS");
  delay(3000);
  lcd.clear();
  
  lcd.setCursor(4,0);
  lcd.print("SAYMAN");
  lcd.setCursor(0,1);
  lcd.print("  Hosgeldiniz");
  
}

void loop() {
  
   String veri;
   int sure,mesafe;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  mesafe = (sure/2) / 29.1;
  
 if(mesafe >0  && mesafe <= 30) {
    
    digitalWrite(ledpin,HIGH);
    sensor1 = true;
    delay(100);
  }
  

   int sure2,mesafe2;
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(500);
  digitalWrite(trigPin2, LOW);
  sure2 = pulseIn(echoPin2, HIGH);
  mesafe2 = (sure2/2) / 29.1;

 if(mesafe2 >0 && mesafe2 <= 30) {
    
    digitalWrite(ledpin2,HIGH);
    
    sensor2 = true;
    delay(100);
  }
 
  if(sensor1 == true && sensor2 == false)
  {
    giris_durumu = true;
    cikis_durumu = false;
    sensor2 =false;
   }
   else if(sensor2 == true && sensor1 == false)
    {
     cikis_durumu = true;
     giris_durumu = false;
     sensor1 = false;
    }


  if(giris_durumu == true && sensor2 == true)
  {
    kisi_sayisi++;
    
      Serial.println(kisi_sayisi);
      lcd.clear();
lcd.print("   Kisi Sayisi");
lcd.setCursor(7,1);
lcd.print(kisi_sayisi);
      denetle();
  }
  else if(cikis_durumu == true && sensor1==true)
  {
    kisi_sayisi--;

    if(kisi_sayisi <0)
    {
      kisi_sayisi=0;
    }
      Serial.println(kisi_sayisi);
     lcd.clear();
lcd.print("   Kisi Sayisi");
lcd.setCursor(7,1);
lcd.print(kisi_sayisi);
      denetle();
  }
  if(sensor1 == true && sensor2 == true)
  {
    denetle();
  }
  
 veri =kisi_sayisi;

if (Serial.available()) {
veri = Serial.read();
Serial.println(veri);
lcd.clear();
lcd.print("   Kisi Sayisi");
lcd.setCursor(7,1);
lcd.print(kisi_sayisi);
}
}

void denetle()
{
     cikis_durumu = false;
     giris_durumu = false;
     sensor1 = false;
     sensor2 = false;   
     digitalWrite(ledpin,LOW);
     digitalWrite(ledpin2,LOW);
      delay(500);
     return;
}
