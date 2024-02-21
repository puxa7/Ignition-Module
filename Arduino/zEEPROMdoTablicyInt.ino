void zEEPROMdoTablicyInt()
{
  char* wsk;
  char *charZEEPROM;
  string_z_EPPROM="";
  string_z_EPPROM=odczytajStringZEEPROM(0);

  String str_obj(string_z_EPPROM);
  charZEEPROM = &str_obj[0];
  rozmiar = string_z_EPPROM.length();  

  for (int i = 0; i < rozmiar; i++)
  {
    if (charZEEPROM[i] == ';')
    {
      licznik++;
    }
  }
    
  for (int i = 0; i <5; i++)
  {
    if(i==0)wsk = strtok(charZEEPROM, ",");
    else wsk = strtok(NULL, ",");
    int k = 0;
    int elementyWwsk = strlen(wsk);
    String nazwaMapy = "";

    while (k < elementyWwsk)
    {
      if (wsk[k] == '<' || wsk[k] == '>')
      {

      }
      else 
      {
        nazwaMapy += wsk[k];
      }
           
      k++;
    }
    tablicaMapy[i] = nazwaMapy;
               
    wsk = strtok(NULL, ",");
    tablicaINT[i][0] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][1] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][2] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][3] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][4] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][5] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][6] = atoi(wsk);

    wsk = strtok(NULL, ",");
    tablicaINT[i][7] = atoi(wsk);

    wsk = strtok(NULL, ";");
    tablicaINT[i][8] = atoi(wsk);
  }   
}
