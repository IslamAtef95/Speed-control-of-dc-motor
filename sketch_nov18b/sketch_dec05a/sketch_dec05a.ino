#include <PID_v1.h>
double n = 255;
int val = 0;
int count = 2;
double rpmcount = 0;
double rpmsmall = 0;
double u;
double rpm = 0;
int timeold = 0;
bool t = false;
bool z = false;
int old_value = 1;
String readString;
//PID myPID(&u, &n, &val,0.01,0.05,0.01, DIRECT);
void setup() {
 // myPID.SetMode(AUTOMATIC);
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, INPUT);  //RIGHT
  pinMode(6, INPUT);  //STOP
  pinMode(8, INPUT);  //LEFT
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  analogWrite(10,n);
  attachInterrupt(0, rpm_count, FALLING);
}

void rpm_count()
{
  rpmcount++;
  //Serial.println(rpmcount);
    
}

void loop() {
  detachInterrupt(0);
    
    rpm = (rpmcount /12)*60;
    rpmsmall = (rpmcount/238)*60;
    z = false;
   
   //Serial.println(rpmcount);
   rpmcount = 0;
   Serial.print("Current Low speed = ");
   Serial.print(rpmsmall);
   Serial.print(" rpm Current High speed = ");
   Serial.print(rpm);
   Serial.print(" rpm\n");
  
  double tt;
  if (Serial.available())
  {
    val = Serial.parseInt();
    t = true;
    z = true;
    tt = val;
    //Serial.println(n);
    //analogWrite(10, n);
  }
  if (z)
  {
    if ((old_value*tt) < 0)
    {
    digitalWrite(4,LOW);
    digitalWrite(5, LOW);
    Serial.println("Changing direction");
    delay(2000);
    
    }
  if (tt > 0)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  if (tt < 0)
  {
    val *= -1;
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  }
  old_value = tt;
  }
 
  double x;
  int diff;
  diff = val - rpmsmall;
  if (diff < 0)
  {
    diff *= -1;
  }
  if (diff > 10)
  {
    x = 20;
  }
  if (diff > 1)
  {
    x = 10;
  }
  else 
  {
    x=0.3;
  }
  if (t)
  {
    
    if (val < rpmsmall)
    {
      n-=x;
    }
    if (val >rpmsmall)
    {
      n+=x;
    }
  }
  
 // myPID.Compute();
  analogWrite(10, n);
  // put your main code here, to run repeatedly:

  if  (digitalRead(6) == HIGH)  //stopping condition
  { 
    Serial.println("Emergency");
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    count=2;
  }
  
  
// t = false;
attachInterrupt(0, rpm_count, FALLING);
delay(1000);
}
