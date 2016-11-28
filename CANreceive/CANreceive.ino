// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_125KBPS,MCP_8MHz);                       // init can bus : baudrate = 500k 
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
  
}
int count = 0;
byte pixels[1024];

void printPixel(){
  Serial.print('S');
  for(int i=0;i<1024;i++){
    Serial.print(pixels[i]);
    Serial.print(",");
  }
  Serial.println();
}

void readInput(){
  if(count < 1023 ){
      if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
      {
        CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
        rxId = CAN0.getCanId();                    // Get message ID
  //Serial.println(rxId, HEX);
  //      Serial.println(len);
        if(rxId==0x10){
        for(int i = 0; i<len; i++)                // Print each byte of the data
        {
          pixels[count] = rxBuf[i];
          Serial.print(rxBuf[i]);
          Serial.print(" ");
          count ++;
        }
        Serial.println();
        }
        
      }
  }
}

void loop()
{
  readInput();
  if(count==1024){
    printPixel();
    count++;
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
