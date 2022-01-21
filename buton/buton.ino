int buton=2;
int kirmizi=7;
int yesil = 6;
int deger = 0;
int say = 0;
bool islem = false;
void setup() {
  pinMode(buton, INPUT);
  pinMode(kirmizi, OUTPUT);
  pinMode(buton, OUTPUT);
  Serial.begin(9600);
  
}
 
void loop() {
  deger = digitalRead(buton);
  Serial.println(deger);
  while (deger == 1)
  {
    delay(100);
    say++; 
    deger = digitalRead(buton); //butonu tekrar okuyoruz ki while takılı kalmasın. aksi halde 
    islem = true;               // deger değişkeni hep 1 olduğu için while sonsuz döngüye girer
  }
  Serial.println(say);
  if (islem == true)
  {
        if (say >0 && say <= 10) //1 saniye basıldı
        {
          digitalWrite(kirmizi,HIGH);
          digitalWrite(yesil,LOW);
        }
        else if (say >10 && say <= 20) //2 saniye basıldı
        {
           digitalWrite(yesil,HIGH);
           digitalWrite(kirmizi,LOW);
        }
        else //2 saniyeden fazla basıldı
          {
             digitalWrite(yesil,LOW);
             digitalWrite(kirmizi,LOW);
          }
           say=0; 
           islem = false;
  }
}
