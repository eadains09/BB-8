
//Arduino Bluetooth
// HC-06 bluetooth module name


#include <SoftwareSerial.h>

int bluetoothTx = 1;
int bluetoothRx = 0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); // D11=Rx, D10=Tx
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  
  bluetooth.begin(9600);
  bluetooth.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (bluetooth.available()){
BluetoothData=bluetooth.read();
   if(BluetoothData=='1'){   // if number 1 pressed ....
   digitalWrite(ledpin,1);
   bluetooth.println("LED  On D13 ON ! ");
   }
  if (BluetoothData=='0'){// if number 0 pressed ....
  digitalWrite(ledpin,0);
   bluetooth.println("LED  On D13 Off ! ");
  }
}
delay(100);// prepare for next data ...
}

