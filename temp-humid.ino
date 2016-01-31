
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

const byte nsum=10;

//int humidityPin=A0;
//int Thgm20Pin=A1;
int atomizationPin = 2;
unsigned int sensorValue2 = 0;  // variable to store the value coming from the sensor
unsigned int sensorValue3 = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  pinMode(atomizationPin, OUTPUT);
  lcd.begin(16, 2);
}

void loop() {
  for (byte i=0;i<nsum;i++)
  {    // read 10 values for T & H
    sensorValue2 += analogRead(A0);    
    sensorValue3 += analogRead(A1); 
  }   
  // average the value 
  int sensorValue2Avg=sensorValue2/nsum;
  float RH= 0.1515*sensorValue2Avg-12.0;
  
  int sensorValue3Avg=sensorValue3/nsum;
  float Vt=(float) sensorValue3Avg*5.0/1023.0;
  float R=(5.0-Vt)*10.0/Vt; // convert the value to relative humidity
  float TinC=281.583*pow(1.0230,(1.0/R))*pow(R,-0.1227)-150.6614; 
  float TinF=TinC*(9.0/5.0)+32; // convert the temperature to fahrenheit
  // print to serial monitor
  Serial.print(RH,0);
  Serial.println(" %RH");
  Serial.print(TinC,1);
  Serial.println(" deg C");
  Serial.print(TinF,1);
  Serial.println(" deg F");
  Serial.println(R);
  // print the value to lcd display
  lcd.setCursor(0, 0);
  lcd.print("%RH = ");
  lcd.setCursor(6, 0); //col, row
  lcd.print(R);
  lcd.setCursor(0, 1);
  lcd.print("T = ");
  lcd.setCursor(5, 1);
  lcd.print(TinC);
  //
  // if relatie humidity less than 40 % then turn on humidifire
  // for 10sec.
  if(R < 50){
  digitalWrite(atomizationPin, HIGH);
  delay(10000);
  digitalWrite(atomizationPin, LOW);
  }
  sensorValue2=0;
  sensorValue3=0;
  delay(5000);
}


