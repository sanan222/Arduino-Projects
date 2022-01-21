const int Enable_A = 3;
const int Enable_B = 5;
const int inputA1 = 9;
const int inputA2 = 10;
const int inputB1 = 11;
const int inputB2 = 12;

void setup()
{
pinMode(Enable_A, OUTPUT);
pinMode(Enable_B, OUTPUT);
pinMode(inputA1, OUTPUT);
pinMode(inputA2, OUTPUT);
pinMode(inputB1, OUTPUT);
pinMode(inputB2, OUTPUT);
}
void loop()
{
//---- A ve B Cikis olarak etkinlestir------//
digitalWrite(Enable_A, HIGH);
digitalWrite(Enable_B, HIGH);
//----------Run motors-----------//
digitalWrite(inputA1, HIGH);
digitalWrite(inputA2, LOW);
digitalWrite(inputB1 , HIGH);
digitalWrite(inputB2, LOW);
delay(3000);
//-------motoru devre disi birak----------//
digitalWrite(Enable_A, LOW);
digitalWrite(Enable_B, LOW);
delay(3000);
//-------Ters Bağlama----------//
digitalWrite(Enable_A, HIGH);
digitalWrite(Enable_B, HIGH);
digitalWrite(inputA1, LOW);
digitalWrite(inputA2, HIGH);
digitalWrite(inputB1 , LOW);
digitalWrite(inputB2, HIGH);
delay(3000);
//-------Motor devre disi----------//
digitalWrite(Enable_A, LOW);
digitalWrite(Enable_B, LOW);
delay(3000);
//----------Hiz yukselt----------//


//-------motoru devre dışı bırak----------//
digitalWrite(Enable_A, LOW);
digitalWrite(Enable_B, LOW);
delay(3000);
}
