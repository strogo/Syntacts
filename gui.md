---
layout: page
title: GUI
permalink: /gui/
---

## Introduction

This tutorial will teach you how to setup and use the Syntacts GUI. This will allow you to create, visualize, and sequence cues for your desired use.

## Requirements

- Latest [Syntacts Release](https://github.com/mahilab/Syntacts/releases)

## Basic Setup

- Download the [latest pre-compiled Syntacts binaries](https://github.com/mahilab/Syntacts/releases) for your system and extract the files. 
- Run the GUI executable `syntacts-gui` in the top level directory. 
- On Windows, you may receive a “Windows protected your PC” screen. Click “More info”, then “Run anyway”.
- On macOS, the executable `syntacts-gui` may not run, and it will instead open the binary code. If this occurs, open a Terminal and run the following command in the directory of the Syntacts binaries. After this, you will be able to successfully run `syntacts-gui`.

```shell
> sudo chmod 777 syntacts-gui
```

## GUI Panel Overview

This will provide an overview of the GUI's panels and a basic guide about their uses. For more detailed information on how to use different components of the GUI, simply drag the help button (the question mark in the bottom right corner) over the area of interest.

# Device Bar

- The Device Bar is located at the top-center of the GUI.
- Using the drop down arrows, you can choose your API, device, and sample rate.

# Status and Info Bar

- The Status and Info Bar is located at the bottom-right of the GUI.
- When you hover your mouse over different areas/panels of the GUI, the Info Bar states the function of that component.

# Palette/Library

- The Palette and Library panels are located on the left side of the GUI.
- The Palette contains tools to create different Signals. Signals represent various vibration waveforms. 
- Using the Palette, you can use different types of oscillators, envelopes, and processes to create your desired cue.
- The Library allows you to save and load created Signals.

# Player

- The Player is located on the right side of the GUI.
- This is used to play Signals on different channels.
- Using the Player, you can also change the volume and pitch by moving the V and P toggles.

# Designer

- The Designer is the first tab located in the center of the GUI.
- This is where you can drag Signals to create your desired cue.
- You can combine Signals using different processes. Signals can be mixed using basic arithmetic. Multiplying and adding Signals can be thought of as an element-wise operation between two vectors.
- You can also change the frequency of Signals.

# Sequencer

*Coming Soon*

# Spatializer

*Coming Soon*