// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);                                      // Set CS to pin 10
unsigned char pixels[1024];
unsigned char temp[8] = {0,0,0,0,0,0,0,0};
void setup()
{
  Serial.begin(115200);
  // init can bus, baudrate: 500k
  if(CAN0.begin(CAN_125KBPS,MCP_8MHz) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
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
}



void loop()
{
  // send data:  id = 0x00, standrad flame, data len = 8, stmp: data buf
  while(Serial.available() > 0) {
    // read the incoming byte:
    int c = Serial.readBytes(pixels,1024);
    Serial.println(c);
    sendCan(); 
    Serial.println(count);
   }
   
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
