#pragma once

// HC-05 wiring
#define BT_RX_PIN  10   // Arduino RX <- HC-05 TX
#define BT_TX_PIN  11   // Arduino TX -> HC-05 RX
#define BT_BAUD    9600

// Pins the host is allowed to control
const int CTRL_PINS[]  = {2, 3, 4, 5, 6, 7};
const int NUM_CTRL_PINS = 6;
