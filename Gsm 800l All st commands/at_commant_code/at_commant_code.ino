#include <SoftwareSerial.h>
#include <stdlib.h>
#include <TinyGPS++.h>
static const int RXPin = 2, TXPin = 3;
static const uint32_t GPSBaud = 9600;
                                                                                                                                                                                                                              int  m = 9740;
                                                                                                                                                                                                                       int y = 71;
// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin); // for gps
SoftwareSerial SIM900(7, 8); // for gsm module


String textForSMS;
 int Yk_D0 = 12; // wire from the D0 pin of the yk04 receiver
 int buzz=10;
 
 double longitude; 
 double latitude;
char buff[10];

String mylong = ""; // for storing the longittude value
String mylati = ""; // for storing the latitude value
 
void setup()
{
  SIM900.begin(19200);
  Serial.begin(9600);
    ss.begin(GPSBaud);
  delay(5000);  // give time to log on to network. 
  Serial.println(" logging time completed!");
  randomSeed(analogRead(0));
  pinMode(Yk_D0, INPUT);
  digitalWrite(Yk_D0, LOW);
    pinMode(buzz, OUTPUT);
  digitalWrite(buzz, LOW);
  

}
 

 
void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(100);
 SIM900.println("AT + CMGS = \"+8801763663879\"");  // recipient's mobile number, in international format
  delay(100);
  SIM900.println(message);                         // message to send
  delay(100);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
                                  
}
 
void loop()
{

 
    // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
 // for the Yk_D0 
//*****************************************************************
//****************************************************************
  if(digitalRead(Yk_D0) == HIGH)
  {
    digitalWrite(buzz,HIGH);
  Serial.println(" Button Pressed");
 displayInfo();
 latitude = gps.location.lat(), 6 ;
longitude = gps.location.lng(), 6 ;
// for latitude
  mylati = dtostrf(latitude, 3, 6, buff);
  mylong = dtostrf(longitude, 3, 6, buff);
  
 //textForSMS = textForSMS + "Latitude:" + "," + mylati + "," + "Longitude:  "+ mylong + ",";
 textForSMS = textForSMS + "http://www.google.com/maps/place/" + mylati + "," + mylong ; 
  sendSMS(textForSMS);
    textForSMS = " I am in emergency I need help! ";
  Serial.println(textForSMS);
  Serial.println("message sent.");
  delay(5000);
  }
 

}


void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(" ");
    Serial.print(F("Speed:"));
    Serial.print(gps.speed.kmph());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
