#define BLYNK_TEMPLATE_ID "TMPLlEZ8Gt1n"
#define BLYNK_DEVICE_NAME "sistem kunci kereta"
#define BLYNK_AUTH_TOKEN "X-JogQCYRiL3saca161JmpsTXBh6GuZB"

int lock = 32;
String Status = "";

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "NAFZA";
char pass[] = "VPGNFS6euS";

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin V1
BLYNK_WRITE(V0)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if (pinValue == 1){
    digitalWrite(lock1, HIGH);
    Status = "pintu tidak berkunci";
    }
  else {
    digitalWrite(lock, LOW);
    Status = "pintu berkunci";
    }
}

void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, Status);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(lock1, OUTPUT);
  pinMode(lock2, OUTPUT);
  Status = "pintu tidak berkunci";
  
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
