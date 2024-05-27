#define BLYNK_PRINT Serial

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_TEMPLATE_ID           "TMPL6SGbaLNUC"
#define BLYNK_TEMPLATE_NAME         "Test1"
#define BLYNK_AUTH_TOKEN            "p_aCWM7rXwdY2nH2EzuurR9CEhqKlwB9"

#include <BlynkSimpleEthernet.h>

char auth[] = "p_aCWM7rXwdY2nH2EzuurR9CEhqKlwB9";

void setup() {
  Serial.begin(9600);

  DebugSerial.begin(9600);

  Blynk.begin(Serial, auth);
}

void loop() {
  Blynk.run();
}
