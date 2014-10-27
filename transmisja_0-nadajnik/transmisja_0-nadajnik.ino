#include <IRremote.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int RECV_PIN = 0;
bool value_dioda = false;
uint8_t pin_dioda =8;
int i = 0;

IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend irsend; // chyba nie moze dzialac na raz receiver i sender
long unsigned int msg = 0x46467878;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

////////////// SETUP ////////////// 
void setup()
{
  pinMode(pin_dioda, OUTPUT);
  digitalWrite(pin_dioda, HIGH); delay(1000); digitalWrite(pin_dioda, LOW);
  
  irrecv.enableIRIn(); 
  
  lcd.begin(16, 2);
  lcd.print("Ready...");
  
  //radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(8); 	
  radio.begin(); // Setup and configure rf radio
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe); // jesli nadajnik
  
  digitalWrite(pin_dioda, HIGH); delay(1000); digitalWrite(pin_dioda, LOW);
  radio.write(&msg , 8 );
}

////////////// LOOP ////////////// 
void loop() {    
  if (irrecv.decode(&results)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    
    if (results.decode_type == NEC) { lcd.print("NEC: "); } 
    else if (results.decode_type == SONY) { lcd.print("SONY: "); } 
    else if (results.decode_type == RC5) { lcd.print("RC5: "); } 
    else if (results.decode_type == RC6) { lcd.print("RC6: "); } 
    else if (results.decode_type == UNKNOWN) { lcd.print("?: "); }
    else { lcd.print(results.decode_type); lcd.print(": "); }
    
    lcd.print(results.value, HEX);
    lcd.setCursor(0, 1);
    lcd.print(++i);
    irrecv.resume(); // Receive the next value
    
    delay(500);
    results.value++; // <----- UWAGA!!!
    radio.write(&results.value , 8 );
  }
}
