#define sda 9 //data line
#define sck 10 //clock line

//reading from TC74A0 and DS1631 sensors
byte temp;
double tempb;
double tempc;
byte temp2;
int temp2f;
boolean neg=0; //determine if numb is + or -
boolean neg2=0;
void setup()
{
P2DIR|=B00000110;
P2OUT|=B00000110;
Serial.begin(9600); 
DS1631startconvert();
}

void loop()
{
  // put your main code here, to run repeatedly:
  DS1631readtemp();
  TC74A0readtemp();
  displaytemp();
  delay(2000);
}
void start(){
 P2DIR|=(1<<1);
P2OUT|=(1<<1);
P2OUT|=(1<<2);
P2OUT&=~(1<<1);
P2OUT&=~(1<<2);
}

void stop1(){
P2DIR|=(1<<1);
P2OUT&=~(1<<2);
P2OUT&=~(1<<1);
P2OUT|=(1<<2);
P2OUT|=(1<<1);
  }
void clk(){
P2OUT|=(1<<2);
P2OUT&=~(1<<2);
delay(1);
  }
void DS1631startconvert(){
start();
//send address
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);//write
P2OUT&=~(1<<1);
clk();
//ignore ack
clk();
//start t convert command
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
clk();//ignoring ack
stop1();
}
void DS1631readtemp(){
start();
//send device address
//send address
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);//write
P2OUT&=~(1<<1);
clk();
//ignore ack
clk();
//send read temp command AAh
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
 clk();
 //digitalWrite(sda,LOW);
 P2OUT&=~(1<<1);
 clk();
 //digitalWrite(sda,HIGH);
 P2OUT|=(1<<1);
 clk();
 //digitalWrite(sda,LOW);
 P2OUT&=~(1<<1);
 clk();
 //digitalWrite(sda,HIGH);
 P2OUT|=(1<<1);
 clk();
 //digitalWrite(sda,LOW);
 P2OUT&=~(1<<1);
 clk();
 //digitalWrite(sda,HIGH);
 P2OUT|=(1<<1);
 clk();
 //digitalWrite(sda,LOW);
 P2OUT&=~(1<<1);
 clk();
 clk(); //ignoring ack again
 stop1();
 start();
 //send device address
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);//read
P2OUT|=(1<<1);
clk(); 
//pinMode(sda,INPUT);//change pin from output to input for readin
P2DIR&=~(1<<1);
byte raw=0;
clk();
//read the temp
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp=temp+128;
 neg=1; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp=temp+64;
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp=temp+32; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp=temp+16;
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp=temp+8; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp=temp+4;
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp=temp+2; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp=temp+1;
 }
 clk();
 
//doing more significant read
/*
0000
.5 1
.25 2
.125 3
.0625 4


*/
//pinMode(sda,OUTPUT);
P2DIR|=(1<<1);
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//pinMode(sda,INPUT);
P2DIR&=~(1<<1);
//raw=digitalRead(sda);
raw=P2IN&BIT1;
if(raw==2){
   tempb=tempb+.5;
 }
clk();
//raw=digitalRead(sda);
raw=P2IN&BIT1;
if(raw==2){
   tempb=tempb+.25;
 }
clk();
//raw=digitalRead(sda);
raw=P2IN&BIT1;
if(raw==2){
   tempb=tempb+.125;
 }
clk();
//raw=digitalRead(sda);
raw=P2IN&BIT1;
if(raw==2){
   tempb=tempb+.0625;
 }
clk();
clk();
clk();
clk();
clk();
clk();
stop1();



}

void TC74A0readtemp(){
start();
//send device address
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);//write
//P2OUT&=~(1<<1);
clk();
clk();//ignore ack
//send read temp register
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
clk();//ignoring ack
stop1();
start();
//send address
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);
P2OUT|=(1<<1);
clk();
//digitalWrite(sda,LOW);
P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,LOW);
//P2OUT&=~(1<<1);
clk();
//digitalWrite(sda,HIGH);//read
P2OUT|=(1<<1);
clk();
//pinMode(sda,INPUT);
P2DIR&=~(1<<1);
byte raw=0;
clk();
//read the temp
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp2=temp2+128;
 neg2=1; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp2=temp2+64;
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp2=temp2+32; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp2=temp2+16;
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp2=temp2+8; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp2=temp2+4;
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
  temp2=temp2+2; 
 }
 clk();
 //raw=digitalRead(sda);
 raw=P2IN&BIT1;
 if(raw==2){
   temp2=temp2+1;
 }
 clk();
 //pinMode(sda,OUTPUT);
 P2DIR|=(1<<1);
//digitalWrite(sda,LOW);
P2OUT|=(1<<1);
clk();
stop1();

  
}
void displaytemp(){
  if (neg==1){
   temp=temp-1;
   temp=~(temp);
   tempc=temp*-1;
   tempc=tempc+tempb;
  }
  else{
   tempc=tempb+temp; 
  }
  if (neg2==1){
    temp2=temp2-1;
    temp2=~(temp2);
    temp2f=temp2*-1;
  }
  else{
   temp2f=temp2; 
  }
  
  
  neg=0;
  neg2=0;
 Serial.println(tempc,4);//4 decimal places 
 Serial.println(temp2f);
 temp=0;
 tempb=0;
 temp2=0;
 temp2f=0;
}
