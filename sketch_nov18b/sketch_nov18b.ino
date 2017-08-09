int n = 255;
int val = 0;
int count = 2;
double rpmcount = 0;
double rpmsmall = 0;
double rpm  = 0;
int timeold = 0;
bool t = false;
String readString;

void setup() {
  
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
  analogWrite(10,255);
  attachInterrupt(0, rpm_count, FALLING);
}

void rpm_count()
{
  rpmcount++;
}

void loop() {
  detachInterrupt(0);
  t = false;
    rpm = (rpmcount/12)*60; // rpm for fast part
    rpmsmall = (rpmcount /(238))*60; // rpm for small part
    
   
   //Serial.println(rpmcount);
   rpmcount = 0;
   Serial.print("Current lOW speed = ");
   Serial.print(rpmsmall);
   Serial.print(" rpm || Current High speed = ");
   Serial.print(rpm);
   Serial (" rpm\n")
  
  double tt;
  if (Serial.available())
  {
    val = Serial.parseInt();
    t = true;
    
    //Serial.println(n);
    //analogWrite(10, n);
  }
  tt = val;
  if (tt > 0)
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  }
  if (tt < 0)
  {
    val *= -1;
    digitalWrite(4,LOW);
    digitalWrite(5, LOW);
    delay(2000);
    //delay(1000);
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
  }
  int x;
  int diff;
  diff = val - rpm;
  if (diff < 0)
  {
    diff *= -1;
  }
  if (diff > 5)
  {
    x = 4;
  }
  else
  {
    x = 1;
  }
  if (t)
  {
    
    if (val < rpm)
    {
      n-=x;
    }
    if (val >rpm)
    {
      n+=x;
    }
  }
  analogWrite(10, n);
  // put your main code here, to run repeatedly:
  if  (!((digitalRead(8) == HIGH) && (digitalRead(7) == HIGH)))//mabey3melsh 7aga fe om el conditions lama yedaso ma3 b3d
  {
  if (((digitalRead(8) == HIGH) || count  == 0)&& (count !=1)) //cont clockwise rotation
  {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    count = 0;
  }
  if (((digitalRead(7) == HIGH) || count == 1) && (count != 0)) //cont anti-clockwise rotation
  {
    digitalWrite(5, LOW);
    digitalWrite(4, HIGH);
    count = 1;
  }
  if  (digitalRead(6) == HIGH)  //stopping condition
  { 
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    count=2;
  }
  
  }
 
attachInterrupt(0, rpm_count, FALLING);
delay(1000);
}
