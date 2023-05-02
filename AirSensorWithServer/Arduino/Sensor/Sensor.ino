#include "DHT.h"
#include "WiFiNINA.h"
#include "arduino_secrets.h"
#include "SPI.h"


#define DHTTYPE DHT11
#define DHTPIN 12

DHT dht(DHTPIN, DHTTYPE);

float val;
int redPin = 2;
int greenPin = 7;


char ssid[] = SECRET_WIFINAME;
char pass[] = SECRET_WIFIPASS;
char serv[] = SECRET_SERVER;


int status = WL_IDLE_STATUS;
String postData;
String tempVariable = "temperature=";
String humidVariable = "&humidity=";
String heatVariable = "&heatIndex=";
String sensorIdVariable = "&sensorId=1";
String postText;

//server required SSL, if ever not needed, change  this to WifiClient and port to 80. 
// if this app does not work, try to update firmware first. Later, try to upload ssl cert.
WiFiSSLClient client;


void setup() {

  Serial.begin(9600);

  // init diodes
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);

  //init sensor
  dht.begin();
  delay(2000);

  //init wifi
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


void loop() {

  //getting sensor data
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  float hic = dht.computeHeatIndex(t, h, false);

  // combining gathered data into post data
  postData = tempVariable + t + humidVariable + h + heatVariable + hic + sensorIdVariable;


  //checking if recieved data is ok or nok
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    return;
  } else {

    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
  }



  //was the board connected so far?
  while (client.available()) {

    char c = client.read();

    Serial.write(c);
  }


  //connect to server and post data
  if (client.connect(serv, 443)) {
    Serial.println(client);
    Serial.println("connected to server");


    client.println("POST / HTTP/1.1");
    client.println("Host: " + String(SECRET_SERVER));
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection: close");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.print(postData);
    delay(10000);


  }



  else {

    // if you couldn't make a connection:

    Serial.println("connection failed");
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
  }


  while (client.available()) {
    char c = client.read();
    Serial.write(c);
  }



  if (client.connected()) {
    Serial.println("connection closed");
    client.stop();
  }





  delay(60000);
}
