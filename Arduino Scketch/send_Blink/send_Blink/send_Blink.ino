// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
#else
  #define SERIAL Serial
#endif

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 9;
const int ledHIGH    = 1;
const int ledLOW     = 0;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    SERIAL.begin(115200);

    while (CAN_OK != CAN.begin(CAN_1000KBPS))              // init can bus : baudrate = 1000k
    {
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println(" Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
}

unsigned char stmp[8] = {ledHIGH, 1, 2, 3, ledLOW, 5, 6, 7};
unsigned char data[8] = {'V', 'i', 't', 't', 'o', 'r', 'i', 'a'};

void loop()
{   SERIAL.println("In loop");
    // send data:  id = 0x70, standard frame, data len = 8, stmp: data buf
    //    CAN.sendMsgBuf(0x70, 0, 8, stmp);
    CAN.sendMsgBuf(0xF1, 0, 8, data);

    delay(1000);                       // send data once per second
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
