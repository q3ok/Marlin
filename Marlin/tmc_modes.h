#ifndef __TMC_MODES_H__
#define __TMC_MODES_H__

#include "MarlinConfig.h"
#include "planner.h"
#include "enum.h"
#include "stepper.h"
#include "endstops.h"
#include <TMC2130Stepper.h>
#include <SPI.h>

#define TMC_AXIS_X 0
#define TMC_AXIS_Y 1
#define TMC_AXIS_E 2

static bool tmc_modeset_power = true; // = false;
static bool tmc_mode_stealth = false; // = false;
static bool tmc_mode_hybrid = false; // = true; // enabled by default
static bool tmc_mode_stealthchop_enabled = false; // = true;

#if ENABLED(REHOME_XY_ON_ENDSTOP_HIT)
    static volatile bool tmc_crash_detected = false;
    static volatile uint8_t tmc_sg_count[3] = { 0, 0, 0 };
#endif

void tmc_mode_set_power();
void tmc_mode_set_stealth();
void tmc_mode_set_hybrid();
void tmc_mode_enable_stealthchop();
void tmc_mode_doesnt_limit_speed();
#if ENABLED(REHOME_XY_ON_ENDSTOP_HIT)
    void tmc_isr();
    void tmc_reset_crash();
    void tmc_monitor_crash();
#endif

#endif // _TMC_MODES_H__
