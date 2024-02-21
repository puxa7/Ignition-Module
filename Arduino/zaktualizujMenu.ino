void zaktualizujMenu() 
{
  if(tablicaMapy[0]!="")
  {
    switch (menu)
    {
      case 0:
        menu = 1;
        break;
      case 1:
        lcd.setCursor(0,0);
        lcd.print(tablicaMapy[0]);
        for(int i=0; i<(16-tablicaMapy[0].length());i++)
        {
          lcd.print(" ");
        }
        pracujNaMapie(0);
        break;
      case 2:
        lcd.setCursor(0,0);
        lcd.print(tablicaMapy[1]);
        for(int i=0; i<(16-tablicaMapy[1].length());i++)
        {
          lcd.print(" ");
        }
        pracujNaMapie(1);  
        break;
      case 3:
        lcd.setCursor(0,0);
        lcd.print(tablicaMapy[2]);
        for(int i=0; i<(16-tablicaMapy[2].length());i++)
        {
          lcd.print(" ");
        }
        pracujNaMapie(2);
        break;
      case 4:
        lcd.setCursor(0,0);
        lcd.print(tablicaMapy[3]);
        for(int i=0; i<(16-tablicaMapy[3].length());i++)
        {
          lcd.print(" ");
        }
        pracujNaMapie(3);
        break;
      case 5:
        lcd.setCursor(0,0);
        lcd.print(tablicaMapy[4]);
        for(int i=0; i<(16-tablicaMapy[4].length());i++)
        {
          lcd.print(" ");
        }
        pracujNaMapie(4);
        break;
      case 6:
        menu = 5;
        break;
    }
  }
}