// A simple circuit that changes a decimal numer into binary and counts downward.
// if i had a numberpad, this algorythm could be changed to a decimal to binary translator, without counting downwards.

int diodes[] = { 2, 4, 7, 8, 12, 13 };
int initialNum = 63;  //max = length()^^2

// https://forum.arduino.cc/t/how-do-you-check-the-length-of-an-array/88325/10
int sizeOfDiodes = sizeof(diodes) / sizeof(diodes[0]);
int num = initialNum;

void setup() {

  for (int i = 0; i < sizeOfDiodes; i++) {
    pinMode(diodes[i], OUTPUT);
  }
  Serial.begin(115200);
}

void loop() {


  String currentNum = fitToSize(decimalToBinary(num));
  Serial.println(currentNum);

  for (int i = 0; i < currentNum.length(); i++) {
    char c = currentNum[i];

    if (c == '1') {
      digitalWrite(diodes[i], HIGH);

    } else {
      digitalWrite(diodes[i], LOW);
    }
  }

  num -= 1;



  if (num < 0) {
    num = initialNum;
  }
  delay(1000);
}



// decimalToBinary gives a number without trailing zeros. Those have to be added to fit the diode scheme
String fitToSize(String num) {
  while (num.length() < sizeOfDiodes) {
    num = "0" + num;
  }
  Serial.println(num);
  return num;
}


// changes decimal to binary, returns a string of zeroes and ones
String decimalToBinary(int num) {
  if (num == 0) {
    return "0";
  }

  int binaryNum[sizeOfDiodes];
  int i = 0;

  for (; num > 0;) {
    binaryNum[i++] = num % 2;
    num /= 2;
  }
  String rtd = "";
  // Printing array in reverse order.
  for (int j = i - 1; j >= 0; j--) {
    rtd += binaryNum[j];
  }
  return rtd;
}
