void przyciskPrzelaczMape()
{
  stanAktualny = digitalRead(pinPrzycisk);
  
  if( stanAktualny != ostatniaAktywacja )
  {
    if( stanAktualny == LOW )
    {
      czasAktywacji = millis();
      sprawdzeniePrzycisku = true;    
    }
    else
    {
      sprawdzeniePrzycisku = false;  
    }  
    ostatniaAktywacja = stanAktualny;
  }
    
  if( sprawdzeniePrzycisku )
  {
    if( (millis() - czasAktywacji ) >= czas_trzymania_przycisku )
    {
      if(menu==5)
      {
        menu=0;
      }
      menu++;
      zEEPROMdoTablicyInt();
      zaktualizujMenu();
      
      while(digitalRead(pinPrzycisk)==LOW);
    }     
  }
}
