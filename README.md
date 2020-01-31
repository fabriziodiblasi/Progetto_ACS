# Progetto_ACS
Design and implementation of a "sensor" ECU. The ECU will take as input the formal specification of a CAN message from a DBC file, as well as a number of time series that represent the evolution over time of the value of the signals encoded in the CAN message. The ECU will produce the corresponding CAN messages and write them on a (virtual) CAN bus. Suggested programming language: Python

# Comandi shell linux
```bash
sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0
sudo candump can0
```

# Impostazione PinOut ARDUINO
### Default SPI_CS_PIN = 9 

# DBC
https://cantools.readthedocs.io/en/latest/

http://socialledge.com/sjsu/index.php/DBC_Format

https://github.com/commaai/opendbc

# Link utili
https://www.peak-system.com/produktcd/Pdf/English/PCAN-USB_UserMan_eng.pdf

https://github.com/Seeed-Studio/CAN_BUS_Shield

http://wiki.seeedstudio.com/CAN-BUS_Shield_V1.2/

https://www.seeedstudio.com/CAN-BUS-Shield-V1-2-p-2256.html

https://seeeddoc.github.io/CAN-BUS_Shield/

https://www.seeedstudio.com/blog/2019/11/27/introduction-to-can-bus-and-how-to-use-it-with-arduino/

https://wiki.dfrobot.com/CAN-BUS_Shield_V2__SKU__DFR0370_

http://matthewcmcmillan.blogspot.com/2013/10/arduino-sending-data-over-can-bus.html


