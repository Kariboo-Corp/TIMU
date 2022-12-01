#ifndef HIGH_SPEED_LOGGER_H
#define HIGH_SPEED_LOGGER_H

#include <Arduino.h>
#include <common/mavlink.h>
#include <Streaming.h>
#include <SPI.h>
#include <SD.h>

class HighSpeedLogger
{
    private:
        SDClass *card;
    public:
        HighSpeedLogger(SDClass *__card);
        HighSpeedLogger();
        ~HighSpeedLogger();

        int begin(int __cs);
        File open(const char* __name);
        void write(mavlink_message_t __message);
        void close();
        void end();

        File logger;


        bool is_logging = false;
};

#endif