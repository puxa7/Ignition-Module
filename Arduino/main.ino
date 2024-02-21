#include <Arduino.h>
#include <Wire.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>

int kk=0;
int tab1[200];

LiquidCrystal_I2C lcd(0x27,20,4);  
File myFile;

String 
  tablicaMapy[5],
  string_z_EPPROM = "";

const int 
  pinCewkaHV = 8,
  pinHallSensor = 1, // 3 dla UNO, 1 dla Leonardo
  pinPrzycisk = 7;

const 
  byte liczbaZnakow = 250;

char 
  otrzymaneZnaki[liczbaZnakow],
  tablicaTymczasowa[liczbaZnakow]; // tymczasowa tablica do użycia podczas analizowania

boolean 
  noweDane = false;

volatile unsigned long
 aktualneMicros,
 aktualneMicros2,
 czasZerowanieWyswietlacza=0,
 poprzedniCzasStartu,
 poprzedniCzasStartu2,
 uplynaCzasKorekta,
 wyprzedzenie = 0xFFFF;


volatile float 
  jedenStopien; // czas obrotu wału korbowego o jeden stopień [us]

volatile 
  boolean iskraWlaczona = false; // używane do wyłączenia funkcji generującej iskrę

volatile int 
  wyprzedzenieDocelowe = 0;  

int
  kat[] = {20, 20, 20, 20, 20, 20, 20, 20, 20},
  rpm = 0,
  licznik=0,
  rozmiar,
  menu=0,
  czas_trzymania_przycisku=250,
  tablicaINT[5][9];

byte 
  stanAktualny, 
  ostatniaAktywacja;

unsigned long
  czasOpoznienieWyswietlacza,
  czasAktywacji,
  czasDatalog;

bool 
  pokaz=false,
  datalog=false,
  sprawdzeniePrzycisku;

void funkcjaPrzerwania()
{
    //Serial.println(millis());
    aktualneMicros = micros();
    unsigned long uplynalCzas = (aktualneMicros - poprzedniCzasStartu);
    /*unsigned long*/ uplynaCzasKorekta = uplynalCzas + 1980;
    //Serial.println(uplynaCzasKorekta); sprawdzanie - ok
    // Filtr
	  if(uplynaCzasKorekta  <= 6976) // czujnik zgłasza z powodu zakłóceń obroty wyższe niż 8600 rpm
    {                              // lub czas obrotu wału mniejszy niż 6976 us - przypisz poprzednią prawidłową wartość
      jedenStopien=jedenStopien;
    }
    else
    {
	    jedenStopien = uplynaCzasKorekta / 360.0; //jeżeli czas obrotu wału nie jest za niski
    }                                           // zaktualizuj w zmiennej czas aktualnego obrotu wału
    // Filtr

    poprzedniCzasStartu = aktualneMicros;
    if(jedenStopien>19.608) // ograniczenie obrotów maksymalnych 8500 RPM 
    {
        TCCR1B |= _BV(CS10) | _BV(CS11); //Start TIMER1 Preskaler 64
    }
}

ISR(TIMER1_COMPA_vect) //Timer1 Compare Match ISR: Funkcja przerwania timera
{
    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12)); //zatrzymaj licznik
    TCNT1 = 0;                                      //wyzeruj licznik
    Iskra();                                        //uruchom funkcję generowania funkcji
    /*if(iskraWlaczona)
    {
        digitalWrite(pinCewkaHV, HIGH);
    } 
    TCCR3B |= _BV(CS30) | _BV(CS31); //Start TIMER3 Preskaler 64*/
}

ISR(TIMER3_COMPA_vect) //Timer3 Compare Match ISR: Funkcja przerwania timera
{
    TCCR3B &= ~(_BV(CS30) | _BV(CS31) | _BV(CS32)); //zatrzymaj licznik
    TCNT3 = 0;                                      //wyzeruj licznik
    digitalWrite(pinCewkaHV, LOW);                                        
}

void Iskra()
{
    if(iskraWlaczona)
    {
        digitalWrite(pinCewkaHV, HIGH);
        delayMicroseconds(3000);
        digitalWrite(pinCewkaHV, LOW);
    } 
         
        aktualneMicros2 = micros();
        unsigned long uplynalCzas2 = (aktualneMicros2 - poprzedniCzasStartu2+1980);
        //Serial.print(uplynaCzasKorekta);
        //Serial.print(",");
        //Serial.println(uplynalCzas2);
        poprzedniCzasStartu2 = aktualneMicros2;
        
    czasZerowanieWyswietlacza=millis();
}

int mapowanie(int x, int in_min, int in_max, int out_min, int out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void zarzadzanieKat()
{
    if (rpm < 130)
    {
        iskraWlaczona = false;
        wyprzedzenieDocelowe = 0;
    }
    else if (rpm < 1000) 
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 130, 1000, kat[0], kat[1]);
    }
    else if (rpm < 2000) 
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 1000, 2000, kat[1], kat[2]);
    }
    else if (rpm < 3000) 
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 2000, 3000, kat[2], kat[3]);
    }
    else if (rpm < 4000) 
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 3000, 4000, kat[3], kat[4]);
    }
    else if (rpm < 5000) 
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 4000, 5000, kat[4], kat[5]);
    }
    else if (rpm < 6000)
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 5000, 6000, kat[5], kat[6]);
    }
    else if (rpm < 7000)
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 6000, 7000, kat[6], kat[7]);
    }
    else if (rpm < 8000) 
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -1 * mapowanie(rpm, 7000, 8000, kat[7], kat[8]);
    }
    else
    {
        iskraWlaczona = true;
        wyprzedzenieDocelowe = -30;
    }
}

void setup();
void loop();

void zapiszStringDoEEPROM(int adres, String str)
{
  byte len = str.length();
  EEPROM.write(adres, len);

  for (int i=0;i<len;i++)
  {
    EEPROM.write(adres + 1 +i, str[i]);
  }
}

String odczytajStringZEEPROM(int adres)
{
  int len = EEPROM.read(adres);
  char dane[len+1];

  for(int i=0;i<len;i++)
  {
    dane[i]=EEPROM.read(adres + 1 +i);
  }
  dane[len]='\0';

  return String(dane);
}
