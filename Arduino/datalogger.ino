void datalogger()
{
  String daneString = "";

  if(menu==1)
  {
    daneString += String(millis());
    daneString += ",";
    daneString += tablicaMapy[0];
    daneString += ",";
    daneString += String(rpm);
    daneString += ",";
    daneString += String(wyprzedzenieDocelowe*(-1));
  }
  else if(menu==2)
  {
    daneString += String(millis());
    daneString += ",";
    daneString += tablicaMapy[1];
    daneString += ",";
    daneString += String(rpm);
    daneString += ",";
    daneString += String(wyprzedzenieDocelowe*(-1));
  }
  else if(menu==3)
  {
    daneString += String(millis());
    daneString += ",";
    daneString += tablicaMapy[2];
    daneString += ",";
    daneString += String(rpm);
    daneString += ",";
    daneString += String(wyprzedzenieDocelowe*(-1));
  }
  else if(menu==4)
  {
    daneString += String(millis());
    daneString += ",";
    daneString += tablicaMapy[3];
    daneString += ",";
    daneString += String(rpm);
    daneString += ",";
    daneString += String(wyprzedzenieDocelowe*(-1));
  }
  else if(menu==5)
  {
    daneString += String(millis());
    daneString += ",";
    daneString += tablicaMapy[4];
    daneString += ",";
    daneString += String(rpm);
    daneString += ",";
    daneString += String(wyprzedzenieDocelowe*(-1));
  }

  if(daneString != "" )
  {
    if(datalog == false)
    {
      czasDatalog=millis();
      datalog = true;  
    }
                
    if(millis() > czasDatalog+50)
    {
      File myFile = SD.open("datalog.txt", FILE_WRITE);  
      if (myFile) 
      {
        myFile.println(daneString);
        myFile.close(); 
        
      }
      else 
      {
        Serial.println("blad w trakcie otwierania datalog.txt");
      }
      
      
      
      
     /* tab1[kk]=millis();
      kk++;
      //Serial.println(kk);
      if(kk==60)
      {
        for(int ii=0;ii<60;ii++)
        {
          Serial.println(tab1[ii]);  
        }
      }*/
      
      datalog=false;
    }   
  }    
} 
