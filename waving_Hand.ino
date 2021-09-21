#define GREEN 7
#define RED_RIGHT_1 6
#define RED_RIGHT_2 5
#define RED_MIDDLE 4
#define RED_LEFT_2 3
#define RED_LEFT_1 2
//Sensors
#define Left_Sensor A0
#define Right_sensor A1
#define potentiometer_sensor A2

int Left_Hand = 0, Right_Hand = 0, potentiometer = 0;
int Potenciometr = 820; // minimum
 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(GREEN,OUTPUT); //green
  pinMode(RED_RIGHT_1,OUTPUT);
  pinMode(RED_RIGHT_2,OUTPUT);
  pinMode(RED_MIDDLE,OUTPUT);
  pinMode(RED_LEFT_2,OUTPUT); 
  pinMode(RED_LEFT_1,OUTPUT);

  // 2,3 left diods
  // 4 central
  // 6,7 rigth diods

  digitalWrite(GREEN,HIGH); //Green Light, system is ready
  digitalWrite(RED_RIGHT_1,LOW);
  digitalWrite(RED_RIGHT_2,LOW);
  digitalWrite(RED_MIDDLE,LOW);
  digitalWrite(RED_LEFT_2,LOW);
  digitalWrite(RED_LEFT_1,LOW);
}

int LeftD(){  
  int b=analogRead(Left_Sensor) ;
  return b;
}

int RightD(){    
  int b=analogRead(Right_sensor);
  return b;
}

int PotentiometerD(){    //Prawy czujnik
  int b = analogRead(potentiometer_sensor);
  return b;
}

void logger()
{
  Serial.print("L_H : ");
  Serial.print(Left_Hand);
  Serial.print(" , R_H : "); 
  Serial.print(Right_Hand);
  Serial.print(" , P_S: ");
  Serial.println(potentiometer);
}


void MiddleHand(){
  digitalWrite(GREEN,LOW);
  digitalWrite(RED_RIGHT_1,LOW);
  digitalWrite(RED_LEFT_1,LOW);
  digitalWrite(RED_RIGHT_2,LOW);
  digitalWrite(RED_LEFT_2,LOW);

     delay(300);
      
      digitalWrite(RED_MIDDLE,HIGH);

      
          
}


void loop() {
   int i=0;
   int Middle_from = potentiometer * 0.48;
   int Middle_to = potentiometer * 0.73;
   int Left_from = 0;
   int Left_to = Middle_from;
   
   Left_Hand = LeftD(); Right_Hand = RightD();potentiometer= PotentiometerD();
   logger();
  
   if  (
    ((Left_Hand > Middle_from) && (Left_Hand < Middle_to))// 563
   && 
   ((Right_Hand > Middle_from) && (Right_Hand < Middle_to))
   ) 
   {
     MiddleHand(); 
   }
   else if ((Left_Hand > Left_from) 
        and(Left_Hand <= Left_to ))
   {
     digitalWrite(7,LOW);
      for (i=2;i<=4;i++) {
        delay(100);
        digitalWrite(i,HIGH);
      }
      for (i=2;i<=6;i++) {
        delay(50);
        digitalWrite(i,LOW);
      }  
   }
   else if ((Right_Hand >= Left_from)
        and(Right_Hand < Left_to ))
   {
       digitalWrite(GREEN,LOW);
       
      for (i=6;i>3;i--) {
        delay(100);
        digitalWrite(i,HIGH);
      }
      for (i=6;i>1;i--) {
        delay(50);
        digitalWrite(i,LOW);
      } 
   }
   else {
        digitalWrite(7,HIGH);
   }


    delay(100);
}
