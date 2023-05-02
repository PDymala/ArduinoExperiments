
//diodes
int diodeRed = 4;
int diodeYellow = 6;
int deiodeGreen = 2;

//distances
int distanceRed = 30;
int distanceYellow = 60;
// distanceGreen is just above distanceYellow

//misc
int frequencyApp = 200;  //delay for loop

//sensor
int Trig = 11;
int Echo = 13;
int CM;
long CZAS;

/*
A simple garage parking sensor with 3 LEDS. Depending on distance, shows different colors. Should work max 40cm
*/

void setup() {


  pinMode(diodeRed, OUTPUT);
  pinMode(diodeYellow, OUTPUT);
  pinMode(deiodeGreen, OUTPUT);
  pinMode(Trig, OUTPUT);  //ustawienie pinu 2 w Arduino jako wyjście
  pinMode(Echo, INPUT);   //ustawienie pinu 3 w Arduino jako wejście
  Serial.begin(9600);
  Serial.println("Testing...");
}

void loop() {




  measure();
  Serial.print("Length: ");
  Serial.print(CM);
  Serial.println(" cm");


  if (CM < distanceRed) {

    digitalWrite(diodeRed, HIGH);
    digitalWrite(diodeYellow, LOW);
    digitalWrite(deiodeGreen, LOW);
  } else if ((CM >= distanceRed) && (CM < distanceYellow)) {
    digitalWrite(diodeRed, LOW);
    digitalWrite(diodeYellow, HIGH);
    digitalWrite(deiodeGreen, LOW);
  } else {
    digitalWrite(diodeRed, LOW);
    digitalWrite(diodeYellow, LOW);
    digitalWrite(deiodeGreen, HIGH);
  }



  delay(frequencyApp);
}

void measure() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  //init signal 10ms
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  //actuall singnal
  digitalWrite(Echo, HIGH);
  CZAS = pulseIn(Echo, HIGH);
  CM = CZAS / 58;  //distance in cm
}
