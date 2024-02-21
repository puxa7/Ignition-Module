void zSerialDoEEPROM() //funkcja odbierająca dane z aplikacji
{
  static boolean odbieranieWtoku = false;
  static byte indeks = 0;
  char znakPoczatku = '<';
  char znakKonca = '>';
  char znak;
    
  while (Serial.available() > 0 && noweDane == false) 
  {
    znak = Serial.read();
    if (odbieranieWtoku == true)
    {
      if (znak != znakKonca)
      {
        otrzymaneZnaki[indeks] = znak;  
        indeks++;
        if (indeks >= liczbaZnakow)    
        {
          indeks = liczbaZnakow - 1;
        }
      }
      else
      {
        otrzymaneZnaki[indeks] = '\0';
        odbieranieWtoku = false;
        indeks = 0;
        noweDane = true;
      }
    }
    else if (znak == znakPoczatku)  // Zapis map z aplikacji do EEPROM
    {
     odbieranieWtoku = true;
    }
    else if(znak == '#') // Zmiana aktualnej mapy na podstawie informacji z aplikacji
    {
      char odebranyZnak = Serial.read();
      if(odebranyZnak=='1')
      {
        menu=1;
        zEEPROMdoTablicyInt();
        zaktualizujMenu();
      }
      else if(odebranyZnak=='2')
      {
        menu=2;
        zEEPROMdoTablicyInt();
        zaktualizujMenu();
      }
      else if(odebranyZnak=='3')
      {
        menu=3;
        zEEPROMdoTablicyInt();
        zaktualizujMenu();   
      }
      else if(odebranyZnak=='4')
      {
        menu=4;
        zEEPROMdoTablicyInt();
        zaktualizujMenu();
      }
      else if(odebranyZnak=='5')
      {
        menu=5;
        zEEPROMdoTablicyInt();
        zaktualizujMenu();
      }
    }
    else if(znak=='!') // Wysyłanie zawartości SD do aplikacji
    {
      char odebranyZnak = Serial.read();
      if(odebranyZnak == 'o')
      {
        myFile = SD.open("datalog.txt");
        if (myFile)
        {
          while (myFile.available())
          {
            Serial.write(myFile.read());
          }
          myFile.close();
        }
        else
        {
          Serial.println("blad w trakcie otwierania datalog.txt");
        }
      }
    }
  }
}
