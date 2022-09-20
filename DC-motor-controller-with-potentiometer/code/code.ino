// C++ code
//

int potentiometer = 5; 
int aux = 0; // variable for map

void setup()
{
  pinMode(5, OUTPUT);
    pinMode(A5,INPUT);  
}

void loop()
{
  potentiometer = analogRead(A5);
    aux = map(potentiometer, 0, 1023, 0, 255);
    analogWrite(5, aux);
}
