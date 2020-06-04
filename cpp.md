---
layout: page
title: C++ API
permalink: /cpp/
---

## Introduction

This tutorial will teach you how to setup and use the Syntacts C++ API. 
You should have first built and installed the Syntacts library to your system. 
For this tutorial we will use [CMake](https://cmake.org/) to manage our project and build. 
However, the process should be similar if you are using an IDE such as Visual Studio or Xcode.

## Requirements

- C++ compiler
- [CMake](https://cmake.org/)

## Basic Setup

- If you haven't already, [build and install](building.md) Syntacts.
- Create an empty directory for your project.
- Create a new `CMakeLists.txt` build script with the following contents:

```cmake
# create a new CMake project
cmake_minimum_required(VERSION 3.13.0)
project(MySyntactsProject VERSION 1.0.0)
# find the installed Syntact libraries
find_package(syntacts REQUIRED)
# create an executable from main.cpp and link it against Syntacts
add_executable(myApp main.cpp)
target_link_libraries(myApp syntacts)
```

- Add a C++ source file `main.cpp` with the following contents:

```cpp
#include <syntacts>

using namespace tact;

int main(int argc, char const *argv[])
{
    Session s;
    s.open();
    s.playAll(Sine(440));
    sleep(2);
    return 0;
}
```

## Building

- After you've created `CMakeLists.txt` and `main.cpp`, open Powershell (or Terminal) in the directory that contains those files.
- Make sure CMake is added to your system PATH.
- Run the following commands:

```shell
mkdir build                      # make out-of-source build folder
cd build                         # change directory
cmake ..                         # generate build files from our CMakeLists.txt file
cmake --build . --config Release # build the project
```

- When the build completes, find the output file `myApp.exe` in the build folder and run it. You should hear a two second 440 Hz sine wave from your default speakers.

## API Overview

# Session

Using Syntacts begins with creating a `Session`, or an audio-context that manages communication with an output device. Devices available for opening can be enumerated and queried for information using a `Session`: 

```cpp
Session session;

for (auto& d : session.getAvailableDevices()) {
    auto& dev = d.second;
    std::cout << dev.index << std::endl;
    std::cout << dev.name  << std::endl;
}
```

Devices can be opened using the `open` function. The no-argument overload will open the system default audio device (usually the main speakers). Non-default devices can be opened by passing a device index argument or the device name and preferred API:

```cpp
// open default device
session.open();   
session.close();  
// open device by index
session.open(22); 
session.close();  
// open device by name and preferred API
session.open("MOTU Pro Audio", API::ASIO);
session.close();
```

Device indices represent the combination of a device and an API it supports. Therefore, one device may have multiple indices each with a diffrent API. You can retrieve your device's index and/or name by iterating as in the above example, or by opening the [Syntacts GUI](gui.md) and viewing the information there.

> **Warning:** Device indices are NOT persistent. They may change when devices are power cycled, plugged/unplugged, or when other devices are connected to the PC. If you need a persistent method of opening a device, use the **name + API** version of `open`.

|Relevant Header(s)|Relevant Examples(s)|
|---|---|
|[Session.hpp](https://github.com/mahilab/Syntacts/blob/master/include/Tact/Session.hpp)|[example_devices.cpp](https://github.com/mahilab/Syntacts/blob/master/examples/example_devices.cpp)|

# Signals

- Vibration waveforms are represented by one or more Signals.
- In Syntacts, you can create Signals of different behaviors and lengths.
- Sine, Square, Saw, and Triangle classes are available in Syntacts. These implement typical oscillators with normalized amplitude and infinite duration. 
- Basic oscillators can be created using simple functions:

```cpp
    Signal sin = Sine(10); // 10 Hz Sine wave
    Signal sqr = Square(100); // 100 Hz Square wave
    Signal saw = Saw(440); // 440 Hz Saw wave (audible and ok for speakers)
    Signal tri = Triangle(440); // 440 Hz Triangle wave
```

- Envelope and ASR (Attack, Sustain, Release) define amplitude modifiers with finite duration:

```cpp
    // This is a basic envelope that specifies amplitude (0.9), and duration        (0.5 sec)
    Signal bas = Envelope(0.9, 0.5);
    // This is an attack (0.1 sec), sustain (0.1 sec), release (0.1 sec) envelope. The sustain amplitude is 1.0. 
    // Envelopes can interpolate between amplitudes with different curves, this example uses a smooth s-curve and linear.
    Signal asr = ASR(0.1, 0.1, 0.1, 1.0, Curves::Smootheststep(), Curves::Linear());
```

-Signals can be mixed using basic arithmetic.
-Multiplying two Signals creates a new Signal of duration equal to the shortest operand.  
-Adding two Signals creates a new Signal of duration equal to the longest operand.
-Gain and bias can also be applied to Signals with scalar operands.
-Additionally, some signals can accept other Signals as their input arguments.
-Below are basic examples of mixing the Signals from above:

```cpp
    Signal sig1 = sqr * sin; // duration is infinite
    Signal sig2 = sig1 * asr; // duration is 0.3 seconds
    Signal sig3 = 0.5 * (sqr + sin) * asr;
```

-Custom Signals can be created through classes that define the functions sample and length.
-Signals can be played and stopped:

```cpp
    // play Signals on channel 0 and 1
    session.play(0, sig1) // plays until stopped
    session.play(1, sig2) // plays for 0.3 seconds
    session.stop(0) // stop sig1
```

# Sequences

*Coming soon*

# Spatializers

*Coming soon*
