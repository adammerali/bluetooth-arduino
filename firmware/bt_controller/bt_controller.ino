#include <SoftwareSerial.h>
#include "config.h"

SoftwareSerial btSerial(BT_RX_PIN, BT_TX_PIN);

String inputBuffer = "";
bool inputComplete = false;

void setup() {
    Serial.begin(9600);
    btSerial.begin(BT_BAUD);

    for (int i = 0; i < NUM_CTRL_PINS; i++) {
        pinMode(CTRL_PINS[i], OUTPUT);
        digitalWrite(CTRL_PINS[i], LOW);
    }

    Serial.println("bt_controller ready");
    btSerial.println("OK");
}

void loop() {
    // Read incoming BT data
    while (btSerial.available()) {
        char c = (char)btSerial.read();
        if (c == '\n') {
            inputComplete = true;
        } else {
            inputBuffer += c;
        }
    }

    if (inputComplete) {
        handleCommand(inputBuffer);
        inputBuffer = "";
        inputComplete = false;
    }
}

void handleCommand(String cmd) {
    cmd.trim();
    Serial.print("rx: ");
    Serial.println(cmd);

    int sep = cmd.indexOf(':');
    if (sep == -1) {
        btSerial.println("ERR:bad_format");
        return;
    }

    String action = cmd.substring(0, sep);
    String arg    = cmd.substring(sep + 1);

    if (action == "HIGH") {
        int pin = arg.toInt();
        if (isPinAllowed(pin)) {
            digitalWrite(pin, HIGH);
            btSerial.println("OK:HIGH:" + String(pin));
        } else {
            btSerial.println("ERR:pin_not_allowed");
        }

    } else if (action == "LOW") {
        int pin = arg.toInt();
        if (isPinAllowed(pin)) {
            digitalWrite(pin, LOW);
            btSerial.println("OK:LOW:" + String(pin));
        } else {
            btSerial.println("ERR:pin_not_allowed");
        }

    } else if (action == "BLINK") {
        // arg format: "pin,count,delay_ms"
        int c1 = arg.indexOf(',');
        int c2 = arg.indexOf(',', c1 + 1);
        if (c1 == -1 || c2 == -1) {
            btSerial.println("ERR:bad_blink_args");
            return;
        }
        int pin     = arg.substring(0, c1).toInt();
        int count   = arg.substring(c1 + 1, c2).toInt();
        int delayMs = arg.substring(c2 + 1).toInt();

        if (!isPinAllowed(pin)) {
            btSerial.println("ERR:pin_not_allowed");
            return;
        }
        for (int i = 0; i < count; i++) {
            digitalWrite(pin, HIGH);
            delay(delayMs);
            digitalWrite(pin, LOW);
            delay(delayMs);
        }
        btSerial.println("OK:BLINK:" + String(pin));

    } else if (action == "STATUS") {
        String resp = "STATUS";
        for (int i = 0; i < NUM_CTRL_PINS; i++) {
            resp += ":" + String(CTRL_PINS[i]) + "=" + String(digitalRead(CTRL_PINS[i]));
        }
        btSerial.println(resp);

    } else {
        btSerial.println("ERR:unknown_cmd");
    }
}

bool isPinAllowed(int pin) {
    for (int i = 0; i < NUM_CTRL_PINS; i++) {
        if (CTRL_PINS[i] == pin) return true;
    }
    return false;
}
