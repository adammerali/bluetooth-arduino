"""
bt_serial.py — send commands to the bt_controller sketch over serial.
Usage:
    python host/bt_serial.py COM3          # interactive mode
    python host/bt_serial.py COM3 --demo   # run demo sequence
"""

import serial
import time
import sys
import argparse


def open_port(port: str, baud: int = 9600, timeout: float = 2.0) -> serial.Serial:
    ser = serial.Serial(port, baud, timeout=timeout)
    time.sleep(2)  # wait for Arduino reset
    ser.reset_input_buffer()
    return ser


def send(ser: serial.Serial, cmd: str) -> str:
    ser.write((cmd.strip() + "\n").encode())
    response = ser.readline().decode().strip()
    return response


def demo(ser: serial.Serial):
    cmds = [
        "HIGH:2",
        "HIGH:3",
        "STATUS",
        "BLINK:2,5,200",
        "LOW:2",
        "LOW:3",
        "STATUS",
    ]
    for cmd in cmds:
        print(f">> {cmd}")
        resp = send(ser, cmd)
        print(f"<< {resp}")
        time.sleep(0.5)


def interactive(ser: serial.Serial):
    print("Connected. Type commands (HIGH:pin / LOW:pin / BLINK:pin,count,ms / STATUS). Ctrl+C to exit.")
    try:
        while True:
            cmd = input(">> ").strip()
            if not cmd:
                continue
            resp = send(ser, cmd)
            print(f"<< {resp}")
    except KeyboardInterrupt:
        print("\nDisconnected.")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("port", help="Serial port (e.g. COM3 or /dev/ttyUSB0)")
    parser.add_argument("--baud", type=int, default=9600)
    parser.add_argument("--demo", action="store_true", help="Run demo sequence")
    args = parser.parse_args()

    ser = open_port(args.port, args.baud)
    try:
        if args.demo:
            demo(ser)
        else:
            interactive(ser)
    finally:
        ser.close()


if __name__ == "__main__":
    main()
