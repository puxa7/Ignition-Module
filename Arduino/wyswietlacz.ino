void wyswietlacz()
{
  if(millis() - czasZerowanieWyswietlacza > 200)
  {
    lcd.setCursor(0,1);
    lcd.print("RPM ");
    lcd.setCursor(4,1);
    lcd.print("0   ");
    lcd.setCursor(9,1);
    lcd.print("BTDC ");
    lcd.setCursor(14,1);
    lcd.print("0 ");
  }
  else 
  {
    if(pokaz == false)
    {
      czasOpoznienieWyswietlacza=millis();
      pokaz = true;  
    }
                
    if(millis() > czasOpoznienieWyswietlacza+200)
    {
      lcd.setCursor(0,1);
      lcd.print("RPM ");
      lcd.setCursor(4,1);
      lcd.print(rpm);
      lcd.setCursor(9,1);
      lcd.print("BTDC ");
      lcd.setCursor(14,1);
      lcd.print(wyprzedzenieDocelowe*(-1));  
      pokaz=false;
    }
  }
}
