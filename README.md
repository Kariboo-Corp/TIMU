# TIMU - Tele Inertial Measurement Unit [IN DEV]

## TODO
 - [firmware] Test SDCARD logging system;
 - [hardware] Put a button to start/stop log recording;

## Firmware
This system is capable of collecting telemetry data from a Pixhawk, save them on board with a removable SD CARD and to transmit them to the ground station. The ground station is capable of display this values in real time.

### Hardware

This code is ment to be used with an Arduino MKR ZERO (ATSAMD21) with a cube orange pixhawk connected to hardware serial 1 and an SDCARD plugged in the Arduino's slot. 

You could configure with messages or group of messages you want to send within the MAVLink menu of QGC:
* [MAV_1_CONFIG](https://docs.px4.io/v1.9.0/en/advanced_config/parameter_reference.html#MAV_1_CONFIG) = `TELEM 2`
* [MAV_1_MODE](https://docs.px4.io/v1.9.0/en/advanced_config/parameter_reference.html#MAV_1_MODE) = `Normal`
* [MAV_1_RATE](https://docs.px4.io/v1.9.0/en/advanced_config/parameter_reference.html#MAV_1_RATE)= `92160` baud (Should be SER_TEL2_BAUD / 10) ie. `SER_TEL2_BAUD = 921600` bps
* [MAV_1_FORWARD](https://docs.px4.io/v1.9.0/en/advanced_config/parameter_reference.html#MAV_1_FORWARD) = `True`

MAV_1_MODE could be change to change group of messages you want to send through TELEM2, in our case.

**Comment:** The MAVLink Mode defines the set of streamed messages (for example the vehicle's attitude) and their sending rates.

**Values:**

* **0:** Normal: Standard set of messages for a GCS.
* **1:** Custom: Nothing (in the default PX4 implementation). These might be used for testing when developing a new mode.
* **2:** Onboard: Standard set of messages for a companion computer.
* **3:** OSD: Standard set of messages for an OSD system.
* **4:** Magic: Nothing (in the default PX4 implementation). These might be used for testing when developing a new mode.
* **5:** Config: Standard set of messages and rate configuration for a fast link (e.g. USB).
* **7:** Minimal: Minimal set of messages for use with a GCS connected on a high latency link.
* **8:** External Vision

**Reboot required:** True

## Contribute

Use Platform IO and clone this repository in your project directory :
```bash
git clone --recursive git@github.com:Kariboo-Corp/TIMU.git
```

Connect an MKR Zero to your PC and upload the code.

## MavLink DATA gathered

 - Altitude (10 Hz)
   - `altitude_monotic`
   - `altitude_amsl`
   - `altitude_local`
   - `altitude_relative`
   - `altitude_terrain`
   - `bottom_clearance`
 - Attitude (50 Hz)
   - `roll`
   - `pitch`
   - `yaw`
   - `rollspeed`
   - `pitchspeed`
   - `yawspeed`
 - Attitude Quaternion (50 Hz)
   - `q1`
   - `q2`
   - `q3`
   - `q4`
   - `rollspeed`
   - `pitchspeed`
   - `yawspeed`
   - `repr_offset_q`
 - Battery Status (<1 Hz)
   - `id`
   - `battery_function`
   - `type`
   - `temperature`
   - `voltages`
   - `current_battery`
   - `current_consumed`
   - `energy_consumed`
   - `battery_remaining`
   - `time_remaining`
   - `charge_state`
   - `volatges_ext`
   - `mode`
   - `fault_bitmask`
 - Estimator Status (5 Hz)
   - `vel_ratio`
   - `pos_horiz_ratio`
   - `pos_vert_ratio`
   - `mag_ratio`
   - `hagl_ratio`
   - `tas_ratio`
   - `pos_horiz_accuracy`
   - `pos_vert_accuracy`
 - Highres IMU (50 Hz)
   - `xacc`
   - `yacc`
   - `zacc`
   - `xgyro`
   - `ygyro`
   - `zgyro`
   - `xmag`
   - `ymag`
   - `zmag`
   - `abs_pressure`
   - `diff_pressure`
   - `pressure_alt`
   - `temperature`
 - Odometry (30 Hz)
   - `x`
   - `y`
   - `z`
   - `q`
   - `vx`
   - `vy`
   - `vz`
   - `rollspeed`
   - `pitchspeed`
   - `yawspeed`
   - `pose_covariance`
   - `velocity_covariance`
 - Vibration (<3 Hz)
   - `vibration_x`
   - `vibration_y`
   - `vibration_z`
   - `clipping_0`
   - `clipping_1`
   - `clipping_2`