iot-arduino
===========

This repository contains the quickstart and registered device sample, and contains samples for connecting Arduino Uno devices to the IBM Internet of Things cloud

The events that are emitted in this sample are:

+ Internal sensor temperature 


Connect
=========

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
10. In case of regsitered flow, you need to create a Bluemix application, which has the auth token


Development
--------------------------------
+ The code contains comments, which explains how to modify the parameters
+ In case of registered flow, you will have to connect to https://internetofthings.ibmcloud.com/dashboard/#/ and create the following
+ Organization
+ Device
+ Auth tokens
