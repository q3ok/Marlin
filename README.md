# Marlin 3D Printer Firmware for MK2Clone

<img align="top" width=175 src="buildroot/share/pixmaps/logo/marlin-250.png" />

## Marlin for MK2Clone

Based on Marlin 1.1.0-RC8 from 06 Dec 2016
This version of Marlin is made especially for Prusa i3 MK2 Clone, it can cause problems with printers using different kinematics than XYZ.
If you want a marlin RC8 with filament load/unload option - check the RC branch of my repo.

## Changes
  - Predefined configuration for Prusa i3 MK2 Clone by q3ok - https://prusaclone.wordpress.com/
  - Filament load and unload (M701 and M702) support from LCD and GCode
  - Instant XYZE moved from LCD menu
  - Added preheat options for materials like in Original MK2
  - Added confirmation from LCD to stop print
  - LCD Menu reorganization
  
## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.