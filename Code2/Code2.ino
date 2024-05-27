#define BLYNK_PRINT DebugSerial

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_TEMPLATE_ID "TMPL6SGbaLNUC"
#define BLYNK_TEMPLATE_NAME "Truong Bao Quoc"
#define BLYNK_AUTH_TOKEN "8LMmcV-k1YZ0-POJvWmP4cNviCvhsLUe"
#include <BlynkSimpleStream.h>
char auth[] = "8LMmcV-k1YZ0-POJvWmP4cNviCvhsLUe";

int var;
#define LED 12
BLYNK_WRITE(V1)
{
  var = param.asInt();
  digitalWrite(LED,var);
}

int pinRelay1 = 4;
int pinRelay2 = 5;

#include "DHT.h"
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Đọc nhiệt độ theo độ C

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V0, t); // Gửi nhiệt độ đến Blynk app (Virtual Pin V5)
  Blynk.virtualWrite(V1, h); // Gửi độ ẩ đến Blynk app (Virtual Pin V6)

  DebugSerial.print("Nhiet do:");
  DebugSerial.println(t);
  DebugSerial.print("Do am:");
  DebugSerial.println(h);
  DebugSerial.println("");
}

// BLYNK_WRITE(V2)
// {
//   int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
//   if (pinValue == 1){
//     digitalWrite(pinRelay1, HIGH);
//   } else if (pinValue == 0) {
//     digitalWrite(pinRelay1, LOW);
//   }
  
//   Serial.print("V1 button value is: "); // printing value to serial monitor
//   Serial.println(pinValue);
// }

// BLYNK_WRITE(V3)
// {
//   int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  
//   if (pinValue == 1){
//     digitalWrite(pinRelay2, HIGH);
//   } else if (pinValue == 0) {
//     digitalWrite(pinRelay2, LOW);
//   }
  
//   Serial.print("V1 button value is: "); // printing value to serial monitor
//   Serial.println(pinValue);
// }

void setup() {
  DebugSerial.begin(9600);

  pinMode(pinRelay1, OUTPUT);
  pinMode(pinRelay2, OUTPUT);

  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  Blynk.begin(Serial, auth);
  dht.begin();
  timer.setInterval(2000L, sendSensor);
  DebugSerial.println("");
}

void loop() {
  Blynk.run();
  timer.run();
}