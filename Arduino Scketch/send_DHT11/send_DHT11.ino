#include <SPI.h>
#include <mcp_can.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define SPI_CS_PIN 9
#define DHTPIN    7     // pin sensore DHT sensor 
#define DHTTYPE    DHT11     // DHT 11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;


/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
  #define SERIAL SerialUSB
#else
  #define SERIAL Serial
#endif

unsigned char stmp[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char *p;
int umidita, temp;
MCP_CAN CAN(SPI_CS_PIN);

/*
     * On the Arduino Uno (and other ATmega based boards) an int stores a 16-bit (2-byte) value. 
     * This yields a range of -32,768 to 32,767 (minimum value of -2^15 and a maximum value of (2^15) - 1). 
     * 
     * arduino is Little Endian
*/
void erasePayload(){
  stmp[0]=0x00;
  stmp[1]=0x00;
  stmp[2]=0x00;
  stmp[3]=0x00;
  stmp[4]=0x00;
  stmp[5]=0x00;
  stmp[6]=0x00;
  stmp[7]=0x00;
}


void createTempPayload(){
    p=(unsigned char *)&temp;
    stmp[2]=p[1];
    stmp[3]=p[0];
}

void createUmidityPayload(){  
    p=(unsigned char *)&umidita;
    stmp[0]=p[1];
    stmp[1]=p[0];
}


void setup()
{
    
    
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");

    // Initialize device.
    dht.begin();
    Serial.println(F("DHTxx Unified Sensor Example"));
    // Print temperature sensor details.
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    // Set delay between sensor readings based on sensor details.
    delayMS = sensor.min_delay / 1000;
}

    
void loop()
{ 
   
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    temp=0;
  }
  else {
    Serial.print(F("Temperature: "));
    temp=event.temperature;
    Serial.print(temp);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
    umidita = 0;

  }
  else {
    Serial.print(F("Humidity: "));
    umidita = event.relative_humidity;
    Serial.print(umidita);
    Serial.println(F("%"));
  }
  createTempPayload();
  createUmidityPayload();
  CAN.sendMsgBuf(0x43, 0, 8, stmp);
  delay(1000);
  erasePayload();

}
