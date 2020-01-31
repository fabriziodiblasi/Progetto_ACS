#include <SPI.h>
#include <mcp_can.h>

//PIN UTILIZZATI PER IL SENSORE
#define SENSOR_DIGITAL_IN 7
#define SENSOR_ANALOG_IN  A0


/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
#else
  #define SERIAL Serial
#endif


const int SPI_CS_PIN = 9;
int gas_value;
//unsigned char bufferVal[8];
unsigned char stmp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char hex_value[8];
unsigned char *p;
MCP_CAN CAN(SPI_CS_PIN);


void leggipayload(){
    gas_value=analogRead(SENSOR_ANALOG_IN);
    //gas_value=125;
    p=(unsigned char *)&gas_value;

    /*
     * On the Arduino Uno (and other ATmega based boards) an int stores a 16-bit (2-byte) value.
     * arduino is Little Endian
     */
    stmp[0]=p[1];
    stmp[1]=p[0];
    //stmp[2]=p[2];
    //stmp[3]=p[3];
    
    sprintf(hex_value,"%X",gas_value);
    Serial.println("\nHEX :");
    Serial.write(hex_value,sizeof(char)*8);
    Serial.println("\nDEC:");
    Serial.println(gas_value);
    hex_value[0]='\0';

}



void setup()
{
    pinMode(SENSOR_ANALOG_IN,INPUT);
    
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");
}

    
void loop()
{   
  leggipayload();
  CAN.sendMsgBuf(0x43, 0, 8, stmp);
  delay(1000);
}
