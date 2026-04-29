# bluetooth-arduino

Control Arduino digital pins over Bluetooth with an HC-05 module. simple serial command prot, ideally would move to some sort of interface or app in future.

## Wiring

| HC-05 | Arduino |
|---|---|
| TX | Pin 10 |
| RX | Pin 11 (voltage divider — HC-05 is 3.3V) |
| VCC | 5V |
| GND | GND |

## Commands

`HIGH:pin` — `LOW:pin` — `BLINK:pin,count,ms` — `STATUS`

## Use

Flash `firmware/bt_controller/bt_controller.ino`, pair the HC-05, then:

```bash
pip install pyserial
python host/bt_serial.py COM3          # interactive
python host/bt_serial.py COM3 --demo   # demo sequence
```
