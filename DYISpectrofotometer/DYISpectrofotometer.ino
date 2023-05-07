//SENSORS
int sensorRed = A0;
int sensorGreen = A1;
int sensorBlue = A2;

//LED
int PIN_RED = 5;
int PIN_GREEN = 10;
int PIN_BLUE = 11;

/*
A DYI attempt at spectrofotometer. Has 3 photoresistors with RGB stickers on them. The idea was that only the sticker color passes through.
RGB LED shows the color that is being read.

*/
void setup() {
  Serial.begin(9600);
  Serial.println("----  Test  ----");
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);

  //not necesesary
  analogWrite(PIN_RED, 255);
  analogWrite(PIN_GREEN, 255);
  analogWrite(PIN_BLUE, 255);
}

void loop() {

  //read the color via sensor. Maps the colors from sensor range to RGB range. Shows the result in console. Pushes the value later to RGB LED

  int valRed = analogRead(sensorRed);
  int valRedRange = map(valRed, 0, 1023, 0, 255);
  Serial.print("Red:");
  Serial.print(valRedRange);

  int valGreen = analogRead(sensorGreen);
  int valGreenRange = map(valGreen, 0, 1023, 0, 255);
  Serial.print(" Green:");
  Serial.print(valGreenRange);

  int valBlue = analogRead(sensorBlue);
  int valBlueRange = map(valBlue, 0, 1023, 0, 255);
  Serial.print(" Blue:");
  Serial.println(valBlueRange /);


  analogWrite(PIN_RED, valRedRange);
  analogWrite(PIN_GREEN, valGreenRange);
  analogWrite(PIN_BLUE, valBlueRange);

  delay(200);
}