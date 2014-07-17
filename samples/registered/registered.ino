#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x03 };

int mqttPort = 1883;

char topic[] = "iot-2/evt/status/fmt/json";
char subtopic[] = "iot-2/cmd/+/fmt/json";

char organization[] = "w8wx0";
char typeId[] = "ArduinoUno";

char deviceId[] = "00aabbccde03";

char authMethod[] = "use-token-auth";

char authToken[] = "W7TXtNbehlf7Bq5BEm";

char registeredMQTTDNS[] = "w8wx0.messaging.internetofthings.ibmcloud.com";

char clientId[] = "d:w8wx0:ArduinoUno:00aabbccde03";

void callback(char* topic, byte* payload, unsigned int length);


EthernetClient ethClient;
PubSubClient client(registeredMQTTDNS, mqttPort, callback, ethClient);

void setup() {
  Serial.begin(9600);
  Ethernet.begin(mac);
 
  if( ! client.connected()) {
    client.connect(clientId, authMethod, authToken);
  }
  client.subscribe(subtopic); 
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message has arrived");
  
/*  char p[100];
  int count = 0;
  for(count = 0 ; count < length ; count++) {
    p[count] = payload[count];
  }
  p[count] = '\0';

  Serial.println(p);
*/

  char * msg = (char *)malloc(length * sizeof(char));
  int count = 0;
  for(count = 0 ; count < length ; count++) {
    msg[count] = payload[count];
  }
  msg[count] = '\0';
  Serial.println(msg);
  free(msg);
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
