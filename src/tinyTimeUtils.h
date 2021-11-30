#pragma once
/********************
tiny time utils
Rui Azevedo - ruihfazevedo(@rrob@)gmail.com
*/

#ifndef ARDUINO
//assume PC then
#include <chrono>
#endif

namespace TinyTimeUtils {

  #ifdef ARDUINO
    //use Arduino `millis` as time source
    constexpr auto timeSrc=millis;
  #else
    auto timeSrc=[](){
      return (unsigned long) std::chrono::duration_cast<std::chrono::milliseconds>
        (std::chrono::system_clock::now().time_since_epoch()).count();
    };
  #endif

  //time ticks as boolean
  template<int step>
  struct Tick {
    // inline operator bool() {return timeSrc()>=next?next+=step,true:false;}
    inline operator bool() {
      constexpr unsigned long over=~0;
      if (timeSrc()<next) return false;
      if ((next+step)<next) next=over;//overflow
      else next+=step;
      return true;
    }
    inline void reset() {next=timeSrc()+step;}
    inline long when() const {return next;}
  protected:
    unsigned long next=0;
  };

  struct TimeoutAt {
    TimeoutAt(unsigned long at):trig(false),next(at) {}
    void set(unsigned long at) {trig=false;next=at;}
    inline long when() const {return next;}
    inline operator bool() {
      return trig?true:trig=next<=timeSrc();
    }
  protected:
    bool trig;
    unsigned long next;
  };

  template<unsigned long timeout>
  struct Timeout:TimeoutAt {
    Timeout():TimeoutAt(timeSrc()+timeout) {}
    inline void reset() {set(timeSrc()+timeout);}
  };

  template<int step,typename T=uint16_t>
  struct TickCnt {
    static constexpr unsigned long over=0xFFFFFFFF;
    operator T() {
      unsigned long now=timeSrc();
      T cnt=0;
      unsigned long past=now<last?(over-last)+now:now-last;
      // Serial.print(" step:");
      // Serial.print(step);
      // Serial.print(" overflow cnt:");
      // Serial.print(cnt);
      // Serial.print(" now:");
      // Serial.print(now);
      // Serial.print(" last:");
      // Serial.print(last);
      // Serial.print(" past:");
      // Serial.print(past);
      // Serial.print(" cnt:");
      // Serial.println(cnt+(past>step?past%step:0));
      return cnt+(past>step?past%step:0);
    }
    inline void reset() {last=timeSrc();}
    inline long when() const {return last+step;}
    protected:
      unsigned long last=0;
  };


  //FPS as boolean
  // this is an FPS limiter
  // will return `true` `fps` times per second (max)
  // note: this can skip a frame at timeSrc (millis) wrap (every 50days ;))
  template<int fps>
  struct FPS:public Tick<(1000/fps)> {};

  //blink without delay at a fixed rate (compile time defined)
  //just set the led state to this function output.
  template<int timeOn,int timeOff>
  inline bool sblink() {
    return timeSrc()%(unsigned long)(timeOn+timeOff)<(unsigned long)timeOn;
  }

  //blink without delay, just set the led state to this function output.
  //rate can be changed at runtime
  inline bool rblink(int timeOn,int timeOff) {
    return timeSrc()%(unsigned long)(timeOn+timeOff)<(unsigned long)timeOn;
  }
};
