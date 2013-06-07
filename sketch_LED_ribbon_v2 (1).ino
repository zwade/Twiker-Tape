#include "TimerOne.h"
const byte imgWidth = 2;
const byte totalRows = imgWidth*7-2;
byte row = 0;
byte col = 0;
byte frameCount = 0;
byte img[totalRows];
//char fontChar[95]={' ','!','\"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\\','^','[','_',']','`','{','|','}','~'};
//char fontChar[66]={' ','!','\"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']','^','_','`','|','~'};
byte fontData[95][5]={{0,0,0,0,0},{125,0,0,0,0},{48,0,48,0,0},{20,127,20,127,20},{18,42,127,42,36},{97,102,8,51,67},{20,42,127,42,0},{48,0,0,0,0},{28,34,65,0,0},{65,34,28,0,0},{40,16,40,0,0},{8,28,8,0,0},{3,0,0,0,0},{8,8,8,8,0},{1,0,0,0,0},{3,28,96,0,0},{62,69,73,81,62},{33,127,1,0,0},{35,69,73,49,0},{34,73,73,54,0},{120,8,8,127,0},{121,73,73,79,0},{62,73,73,38,0},{64,79,80,96,0},{54,73,73,54,0},{50,73,73,62,0},{34,0,0,0,0},{38,0,0,0,0},{8,20,34,0,0},{20,20,20,20,0},{34,20,8,0,0},{48,69,72,48,0},{127,65,93,65,125},{63,72,72,72,63},{127,73,73,73,54},{62,65,65,65,65},{127,65,65,65,62},{127,73,73,73,65},{127,72,72,72,64},{62,65,73,73,46},{127,8,8,8,127},{65,65,127,65,65},{7,1,1,127,0},{127,8,8,20,99},{127,1,1,1,0},{127,64,48,64,127},{127,96,28,3,127},{62,65,65,65,62},{127,72,72,72,48},{62,65,69,67,62},{127,72,72,72,55},{50,73,73,73,38},{64,64,127,64,64},{126,1,1,1,126},{112,14,1,14,112},{126,1,6,1,126},{99,20,8,20,99},{64,48,15,48,64},{67,69,73,81,97},{127,65,65,0,0},{96,28,3,0,0},{65,65,127,0,0},{16,32,64,32,16},{1,1,1,1,1},{32,16,0,0,0},{63,72,72,72,63},{127,73,73,73,54},{62,65,65,65,65},{127,65,65,65,62},{127,73,73,73,65},{127,72,72,72,64},{62,65,73,73,46},{127,8,8,8,127},{65,65,127,65,65},{7,1,1,127,0},{127,8,8,20,99},{127,1,1,1,0},{127,64,48,64,127},{127,96,28,3,127},{62,65,65,65,62},{127,72,72,72,48},{62,65,69,67,62},{127,72,72,72,55},{50,73,73,73,38},{64,64,127,64,64},{126,1,1,1,126},{112,14,1,14,112},{126,1,6,1,126},{99,20,8,20,99},{64,48,15,48,64},{67,69,73,81,97},{8,54,65,65,0},{127,0,0,0,0},{65,65,54,8,0},{8,16,8,16,0}};
//byte hw[11]={39,36,43,43,46,65,54,46,49,43,35};
char hw[imgWidth] = {72,105};

void setup()
{
  pinMode(8, OUTPUT); // din
  pinMode(7, OUTPUT); // Load Enable 
  pinMode(9, OUTPUT); // clock
  pinMode(13, OUTPUT); //The Flashy Red Light
  pinMode(10, OUTPUT); //
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);//OE
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(12, LOW);
  selectOut(0);
  int i;
  int j;
  byte temp;
  for (i = 0; i < totalRows; i++) {
    img[i] = 0;
  }
  byte conChar[imgWidth];
  for (i = 0; i < imgWidth; i++) {
    conChar[i] = hw[i]+32;
  }
    
  for(i=0; i <imgWidth; i++){
    for (j=0; j<5; j++) {
      byte temp = conChar[i];
      img[i*7+j] = fontData[temp][j];
    }
    img[i*7-2]=0;
    img[i*7-1]=0;
  }
  Timer1.initialize(1000);
  Timer1.attachInterrupt(updateLine);
}
void loop()
{
  /*
  for (int i = 0; i < 7; i++) {
    selectOut(i);
    //delay(1);
    if (i%2==0) {
      boolean x[] = {false,true,false,true,false};
      writeLine(x);
    } else {
      boolean x[] = {true,false,true,false,true};
      writeLine(x);
    }
  }*/
  
}
void updateLine(){
  //digitalWrite(12, HIGH);
  selectOut(row);
  //delay(1);
  digitalWrite(12, HIGH);
  writeLine();
  digitalWrite(12, LOW);
  row++;
  if(row > 6){
     row = 0;
     frameCount++;
     if(frameCount == 100){
       frameCount = 0;
       if (col>totalRows-6) {
         col = 0;
       } else {
         col++;
       }  
     } 
  }
}

void selectOut(byte num){
 if (num>=4) {
     digitalWrite(2, HIGH);
     num-=4;
 } else {
     digitalWrite(2, LOW);
 }
 if (num>=2) {
     digitalWrite(3, HIGH);
     num-=2;
 } else {
     digitalWrite(3, LOW);
 } 
 if (num>=1) {
     digitalWrite(4, HIGH);
 } else {
     digitalWrite(4, LOW);
  }
}

void writeLine(){
  for (byte i = col; i < col+5; i++)
  {
    digitalWrite(9, LOW);

     if (img[i]&(0b00000001<<(row)))
     {
        digitalWrite(8, HIGH);
     } else {
      digitalWrite(8, LOW);
     }
    digitalWrite(9, HIGH);

   
  }
  digitalWrite(7, HIGH);
  delay(0);
  digitalWrite(7,LOW);
}


