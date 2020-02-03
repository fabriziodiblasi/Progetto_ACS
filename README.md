# Progetto_ACS
Design and implementation of a "sensor" ECU. The ECU will take as input the formal specification of a CAN message from a DBC file, as well as a number of time series that represent the evolution over time of the value of the signals encoded in the CAN message. The ECU will produce the corresponding CAN messages and write them on a (virtual) CAN bus. Suggested programming language: Python

# Comandi shell linux
```bash
sudo ip link set can0 type can bitrate 500000
sudo ip link set up can0
sudo candump can0
```

# Sensore adottato
In questo progetto è stato utilizzato un sensore di temperatura DHT11, capace di fornire in output due segnali
- Temperatura (°C)
- Umidità     (％RH)
[link datasheet](https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf)

Essendo la sensibilità molto scarsa, per i valori di tempertatura ed umidità sono state utilizzate due variabili intere.
Infine, tali dati sono stati pacchettizzati all'interno di frame CAN-BUS.

# Specifiche del messaggio CAN
```bash
BO_67 IO_TEMP_HUM_INFO: 4 DHT11
    MSG_HUMIDITY: 0|8@0- (1,0) [20|90] "RH" 
    MSG_TEMPERATURE: 8|8@0- (1,0) [0|50] "C" 
```
