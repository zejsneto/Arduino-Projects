// C++ code
//
int buttonState = 0;

/**
*Notes
*
*1 - DO or C
*2 - RE or D
*3 - MI or E
*4 - FA or F
*5 - SOL or G
*/
int empty[24];
int song[] = {1,2,3,4,4,4,1,2,1,2,2,2,1,5,4,3,3,3,1,2,3,4,4,4};
  
int count = 0;
int aux = 0;

void setup()
{
  /* RELAY */
  pinMode(13, OUTPUT);//RELAY
  
  /* BUTTONS */
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  
  /* LAMP AND LED(FOR TEST) */
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
 
  /* BUZZER */
  pinMode(2, OUTPUT);
  
  Serial.begin(9600);

}

void loop()
{
  buttonState = digitalRead(12);
  buttonState = digitalRead(11);
  buttonState = digitalRead(10);
  buttonState = digitalRead(9);
  buttonState = digitalRead(8);
 
  //DO or C
  if (digitalRead(12) == LOW) {
    tone(2, 262);
    delay(250);
    noTone(2);
    empty[count] = 1;
    
    //COMPARE BOTH ARRAYS
    if (empty[count] == song[count]) {
      aux = aux +1;
      if (aux == 24) {
        digitalWrite(7, HIGH);  //LED
            digitalWrite(13, HIGH); //LAMP
            delay(3000);
      }
    }
    count = count +1 ;
  }
  //RE or D
  if (digitalRead(11) == LOW) {
    tone(2, 294);
    delay(250);
    noTone(2);
    empty[count] = 2;
    
    //COMPARE BOTH ARRAYS
    if (empty[count] == song[count]) {
      aux = aux +1;
      if (aux == 24) {
        digitalWrite(7, HIGH);  //LED
            digitalWrite(13, HIGH); //LAMP
            delay(3000);
      }
    }
    count = count +1 ;
  }
  //MI or E
  if (digitalRead(10) == LOW) {
    tone(2, 330);
    delay(250);
    noTone(2);
    empty[count] = 3;
    
    //COMPARE BOTH ARRAYS
    if (empty[count] == song[count]) {
      aux = aux +1;
      if (aux == 24) {
        digitalWrite(7, HIGH);  //LED
            digitalWrite(13, HIGH); //LAMP
            delay(3000);
      }
    }
    count = count +1 ;
  }
  //FA or F
  if (digitalRead(9) == LOW) {
    tone(2, 394);
    delay(250);
    noTone(2);
    empty[count] = 4;
    
    //COMPARE BOTH ARRAYS
    if (empty[count] == song[count]) {
      aux = aux +1;
      if (aux == 24) {
        digitalWrite(7, HIGH);  //LED
            digitalWrite(13, HIGH); //LAMP
            delay(3000);
      }
    }
    count = count +1 ;
  }
  //SOL or G
  if (digitalRead(8) == LOW) {
    tone(2, 392);//SOL
    delay(250);
    noTone(2);
    empty[count] = 5;
    
    //COMPARE BOTH ARRAYS
    if (empty[count] == song[count]) {
      aux = aux +1;
      if (aux == 24) {
        digitalWrite(7, HIGH);  //LED
            digitalWrite(13, HIGH); //LAMP
            delay(3000);
      }
    }
    count = count +1 ;
  }
  
  
  
}
