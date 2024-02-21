void loop()
{
  rpm = 1000000 * 60 / ((jedenStopien * 360));                                   // obroty na minutę
  wyprzedzenie = ((((193 + wyprzedzenieDocelowe) * jedenStopien) - 3000) / 4);   // wyliczenie wartości przekazywanej do rejestru OCR1A
  OCR1A = wyprzedzenie;
  
  zSerialDoEEPROM(); 
    
  if(noweDane == true) 
  {    
    String daneDoEEPROM="";
    for(int i=0;i<strlen(otrzymaneZnaki);i++)
    {
      daneDoEEPROM.concat(otrzymaneZnaki[i]);
    }
    zapiszStringDoEEPROM(0,daneDoEEPROM);
    noweDane = false;
  }
  else
  {
   zarzadzanieKat();
  }
  
  wyswietlacz(); // to wprowadza opóźnienie!!!!!!!!!!!!!!!!!
  przyciskPrzelaczMape();
  datalogger();
}
