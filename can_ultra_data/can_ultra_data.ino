// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>
#include <DHT.h>

MCP_CAN CAN0(10);                                      // Set CS to pin 10
#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
int chk;
float hum;

void setup()
{
  Serial.begin(115200);
   //init can bus, baudrate: 500k
  if(CAN0.begin(CAN_125KBPS,MCP_8MHz) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
  dht.begin();
}

unsigned char stmp[8] ;
void loop()
{
  for(int i=0;i<8;i++){
          hum = dht.readHumidity();
          if(hum>50){
            stmp[i]='2';
          }
          else{
            stmp[i]='0';
          }
          
  }
// Prints the distance on the Serial Monitor
for(int i=0;i<8;i++){
  Serial.println(stmp[i]);
}
  CAN0.sendMsgBuf(0x10, 0, 8, stmp);  
  delay(100);                       // send data per 100ms
}

