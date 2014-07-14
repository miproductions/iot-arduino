#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03 };

int mqttPort = 1883;

char topic[] = "iot-2/evt/status/fmt/json";


//Create an organization in https://internetofthings.ibmcloud.com/dashboard/#/organizations/ and paste the orgid
char organization[] = "w8wx0";
char typeId[] = "ArduinoUno";


//This is the MAC Address of the Ardunio device
char deviceId[] = "00aabbccde03";


//Currently only Auth Token is allowed
char authMethod[] = "use-token-auth";


//This is the auth token obtained on registering the device in the https://internetofthings.ibmcloud.com/dashboard/#
char authToken[] = "W7TXtNbehlf7Bq5BEm";


//The convention to be followed is <orgid>.messaging.internetofthings.ibmcloud.com
char registeredMQTTDNS[] = "w8wx0.messaging.internetofthings.ibmcloud.com";


//The convention to be followed is d:<orgid>.ArduinoUno:<MAC Address>
char clientId[] = "d:w8wx0:ArduinoUno:00aabbccde03";

void callback(char* topic, byte* payload, unsigned int length) {

}

EthernetClient ethClient;
PubSubClient client(registeredMQTTDNS, mqttPort, callback, ethClient);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
 
  delay(2000);
}

void loop() {

  if( ! client.connected()) {
    client.connect(clientId, authMethod, authToken);
  }

  char json[56] = "{\"d\":{\"myName\":\"Arduino Uno\",\"temperature\":";
  dtostrf(getTemp(),1,2, &json[43]);

  json[48] = '}';
  json[49] = '}';
  json[50] = '\0';
  Serial.println(json);
  client.publish(topic, json );

  client.loop();
  delay(1000);
}


/*
This function is reproduced as is from Arduino site => http://playground.arduino.cc/Main/InternalTemperatureSensor
*/
double getTemp(void) {
  unsigned int wADC;
  double t;

  ADMUX = (_BV(REFS1) | _BV(REFS0) | _BV(MUX3));
  ADCSRA |= _BV(ADEN);  // enable the ADC

  delay(20);            // wait for voltages to become stable.

  ADCSRA |= _BV(ADSC);  // Start the ADC

  // Detect end-of-conversion
  while (bit_is_set(ADCSRA,ADSC));

  // Reading register "ADCW" takes care of how to read ADCL and ADCH.
  wADC = ADCW;

  // The offset of 324.31 could be wrong. It is just an indication.
  t = (wADC - 324.31 ) / 1.22;

  // The returned temperature is in degrees Celcius.
  return (t);
}
