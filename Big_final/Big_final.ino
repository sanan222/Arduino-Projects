#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <QTRSensors.h>
#define NUM_SENSORS 6 // kullanılan sensör numarası siz 8ini de kullanabilirsiniz.
#define rightMotor1 7
#define rightMotor2 8
#define rightMotorPWM 6
#define leftMotor1 3
#define leftMotor2 4  

#define leftMotorPWM 5
#define base 70
#define degisgen 0.942


#define Kp 0.008 // Kendi deneyimlerinizle bulmanız gerekli küçük bir değer ile başlayıp, büyütebilirsiniz en kararlı Kp değerini bulana kadar..
#define Kd 0.1 // Bunu da küçük bir değerden başlatın ve deneyimleyerek büyütün. ( Not: Kp < Kd)
#define rightMaxSpeed 110*degisgen
#define leftMaxSpeed 110
#define rightBaseSpeed 70*degisgen
#define leftBaseSpeed 70
QTRSensorsAnalog qtrrc((unsigned char[]) {0,1,2,3,4,5} ,NUM_SENSORS);
unsigned int sensorValues[NUM_SENSORS];
int lastError = 0;    
unsigned int sensors[6];


 //SCK -> 13//MISO -> 12//MOSI -> 11//CSN -> 9//CE -> 10
RF24 radio(10,9);
 const uint64_t pipe = 0xE8E8F0F0E1LL;
 int msg[1];

 void setup()
 {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);
  int i;
  for (int i = 0; i < 200; i++){ // tercihe bağlı alandır ya robotunuzu hatta yürüterek kalibre edin veya bunu otomatik yapın.
    qtrrc.calibrate();
  }
  delay(20);
  wait(1000);
 
 }

 void loop()
 {
  wait(3000);
  oda1();
  wait(3000);
  oda2();
  while(1) wait(500);
 }
 

 void pidline(int x){

  while(1)
  {


    qtrrc.readCalibrated(sensors);
    int position = qtrrc.readLine(sensors,true,1);
    Serial.print(position);Serial.print("      ");
    int error = position - 2500;
    int motorSpeed = Kp * error + Kd * (error - lastError);
    lastError = error;
    int rightMotorSpeed = x*degisgen - motorSpeed;
    int leftMotorSpeed = x + motorSpeed;
    if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed;
    if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
    if (rightMotorSpeed < 0) rightMotorSpeed = 0;
    if (leftMotorSpeed < 0) leftMotorSpeed = 0;
    Serial.print(leftMotorSpeed);Serial.print("      ");
    Serial.println(rightMotorSpeed);
    
    {
    
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    analogWrite(rightMotorPWM, rightMotorSpeed);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    analogWrite(leftMotorPWM, leftMotorSpeed);
    }
    if(sensors[5]<300&&sensors[0]<300)//beyaz icin
    {
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
      analogWrite(rightMotorPWM, 0);
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
      analogWrite(leftMotorPWM, 0);
      delay(1000); break;
    }
  }
}

void turnright(int a)
{
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, base*degisgen);
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, HIGH);
  analogWrite(leftMotorPWM, base);
  delay(a);
}
void turnleft(int a)
{
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM, base*degisgen);
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, base);
  delay(a);
}
void wait(int a)
{
  digitalWrite(leftMotor1, LOW);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, 0);
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, 0);  
  delay(a);
}
void ilerle(int a)
{
  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, LOW);
  analogWrite(leftMotorPWM, base);
  digitalWrite(rightMotor1, HIGH);
  digitalWrite(rightMotor2, LOW);
  analogWrite(rightMotorPWM, base*degisgen);
  delay(a);
}

void geri(int a)
{
  digitalWrite(rightMotor1, LOW);
  digitalWrite(rightMotor2, HIGH);
  analogWrite(rightMotorPWM,base*degisgen);
  digitalWrite(leftMotor1,LOW );
  digitalWrite(leftMotor2, HIGH);
  analogWrite(leftMotorPWM, base);
  delay(a);
}







void oda1(){
pidline(70);
wait(500);
ilerle(3300);
wait(1000);
turnleft(520);//90 derece sola
wait(1000);
qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(30);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  } // 50cm gidecek

wait(1000);
turnleft(500);
wait(1000);
pidline(60); // 90 derece saga
wait(1000);
ilerle(500); // 50 cm gidecek
wait(1000);
geri(1300);
wait(1000);
turnleft(570); // 90 derece saga 
wait(1000);
ilerle(2000);
wait(1000);
turnleft(585);
wait(1000);
geri(50);
delay(50);
ilerle(1800);
wait(2000);
qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(20);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  }
  
wait(500);
 pidline(70);


}


void oda2(){
pidline(70);
wait(500);
ilerle(3300);
wait(500);
turnleft(520);//90 derece sola
wait(500);
qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(10);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  }
ilerle(100);
wait(500);
turnright(520); //90 derece sola
wait (500);
pidline(60);
wait(1000);
ilerle(800);
wait(1000);
geri(1500); // 30 cm geri
wait(1000);
turnright(520); // 90 derece saga
wait(1000);
ilerle(1800); // 50 cm gidecek
wait(1000);
turnleft(520); // 90 derece saga 
wait(1000);
ilerle(1500);
wait(1000);

qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(20);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  }
  wait(500);

pidline(70);


}

void oda3(){
    pidline(70);
  wait(500);
ilerle(3300);
wait(500);
turnright(520);//90 derece sola
wait(500);
qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(10);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  } // 50cm gidecek
wait(500);
turnleft(520); //90 derece sola
wait (500);
pidline(60);
wait(1000); 
ilerle(500);
wait(1000);
geri(1500); // 30 cm geri
wait(1000);
turnleft(520);
wait(1000);
ilerle(1800);
wait(1000);
turnright(520);
wait(500);
ilerle(1500);

qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(30);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  }
  wait(500);
 

 pidline(70);


}


void oda4(){
pidline(70);
wait(500);
ilerle(3300);
wait(500);
turnright(520);//90 derece sola
wait(500);
ilerle(1500);
wait(500);
qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(30);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  }
// 50cm gidecek
wait(500);
turnright(520); //90 derece sola
wait (500);
pidline(60);

wait(1000); 
ilerle(500);
wait(1000);
geri(1200); // 30 cm geri
wait(1000);
turnright(520); // 90 derece saga
wait(1000);
ilerle(1800); // 50 cm gidecek
wait(1000);
turnright(600); // 90 derece saga 
wait(1000);

ilerle(2500);
wait(1000);

qtrrc.readCalibrated(sensors);
  
  while(sensors[5]>300&&sensors[4]>300&&sensors[3]>300&&sensors[2]>300&&sensors[1]>300&&sensors[0]>300)
  {
    ilerle(10);
    qtrrc.readCalibrated(sensors);
    Serial.println("ilerliyor");
  }
 
wait(1000);
pidline(70);


}
