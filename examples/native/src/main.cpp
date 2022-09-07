#include <iostream>
using namespace std;
#include <tinyTimeUtils.h>
using namespace TinyTimeUtils;

int main() {
  for(int n=0;n<10;n++) {
    cout<<'.'<<flush;
    delay(1000);
  }
  return 0;
}