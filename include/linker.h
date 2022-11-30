#ifndef LINKER_H
#define LINKER_H

#include <Arduino.h>
// #include <standard/mavlink.h>
// #include <ardupilotmega/mavlink.h>
#include <common/mavlink.h>
// #include <cubepilot/mavlink.h>
// #include <development/mavlink.h>
// #include <icarous/mavlink.h>
// #include <matrixpilot/mavlink.h>
// #include <minimal/mavlink.h>
// #include <test/mavlink.h>
// #include <uAvionix/mavlink.h>
#include <Streaming.h>

class Linker
{
    public:
        Linker();
        Linker(int baudrate);
        virtual ~Linker();

        int read_message(mavlink_message_t &message);
        int write_message(const mavlink_message_t &message);

        bool is_running() {
            return is_open;
        }

        void stop();
    
    private:
        bool debug = false;
        
        mavlink_status_t lastStatus;
        bool is_open;
        int baudrate = 115200;
};

#endif