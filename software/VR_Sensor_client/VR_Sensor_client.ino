//
//SENSOR PECHO
//
// __   __   ______        ______     ______     __   __     ______     ______     ______
///\ \ / /  /\  == \      /\  ___\   /\  ___\   /\ "-.\ \   /\  ___\   /\  __ \   /\  == \      
//\ \ \'/   \ \  __<      \ \___  \  \ \  __\   \ \ \-.  \  \ \___  \  \ \ \/\ \  \ \  __<
// \ \__|    \ \_\ \_\     \/\_____\  \ \_____\  \ \_\\"\_\  \/\_____\  \ \_____\  \ \_\ \_\    
//  \/_/      \/_/ /_/      \/_____/   \/_____/   \/_/ \/_/   \/_____/   \/_____/   \/_/ /_/    V5
//

//
//
// CADENA DE SENSORES:

// (((SENSOR PULSO)))---\
// (((SENSOR PANZA)))--->(((RECEPTOR))--->[[[unity]]]
// (((SENSOR PECHO)))---/
//

/*
    This sketch connects via WiFI + websockets to a ESP8266 AP and sends sensor data as UDP packets
    Alexandre Castonguay acastonguay@artengine.ca For Yesica Duarte. Thank you to EWMA library creator Arsen Torbarina.
*/
/**
   Smooth

   Demonstrates analog input smoothing.

   The circuit:
   - Potentiometer attached to analog input 0 center pin of the potentiometer
     to the analog pin: one side pin (either one) to ground the other side pin to +5V

   Created in 2016 by Sofian Audry

   This example code is in the public domain.

   Inspired from the following code:
   http://www.arduino.cc/en/Tutorial/AnalogInput
*/

#include <Plaquette.h>
#include <Thresholder.h>

// The analog input.
AnalogIn in(A0);

// The serial output.
StreamOut serialOut;

AdaptiveNormalizer norm;

Thresholder peakDetector(0.9, THRESHOLD_RISING, 0.8);

//// WiFi socket connection ////
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

//#include <Arduino.h>
//#include <Ewma.h>

//Ewma adcFilter1(0.1);   // Less smoothing - faster to detect changes, but more prone to noise


const char* ssid     = "ESPdatos";
const char* password = "respiracion";

IPAddress ip(192, 168, 4, 1);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
WiFiUDP Udp;
//// Fin WiFi socket connection ////

////// para la calibración ////
//bool calibrate = 1; // Set flag so this is executed once at the start
//int numberofMeasures = 0;
//int sensorMax = 0; // Valeurs initiales pour être remplacées
//int sensorMin = 1023; // Valeurs initiales pour être remplacées
//int storedSensorValue = 0;
//int misDatosMax[10] = {0};  // sliding array with 5 values
//int misDatosMin[10] = {0};
///// Fin calibración ////

//// para sensorLanaPecho ////
//const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
//int sensorValue = 0;        // value read from the pot
//float filteredSensorValue;
//int outputValue = 0;        // value output to the PWM (analog out)
//int moyenneMax = 0;
//int moyenneMin = 0;
//int counter = 0;
//int tmpMaxSensorValue;
//int tmpMinSensorValue;
//bool maxFlag = true;
//bool minFlag = true;
int datoL2 = 0; // Indicates state of breathing "1" or "2"
//// Fin sensorLanaPecho ////

///// para autoAdjust /////

// store sensorValues in a 5 value array to get a clear sense of if the cycle is increasing or decreasing

int unCompteur = 0;
// int cyclePositionDetect[5] = {0}; // déclaration d'un tableau contenant 5 valeurs
int monTotal;
int maMoyenne;
int viejaMoyenne;
int maDiff;
bool flagBias = true;
bool oldFlagBias = true;

///// Fin autoAdjust /////


//void setup() {
  
void begin() {

  Serial.begin(9600);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


  pinMode (LED_BUILTIN, OUTPUT); // LED del ESP8266

  for ( int i = 0 ; i < 5 ; i++ ) { //el led parpadea 5 veces para saludar!
    digitalWrite(LED_BUILTIN, 1 ) ;
    delay ( 100 ) ;
    digitalWrite (LED_BUILTIN, 0 ) ;
    delay ( 100 ) ;
  }

  digitalWrite (LED_BUILTIN, LOW);//apago led por las dudas

  // Smooth over a window of 100ms (ie. one tenth of a second).
  // NOTE: Try changing the smoothing value to see how it affects the outputs.
  in.smooth(0.2);

  norm.time(10);

}


void step() {
  in >> norm >> peakDetector;
  Serial.print(6 * norm);
  Serial.print(" ");
  Serial.println(6 * peakDetector);

  if (peakDetector == 1){
    datoL2 == 1; // peak detected
  }
  else{
    datoL2 == 2; // nope
  }

    if (datoL2 == 1) {
      Udp.beginPacket(ip, 8888);
      Udp.write("belly,1");
      Udp.endPacket();
      // Serial.println("data one sent");
    }
    else if (datoL2 == 2 ) {
      Udp.beginPacket(ip, 8888);
      Udp.write("belly,2");
      Udp.endPacket();
      //  Serial.println("data dos sent");
    }
  
} // fin step

//void loop() {
//
//  if (calibrate == 1) {
//    calibracion (); // execute once at the start
//  }
//
//  sensorLanaPecho (); //función donde esta el sensado de la respiracion
//
//  if (datoL2 == 1) {
//    Udp.beginPacket(ip, 8888);
//    Udp.write("belly,1");
//    Udp.endPacket();
//    // Serial.println("data one sent");
//  }
//  else if (datoL2 == 2 ) {
//    Udp.beginPacket(ip, 8888);
//    Udp.write("belly,2");
//    Udp.endPacket();
//    //  Serial.println("data dos sent");
//  }
//
//  delay(500);
//}
