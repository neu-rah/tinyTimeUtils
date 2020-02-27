#include <tinyTimeUtils.h>
using namespace TinyTimeUtils;

constexpr uint8_t ledPin=10;

FPS<1> adjust;//will adjust rate once per second

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(ledPin,OUTPUT);
}

void loop() {
  //initialize vars (static here means just once)
  static int rate_change=10;
  static int time_on=100;
  static int time_off=900;

  digitalWrite(ledPin,rblink(time_on,time_off));//changing on/off at compile time
  digitalWrite(LED_BUILTIN,sblink<100,900>());//fixed rate at compile time, can not change

  if(adjust) {//only once per second
    //changing the rate at runtime
    time_on+=rate_change;
    time_off-=rate_change;
    if (time_on>500) rate_change=-10;
    else if(time_on<100) rate_change=10;
  }
}
