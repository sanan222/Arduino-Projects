#include <QTRSensors.h>
#include <Servo.h> /* Servo kutuphanesi projeye dahil edildi */
#define NUM_SENSORS 6 // kullanılan sensör numarası siz 8ini de kullanabilirsiniz.
#define TIMEOUT 2500 // Sensörlerden başlangıçta kusursuz değerler almak için 2.5 sn. bekle
#define rightMotor1 7
#define rightMotor2 8
#define rightMotorPWM 6
#define leftMotor1 3
#define leftMotor2 4
#define leftMotorPWM 5
#define trigpin1 8 //TRİG pin'ini arduino'daki 5.pine bağladığımızı belirtiyoruz.
#define echopin1 7 //ECHO pin'ini arduino'daki 3.pine bağladığımızı belirtiyoruz.
#define trigpin2 9//TRİG solll pin'ini arduino'daki 5.pine bağladığımızı belirtiyoruz.
#define echopin2 10//ECHO pin'ini arduino'daki 3.pine bağladığımızı belirtiyoruz.
Servo servo;//servo 9. pinde
int lastError = 0;
unsigned int sensors[6];
QTRSensorsAnalog qtrrc((unsigned char[]) {0,1,2,3,4,5} ,NUM_SENSORS);
unsigned int sensorValues[NUM_SENSORS];



  
  
void setup()
{
Serial.begin(9600);
pinMode(trigpin1, OUTPUT);
pinMode(echopin1, INPUT);
pinMode(trigpin2, OUTPUT);
pinMode(echopin2, INPUT);
pinMode(rightMotor1, OUTPUT);
pinMode(rightMotor2, OUTPUT);
pinMode(rightMotorPWM, OUTPUT);
pinMode(leftMotor1, OUTPUT);
pinMode(leftMotor2, OUTPUT);
pinMode(leftMotorPWM, OUTPUT);
servo.attach(9); 
int i;
for (int i = 0; i < 100; i++){ // tercihe bağlı alandır ya robotunuzu hatta yürüterek kalibre edin veya bunu otomatik yapın.
  
  if ( i  < 25 || i >= 75 ) // sensörleri, karşılaşılabilecek en aydınlık ve en karanlık okumalara maruz bırakmak için sola ve sağa çevirin.
     turnright(1);  
   else
     turnleft(1);
qtrrc.calibrate();
}
delay(20);
wait(1000);



}

void loop()
{
int oda[4];
qtrrc.readCalibrated(sensors);
pidline(120);
Serial.println("çizgi izleme bitti");
oda1();
while(1)wait(500);
}



void oda1(){
  qtrrc.readCalibrated(sensors);
pidline(120);
Serial.println("çizgi izleme bitti");
ilerle(5000);//90cm gidecek
wait(1000);
turnleft(550);//90 derece sola
wait(1000);
ilerle(1900); // 50cm gidecek
wait(1000);
turnleft(550); //90 derece sola
wait (1000);
ilerle(2000); // 30 cm ileri
wait(3000); 
geri(2000); // 30 cm geri
wait (200000);

}


void oda2(){
  qtrrc.readCalibrated(sensors);
pidline(120);
Serial.println("çizgi izleme bitti");
ilerle(5000);//90cm gidecek
wait(500);
turnleft(550);//90 derece sola
wait(500);
ilerle(1900); // 50cm gidecek
wait(500);
turnright(550); //90 derece sola
wait (500);
ilerle(4000); // 30 cm ileri
wait(2000); 
geri(5000); // 30 cm geri
wait (200000);

}

void oda3(){
  qtrrc.readCalibrated(sensors);
pidline(120);
Serial.println("çizgi izleme bitti");
ilerle(5000);//90cm gidecek
wait(500);
turnright(550);//90 derece sola
wait(500);
ilerle(1900); // 50cm gidecek
wait(500);
turnleft(550); //90 derece sola
wait (500);
ilerle(4000); // 30 cm ileri
wait(2000); 
geri(5000); // 30 cm geri
wait (200000);

}


void oda4(){
  qtrrc.readCalibrated(sensors);
pidline(120);
Serial.println("çizgi izleme bitti");
ilerle(6000);//90cm gidecek
wait(500);
turnright(550);//90 derece sola
wait(500);
ilerle(1900); // 50cm gidecek
wait(500);
turnright(550); //90 derece sola
wait (500);
ilerle(4000); // 30 cm ileri
wait(2000); 
geri(5000); // 30 cm geri
wait (200000);

}








int onsensor(){
  long sure, mesafe;
digitalWrite(trigpin2, LOW); //ses sinyalleri göndermeyi kesiyor.
delayMicroseconds(3);// 3 mikrosaniye bekliyor.
digitalWrite(trigpin2, HIGH); //ardından tekrar ses sinyallerini gönderiyor.
delayMicroseconds(20); //20 microsaniye bekliyor.
digitalWrite(trigpin2, LOW); //ses sinyalleri göndermeyi kesiyor.
sure = pulseIn(echopin2, HIGH); // dönen ses dalgalarını alıyor ve ses sinyallerinin geri dönme süresini hesaplayıp "sure" değişkenine atıyor.
mesafe = (sure/2) / 29.1; //ölçülen sure uzaklığa(cm)'ye çeviriliyor.
   if (mesafe > 200 || mesafe < 0)// mesafe 200'den büyükse veya mesafe 0'dan küçükse süslü parantez içerisindeki işlemi yaptırıyor.
   {
    return 0;
   }
   else {
   return mesafe;
   }

  }
int sagsensor(){
long sure, mesafe;
digitalWrite(trigpin1, LOW); //ses sinyalleri göndermeyi kesiyor.
delayMicroseconds(3);// 3 mikrosaniye bekliyor.
digitalWrite(trigpin1, HIGH); //ardından tekrar ses sinyallerini gönderiyor.
delayMicroseconds(10); //10 microsaniye bekliyor.
digitalWrite(trigpin1, LOW); //ses sinyalleri göndermeyi kesiyor.
sure = pulseIn(echopin1, HIGH); // dönen ses dalgalarını alıyor ve ses sinyallerinin geri dönme süresini hesaplayıp "sure" değişkenine atıyor.
mesafe = (sure/2) / 29.1; //ölçülen sure uzaklığa(cm)'ye çeviriliyor.
   if (mesafe > 200 || mesafe < 0)// mesafe 200'den büyükse veya mesafe 0'dan küçükse süslü parantez içerisindeki işlemi yaptırıyor.
   {
    return 0;
   }
   else {
   return mesafe;
   }
}
void pidline(int basespeed){
  //all sensonrs =0 ==>0
#define Kp 0.01 // Kendi deneyimlerinizle bulmanız gerekli küçük bir değer ile başlayıp, büyütebilirsiniz en kararlı Kp değerini bulana kadar..
#define Kd 0.125 // Bunu da küçük bir değerden başlatın ve deneyimleyerek büyütün. ( Not: Kp < Kd)
#define rightMaxSpeed 200
#define leftMaxSpeed 200
 // robot için kp ve kd değerlerini tutturduysanız şayet motorların dönmesi gereken hız budur

qtrrc.readCalibrated(sensors);
while(sensors[5]<950||sensors[0]<950){//büyüktürler(beyaz) küçüktür(siyah) olacak
int position = qtrrc.readLine(sensors,true, 0);//0 siyah ,1 beyaz 
Serial.print(sensors[0]);Serial.print("      ");Serial.print(sensors[7]);Serial.print("  position:    ");Serial.println(position);
int error = position - 2500;
int motorSpeed = Kp * error + Kd * (error - lastError);
lastError = error;
int rightMotorSpeed = basespeed- motorSpeed;
int leftMotorSpeed = basespeed + motorSpeed;
if (rightMotorSpeed > rightMaxSpeed ) rightMotorSpeed = rightMaxSpeed;
if (leftMotorSpeed > leftMaxSpeed ) leftMotorSpeed = leftMaxSpeed;
if (rightMotorSpeed < 0) rightMotorSpeed = 0;
if (leftMotorSpeed < 0) leftMotorSpeed = 0;
Serial.print(leftMotorSpeed);Serial.print("      ");
Serial.println(rightMotorSpeed);

digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
analogWrite(rightMotorPWM, rightMotorSpeed);
digitalWrite(leftMotor1, HIGH);
digitalWrite(leftMotor2, LOW);
analogWrite(leftMotorPWM, leftMotorSpeed);
qtrrc.readCalibrated(sensors);
if(sensors[5]>800&&sensors[0]>800){
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



void turnright(int a){
digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
analogWrite(rightMotorPWM, 90);
digitalWrite(leftMotor1, LOW);
digitalWrite(leftMotor2, HIGH);
analogWrite(leftMotorPWM, 90);
delay(a);
}
void turnleft(int a){
digitalWrite(rightMotor1, LOW);
digitalWrite(rightMotor2, HIGH);
analogWrite(rightMotorPWM, 90);
digitalWrite(leftMotor1, HIGH);
digitalWrite(leftMotor2, LOW);
analogWrite(leftMotorPWM, 90);
delay(a);
  }
 void wait(int a){
digitalWrite(leftMotor1, LOW);
digitalWrite(leftMotor2, LOW);
analogWrite(leftMotorPWM, 0);
digitalWrite(rightMotor1, LOW);
digitalWrite(rightMotor2, LOW);
analogWrite(rightMotorPWM, 0);

delay(a);
  }
 void ilerle(int a){

digitalWrite(leftMotor1, HIGH);
digitalWrite(leftMotor2, LOW);
analogWrite(leftMotorPWM, 90);
digitalWrite(rightMotor1, HIGH);
digitalWrite(rightMotor2, LOW);
analogWrite(rightMotorPWM, 90);
delay(a);
  }
   void geri(int a){
digitalWrite(rightMotor1, LOW);
digitalWrite(rightMotor2, HIGH);
analogWrite(rightMotorPWM, 90);
digitalWrite(leftMotor1,LOW );
digitalWrite(leftMotor2, HIGH);
analogWrite(leftMotorPWM, 90);
delay(a);
  }
