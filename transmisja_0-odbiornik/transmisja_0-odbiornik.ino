#include <IRremote.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"


// Hardware configuration

RF24 radio(1,0); // Set up nRF24L01 radio on SPI bus plus pins 9 & 10

IRsend irsend;

//const int role_pin = A4; // Connect to GND to be the 'led' board receiver, leave open to be the 'remote' transmitter
const uint8_t ok_led = 8;
bool ok_state = false;
const uint8_t waiting_led = 7;
const uint8_t error_led = 6;

long unsigned int msg = 0; 

const uint64_t pipe = 0xE8E8F0F0E1LL; // Single radio pipe address for the 2 nodes to communicate.

////////////////////////////// SETUP  ///////////////////////////////////////////
void setup(void) {
  pinMode(ok_led,OUTPUT); pinMode(waiting_led,OUTPUT); pinMode(error_led,OUTPUT);
  //radio.setAutoAck(false);
  //radio.setRetries(0,15); //(delay x*250us, tries)
  //ustawic predkosc transmisji na 250kbps i znalezc jakis sposob na przesylanie zbieranych danych
  //radio.setDataRate(RF24_250KBPS); //250KBPS, 1MBPS, 2MBPS
  radio.setPayloadSize(8); 	
  radio.begin(); // Setup and configure rf radio
  radio.setDataRate(RF24_250KBPS);


  radio.openReadingPipe(1,pipe); // Open pipes to other nodes for communication.
  radio.startListening(); // Start listening

  pinMode(ok_led,OUTPUT); pinMode(waiting_led,OUTPUT); pinMode(error_led,OUTPUT);
  digitalWrite(waiting_led, HIGH); delay(1000); 
  irsend.sendNEC(0x11223344, 64);  delay(1000); 
}

////////////////////////////// LOOP  ////////////////////////////////////////////
void loop(void) {
 // Receive the state of all buttons, and reflect that in the LEDs if there is data ready
  if ( radio.available() ) {     
    while (!radio.read( &msg, 8 )) { // Dump the payloads until we've gotten everything
      digitalWrite(waiting_led, HIGH);
    }
    
    irsend.sendNEC(msg, 64);

    ok_state ^= true;
    digitalWrite(ok_led, ok_state);
    //delay(1000);
  }
  digitalWrite(waiting_led, LOW);
}
