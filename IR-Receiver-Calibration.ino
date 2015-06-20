#include <IRremote.h>
 
#define RECV_PIN 3 // the pin where you connect the output pin of TSOP4838
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
  Serial.begin(9600);   
  irrecv.enableIRIn();  
  pinMode(13, OUTPUT);
}
 
void loop() {
  if (irrecv.decode(&results)) {
    digitalWrite(13,HIGH);
    unsigned int value = results.value;
    Serial.print("Reading: ");
    Serial.println(value); 
    irrecv.resume(); 
  }
  delay(10);
  digitalWrite(13,LOW);
}
