# Tiny time utils

Tiny easy timeouts, FPS and blinks without delay

## rblink

runtime blink  
return true/false on a defined on/off rate that can be adjusted at runtime

```c++
bool rblink(time_on,time_off)
```

`time_on` milliseconds to stay on
`time_off` milliseconds to stay off

**usage**

just set this function as the led state and it will blink at defined rate.

```c++
digitalWrite(ledPin,rblink(100,900));
```

## sblink

static blink  
return true/false on a compile time fixed on/off rate, can not be changed at runtime.

```c++
bool sblink<time_on,time_off>()
```

`time_on` milliseconds to stay on

`time_off` milliseconds to stay off

**usage**

just set this function as the led state and it will blink at defined rate.

```c++
digitalWrite(ledPin,rblink<100,900>());
```

## FPS

Limit the FPS rate of a function/process  
useful to execute a function at a defined maximum rate without worry of time process details.

The rate is defined at compile time and can not be changed after.

```c++
FPS<n> varName;
```

`n` milliseconds minimal interval

`varName` a variable name of your choice

**usage**

```c++
FPS<2> fps;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if(fps) Serial.print(".");//will print a maximum of 2 dots per seconds (can be less if busy)
}
```

## Tick

Allow a process to run at least some time step appart from the previous call. It will be on/true after defined timeout, and reset itself for next step.

This is the base for FPS but exposes extra functionalities.

The timming distance is fixed at compile time.

Self reset is done **only** on first reached read.

```c++
Tick<step> tick;
```

`step` milliseconds minimal interval

`tick` a variable name of your choice

**member functions**

`void reset()` force reset timeout from now to `step` ms.

`long when()` just returns next target millis
