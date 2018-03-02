#include "tmc_modes.h"

void tmc_mode_enable_stealthchop() {
  tmc_mode_stealthchop_enabled = true;
}

void tmc_mode_disable_stealthchop() {
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

  tmc2130_init();
  
}

void tmc_mode_set_stealth() {
  planner.max_feedrate_mm_s[X_AXIS] = STEALTH_MAX_XY_SPEED;
  planner.max_feedrate_mm_s[Y_AXIS] = STEALTH_MAX_XY_SPEED;
  planner.max_acceleration_mm_per_s2[X_AXIS] = STEALTH_MAX_XY_ACCELERATION;
  planner.max_acceleration_mm_per_s2[Y_AXIS] = STEALTH_MAX_XY_ACCELERATION;

  tmc_mode_enable_stealthchop();
  
  tmc_mode_hybrid = false;
  tmc_modeset_power = false;
  tmc_mode_stealth = true;

  tmc2130_init();
}

void tmc_mode_set_hybrid() {
  tmc_mode_enable_stealthchop();
  tmc_mode_doesnt_limit_speed();
  
  tmc_mode_hybrid = true;
  tmc_modeset_power = false;
  tmc_mode_stealth = false;

  tmc2130_init();
  
}

#if ENABLED(REHOME_XY_ON_ENDSTOP_HIT)
  void tmc_isr() {
    if ( !tmc_modeset_power || tmc_crash_detected || endstops.enabled ) return;

    bool x_pin_triggered = (READ(X_MIN_PIN) != 0); // diag1 connected to x/y_min pins
    bool y_pin_triggered = (READ(Y_MIN_PIN) != 0); // diag1 connected to x/y_min pins
    if ( x_pin_triggered ) {
      // stallGuard from diag1 triggered
      if ( ++tmc_sg_count[TMC_AXIS_X] > REHOME_X_THRESHOLD ) {
        tmc_crash_detected = true;
      }
    } else {
      tmc_sg_count[TMC_AXIS_X] = 0; // reset counter
    }
    if ( y_pin_triggered ) {
      if ( ++tmc_sg_count[TMC_AXIS_Y] > REHOME_Y_THRESHOLD ) {
        tmc_crash_detected = true;
      }
    } else {
      tmc_sg_count[TMC_AXIS_Y] = 0; // reset counter
    }
    
  }

  void tmc_reset_crash() {
    tmc_sg_count[TMC_AXIS_X] = 0;
    tmc_sg_count[TMC_AXIS_Y] = 0;
    tmc_crash_detected = false;
  }

  void tmc_monitor_crash() {
    if ( !tmc_crash_detected ) return;

    /* try to recover printer from crash */
    SERIAL_EOL();
    SERIAL_ECHOLNPGM( "Crash detected!" );

    //enqueue_and_echo_commands_P(PSTR("G28 X Y"));
    tmc_recover_crash();
    tmc_reset_crash();
  
  }

#endif // REHOME_XY_ON_ENDSTOP_HIT
