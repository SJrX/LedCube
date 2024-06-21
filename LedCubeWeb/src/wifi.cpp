//
// Created by sjr on 3/31/24.
//

#include <Arduino.h>
#include <WiFi.h>

void initWifi() {
//    if (WiFi.status() == WL_NO_MODULE) {
//        Serial.println("Communication with WiFi module failed!");
//        // don't continue
//        return;
//    }
//
//    String fv = WiFi.firmwareVersion();
//    if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
//
//        String errorStr = "Please upgrade firmware from:" + fv + " to: " + WIFI_FIRMWARE_LATEST_VERSION;
//
//        error = errorStr.c_str();
//
//        errorMode = 2;
//        return;
//
//    }
//
//
//    // attempt to connect to WiFi network:
//    while (status != WL_CONNECTED) {
//        char fullBuffer[64];
//
//        sprintf(fullBuffer, "   Connecting to:%s  ", ssid);
//
//        // Connect to WPA/WPA2 network:
//        status = WiFi.begin(ssid, pass);
//        Serial.println("Connecting");
//        Serial.println(String(status));
//        // wait 1 seconds for connection:
//        delay(1000);
//    }
}
void printWifiStatus() {
    return;
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}
