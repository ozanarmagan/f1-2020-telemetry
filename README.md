![Screenshot](/screenshot.png)

# Simple telemetry library and sim-dash created for F1 2020
### C/C++ library and program to extract and parse telemetry shared from F1 2020 game by UDP 
This is a program to parse and visualize your real-time telemetry data that shared from F1 2020 game with UDP packages.
Program collects that UDP packages,parse them and render them in a OpenGL window to create you a sim dash.

## Usable data that collected by the library

- Car Setup Data
- Car Status Data
- Car Telemetry
- Event Info
- Final Classification
- Lap Data
- Lobby Info
- Motion
- Session Info

## Dependencies

- GLAD
- GLM
- FreeType 2

## Important note

This program only runs in Windows.
However, only with a few library and function changes for collecting UDP packets,it can be used in Linux-based platforms too (check sys/socket.h library).
