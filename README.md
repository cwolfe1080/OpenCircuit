# OpenCircuit
An open-source arcade racing game for the PyBadge, featuring custom community-made tracks, online leaderboards, ESP32-powered WiFi, and a lightweight engine built for retro handheld hardware. Designed to be moddable, hackable, and built together.
# Hardware
OpenCircuit was created to run on the [Adafruit Pybadge](https://www.adafruit.com/product/4200) (with an [ESP32 feather](https://www.adafruit.com/product/5400) attached via header pins). To run OpenCircuit, both devices must be flashed with their respective software and the ESP32 must be connected to the Adafruit PyBadge via the feather sockets on the back of the PyBadge.
# Software
## Pybadge Software
The files in the PB-OC directory are to be flashed onto the Adafruit PyBadge. The PyBadge software (files) mostly contain code for running the actual OpenCircuit game, which includes rendering, loading, menus, and all other code necessary to handle the work for the PyBadge. While the PyBadge does do most of the work for the actual loading and playing of the game, it still requires the ESP32 to help with track loading, downloading, and other functions to make the game playable. NOTE: You cannot play OpenCircuit with only a PyBadge. The ESP32 must be inserted via the Feather Sockets on the PyBadge, and both devices must be flashed with their respective software.
## ESP32 Software
The files in the ESP32-OC directory are to be flashed onto the ESP32 V2 feather. The ESP32's job is mostly to download and store tracks, though there are considerations for adding OTA updates in the future. The main reason that I included the ESP32 feather into the build for OpenCircuit, is to give WiFI capabilities to the whole system. The ESP32 feather V2 also has a good amount of storage for storing custom tracks and whatnot.
## Track-Builder Software
The track builder software is a python script (which uses the PyGame Library) that can be run to easily build and edit tracks in the OpenCircuit Track Format (OTF file). It offers a much easier track building experience compared to editing OTF files in raw text.
# Licenses
All software in each directory will fall under the LICENSE that is contained within that directory or a parent directory. For example, the Experiments directory is under the MIT license, whereas the PB-OC directory is under the Mozilla Public License Version 2.0. 
