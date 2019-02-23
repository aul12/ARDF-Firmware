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
```
TODO
```

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
