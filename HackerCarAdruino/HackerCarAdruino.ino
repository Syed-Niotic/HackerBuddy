/*
 * Copyright (c) 2016 Intel Corporation.  All rights reserved.
 * See the bottom of this file for the license terms.
 */

#include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);
int LED2 = 4; //the Grove port No. you attached a button to
int LED1 = 8;
int motorPin = 3;//the Grove port No. you attached an LED to

void setup() {
  Serial.begin(9600);

  pinMode(LED1, OUTPUT); //set button as an INPUT device
  pinMode(LED2, OUTPUT);
  pinMode(motorPin, OUTPUT);//set LED as an OUTPUT device

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("LED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      if (switchCharacteristic.written()) {
        if (switchCharacteristic.value() == 1) {   // any value other than 0
          Serial.println("LED on");
          while (switchCharacteristic.value() == 1){
            digitalWrite(motorPin, HIGH);
            digitalWrite(LED1,HIGH); 
            digitalWrite(LED2,LOW);
            delay(200);
            digitalWrite(LED1,LOW); 
            digitalWrite(LED2,HIGH);
            delay(200); 
          }         // will turn the LED on
        }if(switchCharacteristic.value() == 2){
         while (switchCharacteristic.value() == 1){
            digitalWrite(LED1,HIGH); 
            digitalWrite(LED2,LOW);
            delay(200);
            digitalWrite(LED1,LOW); 
            digitalWrite(LED2,HIGH);
            delay(200); 
          }       
        }else {                              // a 0 value
          Serial.println(F("LED off"));
          digitalWrite(LED1, LOW); 
          digitalWrite(LED2, LOW);// will turn the LED off
          digitalWrite(motorPin, LOW);
        }
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }

}

