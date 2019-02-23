# ARDF-Firmware
## Build
```
cmake .
make
```

## Flash
```
avrdude -p -t44 -B 10 -c stk500 -U flash:w:ARDF_Firmware.hex:i
```

## Fuses
 * Extended: 0xFE (self programming enabled (not necessary...))
 * High: 0x92 (External Reset enabled, debug wire enabled, isp enabled, watchdog disabled, 
                    eeprom preserve enabled, brown out detection at 2.7V)
 * Low: 0xFF (External Clock, No Clock/8, Fast start (because BOD enabled))

## Pinout
| Pin | I/O | Func |
| --- | --- | ---  |
| A0  | O   | SEND_EN |
| A1  | A   | VBAT (4.7/8.2) |
| A2  | A   | POTI |
| A3  | O   | LED5 |
| A4  | O   | LED4 / SCL  |
| A5  | O   | LED3 / MISO |
| A6  | O   | LED2 / MOSI |
| A7  | O   | LED1 |
| B0  | NC  | CLKI |
| B1  | I   | DIP  |
| B2  | O   | BUZZER |
| B3  | NC  | RESET |
