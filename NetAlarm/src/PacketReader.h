#ifndef PACKETREADER_H_VEIWPRYR
#define PACKETREADER_H_VEIWPRYR
class NetAlarm;
#ifndef NETALARM_TESTING
#include <Arduino.h>
#else
#include "fixtures.hpp"
#endif /* ifndef  */

#include "PacketTypes.h"

class PacketReader
{
#ifdef NETALARM_TESTING
  friend class NetAlarmTests_PacketReader_readByte_Test;
  friend class NetAlarmTests_PacketReader_readUint32_Test;
  friend class NetAlarmTests_PacketReader_gotValidId_Test;
  friend class NetAlarmTests_PacketReader_processPacket_Test;
#endif
  public:
    static const byte MAX_RX_PACKET_SIZE = 32;
    PacketReader(NetAlarm &alarm);

    byte *receiveBuffer() { return receiveBuffer_; }
    void processPacket(byte size);

  private:
    byte receiveBuffer_[MAX_RX_PACKET_SIZE];
    NetAlarm &alarm_;
    byte size_;
    byte processed_;

    byte readByte_();
    uint32_t readUint32_();
    bool gotValidId_();
};

#endif /* end of include guard: PACKETREADER_H_VEIWPRYR */
