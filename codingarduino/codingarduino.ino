#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#include <LedControl.h>
int DIN = 8;
int CS =  9;
int CLK = 10;

//toggle switch
const int mode1 = A3;
byte a0[8]=   {0x00,0x18,0x24,0x24,0x24,0x24,0x18,0x00};
  byte a1[8]=   {0x00,0x1C,0x08,0x08,0x08,0x0C,0x08,0x00};
  byte a2[8]=   {0x00,0x3C,0x08,0x10,0x20,0x24,0x18,0x00};
  byte a3[8]=   {0x00,0x18,0x24,0x20,0x10,0x24,0x18,0x00};
  byte a4[8]=   {0x00,0x20,0x20,0x20,0x3C,0x24,0x24,0x00};
  byte a5[8]=   {0x00,0x18,0x24,0x20,0x1C,0x04,0x3C,0x00};
  byte a6[8]=   {0x00,0x18,0x24,0x1C,0x04,0x24,0x18,0x00};
  byte a7[8]=   {0x00,0x04,0x08,0x10,0x20,0x20,0x3C,0x00};
  byte a8[8]=   {0x00,0x18,0x24,0x24,0x18,0x24,0x18,0x00};
  byte a9[8]=   {0x00,0x18,0x24,0x20,0x38,0x24,0x18,0x00};
  byte a10[8]=   {0x00,0x67,0x92,0x92,0x92,0x93,0x62,0x00};
  byte a11[8]=   {0x00,0x77,0x22,0x22,0x22,0x33,0x22,0x00};
  byte a12[8]=   {0x00,0xF7,0x22,0x42,0x82,0x93,0x62,0x00};
  byte a13[8]=   {0x00,0x67,0x92,0x82,0x42,0x93,0x62,0x00};
  byte a14[8]=   {0x00,0x87,0x82,0x82,0xF2,0x93,0x92,0x00};
  byte a15[8]=   {0x00,0x67,0x92,0x82,0x72,0x13,0xF2,0x00};
  byte a16[8]=   {0x00,0x67,0x92,0x72,0x12,0x93,0x62,0x00};
  byte a17[8]=   {0x00,0x17,0x22,0x42,0x82,0x83,0xF2,0x00};
  byte a18[8]=   {0x00,0x67,0x92,0x92,0x62,0x93,0x62,0x00};
  byte a19[8]=   {0x00,0x67,0x92,0x82,0xE2,0x93,0x62,0x00};
  byte a20[8]=   {0x00,0x6F,0x92,0x94,0x98,0x99,0x66,0x00};
  byte a21[8]=   {0x00,0xEF,0x42,0x44,0x48,0x69,0x46,0x00};
  byte a22[8]=   {0x00,0xFF,0x22,0x44,0x88,0x99,0x66,0x00};
  
int mode;

LedControl lc=LedControl(DIN,CLK,CS,0);

//Ultrasonic 1 (Bagian Depan)
#define echo1 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trig1 5 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration1; // variable for the duration of sound wave travel
int distance1; // variable for the distance measurement
long counter1=0; //variable for counter start
int distance1bef=20;

//Ultrasonic 2 (Bagian Belakang)
#define echo2 3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trig2 6 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration2; // variable for the duration of sound wave travel
int distance2; // variable for the distance measurement
long counter2=0; //variable for counter start
int distance2bef=20;

int sensorValue = 0;
const int red = 2; //lampu merah
const int yel = 1; //lampu kuning
const int grn = 0; //lampu hijau
int queue=0;
const int buttonPin = 7; //number of push button pin
int buttonState = 0; //variable for reading push button status

//Traffic Light
int redLEDpin = 13; // pin number for the red LED
int amberLEDpin = 12; // pin number for the amber LED
int greenLEDpin = 11; // pin number for the green LED
 
int amberDelay = 3; // pause in seconds to maintain the amber light
int redDelay = 6; // pause in seconds to maintain the red light

int x,a,g,f,angka,angka1,apapunlagi,angkak,k;
int y=0;

int jalan = A0;
int berhenti = A1;

void setup() {
  Serial.begin(9600);
  lcd.begin(20,4); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   APPLICATION OF"); 
  lcd.setCursor(0,1);
  lcd.print("   FUZZY LOGIC IN");
  lcd.setCursor(0,2);
  lcd.print("   TRAFFIC  LIGHT"); 
  lcd.setCursor(0,3);
  lcd.print("     CONTROLLER");


  delay(5000);
  lcd.setCursor(0,0);
  lcd.print("RAIN INTENSITY");
  lcd.setCursor(0,1);
  lcd.print("ARRIVING");
  lcd.setCursor(0,2);
  lcd.print("QUEUE");
  lcd.setCursor(0,3);
  lcd.print("GREEN LIGHT");
  

  lc.shutdown(0,false);       
 lc.setIntensity(0,15);      //Adjust the brightness maximum is 15
 lc.clearDisplay(0); 

  pinMode(mode1,INPUT);

  pinMode(trig1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echo1, INPUT); // Sets the echoPin as an INPUT
  pinMode(trig2, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echo2, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed

  pinMode(redLEDpin, OUTPUT); // set the R signal pin as an output
  pinMode(amberLEDpin, OUTPUT); // set the Y signal pin as an output
  pinMode(greenLEDpin, OUTPUT); // set the G signal pin as an output
  //Push Button Crossing
  pinMode(buttonPin, INPUT);

  pinMode(jalan,OUTPUT);
  pinMode(berhenti,OUTPUT);
  
}

void loop(){
    //Traffic Light
    if(Serial.available()){
      String apapun = Serial.readString();
      a=apapun.toInt();
    }
    digitalWrite(redLEDpin,LOW); // set the red LED to off by default
    digitalWrite(amberLEDpin,LOW); // set the amber LED to off by default
    digitalWrite(greenLEDpin,HIGH); // set the green LED to on by default
    digitalWrite(jalan,LOW); // set the green LED to on by default
    digitalWrite(berhenti,HIGH); // set the green LED to on by default
    x=0;
    if(y==0){
      a=5;
    }
    else{
      //dikirim a dr python
    }
    y++;
    angka=a+3;
    while(x<(a*4)){
      all();
      if((x%4)!=0){
        
      }
      else{
        angka--;
        cekangka();
      }
      //Traffic Light
      if (digitalRead(buttonPin)== HIGH){ // check if the incoming data is the letter 'P'
        //Serial.println("--- BUTTON HAS BEEN PRESSED ---");
        //Serial.println("--- GOING TO AMBER ---");  
        angkak=18;
        for (int count = 0; count <= amberDelay; count++){ // Loop through the amber sequence
          digitalWrite(amberLEDpin,HIGH); // set the amber LED to on
          digitalWrite(greenLEDpin,LOW); // set the green LED to off
          digitalWrite(jalan,LOW); // set the green LED to on by default
          digitalWrite(berhenti,HIGH); // set the green LED to on by default
          k=0;
          while(k<4){
            all();
            if((k%4)!=0){
              
            }
            else{
              angkak--;
              cekangkak();
            }
            delay(250);
            k++;
          }
        }
        //Serial.println("--- GOING TO RED ---"); 
        for (int count = 0; count <= redDelay; count++){ // Loop through the amber sequence
          digitalWrite(amberLEDpin,LOW); // set the amber LED to off
          digitalWrite(redLEDpin,HIGH); // set the red LED to on
          digitalWrite(jalan,HIGH); // set the green LED to on by default
          digitalWrite(berhenti,LOW); // set the green LED to on by default
          k=0;
          while(k<4){
            all();
            if((k%4)!=0){
              
            }
            else{
              angkak--;
              cekangkak();
            }
            delay(250);
            k++;
          }
        }
        //Serial.println("--- GOING TO FLASHING AMBER ---"); 
        for (int count = 0; count <= amberDelay*2; count++){ // Loop through the flashing amber sequence
          digitalWrite(redLEDpin,LOW); // set the red LED to off
          digitalWrite(jalan,LOW); // set the green LED to on by default
          digitalWrite(berhenti,HIGH); // set the green LED to on by default
          k=0;
          while(k<4){
            if(digitalRead(amberLEDpin)==LOW){
              digitalWrite(amberLEDpin,HIGH);
            }
            else{
              digitalWrite(amberLEDpin,LOW);
            }
            all();
            if((k%4)!=0){
              
            }
            else{
              angkak--;
              cekangkak();
            }
            delay(250);
            k++;
          }
        }
        //Serial.println("--- GOING TO BACK TO GREEN ---"); 
        digitalWrite(amberLEDpin,LOW); // set the amber LED to off
        digitalWrite(greenLEDpin,HIGH); // set the green LED to on
        digitalWrite(jalan,LOW); // set the green LED to on by default
        digitalWrite(berhenti,HIGH); // set the green LED to on by default
        //Serial.println("Enter P to Cross"); // resend the instruction
      }
      delay(250);
      x++;
    }
    
    //Traffic Light
    digitalWrite(redLEDpin,LOW); // set the red LED to off by default
    digitalWrite(amberLEDpin,HIGH); // set the amber LED to off by default
    digitalWrite(greenLEDpin,LOW); // set the green LED to on by default
    digitalWrite(jalan,LOW); // set the green LED to on by default
    digitalWrite(berhenti,HIGH); // set the green LED to on by default
    f=0;
    while(f<8){
      all();
      if((f%4)!=0){
        
      }
      else{
        angka--;
        cekangka();
      }
      delay(250);
      f++;
    }
    angka=0;
    cekangka();
    
    //Traffic Light
    digitalWrite(redLEDpin,HIGH); // set the red LED to off by default
    digitalWrite(amberLEDpin,LOW); // set the amber LED to off by default
    digitalWrite(greenLEDpin,LOW); // set the green LED to on by default
    digitalWrite(jalan,HIGH); // set the green LED to on by default
          digitalWrite(berhenti,LOW); // set the green LED to on by default
    g=0;
    angka=8+1+2;
    while(g<32){
      all();
      if((g%4)!=0){
        
      }
      else{
        angka--;
        cekangka();
      }
      delay(250);
      g++;
    }
    
    //Traffic Light
    digitalWrite(redLEDpin,LOW); // set the red LED to off by default
    digitalWrite(amberLEDpin,HIGH); // set the amber LED to off by default
    digitalWrite(greenLEDpin,LOW); // set the green LED to on by default
    digitalWrite(jalan,LOW); // set the green LED to on by default
          digitalWrite(berhenti,HIGH); // set the green LED to on by default
    f=0;
    while(f<8){
      all();
      if((f%4)!=0){
        
      }
      else{
        angka--;
        cekangka();
      }
      delay(250);
      f++;
      if(digitalRead(amberLEDpin)==HIGH){
        digitalWrite(amberLEDpin,LOW);
      }
      else{
        digitalWrite(amberLEDpin,HIGH);
      }
    }
    angka=0;
    cekangka();
    if(digitalRead(mode1)==HIGH){
      mode=1;
    }
    else if(digitalRead(mode1)==LOW){
      mode=2;
    }
    Serial.println(String(counter2)+';'+String(queue)+';'+String(sensorValue)+';'+String(mode));
    delay(250);
    Serial.flush();    
    counter2=0;

}

void ultrasonic1(){
  //Ultrasonic 1
  // Clears the trigPin condition
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration1 = pulseIn(echo1, HIGH);
  // Calculating the distance
  distance1 = duration1 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  /*Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");*/

  //Counter Ultrasonic 1
  if (distance1<8){
    if(distance1bef>=8){
      queue++;
      /*Serial.print("Counter 1: ");
      Serial.print(counter1);
      Serial.print('\n');*/
    }
  }
  distance1bef=distance1;
}

void ultrasonic2(){
  //Ultrasonic 2
  // Clears the trigPin condition
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration2 = pulseIn(echo2, HIGH);
  // Calculating the distance
  distance2 = duration2 * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  /*Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");*/
  
  //Counter Ultrasonic 2
  if (distance2<8){
    if(distance2bef>=8){
        if(queue>0){
          queue--;
          counter2++;
          /*Serial.print("Counter 2: ");
          Serial.print(counter2);
          Serial.print('\n');*/
        }
    }
  }
  distance2bef=distance2;
}

void rainsensorfunction(){
  sensorValue = analogRead(A2);
  /*Serial.print("Rain Sensor Value: ");
  Serial.print(sensorValue);
  Serial.println("");*/
  /*//rain sensor
  if(sensorValue>800){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("NO RAIN");
  }
  
  if(sensorValue<=800 && sensorValue>450){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rain: Low");
    lcd.setCursor(13,0);
    lcd.print(sensorValue);
    //delay(1000);
  }
  
  if(sensorValue<=450 && sensorValue>380){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rain: Medium");
    lcd.setCursor(13,0);
    lcd.print(sensorValue);
    //delay(1000);
  }
  
  if(sensorValue<=380){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rain: High");
    lcd.setCursor(13,0);
    lcd.print(sensorValue);
    //delay(1000);
  }*/
}

void all(){
    ultrasonic2();
    ultrasonic1();
    rainsensorfunction();
    lcd.setCursor(0,0);
    lcd.print("RAIN INTENSITY      ");
    lcd.setCursor(16,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,1);
    lcd.print("ARRIVING VEHICLE    ");
    lcd.setCursor(17,1);
    lcd.print(counter2);
    lcd.setCursor(0,2);
    lcd.print("QUEUEING VEHICLE    ");
    lcd.setCursor(17,2);
    lcd.print(queue);
    lcd.setCursor(0,3);
    lcd.print("GREEN DURATION     ");
    lcd.setCursor(17,3);
    lcd.print(a);

}

void cekangkak(){  
  if(angkak==22){
    printByte(a22);
  }
  else if(angkak==21){
    printByte(a21);
  }
  else if(angkak==20){
    printByte(a20);
  }
  else if(angkak==19){
    printByte(a19);
  }
  else if(angkak==18){
    printByte(a18);
  }
  else if(angkak==17){
    printByte(a17);
  }
  
  else if(angkak==16){
    printByte(a16);
  }
  else if(angkak==15){
    printByte(a15);
  }
  else if(angkak==14){
    printByte(a14);
  }
  else if(angkak==13){
    printByte(a13);
  }
  else if(angkak==12){
    printByte(a12);
  }
  else if(angkak==11){
    printByte(a11);
  }
  else if(angkak==10){
    printByte(a10);
  }
  else if(angkak==9){
    printByte(a9);
  }
  else if(angkak==8){
    printByte(a8);
  }
  else if(angkak==7){
    printByte(a7);
  }
  else if(angkak==6){
    printByte(a6);
  }
  else if(angkak==5){
    printByte(a5);
  }
  else if(angkak==4){
    printByte(a4);
  }
  else if(angkak==3){
    printByte(a3);
  }
  else if(angkak==2){
    printByte(a2);
  }
  else if(angkak==1){
    printByte(a1);
  }
  else{
    printByte(a0);
  }
}

void cekangka(){  
  if(angka==22){
    printByte(a22);
  }
  else if(angka==21){
    printByte(a21);
  }
  else if(angka==20){
    printByte(a20);
  }
  else if(angka==19){
    printByte(a19);
  }
  else if(angka==18){
    printByte(a18);
  }
  else if(angka==17){
    printByte(a17);
  }
  
  else if(angka==16){
    printByte(a16);
  }
  else if(angka==15){
    printByte(a15);
  }
  else if(angka==14){
    printByte(a14);
  }
  else if(angka==13){
    printByte(a13);
  }
  else if(angka==12){
    printByte(a12);
  }
  else if(angka==11){
    printByte(a11);
  }
  else if(angka==10){
    printByte(a10);
  }
  else if(angka==9){
    printByte(a9);
  }
  else if(angka==8){
    printByte(a8);
  }
  else if(angka==7){
    printByte(a7);
  }
  else if(angka==6){
    printByte(a6);
  }
  else if(angka==5){
    printByte(a5);
  }
  else if(angka==4){
    printByte(a4);
  }
  else if(angka==3){
    printByte(a3);
  }
  else if(angka==2){
    printByte(a2);
  }
  else if(angka==1){
    printByte(a1);
  }
  else{
    printByte(a0);
  }
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
