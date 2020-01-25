# CPPMap
Stand Alone C++ Map for use in SAMD21 Pro RF using Arduino IDE with arm-none-eabi-gcc version 4.8.3-2014q1.

## Background:
When using the previously mentioned stack, functionalities such as map (in this case) generate a set of dependency issues that can be a pain to fix. We provide a easy solution to this problem for map (and maybe list).

## How to install:
There are two ways to get install the map. You can downloaded the zipped version of this repository and install it using the Arduino IDE. You can also clone the repository into the Arduino library directory. 

## Example:

```c++
#undef max
#undef min
#include <aloneMap.h> // Given this name to prevent confusion.

std::aloneMap<char,char> exampleMap;

void setup() {  
  Serial.begin(9600);
  while(!Serial);
  
  exampleMap["hello"] = "Example 1";
  exampleMap["world"] = "Example 2";

  for (std::aloneMap<char,char>::iterator it=exampleMap.begin(); it!=exampleMap.end(); ++it){
  Serial.print(it->first);
  Serial.print(" : ");
  Serial.println(it->second);
  }
}

void loop(){
}

```

## Sources:
* [sparkfun](https://learn.sparkfun.com/tutorials/installing-arduino-ide/board-add-ons-with-arduino-board-manager)
* [STL for AVR with C++](https://andybrown.me.uk/2011/01/15/the-standard-template-library-stl-for-avr-with-c-streams/#IDComment246044033)
* [StandardCplusplus](https://github.com/maniacbug/StandardCplusplus)
