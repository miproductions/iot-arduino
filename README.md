Arduino Uno Sample
====================

This repository contains the quickstart and registered device sample, and contains samples for connecting Arduino Uno devices to the IBM Internet of Things Cloud

The events that are emitted in this sample are:

+ Internal sensor temperature 


Common setup for the 2 flows
============================
1. Connect Ethernet / Wifi shield to Arduino Uno
2. Connect Ethernet cable to the Ethernet / Wifi shield 
3. Install sketch on desktop / laptop
4. Connect the USB cable to the Arduino Uno and other end to desktop / laptop which has the sketch installed on it
5. The samples folder of this repository contains 2 codes - 
	a) Quickstart flow
	b) Registered flow
6. Compile the 2 flows
7. Depending upon the requirement, copy one of the flows to the Arduino device
8. Reset the Ethernet / Wifi shield
9. Wait for about 10 seconds and the flow starts working


Quickstart flow
=======================
1. Modify the clientId, in the sketch code, by providing the values in the following format "d:quickstart:iotsample-arduino:aabbccde02", by replacing "aabbccde02" with the MAC Address
2. Open the quickstart dashboard (http://quickstart.internetofthings.ibmcloud.com/#/) 
3. Provide the MAC Address (in case of the example, its aabbccde02) in the textbox "Ready to View data?"


Registered Flow
===============================
This has 2 flows
1) Registered Flow from device
2) Registered Flow to device

Registered Flow from device and to device
===========================================
1. Modify the organization, authToken, in the sketch code
2. Modify the registeredMQTTDNS, in the sketch code, by providing the values in the following format "w8wx0.messaging.internetofthings.ibmcloud.com", by replacing "w8wx0" with the organization
3. Modify the clientId, in the sketch code, by providing the values in the following format "d:w8wx0:ArduinoUno:00aabbccde03", by replacing "aabbccde03" with the MAC Address and "w8wx0" with the organization
4. Use mqttpublisher / mqttsubscriber to publish and subscribe the commands / events sent to / received from the Arduino Uno


Development
===============================
+ The code contains comments, which explains how to modify the parameters
+ In case of registered flow, you will have to connect to https://internetofthings.ibmcloud.com/dashboard/#/ and create the following
+ Organization
+ Device
+ Auth tokens
