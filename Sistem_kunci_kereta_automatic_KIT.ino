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
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

int timerNow = 0;
int timerNoti = 0;
int stateTimer = 0;
int state = 0;
int state2 = 0;

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
    digitalWrite(lock, HIGH);
    stateTimer = 1;
    Status = "pintu berkunci";
    }
  else {
    digitalWrite(lock, LOW);
    Status = "pintu tidak berkunci";
    state = 0;
    state2 = 0;
    stateTimer = 0;
    }
}

void myTimerEvent()
{
  DateTime now = rtc.now();

  timerNow = now.minute();

  if ( stateTimer == 1 && state == 0 ){
    timerNoti = now.minute() + 5;
    state = 1;
    }

  if (timerNow == timerNoti && state2 == 0){
    Blynk.logEvent("notification", "pintu tidak kunci");
    state2 = 1;
    }
 
  
  Blynk.virtualWrite(V1, Status);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  pinMode(lock, OUTPUT);
  Status = "pintu berkunci";

  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  
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
