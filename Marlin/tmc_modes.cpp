#include "tmc_modes.h"

void tmc_mode_enable_stealthchop() {
  stepperX.stealth_freq(1); // f_pwm = 2/683 f_clk
  stepperX.stealth_autoscale(1);
  stepperX.stealth_gradient(5);
  stepperX.stealth_amplitude(255);
  stepperX.stealthChop(1);
  stepperY.stealth_freq(1); // f_pwm = 2/683 f_clk
  stepperY.stealth_autoscale(1);
  stepperY.stealth_gradient(5);
  stepperY.stealth_amplitude(255);
  stepperY.stealthChop(1);
  tmc_mode_stealthchop_enabled = true;
}

void tmc_mode_disable_stealthchop() {
   stepperX.stealthChop(0);
   stepperY.stealthChop(0);
   tmc_mode_stealthchop_enabled = false;
}

void tmc_mode_doesnt_limit_speed() {
  static const float tmp2[] PROGMEM = DEFAULT_MAX_FEEDRATE;
  static const uint32_t tmp3[] PROGMEM = DEFAULT_MAX_ACCELERATION;
  LOOP_XYZE_N(i) {
    planner.max_feedrate_mm_s[i] = pgm_read_float(&tmp2[i < COUNT(tmp2) ? i : COUNT(tmp2) - 1]);
    planner.max_acceleration_mm_per_s2[i] = pgm_read_dword_near(&tmp3[i < COUNT(tmp3) ? i : COUNT(tmp3) - 1]);
  }
}

void tmc_mode_set_power() {
  tmc_mode_disable_stealthchop();
  tmc_mode_doesnt_limit_speed();

  tmc_mode_hybrid = false;
  tmc_modeset_power = true;
  tmc_mode_stealth = false;
  
}

void tmc_mode_set_stealth() {
  tmc_mode_enable_stealthchop();
  
  planner.max_feedrate_mm_s[X_AXIS] = STEALTH_MAX_XY_SPEED;
  planner.max_feedrate_mm_s[Y_AXIS] = STEALTH_MAX_XY_SPEED;
  planner.max_acceleration_mm_per_s2[X_AXIS] = STEALTH_MAX_XY_ACCELERATION;
  planner.max_acceleration_mm_per_s2[Y_AXIS] = STEALTH_MAX_XY_ACCELERATION;
  
  tmc_mode_hybrid = false;
  tmc_modeset_power = false;
  tmc_mode_stealth = true;
}

void tmc_mode_set_hybrid() {
  /* enable stealthchop and doesnt limit max speed */
  tmc_mode_enable_stealthchop();
  
  stepperX.stealth_max_speed(12650000UL*X_MICROSTEPS/(256*X_HYBRID_THRESHOLD*planner.axis_steps_per_mm[X_AXIS]));
  stepperY.stealth_max_speed(12650000UL*Y_MICROSTEPS/(256*Y_HYBRID_THRESHOLD*planner.axis_steps_per_mm[Y_AXIS]));
  
  tmc_mode_doesnt_limit_speed();
  
  tmc_mode_hybrid = true;
  tmc_modeset_power = false;
  tmc_mode_stealth = false;
  
}

