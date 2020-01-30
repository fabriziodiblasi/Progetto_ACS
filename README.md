# Progetto_ACS
Design and implementation of a "sensor" ECU. The ECU will take as input the formal specification of a CAN message from a DBC file, as well as a number of time series that represent the evolution over time of the value of the signals encoded in the CAN message. The ECU will produce the corresponding CAN messages and write them on a (virtual) CAN bus. Suggested programming language: Python

# comandi shell linux

sudo ip link set can0 type can bitrate 500000

sudo ip link set up can0

# link utili
http://wiki.seeedstudio.com/CAN-BUS_Shield_V1.2/