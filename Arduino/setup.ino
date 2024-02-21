void setup()
{
  Serial.begin(9600);
  SD.begin(4);
  pinMode(pinCewkaHV, OUTPUT);
  pinMode(pinHallSensor, INPUT_PULLUP); // 3 dla UNO, 1 dla Leonardo
  pinMode(pinPrzycisk, INPUT_PULLUP);
  attachInterrupt(3, funkcjaPrzerwania, FALLING); // 1 dla UNO, 3 dla Leonardo

  // Timer Compare Match Code
  // Inicjalizacja Timer1
  TCCR1A = 0; // zerowanie rejestru TCCR1A 
  TCCR1B = 0; // zerowanie rejestru TCCR1B 

  TCCR3A = 0;
  TCCR3B = 0;
  
  // Ustawienie compare match register na żądany czas odliczania:
  OCR1A = wyprzedzenie;  
  OCR3A = 3000/4; //3000us   
              
  TCCR1B |= (1 << WGM12);          // właczenie trybu CTC mode
  TCCR1B |= _BV(CS10) | _BV(CS11); // 
  TIMSK1 |= (1 << OCIE1A);         // włączenie trybu timer compare interrupt:

  TCCR3B |= (1 << WGM32);          // właczenie trybu CTC mode
  TCCR3B |= _BV(CS30) | _BV(CS31); // 
  TIMSK3 |= (1 << OCIE3A);         // włączenie trybu timer compare interrupt:


  
  lcd.init();                      
  lcd.backlight();
  lcd.clear();
  SD.remove("datalog.txt");         //usunięcie starego pliku datalog.txt z karty SD przy każdym uruchomieniu Arduino
  //Wire.setClock(400000);
}
