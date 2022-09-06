#include "tinyTimeUtils.h"
namespace TinyTimeUtils {
  #ifndef ARDUINO
    void delay(unsigned long ms) {
      TimeoutAt o(timeSrc()+ms);
      while(!o);
    }
  #endif
};