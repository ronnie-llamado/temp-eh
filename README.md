
# temp-eh

ANT+ Temperature Sensor

##  build

`west build -b nrf54l15dk/nrf54l15/cpuapp --snippet rtt-console .`

## rtt

`pyocd rtt -t nrf54l -u <serial_number>`

## notes

- when powering from the nrf54l15dk, use nRF Connect Board Configurator to set VDDIO to 3.3V for blue, green LEDs (default is 1.8V, only works for red)
- `ln -s build/temp-eh/compile_commands.json compile_commands.json` for clangd

### apply patch

```
west update
west patch apply
```
