#ifndef PACKETS_H_ACGYNJXY
#define PACKETS_H_ACGYNJXY
class NetAlarm;
#ifndef NETALARM_TESTING
#include <Arduino.h>
#else
#include "fixtures.hpp"
#endif /* ifndef  */

#include "PacketTypes.h"

class PacketWriter
{
#ifdef NETALARM_TESTING
  friend class NetAlarmTests_PacketWriter_writeHeader_Test;
  friend class NetAlarmTests_PacketWriter_writeByte_Test;
#endif
  public:
    PacketWriter(const NetAlarm &alarm);

    byte *packet() { return packet_; }
    void writePacket(PacketType packetType);
    byte size() const { return size_; }

  private:
    static const byte MAX_TX_PACKET_SIZE = 32;

    byte packet_[MAX_TX_PACKET_SIZE];
    const NetAlarm &alarm_;
    byte size_;
    byte *tip_;

    void writeHeader_();
    void writeByte_(byte byte);

};


#endif /* end of include guard: PACKETS_H_ACGYNJXY */
