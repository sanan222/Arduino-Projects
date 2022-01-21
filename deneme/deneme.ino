#define MotorR1 6
#define MotorR2 7 
#define MotorRE 9

#define MotorL1 4
#define MotorL2 5
#define MotorLE 3



void setup() {


  pinMode(MotorR1, OUTPUT); // Sensör ve Motorların Giriş-Çıkış bilgilerini belirtiyoruz.
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorLE, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorRE, OUTPUT);
  
}
void loop(){

ileri();
  
}
void ileri(){
  digitalWrite (MotorR1, HIGH);
  digitalWrite (MotorR2, LOW);
  analogWrite (MotorRE, 100);

  digitalWrite (MotorL1, HIGH);
  digitalWrite (MotorL2, LOW);
  analogWrite (MotorLE, 100);
}
