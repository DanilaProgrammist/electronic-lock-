#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define BUZZ 7
#define SS_PIN 10
#define RST_PIN 9
#define RED 5
#define BLUE 4
#define GREEN 3
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
const uint8_t valid_uid[] = { 0xA3, 0x78, 0xB7, 0x0A};
Servo servo;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  servo.attach(6);
  servo.write(0);
  
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
}
 
void loop() {
  
  if(!mfrc522.PICC_IsNewCardPresent())
    return;
 
  if(!mfrc522.PICC_ReadCardSerial())
    return;
 
  if((mfrc522.uid.size == sizeof(valid_uid)) &&
      (memcmp(&mfrc522.uid.uidByte, &valid_uid,
              sizeof(valid_uid)) == 0))
  {
    Serial.println("ACCESS GRANTED!");
    tone(BUZZ, 3000, 200);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
    servo.write(90);
    delay(3000);  
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, HIGH);
    servo.write(0);

  } else {
    Serial.println("Access denied.");
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    tone(BUZZ, 1500);
    delay(200);
    noTone(BUZZ);
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, HIGH);
  }
}
void green_led(){
      servo.write(90);
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
}
