#include "linker.h"

Linker::Linker(HighSpeedLogger __logger)
{
    this->baudrate = baudrate;
    this->is_open = true;

    this->logger = __logger;
    this->logger.open(millis() + ".klog");
}

Linker::~Linker() 
{
    ;
}

int Linker::read_message(mavlink_message_t &message) 
{
    mavlink_status_t status;
    uint8_t cp;
    uint8_t msgReceived = false;

    if (Serial1.available() > 0) 
    {
        cp = Serial1.read();

        if (1 > 0) // Specific arduino tric to force message reading.
        {
            msgReceived = mavlink_parse_char(MAVLINK_COMM_0, cp, &message, &status);

            if ((lastStatus.packet_rx_drop_count != status.packet_rx_drop_count) && debug)
            {
                SerialUSB << "ERROR: DROPPED " << status.packet_rx_drop_count << "PACKETS" << endl;
            }

            lastStatus = status;
        } else 
        {
            SerialUSB << "ERROR: Coulnd't read from port" << endl;
        }

        if (msgReceived && logger.is_logging)
        {
            logger.write(message);
        }

        if(msgReceived && debug)
        {
            // Report info
            SerialUSB << "Received message from serial with ID #" << message.msgid << " (sys:" << message.sysid << "|comp:" << message.compid << "):" << endl;
            SerialUSB << "Received serial data:" << endl;
            unsigned int i;
            uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

            // check message is write length
            unsigned int messageLength = mavlink_msg_to_send_buffer(buffer, &message);

            // message length error
            if (messageLength > MAVLINK_MAX_PACKET_LEN)
            {
                SerialUSB << "\nFATAL ERROR: MESSAGE LENGTH IS LARGER THAN BUFFER SIZE\n";
            }

            // print out the buffer
            else
            {
                for (i=0; i<messageLength; i++)
                {
                    unsigned char v=buffer[i];
                    SerialUSB << v;
                }
                SerialUSB << endl;
            }
        }

        // Done!
        return msgReceived;
    }
    
    return -1;
}

int Linker::write_message(const mavlink_message_t &message)
{
    char buf[300];

    unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);
    Serial1.write(buf);

    return len;
}

void Linker::stop()
{
    Serial1.end();
    this->logger.close();
    this->logger.end();
}