/*
this code resembles a submarine circuit with a bmp280, DHT11 and a MPU6050-gyro
together and show the temperatures an humidity on an OLED & serial monitor
with an arduino nano 
all this for an exam exercise for sensors & interfacing
*/

//inits DHT11
#include "DHT.h"
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <Adafruit_Sensor.h>
#include <Adafruit_Sensor.h>

//inits bmp sensor
#include <arduino.h>  //!!NOTE!!//
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;  // I2C
/*
#define BMP_SCK 13
#define BMP_MISO 12
#define BMP_MOSI 11 
#define BMP_CS 10

//Adafruit_BMP280 bmp(BMP_CS);// hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK)
*/

//inits gyro MPU6050
#include <Adafruit_MPU6050.h>
Adafruit_MPU6050 mpu;

// //inits oled
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

// #define SCREEN_WIDTH 128 // OLED display width, in pixels
// #define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// #define OLED_RESET     -1// Reset pin # (or -1 if sharing Arduino reset pin)

// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//leds for gyro indication
const int onder = 2;
const int midden = 3;
const int links = 4;
const int boven = 5;
const int rechts = 6;
//vent & leds
int vent = 9;
int aanled = 8;
int alarmled = 10;

// const int sensorPin = A0; 
// float sensorValue;
// float voltageOut;

float temperatureK;
float temperatureC;
float temperatureF;

float pressure; //used as variable for bmp sensor

void setup() {
  pinMode(onder, OUTPUT);
  pinMode(midden, OUTPUT);
  pinMode(links, OUTPUT);
  pinMode(boven, OUTPUT);
  pinMode(aanled, OUTPUT);
  pinMode(alarmled, OUTPUT);

  Serial.begin(9600);
  //testing dht
  Serial.println(F("DHTxx test!"));
  dht.begin();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(false);
  Serial.print("testing DHT");
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(("Failed to read from DHT sensor!"));
    return;
  }
  //testing bmp
  Serial.println(F("BMP280 test")); 
  if(!bmp.begin()) 
  {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while(1);
  }
  //testin/finding MPU6050
  if (!mpu.begin()) {
    Serial.println("Sensor init failed");
    while (1)
      yield();
  }
  Serial.println("Found a MPU-6050 sensor");

  // //testing OLED
  // if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;);
  // }
  // delay(2000);
  // display.clearDisplay();

  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 0);
  // // Display static text
  // display.println("Hello, world!");
  // display.display(); 
  //   delay(2000);

}
void loop() {
  //setting all gyro controlled les on LOW, this way we don't need do do that in each if at the end
  digitalWrite(onder, LOW);
  digitalWrite(midden, LOW);
  digitalWrite(links, LOW);
  digitalWrite(boven, LOW);
  digitalWrite(rechts, LOW);

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); 
  
  /*
  -this is the normale way of doing things but i dont lik naming 3 variables temperature
  -so when i print the value instead of giving a value i send a function that returns a value

    //Read values from the bmp sensor:
	pressure = bmp.readPressure();
	temperature = bmp.readTemperature();
	altimeter = bmp.readAltitude (30.26); //Change the "1050.35" to your city current barrometric pressure (https://www.wunderground.com)
	//and that is "30.26" for Brussels
  */

  //Print values to serial monitor
	Serial.print(F("BMP Pres: "));
  Serial.print(bmp.readPressure()); //print the read pressure value
  Serial.print(" Pa");
  Serial.print("\t");
  Serial.print(("BMP Temp: "));
  Serial.print(bmp.readTemperature());  //print the read temperature value
  Serial.print(" °C ");
  Serial.print("Altimeter: ");
  Serial.print(bmp.readAltitude (1029)); // this should be adjusted to your local forcase
  Serial.print(" m ");

  Serial.print("DHT Hum: ");
  Serial.print(dht.readHumidity());
  Serial.print("% DHT Temp: ");
  Serial.print(dht.readTemperature());
  Serial.println("°C ");
  // Serial.print(f);
  // Serial.print("°F  Heat index: ");
  // Serial.print(hic);
  // Serial.print("°C ");
  // Serial.print(hif);
  // Serial.println("°F");

  /*
  //print values of the gyro to the monitor not done now cause its cleaner this way
  Serial.print("Accelerometer:");
  Serial.print(" X: ");
  Serial.print(a.acceleration.x, 1);
  Serial.print(" Y: ");
  Serial.print(a.acceleration.y, 1);
  Serial.print(" Z: ");
  Serial.println(a.acceleration.z, 1);
  Serial.print("Gyroscope:");
  Serial.print(" X: ");
  Serial.print(g.gyro.x, 1);
  Serial.print(" Y: ");
  Serial.print(g.gyro.y, 1);
  Serial.print(" Z: ");
  Serial.println(g.gyro.z, 1);
*/

  //since my OLED broke along the way I couldn't use it but I still incude the code for if you want to
  //clear display
  // display.clearDisplay(); //clearing the OLED for good meassure

  // //display bmp temperature
  // display.setTextSize(1);
  // display.setCursor(0,0);
  // display.print("BMP Temp:");
  // display.setTextSize(1);  
  // display.print(bmp.readTemperature()); //print the read temperature value
  // display.print(" ");
  // display.setTextSize(1);
  // display.cp437(true);
  // display.write(167); //the symbol:"°"
  // display.setTextSize(1);
  // display.print("C");

  // //display bmp pressure 
  // display.setTextSize(1);
  // display.setCursor(0,11);
  // display.print("BMP Press:");
  // display.setTextSize(1);  
  // display.print(bmp.readPressure()/100); //print the read pressure value
  // display.print(" ");
  // display.setTextSize(1);
  // display.print("hPa");

  // //display dht temperature
  // display.setCursor(0,20);  //write on the third line
  // display.setTextSize(1);
  // display.print("DHT Temp:");
  // display.setTextSize(1);  
  // display.print(dht.readTemperature()); //print the read temperature value
  // display.print(" ");
  // display.setTextSize(1);
  // display.cp437(true);
  // display.write(167); //the symbol:"°"
  // display.setTextSize(1);
  // display.print("C");

  // display.setCursor(0,30);  //write on the forth line
  // display.setTextSize(1);
  // display.print("DHT Hum:");
  // display.setTextSize(1);  
  // display.print(dht.readHumidity()); //print the read humidity value
  // display.print(" ");
  // display.setTextSize(1);
  // display.print("%");

  // //display.clearDisplay();
  // display.setCursor(0, 40);
  // display.println("Accelerometer:");
  // display.print(a.acceleration.x, 1);
  // display.print(", ");
  // display.print(a.acceleration.y, 1);
  // display.print(", ");
  // display.print(a.acceleration.z, 1);
  // display.println("");

  // display.display();  //for now put this on the oled for a moment
  
  //controlling the leds from the gyro
  if (a.acceleration.x < 11 && a.acceleration.x > 9 && a.acceleration.y < 1 && a.acceleration.y > -1) {
    digitalWrite(midden, HIGH);
  }
  if (a.acceleration.z > 3) {
    digitalWrite(links, HIGH);
  }
  if (a.acceleration.z < -3) {
    digitalWrite(rechts, HIGH);
  }
  if (a.acceleration.y > 2) {
    digitalWrite(onder, HIGH);
  }
  if (a.acceleration.y < -2) {
    digitalWrite(boven, HIGH);
  }
  delay(250); //this is so that you can still see the leds going otherwise this loop would go way to fast for our eyes to see
  
  //if the bmp reads a temperature of 28 or higher a led will light up and the ventilator starts spinning
  if(bmp.readTemperature()>28){
    analogWrite(vent,255);
    digitalWrite(aanled,HIGH);
  }else{
    analogWrite(vent,0);
    digitalWrite(aanled,LOW);
  }
  //if the correct wire is disconnected we will light up a led to indicate this
  if(bmp.readTemperature()>100||bmp.readTemperature()< -30){
    digitalWrite(alarmled,HIGH);
  }else{
    digitalWrite(alarmled,LOW);
  }
}
