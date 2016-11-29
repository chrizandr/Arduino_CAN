// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>
#include <DHT.h>

MCP_CAN CAN0(10);                                      // Set CS to pin 10
unsigned char pixels[1024];
unsigned char temp[8] = {0,0,0,0,0,0,0,0};
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
int chk;
float hum;

void setup()
{
  Serial.begin(115200);
  // init can bus, baudrate: 500k
  if(CAN0.begin(CAN_125KBPS,MCP_8MHz) == CAN_OK) Serial.print("can init ok!!\r\n");
//  else Serial.print("Can init fail!!\r\n");
}
int count = 0;
void sendCan(){
  for(int i=0; i<1024; i=i+8){
    for(int j = 0; j<8; j++){
      temp[j] = pixels[i+j];
      Serial.print(temp[j]);
      Serial.print(" ");
      count ++;
    }
    Serial.println();
    CAN0.sendMsgBuf(0x10, 0, 8, temp);
  }
  delay(10);
}

void sense(){
  while(1){
  for(int i=0;i<8;i++){
        hum = dht.readHumidity();
           //Serial.println(hum); 
           if(hum>75){
             temp[i]='2';
           }
           else{
             temp[i]='0';
           }
    }
   CAN0.sendMsgBuf(0x10, 0, 8, temp);      
   }
}

int flag = 0;
void loop()
{
  // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
  while(Serial.available() > 0) {
    // read the incoming byte:
    int c = Serial.readBytes(pixels,1024);
    Serial.println(c);
    sendCan();
    Serial.println(count);
    delay(100);
    flag = 1;
    delay(1000);
    sense();
   }
   //delay(50);    
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
