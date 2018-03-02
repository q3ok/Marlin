# Marlin 3D Printer Firmware for MK2Clone r2

<img align="top" width=175 src="buildroot/share/pixmaps/logo/marlin-250.png" />

## Marlin for MK2Clone r2

BETA 
This version of Marlin is made for MK2Clone r2 especially for Prusa i3 MK2 Clone.

## Changes worth mentioning
 * Configuration premade for MK2Clone r2
 * X/Y crash detection (missed step) with stallGuard2 from TMC2130 (EARLY alfa version)
 * spreadCycle/stealthChop (and hybrid) mode live changes - M950, M951, M952 (beta) + additional option in LCD for that
 * Extruder stall detection with TMC2130 (EARLY alfa version)
 * Calibration menu
   * Calibration of Z axis by moving to top
   * Automated UBL - G29 P1, P2 with manual measurement (if needed) and save mesh
 * Filament change without parking when not printing (not working properly)
 * Instant moves from LCD move menu (when using high manual move speeds this causes missing steps)
 * Automatically enter move by 1mm instead of choosing 10/1/0.1mm
 * Quick access to Z move by doubleclick while on status
 * Quick access to Z offset adjustment while printing - new position on top of main menu
  
## License

Marlin is published under the [GPL license](/LICENSE) because we believe in open development. The GPL comes with both rights and obligations. Whether you use Marlin firmware as the driver for your open or closed-source product, you must keep Marlin open, and you must provide your compatible Marlin source code to end users upon request. The most straightforward way to comply with the Marlin license is to make a fork of Marlin on Github, perform your modifications, and direct users to your modified fork.