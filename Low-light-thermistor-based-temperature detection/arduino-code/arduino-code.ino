// C++ code
//
void setup()
{
  //ANALOG READERS
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  //LEDs
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  
  Serial.begin(9600);
}

void loop()
{
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);

    Serial.println(analogRead(A1));
    
  //LIGHT LEVEL CHECK
  if (analogRead(A1) >= 600) {
    //VERY COLD
    if (analogRead(A0) < 131) {
    digitalWrite(13,HIGH);
    }
    //COLD
    if (analogRead(A0) >= 131 && analogRead(A0) < 141){
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);  
    }
    //FINE
    if (analogRead(A0) >= 141 && analogRead(A0) < 153){
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);  
        digitalWrite(11,HIGH);  
    }
    //HOT
    if (analogRead(A0) >= 153 && analogRead(A0) < 166){
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);  
        digitalWrite(11,HIGH);  
        digitalWrite(10,HIGH); 
    }
    //VERY hoT
    if (analogRead(A0) >= 166){
        digitalWrite(13,HIGH);
        digitalWrite(12,HIGH);  
        digitalWrite(11,HIGH);  
        digitalWrite(10,HIGH);
        digitalWrite(9,HIGH);
    }
  }
}
