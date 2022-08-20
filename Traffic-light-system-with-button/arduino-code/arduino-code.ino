// C++ code
//Traffic-light-system-with-button

//State of the button declared
int buttonState = 0;
//Button's input
int button = 2;

//LED's output
int greenPedestrian = 8;
int redPedestrian = 9;
int greenCar = 10;
int yellowCar = 11;
int redCar = 12;

void setup()
{
  pinMode(2, INPUT);//button
  pinMode(greenPedestrian, OUTPUT);
  pinMode(redPedestrian, OUTPUT);
  pinMode(greenCar, OUTPUT);
  pinMode(yellowCar, OUTPUT);
  pinMode(redCar, OUTPUT);
}

void loop()
{
  //Setting all LEDs off
  digitalWrite(greenPedestrian, LOW);
  digitalWrite(redPedestrian, LOW);
  digitalWrite(greenCar, LOW);
  digitalWrite(yellowCar, LOW);
  digitalWrite(redCar, LOW);
  
  buttonState = digitalRead(button);
  
  if(buttonState == HIGH){
    //When not pressed = green for cars and red for pedestrians
    digitalWrite(greenCar,HIGH);
    digitalWrite(redPedestrian,HIGH);
  }else{
    //When pressed:
    //Set green for car and red for pedestrians
    digitalWrite(greenCar,HIGH);
    digitalWrite(redPedestrian,HIGH);
    //Yellow for cars for 2 seconds
    digitalWrite(greenCar,LOW);
    digitalWrite(yellowCar,HIGH);
    delay(2000);
    //Red for cars for 2 seconds
    digitalWrite(yellowCar,LOW);
    digitalWrite(redCar,HIGH);
    digitalWrite(redPedestrian,LOW);
    //Green for pedestrians for 2 seconds
    digitalWrite(greenPedestrian,HIGH);
    delay(2000);
    digitalWrite(greenPedestrian,LOW);
    //Pedestrian red led flashes for 2 seconds
    digitalWrite(redPedestrian,HIGH);
    delay(250);
    digitalWrite(redPedestrian,LOW);
    delay(250);
    digitalWrite(redPedestrian,HIGH);
    delay(250);
    digitalWrite(redPedestrian,LOW);
    delay(250);
    digitalWrite(redPedestrian,HIGH);
    delay(250);
    digitalWrite(redPedestrian,LOW);
    delay(250);
    digitalWrite(redPedestrian,HIGH);
    delay(250);
    digitalWrite(redPedestrian,LOW);
    delay(250);
    //Turn green for cars and red for pedestrians
    digitalWrite(greenCar,HIGH);
    digitalWrite(redPedestrian,HIGH);
  }
}
