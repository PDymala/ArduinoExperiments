
float val;
float maxVoltage = 2.0;
int redPin = 2;
int greenPin = 7;
int potentioPin = A2;

// a simple circuit that has a potentiometer that if exceds given voltage, shows ared led
void setup() {

  pinMode(potentioPin, INPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {


  val = mapFloat(analogRead(potentioPin), 0, 1023, 0, 5);  // read the input pin
  Serial.print(val);
  Serial.println("V");

  if (val > 2) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    Serial.println("Warning, voltage too high");
  } else {
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  delay(500);
}


// maps a value from a range to a different range. Standard map function converts all to ints, no use if theres float data
float mapFloat(float x, float inMin, float inMax, float outMin, float outMax) {
  return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}