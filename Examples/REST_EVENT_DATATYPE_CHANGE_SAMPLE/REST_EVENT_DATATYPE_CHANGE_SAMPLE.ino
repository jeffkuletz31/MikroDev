/*
   developed by: rjjrdev
   used for esp shield
   
   root commands: config, wifi, event, type, server, rest ,connect and api

   config mode1 mode2 mode3 mode4
   mode1: -d -r or -o
   mode2: -s or -o
   mode3: -o or key
   mode4: -a or -b

   wifi sta_ssid sta_password/mode1 ap_ssid/mode2 ap_password/mode3 wireless_mode phy_mode tx_power
   mode1&2&3: -o for blank
   wireless_mode: -a -s -as
   phy_mode: -b -g -n
   tx_power: -l and -h

   event event_name1 event_name2 event_name3 event_name4 event_name5
   note: default event name are event0 ... event4, you can use this to override event names
   note: there are only 5 event you can use
   
   type num1 num2 num3 ...
   num1&2&3..10: 1 or 0 only to change key variables types to int or words respectively
   note: this corresponds to server keys count, if num1-num3 then key1-key3

   server port key1 key2 key3 ... key10
   port: rest server port
   key1&2&3..10: 
   
   rest response var1 var2 var3 ... var10
   response: special key in integer cannot be overriden using the type command
   var1&2&3..10: overridable variable key and value pair, check type how to change the data type
   
   connect username password/mode port
   mode: -o for blank password
    
   api arg1 arg2 arg3
   arg1&2&3... mikrotik api commands
   consult mikrotik api for references
   this uses standard mikrotik api fully compatible
*/

#include <MikroDev.h>
#include <SoftwareSerial.h>
#if defined(ESP8266) || defined(ESP32)
SoftwareSerial softSer;
#else
#include <avr/pgmspace.h>
#include <MemoryFree.h>
SoftwareSerial softSer(10, 11);
#endif

#define EVENT_1 1
#define EVENT_2 2
#define EVENT_3 3
#define EVENT_4 4
#define EVENT_5 5

mikrodev dev(softSer);


void initialization() {
  dev.sendCommand("config -o -o -o -a");
  dev.sendCommand("wifi WIFISSID -o -o -o -s -g -h");
  dev.sendCommand("event ev1 ev2 ev3 ev4 ev5");
  dev.sendCommand("type 1 0 1 0 1");
  dev.sendCommand("server 80 rock paper corn clock glass");
  dev.sendCommand("rest 1 bee 2 bear 3 boy");
}

void eventLoop() {
  char  eventData[rx_buffer];
  int eventType;
  char* event_args[5] = {"ev1:", "ev2:" , "ev3:", "ev4:" , "ev5:"};
  dev.event(eventType, eventData, event_args);
  if (eventType == EVENT_1) {
    Serial.print("1stEvent ");
    Serial.println(eventData);
    freeMem();
  } else if (eventType == EVENT_2) {
    Serial.print("2ndEvent ");
    Serial.println(eventData);
    freeMem();
  } else if (eventType == EVENT_3) {
    Serial.print("3rdEvent ");
    Serial.println(eventData);
    freeMem();
  } else if (eventType == EVENT_4) {
    Serial.print("4thEvent ");
    Serial.println(eventData);
    freeMem();
  } else if (eventType == EVENT_5) {
    Serial.print("5thEvent ");
    Serial.println(eventData);
    freeMem();
  }
}

void setup() {
  Serial.begin(9600);
  dev.init(19200);
  initialization();
  Serial.println("start");
}

void freeMem() {
#if defined(ESP8266) || defined(ESP32)
  Serial.printf("[HEAP] Mem Free: %d\n", free);
  Serial.printf("[HEAP] Free Heap: %d\n", ESP.getFreeHeap());
  Serial.printf("[HEAP] Fragmentation: %d\n", ESP.getHeapFragmentation());
  Serial.printf("[HEAP] Max Free Heap: %d\n", ESP.getMaxFreeBlockSize());
#else
  Serial.println(freeMemory());
#endif
}

void loop() {
  eventLoop();
}
