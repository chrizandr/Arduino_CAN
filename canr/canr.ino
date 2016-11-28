// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>
#include <Servo.h>

Servo myservo;

int servoPin = 3;
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_125KBPS,MCP_8MHz);                       // init can bus : baudrate = 500k 
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
  Serial.println("MCP2515 Library Receive Example...");
  myservo.attach(servoPin);
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
        if(int(rxBuf[i])==50 && rxId==0){
          myservo.write(90);
          Serial.println("enter");
          delay(1000);
          break;
        }
      }
      myservo.write(0);
      delay(1000);
      Serial.println();
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
