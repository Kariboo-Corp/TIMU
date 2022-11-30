#include "autopilot_interface.h"

uint64_t
get_time_usec()
{
	return millis() * 1000;
}

Autopilot_Interface::Autopilot_Interface(Linker *linker)
{
    write_count = 0;

	reading_status = 0;      // whether the read thread is running
	writing_status = 0;      // whether the write thread is running
	control_status = 0;      // whether the autopilot is in offboard control mode

	system_id    = 0; // system id
	autopilot_id = 0; // autopilot component id
	companion_id = 0; // companion computer component id

	current_messages.sysid  = system_id;
	current_messages.compid = autopilot_id;

    this->linker = linker;
}

Autopilot_Interface::~Autopilot_Interface()
{}

void
Autopilot_Interface::
update_setpoint(mavlink_set_position_target_local_ned_t setpoint)
{
	;
}

void Autopilot_Interface::read_messages()
{
    bool success;
    bool received_all = false;
    Time_Stamps this_timestamps;

    while (!received_all)
    {
        mavlink_message_t message;
        success = linker->read_message(message);

        if (success) 
        {
            current_messages.sysid  = message.sysid;
            current_messages.compid = message.compid;

            //SerialUSB << "Message ID#" << message.msgid << endl;
            
            switch (message.msgid)
			{

				case MAVLINK_MSG_ID_HEARTBEAT:
				{
					//SerialUSB << ("MAVLINK_MSG_ID_HEARTBEAT\n");
					mavlink_msg_heartbeat_decode(&message, &(current_messages.heartbeat));
					current_messages.time_stamps.heartbeat = get_time_usec();
					this_timestamps.heartbeat = current_messages.time_stamps.heartbeat;
					break;
				}

				case MAVLINK_MSG_ID_SYS_STATUS:
				{
					//SerialUSB << ("MAVLINK_MSG_ID_SYS_STATUS\n");
					mavlink_msg_sys_status_decode(&message, &(current_messages.sys_status));
					current_messages.time_stamps.sys_status = get_time_usec();
					this_timestamps.sys_status = current_messages.time_stamps.sys_status;
					break;
				}

				case MAVLINK_MSG_ID_BATTERY_STATUS:
				{
					//printf("MAVLINK_MSG_ID_BATTERY_STATUS\n");
					mavlink_msg_battery_status_decode(&message, &(current_messages.battery_status));
					current_messages.time_stamps.battery_status = get_time_usec();
					this_timestamps.battery_status = current_messages.time_stamps.battery_status;
					break;
				}

				case MAVLINK_MSG_ID_RADIO_STATUS:
				{
					//printf("MAVLINK_MSG_ID_RADIO_STATUS\n");
					mavlink_msg_radio_status_decode(&message, &(current_messages.radio_status));
					current_messages.time_stamps.radio_status = get_time_usec();
					this_timestamps.radio_status = current_messages.time_stamps.radio_status;
					break;
				}

				case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
				{
					//printf("MAVLINK_MSG_ID_LOCAL_POSITION_NED\n");
					mavlink_msg_local_position_ned_decode(&message, &(current_messages.local_position_ned));
					current_messages.time_stamps.local_position_ned = get_time_usec();
					this_timestamps.local_position_ned = current_messages.time_stamps.local_position_ned;
					break;
				}

				case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
				{
					//printf("MAVLINK_MSG_ID_GLOBAL_POSITION_INT\n");
					mavlink_msg_global_position_int_decode(&message, &(current_messages.global_position_int));
					current_messages.time_stamps.global_position_int = get_time_usec();
					this_timestamps.global_position_int = current_messages.time_stamps.global_position_int;
					break;
				}

				case MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED:
				{
					//printf("MAVLINK_MSG_ID_POSITION_TARGET_LOCAL_NED\n");
					mavlink_msg_position_target_local_ned_decode(&message, &(current_messages.position_target_local_ned));
					current_messages.time_stamps.position_target_local_ned = get_time_usec();
					this_timestamps.position_target_local_ned = current_messages.time_stamps.position_target_local_ned;
					break;
				}

				case MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT:
				{
					//printf("MAVLINK_MSG_ID_POSITION_TARGET_GLOBAL_INT\n");
					mavlink_msg_position_target_global_int_decode(&message, &(current_messages.position_target_global_int));
					current_messages.time_stamps.position_target_global_int = get_time_usec();
					this_timestamps.position_target_global_int = current_messages.time_stamps.position_target_global_int;
					break;
				}

				case MAVLINK_MSG_ID_HIGHRES_IMU:
				{
					//SerialUSB << ("MAVLINK_MSG_ID_HIGHRES_IMU\n");
					mavlink_msg_highres_imu_decode(&message, &(current_messages.highres_imu));
					current_messages.time_stamps.highres_imu = get_time_usec();
					this_timestamps.highres_imu = current_messages.time_stamps.highres_imu;
					break;
				}

				case MAVLINK_MSG_ID_ATTITUDE:
				{
					//printf("MAVLINK_MSG_ID_ATTITUDE\n");
					mavlink_msg_attitude_decode(&message, &(current_messages.attitude));
					current_messages.time_stamps.attitude = get_time_usec();
					this_timestamps.attitude = current_messages.time_stamps.attitude;
					break;
				}

                case MAVLINK_MSG_ID_ATTITUDE_QUATERNION:
                {
                    mavlink_msg_attitude_quaternion_decode(&message, &(current_messages.attitude_quaternion));
                    current_messages.time_stamps.attitude_quaternion = get_time_usec();
                    this_timestamps.attitude_quaternion = current_messages.time_stamps.attitude_quaternion;
                    break;
                }

                case MAVLINK_MSG_ID_ESTIMATOR_STATUS:
                {
                    mavlink_msg_estimator_status_decode(&message, &(current_messages.estimator_status));
                    current_messages.time_stamps.estimator_status = get_time_usec();
                    this_timestamps.estimator_status = current_messages.time_stamps.estimator_status;
                    break;
                }

                case MAVLINK_MSG_ID_ODOMETRY:
                {
                    mavlink_msg_odometry_decode(&message, &(current_messages.odometry));
                    current_messages.time_stamps.odometry = get_time_usec();
                    this_timestamps.odometry = current_messages.time_stamps.odometry;
                    break;
                }

                case MAVLINK_MSG_ID_VIBRATION:
                {
                    mavlink_msg_vibration_decode(&message, &(current_messages.vibration));
                    current_messages.time_stamps.vibration = get_time_usec();
                    this_timestamps.vibration = current_messages.time_stamps.vibration;
                    break;
                }

                case MAVLINK_MSG_ID_ALTITUDE:
                {
                    mavlink_msg_altitude_decode(&message, &(current_messages.altitude));
                    current_messages.time_stamps.altitude = get_time_usec();
                    this_timestamps.altitude = current_messages.time_stamps.altitude;
                    break;
                }

                case MAVLINK_MSG_ID_GPS_RTK:
                {
                    mavlink_msg_gps_rtk_decode(&message, &(current_messages.gps_rtk));
                    current_messages.time_stamps.gps_rtk = get_time_usec();
                    this_timestamps.gps_rtk = current_messages.time_stamps.gps_rtk;
                    break;
                }

                case MAVLINK_MSG_ID_GPS_GLOBAL_ORIGIN:
                {
                    mavlink_msg_gps_global_origin_decode(&message, &(current_messages.gps_global_origin));
                    current_messages.time_stamps.gps_global_origin = get_time_usec();
                    this_timestamps.gps_global_origin = current_messages.time_stamps.gps_global_origin;
                    break;
                }

                case MAVLINK_MSG_ID_GPS_RAW_INT:
                {
                    mavlink_msg_gps_raw_int_decode(&message, &(current_messages.gps_raw));
                    current_messages.time_stamps.gps_raw = get_time_usec();
                    this_timestamps.gps_raw = current_messages.time_stamps.gps_raw;
                    break;
                }

                case MAVLINK_MSG_ID_GPS_STATUS:
                {
                    mavlink_msg_gps_status_decode(&message, &(current_messages.gps_status));
                    current_messages.time_stamps.gps_status = get_time_usec();
                    this_timestamps.gps_status = current_messages.time_stamps.gps_status;
                    break;
                }

				default:
				{
					// printf("Warning, did not handle message id %i\n",message.msgid);
					break;
				}


			}
        }

        received_all = 
        		//this_timestamps.heartbeat                  &&
				// this_timestamps.battery_status             &&
				// this_timestamps.radio_status               &&
				// this_timestamps.local_position_ned         &&
				// this_timestamps.global_position_int        &&
				// this_timestamps.position_target_local_ned  &&
				// this_timestamps.position_target_global_int &&
				// this_timestamps.highres_imu                &&
				this_timestamps.attitude
                // this_timestamps.attitude_quaternion        &&
                // this_timestamps.estimator_status           &&
                // this_timestamps.odometry                   &&
                // this_timestamps.vibration                  &&
                // this_timestamps.altitude                   &&
                // this_timestamps.gps_rtk                    &&
                // this_timestamps.gps_global_origin          &&
                // this_timestamps.gps_raw                    &&
                // this_timestamps.gps_status                 &&
				//this_timestamps.sys_status
				;
    }

    return;
}

int Autopilot_Interface::write_message(mavlink_message_t message)
{
    int len = linker->write_message(message);
    write_count += 1;
    return len;
}