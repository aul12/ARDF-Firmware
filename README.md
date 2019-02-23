# Fuchsjagdsender
## Build
```
cmake .
make
```

## Flash
```
avrdude -p -t44 -B 10 -c stk500 -U flash:w:Fuchsjagdsender.hex:i
```

## Fuses
```
TODO
```
