# OpenCircuit
An open-source arcade racing game for the PyBadge, featuring custom community-made tracks, online leaderboards, ESP32-powered WiFi, and a lightweight engine built for retro handheld hardware. Designed to be moddable, hackable, and built together.
# Hardware
OpenCircuit was created to run on the [Adafruit Pybadge](https://www.adafruit.com/product/4200) (with an [ESP32 feather](https://www.adafruit.com/product/5400) attached via header pins).
# Software
## Pybadge Software
The files in the PB-OC directory are to be flashed onto the Adafruit PyBadge.
## ESP32 Software
The files in the ESP32-OC directory are to be flashed onto the ESP32 V2 feather.
## Track-Builder Software
The track builder software is a python script (which uses the PyGame Library) that can be run to easily build and edit tracks in the OpenCircuit Track Format (OTF file). It offers a much easier track building experience compared to editing OTF files in raw text.
# Licenses
All software in each directory will fall under the LICENSE that is contained within that directory or a parent directory. For example, the Experiments directory is under the MIT license, whereas the PB-OC directory is under the Mozilla Public License Version 2.0. 