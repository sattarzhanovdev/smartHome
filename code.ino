#include <SoftwareSerial.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_NeoPixel.h>

#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 4
#define sensorPower 8
#define sensorPin A1
#define gasPin A0

Adafruit_NeoPixel shelf = Adafruit_NeoPixel(24, 5, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel signal = Adafruit_NeoPixel(1, 7, NEO_RGB + NEO_KHZ800);

byte readCard[4];
String cardID = "81A44524";
String chipId = "20CADE20";
String tagID = "";
unsigned long uidDec, uidDecTemp;  
Servo servo;
long blueRes;


MFRC522 mfrc522(SS_PIN, RST_PIN);

const int buzzerPin = 3;

SoftwareSerial bluetooth(0, 1);

long res;
int echoPin = 6; 
int trigPin = 7; 
 

void setup() {
  pinMode(2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  bluetooth.begin(9600);
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  digitalWrite(sensorPower, LOW);
  shelf.begin();
  signal.begin();   
}

void loop() {
  blueRes = (Serial.read());
  int gasValue = analogRead(gasPin);
  digitalWrite(sensorPower, HIGH); 

  int val = analogRead(sensorPin); 

  if(val > 800 || gasValue > 500){
    digitalWrite(2, HIGH);
    servo.write(90);
  }else{
    digitalWrite(2, LOW);
    servo.write(-90);
  }

  // if ( ! mfrc522.PICC_IsNewCardPresent()) {
  //   return;
  // }

  // if ( ! mfrc522.PICC_ReadCardSerial()) {
  //   return;
  // }
  // uidDec = 0;

  // for (byte i = 0; i < mfrc522.uid.size; i++)
  // {
  //   uidDecTemp = mfrc522.uid.uidByte[i];
  //   uidDec = uidDec * 256 + uidDecTemp;
  // }
  
  if (blueRes == 49){
    servo.write(-90);
    Serial.println(blueRes);
    delay(3000);
    servo.write(90);
  }else {
    servo.write(90);
  }

 
  // switch (blueRes) {
  //   case '1':
  //     digitalWrite(2, HIGH);
  //     delay(5000);
  //     digitalWrite(2, LOW);
  //     break;
  //   case '2':
  //     for(int i = 0; i < 24; i++){
  //       shelf.setBrightness(150);
  //       shelf.setPixelColor(i, shelf.Color(255, 255, 255));
  //       shelf.show();
  //     }
  //     break;
  //   case '3':
  //     servo.write(180);
  //     delay(3000);
  //     servo.write(-180);
  //     break;
  // }

  loop();

}


