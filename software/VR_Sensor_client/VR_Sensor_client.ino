//
//SENSOR PECHO
//
// __   __   ______        ______     ______     __   __     ______     ______     ______
///\ \ / /  /\  == \      /\  ___\   /\  ___\   /\ "-.\ \   /\  ___\   /\  __ \   /\  == \      
//\ \ \'/   \ \  __<      \ \___  \  \ \  __\   \ \ \-.  \  \ \___  \  \ \ \/\ \  \ \  __<
// \ \__|    \ \_\ \_\     \/\_____\  \ \_____\  \ \_\\"\_\  \/\_____\  \ \_____\  \ \_\ \_\    
//  \/_/      \/_/ /_/      \/_____/   \/_____/   \/_/ \/_/   \/_____/   \/_____/   \/_/ /_/    V3
//

//
//
//CADENA DE SENSORES:
//(((SENSOR PULSO)))--->(((SENSOR PANZA)))--->(((SENSOR PECHO)))--->(((RECEPTOR))--->[[[unity]]]
//
/*
    This sketch connects via WiFI to a ESP8266 AP and sends sensor data as UDP packets
    Alexandre Castonguay acastonguay@artengine.ca For Yesica Duarte
*/

///// ***** untested with the actual sensor ***** /////


#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char* ssid     = "ESPdatos";
const char* password = "respiracion";

IPAddress ip(192, 168, 4, 1);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
WiFiUDP Udp;


////// Montréal //////

int misDatos[75] = {0};   // sliding array with 100 values
int myMax = 0; //// find the maximum fron that array on the fly
int myCounter = 0;
int myTmpMax = 0;

///////////////////////

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

int steps = 0 ;
int stepsAnt;
int estado = 0 ;
int ultimoEstado = 0 ;

int datoP = 0 ; // variables para los datos de los sensores
int datoL = 0 ;
int datoL2 = 0 ;

int indice = 0 ; //indice para el protocolito
int dataIN = 0 ; //variable para la data que ingresa por el blutu serie

void sensorLanaPecho () { //funcion donde esta el sensado

  sensorValue = analogRead(analogInPin);//lectura sensor
  outputValue = map(sensorValue, 0, 1023, 1, 10);//mapeo

  if (outputValue >= 3 )//si es mayor que el umbral
  {
    digitalWrite (LED_BUILTIN, HIGH);//prendo led
    datoL2 = 2;//guardo dato
     Serial.println(datoL2);
  }
  else if (outputValue < 3  )//si es menor que el umbral
  {
    digitalWrite (LED_BUILTIN, LOW);//apago led
    datoL2 = 1;//guardo dato
     Serial.println(datoL2);
  }
}


void setup() {
  Serial.begin(115200);

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

  
  pinMode (LED_BUILTIN, OUTPUT);//pin 8 como salida

  for ( int i = 0 ; i < 5 ; i++ ) { //el led parpadea 5 veces para saludar!
    digitalWrite(LED_BUILTIN, 1 ) ;
    delay ( 100 ) ;
    digitalWrite (LED_BUILTIN, 0 ) ;
    delay ( 100 ) ;
  }

  digitalWrite (LED_BUILTIN, LOW);//apago led por las dudas
}



void loop() {

    sensorLanaPecho ();//funcion donde esta el sensado de la respiracion


    switch (indice) {// pregunto por el numero de la variable indice y segun cual sea voy al case
      case 0://arranca siempre aca
        if (dataIN == 255 ) {//si el encabezado del primer dato coincide
          indice ++;//avanzo el indice
        }
        else {//sino coincide
          indice  = 0 ;//vuelvo el indice a 0 y por ende voy al case 0
        }
        break;
      case 1:
        datoP = dataIN;//guardo el dato despues del encabezado que deberia ser el sensor de pulso
        indice++;//avanzo
        break;
      case 2 :
        if (dataIN == 254 ) {////si el encabezado del segundo dato coincide
          indice++;//avanzo el indice
        }
        else {
          indice = 0;//sino vuelvo al principio
        }
        break;
      case 3:
        datoL = dataIN; //guardo dato sensor lana panza
        indice++;//avanzo el indice
        break;
      case 4:
        if ( dataIN == 253 ) { //si me llega el ultimo dato de cierre y coincide envio todos los datos almacenados

            Udp.beginPacket(ip, 8888);
            Udp.write("datos");
            Udp.endPacket();
            Serial.println("data sent");

                   indice = 0 ;//reseteo el indice y vuelvo a leer desde el principio

          //          Serial.println(255);//imprimir en el monitor serie para DEBUGGEAR
          //          Serial.println(datoP);
          //          Serial.println(254);
          //          Serial.println(datoL);
          //          Serial.println(253);
          //          Serial.println(datoL2);
          //          Serial.println(252);

        }
        break;
    }

    // for testing, remove this once we have actual data
    Udp.beginPacket(ip, 8888);
    Udp.write("test datos");
    Udp.endPacket();
    Serial.println("data sent");
    
    delay(100);//cualquier cosa modificar un poco este delay
  }
       
