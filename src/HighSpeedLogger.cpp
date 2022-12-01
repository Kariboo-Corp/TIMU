#include "HighSpeedLogger.h"

HighSpeedLogger::HighSpeedLogger(SDClass *__card)
{
    this->card = __card;
}

HighSpeedLogger::HighSpeedLogger()
{
    ;
}


HighSpeedLogger::~HighSpeedLogger()
{
    ;
}

int HighSpeedLogger::begin(int __cs)
{
    return this->card->begin(__cs);
}

File HighSpeedLogger::open(const char* __name)
{
    this->is_logging = true;
    this->logger = this->card->open(__name, FILE_WRITE);
    return this->logger;
}

void HighSpeedLogger::write(mavlink_message_t __message)
{
    unsigned int i;
    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

    unsigned int messageLength = mavlink_msg_to_send_buffer(buffer, &__message);

    if (messageLength > MAVLINK_MAX_PACKET_LEN)
    {
        this->logger << "ERROR: Message with ID#" << __message.msgid << "is too long ..." << endl;
    } else 
    {
        this->logger << "Msg:" << __message.msgid << ",data:";
        for (i = 0; i < messageLength; i++)
        {
            this->logger << buffer[i];
        }

        this->logger << endl;    
    }
}

void HighSpeedLogger::close()
{
    this->is_logging = false;
    return this->logger.close();
}

void HighSpeedLogger::end()
{
    this->is_logging = false;
    return this->card->end();
}