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
  pinMode(2, INPUT);   // Setting pin 2 for /INT input
  pinMode(5,OUTPUT);
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
    if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      Serial.print("  Data: ");
      for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        if(rxBuf[i] < 0x10)                     // If data byte is less than 0x10, add a leading zero
        {
          Serial.print("0");
        }
        //Serial.print(rxBuf[i], HEX);
        //Serial.print(" ");
      }
      for(int i=0;i<8;i++){
        Serial.println(int(rxBuf[i]));
        if(int(rxBuf[i])==50){
          
          Serial.println("enter");
          digitalWrite(5,HIGH);
          delay(1000);
          break;
        }
      }
      digitalWrite(5,LOW);
      delay(1000);
      Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
