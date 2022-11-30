#ifndef AUTOPILOT_INTERFACE_H
#define AUTOPILOT_INTERFACE_H

#include <Arduino.h>
#include <common/mavlink.h>
#include <Streaming.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <mutex>

#include "linker.h"

struct Time_Stamps
{
	Time_Stamps()
	{
		reset_timestamps();
	}

	uint64_t heartbeat;
	uint64_t sys_status;
	uint64_t battery_status;
	uint64_t radio_status;
	uint64_t local_position_ned;
	uint64_t global_position_int;
	uint64_t position_target_local_ned;
	uint64_t position_target_global_int;
	uint64_t highres_imu;
	uint64_t attitude;
    uint64_t attitude_quaternion;
    uint64_t estimator_status;
    uint64_t odometry;
    uint64_t vibration;
    uint64_t altitude;
    uint64_t gps_rtk;
    uint64_t gps_global_origin;
    uint64_t gps_raw;
    uint64_t gps_status;

	void
	reset_timestamps()
	{
		heartbeat = 0;
		sys_status = 0;
		battery_status = 0;
		radio_status = 0;
		local_position_ned = 0;
		global_position_int = 0;
		position_target_local_ned = 0;
		position_target_global_int = 0;
		highres_imu = 0;
		attitude = 0;
        attitude_quaternion = 0;
        estimator_status = 0;
        odometry = 0;
        vibration = 0;
        altitude = 0;
        gps_rtk = 0;
        gps_global_origin = 0;
        gps_raw = 0;
        gps_status = 0;
	}

};

struct Mavlink_Messages {

	int sysid;
	int compid;

	// Heartbeat
	mavlink_heartbeat_t heartbeat;

	// System Status
	mavlink_sys_status_t sys_status;

	// Battery Status
	mavlink_battery_status_t battery_status;

	// Radio Status
	mavlink_radio_status_t radio_status;

	// Local Position
	mavlink_local_position_ned_t local_position_ned;

	// Global Position
	mavlink_global_position_int_t global_position_int;

	// Local Position Target
	mavlink_position_target_local_ned_t position_target_local_ned;

	// Global Position Target
	mavlink_position_target_global_int_t position_target_global_int;

	// HiRes IMU
	mavlink_highres_imu_t highres_imu;

	// Attitude
	mavlink_attitude_t attitude;

    // Attitude Quaternion

    mavlink_attitude_quaternion_t attitude_quaternion;

    // Estimator Status

    mavlink_estimator_status_t estimator_status;

    // Odometry

    mavlink_odometry_t odometry;

    // Vibration

    mavlink_vibration_t vibration;

	// Altitude

    mavlink_altitude_t altitude;

    // GPS

    mavlink_gps_rtk_t gps_rtk;

    mavlink_gps_global_origin_t gps_global_origin;

    mavlink_gps_raw_int_t gps_raw;

    mavlink_gps_status_t gps_status;

	// Time Stamps
	Time_Stamps time_stamps;

	void
	reset_timestamps()
	{
		time_stamps.reset_timestamps();
	}

};

class Autopilot_Interface
{
    public:
        Autopilot_Interface(Linker *linker);
        ~Autopilot_Interface();

        char reading_status;
        char writing_status;
        char control_status;

        uint64_t write_count;

        int system_id;
        int autopilot_id;
        int companion_id;

        Mavlink_Messages current_messages;
        mavlink_set_position_target_local_ned_t initial_position;

        void update_setpoint(mavlink_set_position_target_local_ned_t setpoint);
        void read_messages();
        int write_message(mavlink_message_t message);
    private:
        Linker *linker;
};


#endif