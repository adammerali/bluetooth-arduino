# bluetooth-arduino

Arduino sketch + Python host for controlling digital pins over Bluetooth using an HC-05 module. Supports setting pins high/low, blinking, and reading pin state — all over a simple serial command protocol.

## Wiring

| HC-05 | Arduino |
|---|---|
| TX | Pin 10 |
| RX | Pin 11 (use voltage divider — HC-05 is 3.3V logic) |
| VCC | 5V |
| GND | GND |

Controllable pins: 2–7 (configurable in `config.h`).

## Commands

| Command | Example | Description |
|---|---|---|
| `HIGH:pin` | `HIGH:3` | Set pin high |
| `LOW:pin` | `LOW:3` | Set pin low |
| `BLINK:pin,count,ms` | `BLINK:3,5,200` | Blink pin N times |
| `STATUS` | `STATUS` | Read all pin states |

## Usage

Flash `firmware/bt_controller/bt_controller.ino` to the Arduino, pair the HC-05, then:

```bash
pip install pyserial
python host/bt_serial.py COM3          # interactive
python host/bt_serial.py COM3 --demo   # demo sequence
```
