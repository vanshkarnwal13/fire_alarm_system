#include <LiquidCrystal.h>
//SETUP FUNCTION
LiquidCrystal lcd(5,6,7,8,9,10);
float temp; 
float vout; 
float vout1;   
int redled = 2;
int greenled = 3;
int buzzer = 4;
int gassensor = A0;
int sensorThresh = 400;


void setup()
{
pinMode(redled, OUTPUT);//LED OUTPUT
pinMode(greenled,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(A1, INPUT);//TEMPERATURE SENSOR
pinMode(gassensor,INPUT);
Serial.begin(9600);
lcd.begin(16,2);//LCD(COLUMNS,ROWS)
}

void loop()
{
  vout=analogRead(A1);//VOLTAGE OUT FOR TEMPERATURE SENSOR
  vout1=(vout/1023)*5000;
  temp=(vout1-500)/10;//FROM VOLTS TO TEMP. IN C
  int analogValue = analogRead(gassensor);
  Serial.println(analogValue); 
  
  if(temp>=70)//CASES FOR TEMP. CONDITIONS
  {
    digitalWrite(redled,HIGH);
    digitalWrite(greenled,LOW);
  }
  else
  {
    digitalWrite(greenled,HIGH);
    digitalWrite(redled,LOW);
  }
  
  if(analogValue>sensorThresh)//SMOKE LEVEL CONDITIONS
  {
    
    tone(buzzer,1000,1000);//BUZZER(tone)
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Smoke Level:");
    lcd.print(analogValue);
    
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("  EVACUATE :(");
    delay(1000);
  }
  else
  {
    
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Smoke Level:");
    lcd.print(analogValue);
    delay(1000);
    
    lcd.setCursor(0,1);
    lcd.print("SAFE  :)");
    delay(1000);
  }
  Serial.print("in DegreeC= "); 
  Serial.print(" "); 
  Serial.print(temp);
  Serial.println();
  delay(500);
}
