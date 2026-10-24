
# temp-eh

Transmit ambient temperature data wirelessly to your device with the temp-eh external wireless temperature sensor.

##  build

`west build -b nrf54l15dk/nrf54l15/cpuapp --snippet rtt-console .`

## rtt

`pyocd rtt -t nrf54l -u <serial_number>`

## notes

- when powering from the nrf54l15dk, vddio is 1.8V by default (47k on VSET1 pin on nPM1300 IC)
