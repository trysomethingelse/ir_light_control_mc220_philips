#include <IRremote.h>
int RECV_PIN = PD2;
int RELAY_PIN = PD4;
int SWITCH_PIN = PD6;


IRrecv irrecv(RECV_PIN);

decode_results results;
unsigned long last = millis();
bool on = false;
bool switchLast = true;


void setup() {
  irrecv.enableIRIn(); // Start the receiver
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  switchLast = digitalRead(SWITCH_PIN);
  //Serial.begin(9600);
}



void loop() {
 if (irrecv.decode(&results)) 
 {
    if(results.value == 0x54C || results.value == 0xD4C || results.value == 0x44C || results.value == 0xC4C)
    {
       if (millis() - last > 250) {
         on = !on;
         digitalWrite(RELAY_PIN, on ? HIGH : LOW);
        // Serial.println(on);
      }
    }
    
    last = millis();  
    irrecv.resume(); // Receive the next value
 }

  
 if(digitalRead(SWITCH_PIN) != switchLast)
 {
    switchLast = !switchLast;
    on = !on;
    digitalWrite(RELAY_PIN, on ? HIGH : LOW);
   // Serial.println(on);
 }

}
