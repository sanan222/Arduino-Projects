#include <PID_v1.h>

#define SensorSol 10
#define SensorOrta 11
#define SensorSag 12

#define MotorR1 6
#define MotorR2 7 
#define MotorRE 9

#define MotorL1 4
#define MotorL2 5
#define MotorLE 3



void setup() {
  // put your setup code here, to run once:
  pinMode(SensorSol, INPUT);
  pinMode(SensorOrta, INPUT);
  pinMode(SensorSag, INPUT);

  pinMode(MotorR1, OUTPUT); // Sensör ve Motorların Giriş-Çıkış bilgilerini belirtiyoruz.
  pinMode(MotorR2, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(SensorSol) == 0 && digitalRead (SensorOrta) == 1 && digitalRead (SensorSag) == 0){
    ileri();
  }
   else if (digitalRead(SensorSol) == 1 && digitalRead (SensorOrta) == 0 && digitalRead (SensorSag) == 0){
    sag();
   }
   else if(digitalRead(SensorSol) == 0 && digitalRead (SensorOrta) == 0 && digitalRead (SensorSag) == 1){
    sol();
    }
   else if (digitalRead(SensorSol) == 0 && digitalRead (SensorOrta) == 0 && digitalRead (SensorSag) == 0){
    ileri();
   }
   else
   {
    dur();
   }
  
}

void ileri(){
  digitalWrite (MotorR1, HIGH);
  digitalWrite (MotorR2, LOW);
  analogWrite (MotorRE, 150);

  digitalWrite (MotorL1, HIGH);
  digitalWrite (MotorL2, LOW);
  analogWrite (MotorLE, 150);
}

void sag(){
  digitalWrite (MotorR1, HIGH);
  digitalWrite (MotorR2, LOW);
  analogWrite (MotorRE, 0);

  digitalWrite (MotorL1, HIGH);
  digitalWrite (MotorL2, LOW);
  analogWrite (MotorLE, 150);
}

void sol(){
  digitalWrite (MotorR1, HIGH);
  digitalWrite (MotorR2, LOW);
  analogWrite (MotorRE, 150);

  digitalWrite (MotorL1, HIGH);
  digitalWrite (MotorL2, LOW);
  analogWrite (MotorLE, 0);
}

void dur(){
  digitalWrite (MotorR1, HIGH);
  digitalWrite (MotorR2, LOW);
  analogWrite (MotorRE, 0);

  digitalWrite (MotorL1, HIGH);
  digitalWrite (MotorL2, LOW);
  analogWrite (MotorLE, 0);
}
