#include <SoftwareSerial.h>
#include <TinyGPS.h>
#define RXPIN 3
#define TXPIN 2

//5461AS pins
#define SEG_E 4
#define SEG_D 5
#define SEG_DP 6
#define SEG_C 7
#define SEG_G 8
#define DIG_4 9
#define SEG_B 10
#define DIG_3 11
#define DIG_2 12
#define SEG_F 14
#define SEG_A 15
#define DIG_1 16

#define DELAY_T 5

TinyGPS gps;
SoftwareSerial ss(RXPIN, TXPIN);

void display_int(int dig, int num);

//bits
bool bits[10][7] = {
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1}, 
  {0,1,1,0,0,1,1}, 
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1}, 
  {1,1,1,0,0,0,0}, 
  {1,1,1,1,1,1,1}, 
  {1,1,1,1,0,1,1}
};

int dig_1;
int dig_2;
int dig_3;
int dig_4;

float num;

void setup(){
  Serial.begin(19200);
  ss.begin(9600);
  pinMode(DIG_1,OUTPUT);
  pinMode(DIG_2,OUTPUT);
  pinMode(DIG_3,OUTPUT);
  pinMode(DIG_4,OUTPUT);
  pinMode(SEG_A,OUTPUT);
  pinMode(SEG_B,OUTPUT);
  pinMode(SEG_C,OUTPUT);
  pinMode(SEG_D,OUTPUT);
  pinMode(SEG_E,OUTPUT);
  pinMode(SEG_F,OUTPUT);
  pinMode(SEG_G,OUTPUT);
  pinMode(SEG_DP,OUTPUT);
}

void loop(){
  int i = 100;
  while(ss.available())
  {
    i++;
    if(gps.encode(ss.read()))
    {
       //gps.f_get_position(&lat, &lon, &age);
       //Serial.println(num);
      
        num = gps.f_speed_kmph();
        
        //Calculate digits
        dig_1 = (int)(num / 10);
        dig_2 = (int)(num) % 10;
        dig_3 = (int)(num*10) % 10;
        dig_4 = (int)(num*100) % 10;
    }
  }    
  
  for(int i = 0; i < 20; i++)
  {
    display_int(1, dig_1);
    delay(DELAY_T);
    display_int(2, dig_2);
    delay(DELAY_T);
    display_int(3, dig_3);
    delay(DELAY_T);
    display_int(4, dig_4);
    delay(DELAY_T);
  }
}

void display_int(int dig, int num) {
  digitalWrite(DIG_1, HIGH);
  digitalWrite(DIG_2, HIGH);
  digitalWrite(DIG_3, HIGH);
  digitalWrite(DIG_4, HIGH);

  switch(dig)
  {
    case 1:
      digitalWrite(DIG_1, LOW);
      break;
    case 2:
      digitalWrite(DIG_2, LOW);
      break;
    case 3:
      digitalWrite(DIG_3, LOW);
      break;
    case 4:
      digitalWrite(DIG_4, LOW);
      break;
  }
  
  digitalWrite(SEG_A, bits[num][0]);
  digitalWrite(SEG_B, bits[num][1]);
  digitalWrite(SEG_C, bits[num][2]);
  digitalWrite(SEG_D, bits[num][3]);
  digitalWrite(SEG_E, bits[num][4]);
  digitalWrite(SEG_F, bits[num][5]);
  digitalWrite(SEG_G, bits[num][6]);
  if(dig == 2)
    digitalWrite(SEG_DP, HIGH);
  else
    digitalWrite(SEG_DP, LOW);
}

