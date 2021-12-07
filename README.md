# 💡OpenHue💡

![GitHub](https://img.shields.io/github/license/BOB450/OpenHue?logoColor=blue)  ![GitHub issues](https://img.shields.io/github/issues/BOB450/OpenHue)  ![GitHub last commit](https://img.shields.io/github/last-commit/BOB450/OpenHue)

A cross platform application to control your Philips hue compatible lights.
licensed under the gpl 3.0 license. Currently in super early version but will be providing binary's for linux and windows soon.

![OpenHue1](imgs/OpenHue3.png)![OpenHue1](imgs/OpenHue4.png)![OpenHue1](imgs/color_selection.png)

## Current Features

- Connect to bridge

- Turn on and off lights

- Change lights color if the selected light supports it. Allows selecting from every possible hexadecimal color value. Also has a eye dropper to pull any color from your screen. You can save theses custom colors for future use.

- Change lights brightness

- Change lights color temperature.

- View bridge info  (ip username key and pridge port) 

## Branches

### Main

Were the stable ready to use code exits.(if building frm source use this branch)

### Dev

Were the not yet completed features live might not compile. fev is merged with main after a feature is mature enough.

## How to Build from source (on linux)

- Clone repo branch main.

- Install cake, gcc and qt-tools

- Install hueplusplus library at [github](https://github.com/enwi/hueplusplus)

- cd into directory with cmakelists file

- Run cmake

- Run make

You should now have a executable.

## Contribute

If you want to contribute to the project submitting bugs via github issues is always helpful. If you want to aid in development go to the [CONTRIBUTING.md](CONTRIBUTING.md)

## Copyright

Copyright (c) 2021 BOB450. See LICENSE for further details.
