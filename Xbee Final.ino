//#include <SoftwareSerial.h>

//SoftwareSerial xbee(0, 1); // RX, TX
//byte incomingByte;
void setup()
{
    Serial.begin(9600);
}

void loop()  
{
  if(Serial.available()>=14)
  {
    if(Serial.read()==0x7E)
    {
      for(int i=1 ; i < 11 ; i++)
      {
        byte discardByte = Serial.read();
        
      }
      
      byte analogMSB1 = Serial.read();
      byte analogLSB1 = Serial.read();
      byte analogMSB2 = Serial.read();
      byte analogLSB2 = Serial.read();
      //Serial.println(analogLSB1,HEX);
      //Serial.println(analogMSB1,HEX);
      //Serial.println((int)analogMSB1);
      //Serial.println((int)analogLSB1);
      ///Serial.println("two");
      //Serial.println((int)analogMSB2);
      //Serial.println((int)analogLSB2);
      //Serial.println(analogMSB2);
      //Serial.println(analogLSB2);
      int analogReadingX = analogLSB1+ analogMSB1*256;
      int analogReadingY = analogLSB2+ analogMSB2*256;
      //Serial.println(analogReadingX);
      Serial.println(analogReadingY);
    }
  }
}
