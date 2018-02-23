#ifndef __TMC_MODES_H__
#define __TMC_MODES_H__

#include <SPI.h>
#include <TMC2130Stepper.h>
#include "MarlinConfig.h"
#include "planner.h"
#include "enum.h"
#include "stepper.h"

static bool tmc_modeset_power = false; // = false;
static bool tmc_mode_stealth = false; // = false;
static bool tmc_mode_hybrid = true; // = true; // enabled by default
static bool tmc_mode_stealthchop_enabled = true; // = true;

void tmc_mode_set_power();
void tmc_mode_set_stealth();
void tmc_mode_set_hybrid();
void tmc_mode_enable_stealthchop();
void tmc_mode_doesnt_limit_speed();

#endif // _TMC_MODES_H__
